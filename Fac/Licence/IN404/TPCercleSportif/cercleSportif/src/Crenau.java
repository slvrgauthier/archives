package cercleSportif;

import java.util.Vector;

public class Crenau {

	private Cours cours;
	private Vector<Lieu> lieux;
	private Planning planning;
	
	private Heure debut;
	private Heure fin;
	
	public Crenau(Heure debut, Heure fin) {
		this.debut = debut;
		this.fin = fin;
	}
	
	public Heure getDebut() {
		return debut;
	}
	public void setDebut(Heure debut) {
		this.debut = debut;
	}
	public Heure getFin() {
		return fin;
	}
	public void setFin(Heure fin) {
		this.fin = fin;
	}

	public Cours getCours() {
		return cours;
	}

	public void setCours(Cours cours) {
		this.cours = cours;
	}

	public Planning getPlanning() {
		return planning;
	}

	public void setPlanning(Planning planning) {
		this.planning = planning;
	}
	
}
