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
public class BrainRocketLauncher extends WarBrain{
	private States state = States.FIRST_LAP;
	//private int zigzag = 0; -> deprecated
	private boolean die = false; //si le launcher est prêt à mourir
	private int leader = -1; //si le launcher est le premier en mode deploiement

	private int base = -1;        //base défendue
	private int baseDistance = 0; //plus un percept car nécessite une
	private int baseAngle = 0;    //mise à jour
	private int dir = 1; //direction pour le tank en défense

	public BrainRocketLauncher(){

	}

	public String action() {
		List<Percept> listeP = getPercepts();
		List<WarMessage> listeM = getMessage();

		//Reloading
		if(!isReloaded()){
			if(!isReloading()){
				return "reload";
			}
		}

		//State setting
		decide(listeM); /** voir ligne 70 */

		//Default messages treatment
		treatMessages(listeM); /** voir ligne 75 */

		//Action
		switch(state) {

		case FIRST_LAP :
			return init(); /** voir ligne 123 */

		case ATTACK :
			return attack(listeP, listeM); /** voir ligne 130 */

		case DEFEND :
			return defend(listeP); /** voir ligne 178 */
			
		case GO_DEPLOY :
			return go(listeP); /** voir ligne 247 */
			
		case DEPLOYMENT :
			return deploy(listeP); /** voir ligne 267 */

		default :
			return "action";
		}
	}

	/* all states */
	private void decide(List<WarMessage> listeM) {
		
	}

	/* all states */
	private void treatMessages(List<WarMessage> listeM) {
		for(WarMessage m : listeM) {
			if(state == States.DEFEND) {
				if(m.getSenderType().equals("WarBase")) {
					if(m.getMessage().equals("attack")) { //passer en mode attaque
						state = States.ATTACK;
					}
					else if(m.getMessage().equals("base")) {
						base = m.getSender();
						baseDistance = m.getDistance();
						baseAngle = m.getAngle();
					}
				}
			}
			else {
				if(m.getSenderType().equals("WarBase")) {
					if(m.getMessage().equals("startAngle")) { //séparer les rocketLaunchers au départ
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
						} //si cette méthode ne convient pas (cf conformation de la map),
						  //on peut se baser directement sur ref... mais pas optimal ici.
					}
					else if(m.getMessage().equals("defend")) { //passer en mode défense
						state = States.DEFEND;
						reply(m,"defense_ok",null); //informer la base
						setHeading(m.getAngle());
					}
				}
				else if(m.getSenderType().equals("WarRocketLauncher")) {
					if(m.getMessage().equals("base")) {
						setHeading(m.getAngle()); //suivre l'indication de position enemie
						state = States.GO_DEPLOY;
						leader = m.getSender();
					}
				}
				else if(m.getSenderType().equals("WarExplorer")) {
					if((state != States.DEPLOYMENT || state != States.GO_DEPLOY) && m.getMessage().equals("base")) {
						setHeading(m.getAngle()); //suivre l'indication de position enemie
					}
				}
			}
		}
	}

	/* FIRST_LAP state */
	private String init() {
		broadcastMessage("WarBase","start", null); //séparer les rockets launchers au départ
		state = States.ATTACK;
		return "move";
	}

	/* ATTACK state */
	private String attack(List<Percept> listeP, List<WarMessage> listeM) {
		Percept bestPercept = null; //cible à choisir
		for(Percept p : listeP){
			if(!p.getTeam().equals(getTeam())) { //ennemi
				if((p.getType().equals("WarBase"))) { // tirer sur les rockets launcher fait perdre trop de temps
/*						|| (p.getType().equals("WarRocketLauncher") && bestPercept == null) 
						|| (p.getType().equals("WarRocketLauncher") && !bestPercept.getType().equals("WarBase"))) {
*/					bestPercept = p; //meilleure cible
				}
			}
		}
		if(bestPercept != null){
			//if(bestPercept.getType().equals("WarBase")) {
				broadcastMessage("WarRocketLauncher", "base", null); //informer les autres rocketLaunchers
				state = States.DEPLOYMENT;
				leader = this.getID();
			//}
			setAngleTurret(bestPercept.getAngle());
			setHeading(bestPercept.getAngle());
			return "fire";
		}
		else {
			if(isBlocked()){                           // ce double test permet de simuler
				int sens = 1;                          // une sorte de "rebond" contre
				setHeading(this.getHeading()+90);      // les murs (le second test permet
				if(isBlocked()) {                      // de savoir dans quel sens tourner)
					sens = -1;                          
					setHeading(this.getHeading()-180);  
				}
				setHeading(this.getHeading()-sens*30);
			}
/*			if(zigzag > 20) {                         // les attaquants se déplacent
				zigzag = 0;                           // en zig-zag pour augmenter
			}                                         // légèrement le champ de perception
			else {                                    // sans pour autant réduire de
				zigzag++;                             // beaucoup leur vitesse de
			}                                         // déplacement (paramétrage)
			if(zigzag < 11) {
				setHeading(this.getHeading()+5);
			}
			else {
				setHeading(this.getHeading()-5);
			}
*/			return "move";
		}
	}

	/* DEFEND state */
	private String defend(List<Percept> listeP) {
		if(!die && getEnergy() < 500) {
			sendMessage(base, "defense_dying", null);
			die = true;
		}
		Percept bestPercept = null;
		for(Percept p : listeP) {
			if(!p.getTeam().equals(getTeam())) {
				if(bestPercept == null //ordre de préférence : Base > RocketLauncher > Exploreur
						|| p.getType().equals("WarBase")
						|| (p.getType().equals("WarRocketLauncher") && !bestPercept.getType().equals("WarBase"))) {
					bestPercept = p; //meilleure cible
				}
			}
			else if(base == -1 && p.getType().equals("WarBase")) {
				this.base = p.getId(); //base rattachée
			}
		}
		if(this.base == -1) {
			return "move";
		}
		if(bestPercept != null){
			if(bestPercept.getType().equals("WarFood")) { //ramasser la nourriture proche
				if(emptyBag()) {
					if(bestPercept.getDistance() <= WarFood.MAX_DISTANCE_TAKE) {
						return "take";
					}
					else {
						setHeading(bestPercept.getAngle());
						return "move";
					}
				}
			}
			else { //attaquer si ce n'est pas de la nourriture
				if(baseDistance < 20 //bloquer les tirs ennemis
						&& bestPercept.getType().equals("WarRocketLauncher")
						&& bestPercept.getDistance() > 2) {
					setHeading(bestPercept.getAngle());
					return "move";
				}
				else {
					setAngleTurret(bestPercept.getAngle());
					return "fire";
				}
			}
		}
		if(!emptyBag()) {
			if(baseDistance <= WarFood.MAX_DISTANCE_TAKE) {
				setAgentToGive(base); //donner sa nourriture à la base
				return "give";
			}
			else {
				setHeading(baseAngle); //retourner à la base
				return "move";
			}
		}
		if(baseDistance > 10) {
			setHeading(baseAngle); //ne pas trop s'éloigner de la base
		}
		else {
			while(isBlocked()) {             //ceci permet de patrouiller
				setHeading(getHeading()+180); //autour de la base sans être
				dir *= -1;
			}                                //gêné par les murs et sans
			setHeading(getHeading()+5*dir);      //s'éloigner trop loin
		}
		return "move";
	}

	/* GO_DEPLOY state */
	private String go(List<Percept> listeP) {
		for(Percept p : listeP) {
			if(p.getId() == leader) {
				if(p.getDistance() < 20) {
					state = States.DEPLOYMENT;
					return "action";
				}
				else {
					setHeading(p.getAngle()); //rejoindre le leader
				}
			}
			else if(!p.getTeam().equals(getTeam()) && p.getType().equals("WarBase")) {
				state = States.DEPLOYMENT;
				return "action";
			}
		}
		return "move";
	}

	/* DEPLOYMENT state */
	private String deploy(List<Percept> listeP) {
		Percept bestPercept = null; //cible à choisir
		Percept ref = null;
		for(Percept p : listeP){
			if(!p.getTeam().equals(getTeam()) && p.getType().equals("WarBase")) {
					bestPercept = p; //meilleure cible
			}
			else if(p.getId() == leader) {
				ref = p;
			}
		}
		if(ref != null && leader != this.getID()) {
			if(ref.getDistance() < 5) {
				setHeading(ref.getHeading()+90*Math.random()%2-45); //se décaler du leader
			}
			else if(ref.getDistance() < 20) {
				setHeading(ref.getHeading()); //se déployer autour de la base
			}
		}
		if(bestPercept != null){
			setHeading(bestPercept.getAngle());
			setAngleTurret(bestPercept.getAngle());
			return "fire";
		}
		else {
			return "move";
		}
	}
}
