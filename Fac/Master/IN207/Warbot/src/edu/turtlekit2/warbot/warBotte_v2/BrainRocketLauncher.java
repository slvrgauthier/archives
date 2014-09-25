package edu.turtlekit2.warbot.warBotte_v2;

import java.util.List;

import edu.turtlekit2.warbot.WarBrain;
import edu.turtlekit2.warbot.message.WarMessage;
import edu.turtlekit2.warbot.percepts.Percept;
import edu.turtlekit2.warbot.waritems.WarFood;

/** War Botte v2 : WarRocketLauncher
 *  
 * @author GAUTHIER silvère
 *
 */
public class BrainRocketLauncher extends WarBrain{
	private States state = States.FIRST_LAP;

	private boolean die = false; // Proche de la mort
	private int leader = -1; // Id du premier WarRocketLauncher en deploiement
	private int dir = 1; // Direction pour la défense et le déploiement

	// Coordonnées de la base défendue
	private int base = -1;
	private int baseDistance = 0;
	private int baseAngle = 0;

	public BrainRocketLauncher(){}

	public String action() {
		List<Percept> listeP = getPercepts();
		List<WarMessage> listeM = getMessage();

		// Rechargement si besoin
		if(!isReloaded()){
			if(!isReloading()){
				return "reload";
			}
		}

		treatMessages(listeM); /** voir ligne 70 */

		/* Pseudo-FSM */
		switch(state) {

		case FIRST_LAP :
			return init(); /** voir ligne 128 */

		case ATTACK :
			return attack(listeP, listeM); /** voir ligne 140 */

		case DEFEND :
			return defend(listeP); /** voir ligne 199 */

		case GO_DEPLOY :
			return go(listeP); /** voir ligne 286 */

		case DEPLOYMENT :
			return deploy(listeP); /** voir ligne 320 */

		default :
			return "action";
		}
	}

	/* all states 
	 * 
	 * Cette méthode traite tous les messages et agit en conséquence.
	 * (excepté messages spécifiques)
	 */
	private void treatMessages(List<WarMessage> listeM) {
		for(WarMessage m : listeM) {
			// Dans le cas de la défense
			if(state == States.DEFEND) {
				if(m.getSenderType().equals("WarBase")) {
					// Mise à jour des coordonnées de la base défendue
					if(m.getMessage().equals("base")) {
						base = m.getSender();
						baseDistance = m.getDistance();
						baseAngle = m.getAngle();
					}
				}
			}
			// Dans le cas de l'attaque
			else {
				if(m.getSenderType().equals("WarBase")) {
					// Séparation des WarRocketLaunchers au départ, commandé par la base
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
					// Passer en mode défense et en informer la base
					else if(m.getMessage().equals("defend")) {
						state = States.DEFEND;
						reply(m,"defense_ok",null);
						setHeading(m.getAngle());
					}
				}
				else if(m.getSenderType().equals("WarRocketLauncher")) {
					// Suivre l'indication de position ennemie (prioritaire)
					if(m.getMessage().equals("base")) {
						setHeading(m.getAngle());
						state = States.GO_DEPLOY;
						leader = m.getSender();
					}
				}
				else if(m.getSenderType().equals("WarExplorer")) {
					// Suivre l'indication de position ennemie (non prioritaire)
					if(m.getMessage().equals("base") 
							&& !(state == States.DEPLOYMENT || state == States.GO_DEPLOY)) {
						setHeading(m.getAngle());
					}
				}
			}
		}
	}

	/* FIRST_LAP state 
	 * 
	 * Cette méthode permet de décliner son identité à la base puis de partir
	 * en attaque.
	 */
	private String init() {
		broadcastMessage("WarBase","start", null);
		state = States.ATTACK;
		return "move";
	}

	/* ATTACK state 
	 * 
	 * Cette méthode permet d'explorer la carte à la recherche d'une base ennemie,
	 * tout en attaquant les WarRocketLaunchers ennemis sans ralentir, afin
	 * d'effectuer un Blitz sur l'ennemi.
	 */
	private String attack(List<Percept> listeP, List<WarMessage> listeM) {
		// Cible à choisir
		Percept bestPercept = null;

		for(Percept p : listeP){
			if(!p.getTeam().equals(getTeam())) {
				// Les bases sont prioritaires sur les autres agents
				if((p.getType().equals("WarBase"))
						|| (p.getType().equals("WarRocketLauncher") 
								&& (bestPercept == null || !bestPercept.getType().equals("WarBase")))) {
					bestPercept = p;
				}
			}
		}

		if(bestPercept != null){
			// Dans le cas d'une base ennemie, passer en mode déploiement,
			// informer les WarRocketLaunchers alliés et devenir leur leader
			if(bestPercept.getType().equals("WarBase")) {
				broadcastMessage("WarRocketLauncher", "base", null); //informer les autres rocketLaunchers
				state = States.DEPLOYMENT;
				leader = this.getID();
				setAngleTurret(bestPercept.getAngle());
				setHeading(bestPercept.getAngle());
				return "fire";
			}
			// Dans le cas d'un WarRocketLauncher ennemi, lui tirer dessus
			// puis partir pour éviter de ralentir
			else if(isReloaded()) {
				setAngleTurret(bestPercept.getAngle());
				return "fire";
			}
			else {
				return "move";
			}
		}
		else {
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
	}

	/* DEFEND state 
	 * 
	 * Cette méthode permet au WarRocketLauncher défenseur de patrouiller
	 * autour de la base qu'il défend, tout en rammassant la nourriture
	 * proche, et bloquant les tirs ennemis afin de protéger la base.
	 * Il peut également attaquer d'éventuels espions.
	 */
	private String defend(List<Percept> listeP) {
		// Si proche de la mort, informer la base pour recréer une défense
		if(!die && getEnergy() < 1000) {
			sendMessage(base, "defense_dying", null);
			die = true;
		}
		// Cible à choisir
		Percept bestPercept = null;
		for(Percept p : listeP) {
			// Ordre de préférence : Base > RocketLauncher > Explorer
			if(!p.getTeam().equals(getTeam())) {
				if(bestPercept == null
						|| p.getType().equals("WarBase")
						|| (p.getType().equals("WarRocket") && !bestPercept.getType().equals("WarBase"))) {
					bestPercept = p;
				}
			}
			// Base défendue
			else if(base == -1 && p.getType().equals("WarBase")) {
				this.base = p.getId();
			}
		}
		// Ne pas se bloquer en cas de perte de base (théoriquement impossible)
		if(this.base == -1) {
			return "move";
		}
		if(bestPercept != null){
			// Ramasser la nourriture proche
			if(bestPercept.getType().equals("WarFood")) {
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
			// Si ce n'est pas de la nourriture
			else {
				// Bloquer les tirs ennemis en restant proche de la base
				// (plus proche on est, plus on intercepte de WarRockets)
				if(baseDistance < 5 && bestPercept.getType().equals("WarRocket")) {
					setHeading(bestPercept.getAngle());
					return "move";
				}
				// Attaquer si possible
				else if(isReloaded()){
					setAngleTurret(bestPercept.getAngle());
					return "fire";
				}
			}
		}
		// Nourrir la base si le sac n'est pas vide
		if(!emptyBag()) {
			if(baseDistance <= WarFood.MAX_DISTANCE_TAKE) {
				setAgentToGive(base);
				return "give";
			}
			else {
				setHeading(baseAngle);
				return "move";
			}
		}
		// Ne pas trop s'éloigner de la base pour la patrouille
		if(baseDistance > 2) {
			setHeading(baseAngle);
		}
		else {
			// Ce block permet de patrouiller autour de la base sans être
			// gêné par les murs et sans s'éloigner trop loin
			while(isBlocked()) {
				setHeading(getHeading()+180); 
				dir *= -1;
			}
			setHeading(baseAngle+90*dir); //patrouille circulaire
		}
		return "move";
	}

	/* GO_DEPLOY state 
	 * 
	 * Cette méthode permet au WarRocketLauncher de rejoindre son leader
	 * sur le champ de bataille, celui-ci l'ayant informé de la position
	 * de la base ennemie.
	 */
	private String go(List<Percept> listeP) {
		for(Percept p : listeP) {
			// Changement d'état en cas de proximité avec le leader du groupe
			if(p.getId() == leader) {
				if(p.getDistance() < 20) {
					state = States.DEPLOYMENT;
					return "action";
				}
				else {
					setHeading(p.getAngle()); //rejoindre le leader
				}
			}
			// Si le leader sur les lieux est mort, on prendra sa place
			else if(!p.getTeam().equals(getTeam()) && p.getType().equals("WarBase")) {
				state = States.DEPLOYMENT;
				return "action";
			}
		}
		while(isBlocked()) {
			setHeading(getHeading()+180); 
			dir *= -1;
		}
		return "move";
	}

	/* DEPLOYMENT state 
	 * 
	 * Cette méthode permet de se déployer autour de la base ennemie, pour éviter
	 * que tous les WarRocketLaunchers ne soient sur un même point. Entre chaque
	 * tir, les WarRocketLaunchers alliés tournent autour de la base ennemie
	 * pour éviter les tirs ennemis ou éviter de voir tous les WarRockets bloqués.
	 * Si des WarRocketsLaunchers ennemis sont mal en point, cette méthode
	 * permet également de les attaquer.
	 */
	private String deploy(List<Percept> listeP) {
		// Cible à choisir
		Percept bestPercept = null;

		for(Percept p : listeP){
			// Ordre de priorité : RocketLaunchers avec peu de vie > Base
			if(!p.getTeam().equals(getTeam())) {
				if(p.getType().equals("WarBase")) {
					bestPercept = p;
				}
				else if(p.getType().equals("WarRocketLauncher") && p.getEnergy() <= 1000) {
					if(isReloaded()) {
						setAngleTurret(p.getAngle());
						return "fire";
					}
				}
			}
		}

		if(bestPercept != null){
			// Attaquer si cela est possible
			if(isReloaded()) {
				setHeading(bestPercept.getAngle());
				setAngleTurret(bestPercept.getAngle());
				
				// Affichage de la bannière comme intimidation avant une victoire
				if(bestPercept.getType().equals("WarBase") && bestPercept.getEnergy() <= 500) {
					broadcastMessage("WarBase", "banner", null);
				}
				
				return "fire";
			}
			// Tourner autour de la base à la manière d'une attaque d'indiens
			else {
				if(bestPercept.getDistance() > 28) {
					setHeading(bestPercept.getAngle());
				}
				else {
					setHeading(bestPercept.getAngle()+90*dir);
				}
				// Changer de sens en rencontrant un mur
				if(isBlocked()) {
					setHeading(getHeading()+180); 
					dir *= -1;
				}
				return "move";
			}
		}
		else { //théoriquement impossible
			return "move";
		}
	}
}
