package edu.turtlekit2.warbot.warBotte;

import java.util.ArrayList;
import java.util.List;

import edu.turtlekit2.warbot.WarBrain;
import edu.turtlekit2.warbot.message.WarMessage;
import edu.turtlekit2.warbot.percepts.Percept;

/**
 *  
 * @author GAUTHIER silvère
 *
 */
public class BrainBase extends WarBrain{
	private States state = States.FIRST_LAP;

	private int cpt = 0; //compteur couplé au seuil
	private int seuil = 2; //avoir une proportion de 2 rocketLaunchers pour 1 exploreur
	private boolean spy = false; //savoir si un espion a été élu ou non
	private int defender = -1;

	public BrainBase(){
	}

	public String action() {
		List<Percept> listeP = getPercepts();
		List<WarMessage> listeM = getMessage();

		//Eating
		if(!emptyBag()){
			return "eat";
		}
		//State setting
		decide(); /** voir ligne 66 */

		//Default messages treatment
		treatMessages(listeM); /** voir ligne 85 */

		//Action
		switch(state) {

		case FIRST_LAP :
			banner(); return init(listeM); /** voir ligne 155 */

		case ASK_DEFENSE :
			return ask(Subjects.DEFENSE, listeP, listeM); /** voir ligne 168 */

		//Plus utilisé pour cause de blocage potentiel de la base
		case ASK_SPY : // -> deprecated
			return ask(Subjects.SPY, listeP, listeM); /** voir ligne 192 */

		case LOW_ENERGY : // -> deprecated
			return ask(Subjects.HELP, listeP, listeM); /** voir ligne 211 */

		case HIGH_ENERGY :
			return createAgent(listeP); /** voir ligne 221 */

		default:
			return "action";
		}
	}

	/* all states */
	public void decide() {
		if(state == States.LOW_ENERGY                 //    états
				|| state == States.HIGH_ENERGY        //     non
				|| state == States.AVERAGE_ENERGY) {  // prioritaires
			int energy = getEnergy();
			if(energy < 9000){
				//state = States.LOW_ENERGY; //demander de l'aide -> deprecated
				broadcastMessage("WarExplorer","lowHealth",null);
			}	
			else if(getEnergy() > 12000){
				state = States.HIGH_ENERGY; //créer un nouvel agent
			}
			else {
				state = States.AVERAGE_ENERGY; //défaut
			}
		}
	}

	/* all states */
	private void treatMessages(List<WarMessage> listeM) {
		//Message sending
		broadcastMessage("WarExplorer","posBase",null); //message de position
		if(defender != -1) {
			sendMessage(defender, "base", null);
		}
		
		//Message reading
		ArrayList<Integer> launchers = new ArrayList<Integer>(); //compter les rocketLaunchers
		ArrayList<Integer> explorers = new ArrayList<Integer>(); //compter les explorers
		
		for(WarMessage m : listeM) {
			if(m.getSenderType().equals("WarRocketLauncher")) {
				if(m.getMessage().equals("start")) {
					launchers.add(m.getSender());
				}
				else if(getEnergy() > 4000 && m.getMessage().equals("defense_dying")) {
					state = States.FIRST_LAP; //recréer une défense
				}
			}
			else if(m.getSenderType().equals("WarExplorer")) {
				if(m.getMessage().equals("start")) {
					explorers.add(m.getSender());
				}/*  -> deprecated
				else if(m.getMessage().equals("ready to spy")) { //remplace ASK_SPY
					if(spy) {
						reply(m, "spy_ok", null);
					}
					else {
						reply(m, "spy", null); //donner l'ordre d'espionner
						this.spy = true; //un espion a été élu
					}
				}*/
			}
			else {
				if(m.getMessage().equals("spy_ok")) {
					this.spy = true;
				}
			}
		}
		// envoyer un angle de départ aux launchers
		if(launchers.size() == 1) {
			String[] sms = new String[1];
			sms[0] = Integer.toString(0);
			sendMessage(launchers.get(0),"startAngle",sms);
		}
		else {
			int ref = Math.min(launchers.size()*12, 90);
			int currentAngle = -ref;
			for(int i=0;i<launchers.size();i++) {
				String[] sms = new String[1];
				sms[0] = Integer.toString(currentAngle+ref);
				sendMessage(launchers.get(i),"startAngle",sms);
				currentAngle += ref/(launchers.size()-1);
			}
		}
		// envoyer un angle de départ aux explorers
		if(explorers.size() == 1) {
			String[] sms = new String[1];
			sms[0] = Integer.toString(0);
			sendMessage(explorers.get(0),"startAngle",sms);
			if(!spy) {
				sendMessage(explorers.get(0),"spy",null);
				this.spy = true;
				broadcastMessage("WarBase","spy_ok",null); //informer les autres bases
			}
		}
		else {
			int ref = 100;
			int currentAngle = -ref;
			for(int i=0;i<explorers.size();i++) {
				String[] sms = new String[1];
				sms[0] = Integer.toString(currentAngle+ref-5);
				sendMessage(explorers.get(i),"startAngle",sms);
				currentAngle += ref/(explorers.size()-1);
				if(!spy && i == (int)((explorers.size()+1)/2)-1) {
					sendMessage(explorers.get(i),"spy",null);
					this.spy = true;
					broadcastMessage("WarBase","spy_ok",null); //informer les autres bases
					banner(); //intimider l'enemi :P
				}
			}
		}
	}

	/* FIRST_LAP state */
	public String init(List<WarMessage> listeM) { //créer un rocketLauncher en défense	
		setNextAgentCreate("RocketLauncher");
		state = States.ASK_DEFENSE;
		return "create";
	}

	/* ASK_DEFENSE, ASK_SPY and LOW_HEALTH states */
	private String ask(Subjects subject, List<Percept> listeP, List<WarMessage> listeM) {
		boolean stop = false;

		switch(subject) {

		//demander un rocketLauncher en défense
		case DEFENSE :
			Percept bestPercept = null;
			for(Percept p : listeP) {
				if(!stop && p.getType().equals("WarRocketLauncher") && (bestPercept == null || p.getDistance() < bestPercept.getDistance())) {
					bestPercept = p;
				}
			}
			if(bestPercept != null) {
				sendMessage(bestPercept.getId(),"defend",null); //ordre de défendre
			}
			for(WarMessage m : listeM) {
				if(m.getSenderType().equals("WarRocketLauncher")) {
					if(m.getMessage().equals("defense_ok")) { //un rocketLauncher a exécuté l'ordre
						defender = m.getSender();
						stop = true; //arrêter la demande de défense
					}
				}
			}
			if(stop) { //seulement si un rocketLauncher a été élu
				state = States.AVERAGE_ENERGY; //demander un espion
			}
			return "action";

		//demander à un exploreur d'espionner (risque de blocage de la base -> abandonné)
/*		case SPY :
			for(WarMessage m : listeM) {
				if(m.getType().equals("WarExplorer")) {
					if(spy == false && m.getMessage().equals("ready to spy")) { //message reçu tant qu'aucun espion n'a été élu
						reply(m, "spy", null); //donner l'ordre d'espionner
						this.spy = true; //un espion a été élu
					}
					else if(m.getMessage().equals("spy_ok")) { //un exploreur a exécuté l'ordre
						broadcastMessage("WarExplorer", "spy_ok", null); //en informer les exploreurs
						stop = true; //arrêter la demande d'espion
					}
				}
			}
			if(stop) {
				state = States.AVERAGE_ENERGY; //état "par défaut"
			}
			return "action";
*//*
		//appeler les exploreurs à l'aide (pas besoin d'état pour cela -> abandon)
		case HELP :
			broadcastMessage("WarExplorer","lowHealth",null);
			return "action";
*/
		//défaut
		default : return "action";
		}
	}

	/* HIGH_ENERGY state */
	public String createAgent(List<Percept> listeP) {
		if(cpt > seuil) { //ration entre exploreurs et rocketLaunchers
			cpt = 0;
			setNextAgentCreate("Explorer");
		}
		else {
			cpt++;
			setNextAgentCreate("RocketLauncher");
		}
		return "create";
	}
	
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
