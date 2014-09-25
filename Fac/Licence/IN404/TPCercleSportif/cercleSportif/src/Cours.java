package cercleSportif;

import java.util.Vector;

public class Cours {

	private Vector<Inscription> inscriptions;
	private Moniteur moniteur;
	private Discipline discipline;
	private Crenau crenau;
	private Lieu lieu;
	
	private Heure duree;
	private float prix;
	private int minIns;
	private int maxIns;
	
	public Cours(Crenau crenau) {
		this.crenau = crenau;
	}
	public Cours(Discipline discipline, Crenau crenau, Lieu lieu, float prix) {
		this.discipline = discipline;
		this.crenau = crenau;
		this.lieu = lieu;
		this.prix = prix;
	}
	public Cours(Moniteur moniteur, Discipline discipline, Crenau crenau,
			Lieu lieu, float prix, int minIns, int maxIns) {
		this.moniteur = moniteur;
		this.discipline = discipline;
		this.crenau = crenau;
		this.lieu = lieu;
		this.prix = prix;
		this.minIns = minIns;
		this.maxIns = maxIns;
	}

	public Moniteur getMoniteur() {
		return moniteur;
	}
	public void setMoniteur(Moniteur moniteur) {
		this.moniteur = moniteur;
	}
	public Discipline getDiscipline() {
		return discipline;
	}
	public void setDiscipline(Discipline discipline) {
		this.discipline = discipline;
	}
	public Crenau getCrenau() {
		return crenau;
	}
	public void setCrenau(Crenau crenau) {
		this.crenau = crenau;
	}
	public Lieu getLieu() {
		return lieu;
	}
	public void setLieu(Lieu lieu) {
		this.lieu = lieu;
	}
	public float getPrix() {
		return prix;
	}
	public void setPrix(float prix) {
		this.prix = prix;
	}
	public int getMinIns() {
		return minIns;
	}
	public void setMinIns(int minIns) {
		this.minIns = minIns;
	}
	public int getMaxIns() {
		return maxIns;
	}
	public void setMaxIns(int maxIns) {
		this.maxIns = maxIns;
	}
	
	public void calculDuree(){
	}

}
