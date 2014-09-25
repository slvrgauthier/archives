package edu.turtlekit2.warbot.warBotte_v2;

import java.util.ArrayList;
import java.util.List;

import edu.turtlekit2.warbot.WarBrain;
import edu.turtlekit2.warbot.message.WarMessage;
import edu.turtlekit2.warbot.percepts.Percept;

/** War Botte v2 : WarBase
 *  
 * @author GAUTHIER silvère
 *
 */
public class BrainBase extends WarBrain{
	private States state = States.FIRST_LAP;

	private int cpt = 0; // Utilisé pour le ratio de création d'agents
	private int seuil = 2; // Utilisé pour le ratio de création d'agents
	private boolean spy = false; // Recrutement des espions
	private int defender = -1; // Id du WarRocketLauncher défenseur
	private int positionEnnemi = -1; // Position de la base ennemie

	public BrainBase(){}

	public String action() {
		List<Percept> listeP = getPercepts();
		List<WarMessage> listeM = getMessage();

		// La base mange dès qu'elle le peut
		if(!emptyBag()){
			return "eat";
		}

		decide(); /** voir ligne 60 */
		treatMessages(listeM); /** voir ligne 80 */

		/* Pseudo-FSM */
		switch(state) {

		case FIRST_LAP :
			return init(listeM); /** voir ligne 193 */

		case ASK_DEFENSE :
			return ask_defense(listeP, listeM); /** voir ligne 213 */

		case HIGH_ENERGY :
			return createAgent(listeP); /** voir ligne 246 */

		default:
			return "action";
		}
	}

	/* all states 
	 * 
	 * Cette méthode permet de décider automatiquement de l'état en cours
	 * selon le status vital de la base.
	 */
	public void decide() {
		if(state == States.HIGH_ENERGY || state == States.AVERAGE_ENERGY) {  // états non prioritaires
			int energy = getEnergy();
			if(energy < 9000){
				broadcastMessage("WarExplorer","lowHealth",null); //appeler de l'aide
			}	
			else if(getEnergy() > 12000){
				state = States.HIGH_ENERGY; //créer un nouvel agent
			}
			else {
				state = States.AVERAGE_ENERGY; //défaut
			}
		}
	}

	/* all states 
	 * 
	 * Cette méthode traite tous les messages et agit en conséquence.
	 * (excepté messages spécifiques)
	 */
	private void treatMessages(List<WarMessage> listeM) {
		ArrayList<Integer> launchers = new ArrayList<Integer>();
		ArrayList<Integer> explorers = new ArrayList<Integer>();

		// Envois
		broadcastMessage("WarExplorer","posBase",null); //message de position
		if(defender != -1) {
			sendMessage(defender, "base", null); //message de position
		}

		// Réceptions
		for(WarMessage m : listeM) {
			if(m.getSenderType().equals("WarRocketLauncher")) {
				// Recenser les WarRocketLaunchers alliés
				if(m.getMessage().equals("start")) {
					launchers.add(m.getSender());
				}
				// Mémoriser le défenseur et stopper le recrutement
				if(m.getMessage().equals("defense_ok")) {
					defender = m.getSender();
				}
				// Recréer une défense si l'existante se meurt
				else if(getEnergy() > 4000 && m.getMessage().equals("defense_dying")) {
					state = States.FIRST_LAP; 
				}
				// Afficher la bannière de l'équipe avant la victoire (bonus)
				else if(m.getMessage().equals("banner")) {
					banner();
				}
			}
			else if(m.getSenderType().equals("WarExplorer")) {
				// Recenser les WarExplorers alliés
				if(m.getMessage().equals("start")) {
					explorers.add(m.getSender());
				}
				// Retenir la position de l'ennemi
				else if(m.getMessage().equals("positionEnnemi")) {
					positionEnnemi = m.getAngle();
				}
			}
			else {
				// Fin du recrutement des espions
				if(m.getMessage().equals("spy_ok")) {
					this.spy = true;
				}
			}
		}
		// Si on ne connait pas la position ennemie, partir en éventail
		// sinon partir directement dans la direction de l'ennemi
		if(positionEnnemi == -1) {
			eventail(launchers, explorers);
		}
		else {
			for(int i : launchers) {
				String[] sms = new String[1];
				sms[0] = Integer.toString(positionEnnemi);
				sendMessage(i, "startAngle", sms);
			}
		}
	}

	/* 
	 * Cette fonction permet d'envoyer les WarRocketLaunchers et les War Explorers
	 * en éventail, pour mieux explorer et tomber "presque" à coup sûr vers la
	 * base ennemie.
	 * Elle permet également de recruter un WarExplorer espion si le recrutement
	 * est actif.
	 */
	private void eventail(ArrayList<Integer> launchers, ArrayList<Integer> explorers) {
		// Envoyer un angle de départ aux WarRocketLaunchers
		// Angle total de l'éventail
		int coneSize = Math.min((launchers.size()-1)*12, 90);
		// Angle courant à envoyer, centré par rapport à 90°
		int currentAngle = (90-coneSize)/3; //division par 2 si la map est un carré
		for(int i=0;i<launchers.size();i++) {
			// Envoi de l'angle courant
			String[] sms = new String[1];
			sms[0] = Integer.toString(currentAngle);
			sendMessage(launchers.get(i),"startAngle",sms);
			// Calcul de l'angle suivant
			if(launchers.size() > 1) {
				currentAngle += coneSize/(launchers.size()-1);
			}
		}

		// Envoyer un angle de départ aux WarExplorers
		// Angle total de l'éventail
		coneSize = 100;
		// Angle courant à envoyer
		currentAngle = -5;
		for(int i=0;i<explorers.size();i++) {
			// Envoi de l'angle courant
			String[] sms = new String[1];
			sms[0] = Integer.toString(currentAngle);
			sendMessage(explorers.get(i),"startAngle",sms);
			// Calcul de l'angle suivant
			if(explorers.size() > 1) {
				currentAngle += coneSize/(explorers.size()-1);
			}
			// Recruter le WarExplorer du "milieu" en tant qu'espion
			if(!spy && i == (int)((explorers.size()+1)/2)-1) {
				sendMessage(explorers.get(i),"spy",null);
				this.spy = true;
				broadcastMessage("WarBase","spy_ok",null); //informer les autres bases
			}
		}
	}

	/* FIRST_LAP state 
	 * 
	 * Cette méthode permet de créer un WarRocketLauncher puis de passer
	 * dans l'état permettant de le recruter en tant que défenseur.
	 */
	public String init(List<WarMessage> listeM) {
		setNextAgentCreate("RocketLauncher");
		defender = -1;
		state = States.ASK_DEFENSE;
		return "create";
	}

	/* ASK_DEFENSE state
	 * 
	 * Cette méthode permet de recruter un WarRocketLauncher en tant que
	 * défenseur. Elle sélectionne le WarRocketLauncher le plus proche
	 * et lui demande de défendre, la WarBase attend une réponse favorable
	 * avant de stopper.
	 * Cette méthode accepte un défenseur par base.
	 * 
	 * -> L'attente de réponse est nécessaire lors du début du jeu, le
	 * WarRocketLauncher ne réceptionnant pas le message pendant sa création.
	 * -> La base ne peut pas boucler, cet état étant atteint uniquement
	 * après création d'un WarRocketLauncher.
	 */
	private String ask_defense(List<Percept> listeP, List<WarMessage> listeM) {
		// Si un WarRocketLauncher est déjà défenseur, stopper le recrutement
		if(defender != -1) {
			state = States.AVERAGE_ENERGY;
		}
		else {
			// Choisir le WarRocketLauncher le plus proche
			Percept bestPercept = null;
			for(Percept p : listeP) {
				if(p.getType().equals("WarRocketLauncher") 
						&& (bestPercept == null 
						|| p.getDistance() < bestPercept.getDistance())) {
					bestPercept = p;
				}
			}

			// Demander au WarRocketLauncher de passer en défense
			if(bestPercept != null) {
				sendMessage(bestPercept.getId(),"defend",null);
			}
			else { //théoriquement jamais atteint : aucun défenseur trouvé
				state = States.FIRST_LAP;
			}
		}

		return "action";
	}

	/* HIGH_ENERGY state 
	 * 
	 * Cette méthode permet de créer un agent selon un ratio prédéfini.
	 * Ce ratio est de "seuil" WarRocketLaunchers pour 1 WarExplorer.
	 */
	public String createAgent(List<Percept> listeP) {
		if(cpt > seuil) {
			cpt = 0;
			setNextAgentCreate("Explorer");
		}
		else {
			cpt++;
			setNextAgentCreate("RocketLauncher");
		}
		return "create";
	}

	/*
	 * Affichage de la bannière "WAR BOTTE !" en 3D ascii.
	 */
	public void banner() {
		System.out.println(" __      __                       ____            __    __               __     ");
		System.out.println("/\\ \\  __/\\ \\                     /\\  _`\\         /\\ \\__/\\ \\__           /\\ \\    ");
		System.out.println("\\ \\ \\/\\ \\ \\ \\     __     _ __    \\ \\ \\L\\ \\    ___\\ \\ ,_\\ \\ ,_\\    __    \\ \\ \\   ");
		System.out.println(" \\ \\ \\ \\ \\ \\ \\  /'__`\\  /\\`'__\\   \\ \\  _ <'  / __`\\ \\ \\/\\ \\ \\/  /'__`\\   \\ \\ \\  ");
		System.out.println("  \\ \\ \\_/ \\_\\ \\/\\ \\L\\.\\_\\ \\ \\/     \\ \\ \\L\\ \\/\\ \\L\\ \\ \\ \\_\\ \\ \\_/\\  __/    \\ \\_\\ ");
		System.out.println("   \\ `\\___x___/\\ \\__/.\\_\\\\ \\_\\      \\ \\____/\\ \\____/\\ \\__\\\\ \\__\\ \\____\\    \\/\\_\\");
		System.out.println("    '\\/__//__/  \\/__/\\/_/ \\/_/       \\/___/  \\/___/  \\/__/ \\/__/\\/____/     \\/_/");
	}
}
