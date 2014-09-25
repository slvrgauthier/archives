package edu.turtlekit2.warbot.warBotte_v2;

import java.util.List;

import edu.turtlekit2.warbot.WarBrain;
import edu.turtlekit2.warbot.message.WarMessage;
import edu.turtlekit2.warbot.percepts.Percept;
import edu.turtlekit2.warbot.waritems.WarFood;

/** War Botte v2 : WarExplorer
 *  
 * @author GAUTHIER silvère
 *
 */
public class BrainExplorer extends WarBrain{
	private States state = States.FIRST_LAP;
	
	// Base ennemie trouvée ou non (permet de n'envoyer qu'un message)
	boolean baseFound = false;
	
	public BrainExplorer(){}
	
	public String action() {
		List<Percept> listeP = getPercepts();
		List<WarMessage> listeM = getMessage();

		decide(listeM); /** voir ligne 55 */
		treatMessages(listeM); /** voir ligne 69 */

		/* Pseudo-FSM */
		switch(state) {
		
		case FIRST_LAP :
			return init(listeM); /** voir ligne 101 */
			
		case RETURN_BASE :
			return returnBase(listeP, listeM); /** voir ligne 113 */
			
		case SEARCH_FOOD :
			return searchFood(listeP); /** voir ligne 168 */
			
		case SPY :
			return spy(listeP); /** voir ligne 232 */
			
		default : 
			return "action";	
		}
	}

	/* all states 
	 * 
	 * Cette méthode permet de décider automatiquement de l'état en cours
	 * selon l'état du sac.
	 */
	public void decide(List<WarMessage> listeM) {
		if(state == States.RETURN_BASE && emptyBag()) { //retourner en recherche 
			state = States.SEARCH_FOOD;     //si on a donné tout le contenu de son sac à la base
		}
		else if(state == States.SEARCH_FOOD && fullBag()) { //retourner à la base
			state = States.RETURN_BASE;            //si on a rempli son sac de nourriture
		}
	}

	/* all states 
	 * 
	 * Cette méthode traite tous les messages et agit en conséquence.
	 * (excepté messages spécifiques)
	 */
	private void treatMessages(List<WarMessage> listeM) {
		for(WarMessage m : listeM) {
			if(m.getSenderType().equals("WarBase")) {
				// Séparation des WarExplorers au départ, commandé par la base
				if(m.getMessage().equals("startAngle")) {
					// Direction opposée à la base alliée
					int ref = (m.getAngle()+180)%360;
					// Dans quel quartier de la map devons nous aller (facultatif)
					// -> 0 = Nord-Est, 1 = Nord-Ouest, 2 = Sud-Ouest, 3 = Sud-Est
					int quartier = (int)(ref/90);
					// Se diriger selon le quartier et l'angle fourni par la base
					setHeading(quartier*90+Integer.parseInt(m.getContent()[0]));
					// On peut aussi utiliser setHeading(ref+Integer.parseInt(m.getContent()[0]));
				}
				// Ramener la nourriture à la base si celle-ci demande de l'aide
				else if(!emptyBag() && m.getMessage().equals("lowHealth")) {
					setHeading(m.getAngle());
					state = States.RETURN_BASE;
				}
				// Passer en espionnage
				else if(m.getMessage().equals("spy")) {
					state = States.SPY;
				}
			}
		}
		
	}

	/* FIRST_LAP state 
	 * 
	 * Cette méthode permet de décliner son identité à la base puis de partir
	 * en recherche de nourriture.
	 */
	private String init(List<WarMessage> listeM) {
		broadcastMessage("WarBase","start", null);
		state = States.SEARCH_FOOD;
		return "action";
	}

	/* RETURN_BASE state 
	 * 
	 * Cette méthode permet de retourner donner tout le contenu du sac à partir
	 * du moment où celui-ci est plein, ou dans le cas où il n'est pas vide et
	 * que la base appelle à l'aide.
	 */
	private String returnBase(List<Percept> listeP, List<WarMessage> listeM) {
		//Base proche (dans le champs de vision)
		boolean closeBase = false;
		//Base ayant le moins d'énergie
		Percept lowestHealth = null;
		
		for(Percept p : listeP) {
			if(p.getType().equals("WarBase")) {
				closeBase = true;
				if(lowestHealth == null
						|| (lowestHealth.getEnergy() > p.getEnergy())) {
					lowestHealth = p;
				}
				// Nourrir la base ayant le moins d'énergie
				if(lowestHealth.getDistance() <= WarFood.MAX_DISTANCE_TAKE) {
					setAgentToGive(lowestHealth.getId());
					return "give";
				}
				// Se diriger vers elle le cas échant
				else {
					setHeading(lowestHealth.getAngle());
				}
			}
		}
		// Choix de la base la plus proche (hors champ de vision)
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
						else if(baseDistance > m.getDistance()) {
							baseAngle = m.getAngle();
							baseDistance = m.getDistance();
						}
					}
				}
			}
			// Si aucune base choisie, s'abstenir (théoriquement impossible)
			if(baseAngle != -1) {
				setHeading(baseAngle);
			}
		}
		return "move";
	}

	/* SEARCH_FOOD state 
	 * 
	 * Cette méthode permet l'exploration de la carte en recherche de nourriture,
	 * dans le but de remplir entièrement son sac avant de rentrer à la base.
	 */
	private String searchFood(List<Percept> listeP) {
		// Nourriture perçue (ou base ennemie le cas échéant)
		Percept bestFood = null;
		// Base ennemie dans le champs de vision
		boolean baseInRadius = false;
		
		for(Percept p : listeP) {
			// Rammasser si assez proche, sinon se diriger vers la plus proche
			if(p.getType().equals("WarFood")) {
				if(p.getDistance() <= WarFood.MAX_DISTANCE_TAKE) {
					return "take";
				}
				else if(bestFood == null || bestFood.getDistance() > p.getDistance()) {
					bestFood = p;
				}
			}
			// Si une base ennemie a été perçue, 
			// informer une seule fois les WarRocketLaunchers alliés
			else if(p.getType().equals("WarBase")) {
				if(!p.getTeam().equals(getTeam())) {
					baseInRadius = true;
					if(!baseFound) {
						baseFound = true;
						broadcastMessage("WarRocketLauncher", "base", null);
					}
				}
				// Repasser par la base si elle est alliée
				else if(!emptyBag()){
					state = States.RETURN_BASE;
				}
			}
		}
		// Ce bloc permet de n'informer qu'une fois les WarRocketLaunchers
		// à chaque fois qu'on trouve "pour la première fois" une base
		// ennemie (entrée-sortie du champs de vision).
		if(!baseInRadius) {
			baseFound = false;
		}
		// Se diriger vers la nourriture la plus proche
		if(bestFood != null) {
			setHeading(bestFood.getAngle());
		}
		
		// Ce double test permet de simuler une sorte de "rebond" contre
		// les murs (le second test permet de savoir dans quel sens tourner)
		if(isBlocked()){
			int sens = 1;
			setHeading(this.getHeading()+90);
			if(isBlocked()) {
				sens = -1;                          
				setHeading(this.getHeading()-180);  
			}
			setHeading(this.getHeading()-sens*30);
		}
		return "move";
	}

	/* SPY state 
	 * 
	 * Cette méthode permet d'espionner l'ennemi en cherchant sa base, se mettant
	 * en son centre, puis en prévenant le reste des troupes. Le WarExplorer
	 * espion a pour mission de chercher la base la plus éloignée afin d'avoir
	 * le maximum de chance de toutes les rencontrer.
	 */
	public String spy(List<Percept> listeP){
		// Base ennemie perçue
		Percept bestPercept = null;
		// Dans la plupart des cas, le dernier percept est le plus éloigné
		for(Percept p : listeP){
			if(p.getType().equals("WarBase") && !p.getTeam().equals(getTeam())){
				bestPercept = p;
			}
		}
		// Une base ennemie a été trouvée
		if(bestPercept != null){
			// Informer la WarBase et les WarRocketLaunchers
			// de la position de l'ennemi
			broadcastMessage("WarBase", "positionEnnemi", null);
			broadcastMessage("WarRocketLauncher", "base", null);
			
			// Aller jusqu'à la base pour avoir la position exacte
			if(bestPercept.getDistance() > 1){
				setHeading(bestPercept.getAngle()); 
				return "move";
			}
			// Si assez proche, ne rien faire
			else {
				return "idle";
			}
		}
		
		// Ce double test permet de simuler une sorte de "rebond" contre
		// les murs (le second test permet de savoir dans quel sens tourner)
		// l'espion longe presque les murs pour avoir plus de chance de
		// trouver une base ennemie.
		if(isBlocked()){
			setHeading(this.getHeading()+10);
			if(isBlocked()) {
				setHeading(this.getHeading()-20);
			}
		}
		return "move";
	}
}
