package puissance4ressource;

import java.io.Serializable;
import puissance4modele.Jeu;
import puissance4modele.Joueur;

public class Profile implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private Joueur joueur;
	
	public Profile(Joueur joueur) {
		this.joueur = joueur;
	}
	
	public void load(Jeu jeu, int numero) {
		Joueur j = jeu.getJoueur(numero);
		//Set indirect car jeu.setJoueur() fait planter le jeu en cours
		j.setNom(joueur.getNom());
		j.setNbGain(joueur.getNbGain());
		j.setNbPerte(joueur.getNbPerte());
		j.setJeton(joueur.getJeton());
	}

	//Getters et Setters
	public Joueur getJoueur() {
		return joueur;
	}

	public void setJoueur(Joueur joueur) {
		this.joueur = joueur;
	}
}
