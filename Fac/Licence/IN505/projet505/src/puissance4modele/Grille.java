package puissance4modele;

import java.io.Serializable;
import java.util.ArrayList;
import puissance4annotation.Modele;
import puissance4annotation.notUsed;

@Modele
public class Grille implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int nbColonnes;
	private int nbLignes;
	private boolean vide=true;
	private boolean pleine=false;
	private Partie partie;
	private ArrayList<Colonne> colonnes = new ArrayList<Colonne>();
	
	public Grille(int nbColonnes, int nbLignes, Partie partie) {
		this.nbColonnes = nbColonnes;
		this.nbLignes = nbLignes;
		this.partie = partie;
		for(int c=0;c<nbColonnes;c++) {
			colonnes.add(new Colonne(nbLignes, this));
			
			//Invariant
			assert ((colonnes.size() == c+1)) : "Grille : erreur ajout de colonne";
			
		}
	}

	public void vider() {
		for(Colonne c: colonnes) {
			c.vider();
			
			//Invariant
			assert (c.isVide()) : "Grille : colonne non vidée";
		}
		setVide(true);
	}
	
	@notUsed
	public void sauver() {
		//voir format de sauvegarde
	}
	
	@notUsed
	public void restaurer() {
		//voir format de sauvegarde
	}
	
	//------------------------------------------------------------------------------------------------------------
	//Getters et Setters
	public int getNbColonnes() {
		return nbColonnes;
	}
	public int getNbLignes() {
		return nbLignes;
	}
	public void setVide(boolean vide) {
		this.vide = vide;
	}
	public boolean isPleine() {
		for(Colonne c: colonnes) { //On regarde chaque colonne
			if(!c.isPleine()){
				setPleine(false);
				return pleine;
			}
			
			//Invariant
			assert (c.isPleine()) : "Grille : erreur pleinitude";
		}
		setPleine(true);
		return pleine;
	}
	public void setPleine(boolean pleine) {
		this.pleine = pleine;
	}
	public ArrayList<Colonne> getColonnes() {
		return colonnes;
	}
	public Partie getPartie() {
		return partie;
	}
	public void setPartie(Partie partie) {
		this.partie = partie;
	}
	public boolean isVide() {
		return vide;
	}
}
