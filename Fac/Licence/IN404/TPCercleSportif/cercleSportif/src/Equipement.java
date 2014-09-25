package cercleSportif;

import java.util.Vector;

public class Equipement {

	private Vector<Lieu> lieux;
	
	private String nom;
	private String description;
	
	public Equipement(String nom) {
		this.nom = nom;
	}
	public Equipement(String nom, String description) {
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
	
}
