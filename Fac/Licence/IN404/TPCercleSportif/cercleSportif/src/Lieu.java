package cercleSportif;

import java.util.Vector;

public class Lieu {

	private Vector<Cours> cours;
	private Collectivite collectivite;
	private Vector<Equipement> equipements;
	private Vector<Crenau> crenaux;
	
	private String nom;
	private String type;
	private String adresse;

	public Lieu(String nom, String adresse) {
		this.nom = nom;
		this.adresse = adresse;
	}
	public Lieu(String nom, String type, String adresse) {
		this.nom = nom;
		this.type = type;
		this.adresse = adresse;
	}

	public String getNom() {
		return nom;
	}
	public void setNom(String nom) {
		this.nom = nom;
	}
	public String getType() {
		return type;
	}
	public void setType(String type) {
		this.type = type;
	}
	public String getAdresse() {
		return adresse;
	}
	public void setAdresse(String adresse) {
		this.adresse = adresse;
	}
	public Collectivite getCollectivite() {
		return collectivite;
	}
	public void setCollectivite(Collectivite collectivite) {
		this.collectivite = collectivite;
	}
	
}
