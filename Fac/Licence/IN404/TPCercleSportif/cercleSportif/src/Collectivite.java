package cercleSportif;

import java.util.Vector;

public class Collectivite {

	private Vector<Lieu> lieux;
	
	private String nom;
	private String statut;
	
	public Collectivite(String nom) {
		this.nom = nom;
	}
	public Collectivite(String nom, String statut) {
		this.nom = nom;
		this.statut = statut;
	}
	
	public String getNom() {
		return nom;
	}
	public void setNom(String nom) {
		this.nom = nom;
	}
	public String getStatut() {
		return statut;
	}
	public void setStatut(String statut) {
		this.statut = statut;
	}
	
}
