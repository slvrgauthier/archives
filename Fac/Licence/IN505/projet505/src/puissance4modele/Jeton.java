package puissance4modele;

import java.io.Serializable;

import puissance4annotation.Modele;
import puissance4enumeration.Couleur;
import puissance4enumeration.Forme;

@Modele
public class Jeton implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private Couleur couleur;
	private Forme forme; //Géré à l'affichage
	Joueur joueur;
	
	public Jeton(Joueur joueur, Couleur couleur, Forme forme) {
		this.joueur = joueur;
		this.couleur = couleur;
		this.forme = forme;
		
		//Post-Condition (inapplicable à cause de l'inter-création de joueur et jeton)
		//assert (joueur != null) : "Jeton : joueur = NULL";
	}
	
	//------------------------------------------------------------------------------------------------------------
	//Getters et Setters
	public Couleur getCouleur() {
		return couleur;
	}
	public void setCouleur(Couleur couleur) {
		this.couleur = couleur;
	}
	public Forme getForme() {
		return forme;
	}
	public void setForme(Forme forme) {
		this.forme = forme;
	}
}
