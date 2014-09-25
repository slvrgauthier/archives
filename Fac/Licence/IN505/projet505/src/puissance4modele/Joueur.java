package puissance4modele;

import java.io.Serializable;

import puissance4annotation.Modele;

@Modele
public class Joueur implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String nom;
	private boolean tour = false;
	private int nbGain = 0;
	private int nbPerte = 0;
	private Jeu jeu;
	private Jeton jeton;
	
	public Joueur(String nom, Jeu jeu, Jeton jeton) {
		this.nom = nom;
		this.jeu = jeu;
		this.jeton = jeton;
		
		//Post-Condition (inapplicable à cause de l'inter-création de joueur et jeton)
		assert (jeu != null) : "Joueur : jeu = NULL";
		//assert (jeton != null) : "Joueur : jeton = NULL";
	}
	
	public int lacherJeton(int colonne) {
		int ligne = -1; //erreur
		if(tour && !jeu.getPartieCourante().isTermine()) {
			Partie partieCourante = jeu.getPartieCourante();
			ligne = partieCourante.getGrille().getColonnes().get(colonne).poserJeton(jeton);
			if(ligne != -1) {
				System.out.println(nom+" a lâché un jeton en ["+colonne+","+ligne+"].");
				Joueur gagnant = partieCourante.gagnant(colonne, ligne, this);
				if(gagnant != null) {
					System.out.println(nom+" a gagné !");
					System.out.println("________________________________________________________");
					incGain();
					System.out.println(stats());
					if(jeu.getJoueur(0).equals(this)) {
						jeu.getJoueur(1).incPerte();
						System.out.println(jeu.getJoueur(1).stats());
					}
					else {
						jeu.getJoueur(0).incPerte();
						System.out.println(jeu.getJoueur(0).stats());
					}
					System.out.println("________________________________________________________");
					jeu.getPartieCourante().setTermine(true);
				}
				partieCourante.tourSuivant();
			}
			else {
				if(ligne == -1) {
					System.out.println("Colonne pleine !");
				}
			}
		}
		return ligne;
	}
	
	public void incGain() {
		nbGain++;
	}
	
	public void incPerte() {
		nbPerte++;
	}
	
	public String stats() {
		return nom+" : "+nbGain+" parties gagnées contre "+nbPerte+" parties perdues";
	}
	
	//------------------------------------------------------------------------------------------------------------
	//Getters et Setters
	public String getNom() {
		return nom;
	}
	public void setNom(String nom) {
		this.nom = nom;
	}
	public boolean isTour() {
		return tour;
	}
	public void setTour(boolean tour) {
		this.tour = tour;
	}
	public int getNbGain() {
		return nbGain;
	}
	public void setNbGain(int nbGain) {
		this.nbGain = nbGain;
	}
	public int getNbPerte() {
		return nbPerte;
	}
	public void setNbPerte(int nbPerte) {
		this.nbPerte = nbPerte;
	}
	public Jeu getJeu() {
		return jeu;
	}
	public void setJeu(Jeu jeu) {
		this.jeu = jeu;
		
		//Post-Condition
		assert (jeu != null) : "Joueur : set jeu = NULL";
	}
	public Jeton getJeton() {
		return jeton;
	}
	public void setJeton(Jeton jeton) {
		this.jeton = jeton;
		
		//Post-Condition
		assert (jeton != null) : "Joueur : set jeton = NULL";
	}
}
