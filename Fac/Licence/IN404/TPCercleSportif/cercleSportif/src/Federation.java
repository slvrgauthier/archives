package cercleSportif;

import java.util.Vector;

public class Federation {

	private Discipline discipline;
	private Vector<Inscription> inscriptions;
	
	private String nom;

	public Federation(String nom) {
		this.nom = nom;
	}
	public Federation(Discipline discipline, String nom) {
		this.discipline = discipline;
		this.nom = nom;
	}

	public Discipline getDiscipline() {
		return discipline;
	}
	public void setDiscipline(Discipline discipline) {
		this.discipline = discipline;
	}
	public String getNom() {
		return nom;
	}
	public void setNom(String nom) {
		this.nom = nom;
	}
	
}
