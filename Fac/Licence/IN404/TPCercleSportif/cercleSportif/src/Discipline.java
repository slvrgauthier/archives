package cercleSportif;

import java.util.Vector;

public class Discipline {
	
	private Vector<Moniteur> moniteurs;
	private Federation federation;
	private Vector<Cours> cours;
	
	private String nom;
	private String description;
	
	
	public Discipline(String nom) {
		this.nom = nom;
	}
	public Discipline(String nom, String description) {
		this.nom = nom;
		this.description = description;
	}
	
	public String getNom() {
		return nom;
	}
	public void setNom(String nom) {
		this.nom = nom;
	}
	public String getDescription() {
		return description;
	}
	public void setDescription(String description) {
		this.description = description;
	}
	public Federation getFederation() {
		return federation;
	}
	public void setFederation(Federation federation) {
		this.federation = federation;
	}
	
}
