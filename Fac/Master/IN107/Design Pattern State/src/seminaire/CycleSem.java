package seminaire;

import java.util.ArrayList;

public class CycleSem {
	// thread pour passer de PreparationSem à EnCours
	//                    de EnCours à Termine
	//                    de Fini à Archive
	private String titre;
	private String resume;
	private int nbInscrits = 0;
	private int capacite = 50;
	
	private EtatCycleSem etat = new Planification();
	
	private ArrayList<Adherent> listeAttente = new ArrayList<Adherent>();
	private ArrayList<Adherent> inscrits = new ArrayList<Adherent>();
	private ArrayList<Creneau> creneaux = new ArrayList<Creneau>();
	private ArrayList<Document> documents = new ArrayList<Document>();
	
	public CycleSem(String t, String r, ArrayList<Creneau> c) {
		titre = t; resume = r; creneaux = c;
	}
	private void ajoutListeAttente(Adherent a) {
		listeAttente.add(a);
	}
	private Adherent popListeAttente() {
		Adherent a = listeAttente.get(0);
		listeAttente.remove(0);
		return a;
	}
	private void ajoutInscrit(Adherent a) {
		if(!inscrits.contains(a)) {
			inscrits.add(a);
			nbInscrits++;
		}
	}
	private void retirerInscrit(Adherent a) {
		inscrits.remove(a);
	}
	public void inscription(Adherent a) {
		etat = etat.inscription(a);
		if(nbInscrits < capacite) {
			ajoutInscrit(a);
		}
		else {
			ajoutListeAttente(a);
		}
	}
	public void desistement(Adherent a) {
		etat = etat.desistement(a);
		retirerInscrit(a);
		if(getListeAttente().size() > 0) {
			ajoutInscrit(popListeAttente());
		}
	}
	public void archiver() {
		etat = etat.archiver();
	}
	public void abandon(Adherent a) {
		etat = etat.abandon(a);
		retirerInscrit(a);
	}
	public void ouvertureReservation() {
		etat = etat.ouvertureReservation();
	}
	public void clotureReservation() {
		etat = etat.clotureReservation();
	}
	public void annuler() {
		etat = etat.annuler();
	}
	public void ajoutDocument(Document d) {
		
	}
	public void setTitre(String titre) {
		etat = etat.setTitre(titre);
	}
	public void setResume(String resume) {
		etat = etat.setResume(resume);
	}
	public void setCapacite(int capacite) {
		etat = etat.setCapacite(capacite);
	}
	public void setCreneaux(Creneau creneau) {
		etat = etat.setCreneaux(creneau);
	}
	//Setters
	public void setT(String titre) {
		this.titre = titre;
	}
	public void setR(String resume) {
		this.resume = resume;
	}
	public void setCa(int capacite) {
		this.capacite = capacite;
	}
	public void setCr(Creneau creneau) {
		this.creneaux.add(creneau);
	}
	//Getters
	public String getTitre() {
		return titre;
	}
	public String getResume() {
		return resume;
	}
	public int getNbInscrits() {
		return nbInscrits;
	}
	public int getCapacite() {
		return capacite;
	}
	public EtatCycleSem getEtat() {
		return etat;
	}
	public ArrayList<Adherent> getListeAttente() {
		return listeAttente;
	}
	public ArrayList<Adherent> getInscrits() {
		return inscrits;
	}
	public ArrayList<Creneau> getCreneaux() {
		return creneaux;
	}
	public ArrayList<Document> getDocuments() {
		return documents;
	}
}
