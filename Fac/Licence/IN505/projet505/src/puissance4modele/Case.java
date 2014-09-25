package puissance4modele;

import java.io.Serializable;

import puissance4annotation.Modele;

@Modele
public class Case implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int ligne;
	private boolean occupee=false;
	private Jeton jeton = null;
	private Colonne colonne;

	public Case(Colonne colonne, int ligne) { //position de la case dans la grille
		this.colonne = colonne;
		this.ligne = ligne;
		
		//Post-Conditions
		assert ((ligne >= 0) && (ligne < colonne.getGrille().getNbLignes())) : "Case : Ligne incorrecte";
		assert ((colonne.getCases().size() >= 0) && (colonne.getCases().size()-1 <= colonne.getGrille().getNbColonnes())) : "Case : Colonne incorrecte"; //le -1 est là car je crée la case avant de l'ajouter à la colonne
	}
	
	public void vider() {
		jeton = null;
		occupee = false;
	}
	
	public void remplir(Jeton jeton) {
		this.jeton = jeton;
		occupee = true;
		
		//Post-Conditions
		assert (jeton != null) : "Case : Jeton = NULL";
	}

	//------------------------------------------------------------------------------------------------------------
	//Getters et Setters
	public int getLigne() {
		return ligne;
	}
	public boolean isOccupee() {
		return occupee;
	}
	public Jeton getJeton() {
		return jeton;
	}
	public Colonne getColonne() {
		return colonne;
	}
	public void setColonne(Colonne colonne) {
		this.colonne = colonne;
		
		//Post-Condition
		assert (colonne != null) : "Case : set colonne = NULL";
	}
}
