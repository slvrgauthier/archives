package edu.turtlekit2.warbot.warBotte;

import java.util.List;

import edu.turtlekit2.warbot.WarBrain;
import edu.turtlekit2.warbot.message.WarMessage;
import edu.turtlekit2.warbot.percepts.Percept;
import edu.turtlekit2.warbot.waritems.WarFood;

/**
 *  
 * @author GAUTHIER silvère
 *
 */
public class BrainExplorer extends WarBrain{
	private States state = States.FIRST_LAP;
	boolean baseFound = false;
	
	public BrainExplorer(){
		
	}
	
	public String action() {
		List<Percept> listeP = getPercepts();
		List<WarMessage> listeM = getMessage();

		//State setting
		decide(listeM); /** voir ligne 55 */

		//Default messages treatment
		treatMessages(listeM); /** voir ligne 65 */

		//Action
		switch(state) {
		
		case FIRST_LAP :
			return init(listeM); /** voir ligne 100 */
			
		case RETURN_BASE :
			return returnBase(listeP, listeM); /** voir ligne 107 */
			
		case SEARCH_FOOD :
			return searchFood(listeP); /** voir ligne 153 */
			
		case SPY :
			return spy(listeP); /** voir ligne 191 */
			
		default : 
			return "action";	
		}
	}

	/* all states */
	public void decide(List<WarMessage> listeM) {
		if(state == States.RETURN_BASE && emptyBag()) { //retourner en recherche 
			state = States.SEARCH_FOOD;     //si on a donné tout le contenu de son sac à la base
		}
		else if(state == States.SEARCH_FOOD && fullBag()) { //retourner à la base
			state = States.RETURN_BASE;            //si on a rempli son sac de nourriture
		}
	}

	/* all states */
	private void treatMessages(List<WarMessage> listeM) {
		for(WarMessage m : listeM) {
			if(m.getSenderType().equals("WarBase")) {
				if(m.getMessage().equals("startAngle")) { //séparer les explorers au départ
					int ref = (m.getAngle()+180)%360; //l'opposé de la base allié
					if(ref >= 0 && ref < 90) { //1er quart
						setHeading(Integer.parseInt(m.getContent()[0]));
					}
					else if(ref >= 90 && ref < 180) { //2eme quart
						setHeading(90+Integer.parseInt(m.getContent()[0]));
					}
					else if(ref >= 180 && ref < 270) { //3eme quart
						setHeading(180+Integer.parseInt(m.getContent()[0]));
					}
					else if(ref >= 270 && ref < 360) { //4eme quart
						setHeading(270+Integer.parseInt(m.getContent()[0]));
					}
				}
				else if(!emptyBag() && m.getMessage().equals("lowHealth")) { //appel à l'aide
					setHeading(m.getAngle());
					state = States.RETURN_BASE;
				}
				else if(m.getMessage().equals("spy")) { //ordre d'espionner
					state = States.SPY;
					//reply(m,"spy_ok",null); //signaler l'exécution de l'ordre -> deprecated
				}/* -> deprecated
				else if(state != States.SPY && m.getMessage().equals("spy_ok")) { //un espion a été élu
					state = States.SEARCH_FOOD;
				}*/
			}
		}
		
	}

	/* FIRST_LAP state */
	private String init(List<WarMessage> listeM) {
		//broadcastMessage("WarBase","ready to spy",null); //informer la base -> deprecated
		broadcastMessage("WarBase","start", null); //séparer les explorers au départ
		state = States.SEARCH_FOOD;
		return "action";
	}

	/* RETURN_BASE state */
	private String returnBase(List<Percept> listeP, List<WarMessage> listeM) {
		boolean closeBase = false; //base proche (dans le champs de vision)
		Percept lowestHealth = null; //base ayant le moins d'énergie
		for(Percept p : listeP) {
			if(p.getType().equals("WarBase")) {
				closeBase = true;
				if(lowestHealth == null) {
					lowestHealth = p;
				}
				else if(lowestHealth.getEnergy() > p.getEnergy()) {
					lowestHealth = p;
				}
				if(lowestHealth.getDistance() <= WarFood.MAX_DISTANCE_TAKE) {
					setAgentToGive(lowestHealth.getId()); //nourrir la base ayant 
					return "give";                        // le moins d'énergie
				}
				else {
					setHeading(lowestHealth.getAngle()); //se diriger vers elle
				}
			}
		}
		if(!closeBase) {
			int baseAngle = -1; //direction vers la base choisie
			int baseDistance = -1; //distance à la base choisie
			for(WarMessage m : listeM) {
				if(m.getSenderType().equals("WarBase")) { 
					if(m.getMessage().equals("posBase")) { //message de position
						if(baseAngle == -1) {
							baseAngle = m.getAngle();
							baseDistance = m.getDistance();
						}
						else if(baseDistance > m.getDistance()) { //base la plus proche
							baseAngle = m.getAngle();             //   (hors champs)
							baseDistance = m.getDistance();
						}
					}
				}
			}
			if(baseAngle != -1) { //si aucune base choisie, s'abstenir
				setHeading(baseAngle);
			}
		}
		if(isBlocked()) {
			setHeading(getHeading() + 90);
			if(isBlocked()) {
				setHeading(getHeading() -180);
			}
		}
		return "move";
	}

	/* SEARCH_FOOD state */
	private String searchFood(List<Percept> listeP) {
		Percept bestFood = null; //nourriture (ou base enemie le cas échéant)
		boolean baseInRadius = false;
		for(Percept p : listeP) {
			if(p.getType().equals("WarFood")) {
				if(p.getDistance() <= WarFood.MAX_DISTANCE_TAKE) {
					return "take"; //récolter si assez proche
				}
				else if(bestFood == null || bestFood.getDistance() > p.getDistance()) {
					bestFood = p; //nourriture la plus proche
				}
			}
			else if(p.getType().equals("WarBase")) {
				if(!p.getTeam().equals(getTeam())) {
					baseInRadius = true;
					if(!baseFound) {
						baseFound = true;
						broadcastMessage("WarRocketLauncher", "base", null); //informer position base enemie
					}
				}
				else if(!emptyBag()){
					state = States.RETURN_BASE;
				}
			}
		}
		if(!baseInRadius) {
			baseFound = false;
		}
		if(bestFood != null) {
			setHeading(bestFood.getAngle());
		}
		if(isBlocked()){                           // ce double test permet de simuler
			int sens = 1;                          // une sorte de "rebond" contre
			setHeading(this.getHeading()+90);      // les murs (le second test permet
			if(isBlocked()) {                      // de savoir dans quel sens tourner)
				sens = -1;                          
				setHeading(this.getHeading()-180);  
			}
			setHeading(this.getHeading()-sens*30);
		}
		return "move";
	}

	/* SPY state */
	public String spy(List<Percept> listeP){
		Percept bestPercept = null; //base enemie
		for(Percept p : listeP){
			if(p.getType().equals("WarBase") && !p.getTeam().equals(getTeam())){
				bestPercept = p; //base enemie dans le champs de vision
			}
		}
		
		if(bestPercept != null){
			broadcastMessage("WarRocketLauncher", "base", null); //informer les rocketsLaunchers
			if(bestPercept.getDistance() > 1){
				setHeading(bestPercept.getAngle()); //aller jusqu'à la base pour 
				return "move";                      // avoir la position exacte
			}
			else {
				return "idle"; //si assez proche, ne rien faire
			}
		}
		if(isBlocked()){                           // ce double test permet de simuler
			setHeading(this.getHeading()+10);       // une sorte de "rebond" contre
			if(isBlocked()) {                      // les murs (le second test permet
				setHeading(this.getHeading()-20);  // de savoir dans quel sens tourner)
			}
		}
		return "move";
	}
}
