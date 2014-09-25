package puissance4modele;

import java.util.ArrayList;
import java.io.Serializable;

import puissance4annotation.Modele;
import puissance4enumeration.*;
import puissance4exception.DifficulteDoesNotExistException;

@Modele
public class Jeu implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int nbParties = 3;
	private boolean autoSave=true;
	private int timeOut = 30; //Non utilisé (cf Partie.java)
	private Difficulte difficulte;
	private ArrayList<Joueur> joueurs = new ArrayList<Joueur>();
	private ArrayList<Partie> parties = new ArrayList<Partie>();
	
	public Jeu(Difficulte difficulte) {
		this.difficulte = difficulte;
		Joueur joueur1 = null;
		Jeton jeton1 = new Jeton(joueur1, Couleur.Rouge, Forme.Rond);
		Joueur joueur2 = null;
		Jeton jeton2 = new Jeton(joueur2, Couleur.Jaune, Forme.Rond);
		joueur1 = new Joueur("Joueur 1", this, jeton1);
		joueur2 = new Joueur("Joueur 2", this, jeton2);
		//joueurs par défaut
		joueurs.add(joueur1);
		joueurs.add(joueur2);
		
		nouveauJeu(nbParties);
		
		//Post-Condition
		assert (joueurs.size() == 2) : "Jeu : joueurs.size() invalide";
	}
	
	public void nouveauJeu(int nbParties) { //sauvegarde via GUI
		this.nbParties=nbParties;
		parties.clear();
		
		System.out.println("====================");
		System.out.println("Nouveau Jeu :");
		System.out.println("====================");
		
		//Post-Condition
		assert (nbParties > 0) : "Jeu : nbParties invalide";
		assert (parties.size() == 0) : "Jeu : erreur parties.clear()";
		
		try {
			nouvellePartie(difficulte);
		}
		catch(DifficulteDoesNotExistException e) { 
			difficulte = Difficulte.Debutant;
			nouveauJeu(nbParties);
		}
				
	}
	
	public void nouvellePartie(Difficulte difficulte) throws DifficulteDoesNotExistException{ //sauvegarde via GUI
		if(parties.size() == nbParties) { //Le jeu est fini (on a joué toutes les parties)
			this.difficulte = difficulte;
			nouveauJeu(nbParties);
		}
		else {
			Partie partie = null;
			if(difficulte == Difficulte.Debutant){
				partie = new PartieDebutant(this);
			}
			if(difficulte == Difficulte.Intermediaire){
				partie = new PartieIntermediaire(this);
			}
			if(difficulte == Difficulte.Confirme){
				partie = new PartieConfirme(this, timeOut);
			}
			if(partie != null) { //Si la partie a été créée
				parties.add(partie);
				joueurs.get(0).setTour(true);
				joueurs.get(1).setTour(false);
				
				System.out.println("--------------------");
				System.out.println("Nouvelle Partie :");
				System.out.println("--------------------");
				
				//Post-Condition
				assert (parties.size() <= nbParties) : "Jeu : parties.size() > nbParties";
			}
			else {
				throw new DifficulteDoesNotExistException();
			}
		}
	}
	
	public Partie getPartieCourante() {
		//Pré-Condition
		assert ((parties.size()-1) <= nbParties) : "Jeu : indice partie courante > nbParties";
		
		return parties.get(parties.size()-1);
	}
/*
	//Fonction de test du corps Métier (vous pouvez la modifier aux besoin des tests)
	public static void main(String argv[]) {
		Jeu jeu = new Jeu(Difficulte.Debutant);
		Joueur j1 = jeu.getJoueur(0);
		Joueur j2 = jeu.getJoueur(1);
		jeu.nouveauJeu(3);
		//gagnant j2 en X
		j1.lacherJeton(0); 
							j2.lacherJeton(0);
		j1.lacherJeton(1);
		j1.lacherJeton(6);
							j2.lacherJeton(2);
		j1.lacherJeton(1);
							j2.lacherJeton(3);
		j1.lacherJeton(0);
							j2.lacherJeton(4);
		j1.lacherJeton(0);
							j2.lacherJeton(5);
		try {
			jeu.nouvellePartie(jeu.getDifficulte());
		}
		catch(DifficulteDoesNotExistException e) { 
			System.out.println("!!! Erreur de difficulté : relance d'un nouveau jeu... !!!");
			jeu.nouveauJeu(jeu.getNbParties());
		}
		//gagnant j2 en Y
		j1.lacherJeton(0); 
							j2.lacherJeton(3);
		j1.lacherJeton(3);
		j1.lacherJeton(6);
							j2.lacherJeton(3);
		j1.lacherJeton(1);
							j2.lacherJeton(3);
		j1.lacherJeton(0);
							j2.lacherJeton(3);
		j1.lacherJeton(0);
							j2.lacherJeton(3);
		try {
			jeu.nouvellePartie(jeu.getDifficulte());
		}
		catch(DifficulteDoesNotExistException e) { 
			System.out.println("!!! Erreur de difficulté : relance d'un nouveau jeu... !!!");
			jeu.nouveauJeu(jeu.getNbParties());
		}
		//gagnant j2 en +XY
		j1.lacherJeton(5); 
							j2.lacherJeton(2);
		j1.lacherJeton(3);
		j1.lacherJeton(6);
							j2.lacherJeton(3);
		j1.lacherJeton(4);
							j2.lacherJeton(4);
		j1.lacherJeton(5);
							j2.lacherJeton(4);
		j1.lacherJeton(5);
							j2.lacherJeton(5);
		try {
			jeu.nouvellePartie(jeu.getDifficulte());
		}
		catch(DifficulteDoesNotExistException e) { 
			System.out.println("!!! Erreur de difficulté : relance d'un nouveau jeu... !!!");
			jeu.nouveauJeu(jeu.getNbParties());
		}
		//gagnant j2 en -XY
		j1.lacherJeton(0); 
							j2.lacherJeton(3);
		j1.lacherJeton(2);
		j1.lacherJeton(6);
							j2.lacherJeton(2);
		j1.lacherJeton(1);
							j2.lacherJeton(1);
		j1.lacherJeton(0);
							j2.lacherJeton(1);
		j1.lacherJeton(0);
							j2.lacherJeton(0);
	}
*/
	
	//------------------------------------------------------------------------------------------------------------
	//Getters et Setters
	public int getNbParties() {
		return nbParties;
	}
	public void setNbParties(int nbParties) {
		this.nbParties = nbParties;
		
		//Post-Condition
		assert (nbParties >0) : "Jeu : set nbParties invalide";
	}
	public boolean isAutoSave() {
		return autoSave;
	}
	public void setAutoSave(boolean autoSave) {
		this.autoSave = autoSave;
	}
	public void setDifficulte(Difficulte difficulte) {
		this.difficulte = difficulte;
	}
	public ArrayList<Joueur> getJoueurs() {
		return joueurs;
	}
	public Joueur getJoueur(int numero) {
		if(numero <= 0) {
			return joueurs.get(0);
		}
		else {
			return joueurs.get(1);
		}
	}
	public void setJoueur(int numero, Joueur joueur) {
		joueurs.set(numero, joueur);

		//Post-Condition
		assert (joueur != null) : "Jeu : set joueur = NULL";
	}
	public void setTimeOut(int timeOut) {
		this.timeOut = timeOut;
	}
}
