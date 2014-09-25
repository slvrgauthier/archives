package cercleSportif;

import java.util.Vector;

public class Moniteur {

	private Vector<Discipline> disciplines;
	private Vector<Cours> cours;
	
	private String nom;
	private String prenom;

	public Moniteur(String nom) {
		this.nom = nom;
	}
	public Moniteur(String nom, String prenom) {
		this.nom = nom;
		this.prenom = prenom;
	}

	public String getNom() {
		return nom;
	}
	public void setNom(String nom) {
		this.nom = nom;
	}
	public String getPrenom() {
		return prenom;
	}
	public void setPrenom(String prenom) {
		this.prenom = prenom;
	}
	
}
