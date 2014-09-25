package puissance4modele;

import java.io.Serializable;
import java.util.ArrayList;

import puissance4annotation.Modele;
import puissance4annotation.notUsed;

@Modele
public class Colonne implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private boolean vide=true;
	private boolean pleine=false;
	private Grille grille;
	private ArrayList<Case> cases = new ArrayList<Case>();;
	
	public Colonne(int nbLignes, Grille grille) {
		this.grille = grille;
		for(int l=0;l<nbLignes;l++) {
			cases.add(new Case(this, l)); //Vu à la façon d'une pile (de bas en haut)

			//Invariant
			assert(cases.size()==l+1) : "Colonne : erreur ajout de case";
		}
		
		//Post-Conditions
		assert (grille != null) : "Colonne : grille = NULL";
		assert (cases.size() == (grille.getNbLignes())) : "Colonne : NbLignes incorrect";
	}
	
	public int poserJeton(Jeton jeton) {
		int c=0;
		while(c < cases.size() && cases.get(c).isOccupee()) { //Chercher la première case libre en partant du bas
			c++;
			
			//Invariant
			assert((c>=0) && (c<grille.getNbLignes())) : "Colonne : mauvais indice de case";
		}
		if(c < cases.size()) { //Si la colonne n'est pas pleine
			cases.get(c).remplir(jeton);
			setVide(false);
			grille.setVide(false);
			if(c+1 == cases.size()) { //Si l'on vient de remplir la dernière case
				setPleine(true);
			}
			
			//Post-Condition
			assert((c>=0) && (c<grille.getNbLignes())) : "Colonne : mauvais indice de case";
			
			return c;
		}
		else { //Si la colonne est pleine
			assert(c>=grille.getNbLignes()) : "Colonne : mauvaise pleinitude";
			return -1;
		}
	}

	public void vider() {
		for(Case c: cases) {
			c.vider();
			
			//Invariant
			assert (!c.isOccupee()) : "Colonne : case non vidée";
		}
		setVide(true);
		setPleine(false);
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
	public boolean isVide() {
		return vide;
	}
	public void setVide(boolean vide) {
		this.vide = vide;
	}
	public boolean isPleine() {
		return pleine;
	}
	public void setPleine(boolean pleine) {
		this.pleine = pleine;
	}
	public Grille getGrille() {
		return grille;
	}
	public ArrayList<Case> getCases() {
		return cases;
	}
}
