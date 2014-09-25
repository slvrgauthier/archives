package puissance4modele;

import java.io.Serializable;

import puissance4annotation.Modele;
import puissance4annotation.notUsed;

@Modele
public abstract class Partie implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int nbJetonsAlignes;
	private boolean termine = false;
	private Jeu jeu;
	private Grille grille;

	public Partie(Jeu j) {
		jeu = j;
	}
	
	public Joueur gagnant(int colonne, int ligne, Joueur joueur) { //le joueur venant de jouer
		int alignes = 1;
		int decalage = 1;
		Jeton jeton = grille.getColonnes().get(colonne).getCases().get(ligne).getJeton();
		//Alignement en X
		while(colonne>(decalage-1) && jeton.equals(grille.getColonnes().get(colonne-decalage).getCases().get(ligne).getJeton())) {
			alignes++;
			decalage++;
		}
		decalage = 1;
		while(colonne<grille.getNbColonnes()-decalage && jeton.equals(grille.getColonnes().get(colonne+decalage).getCases().get(ligne).getJeton())) {
			alignes++;
			decalage++;
		}
		if(alignes >= nbJetonsAlignes) {
			return joueur;
		}
		//Alignement en Y
		alignes = 1;
		decalage = 1;
		while(ligne>(decalage-1) && jeton.equals(grille.getColonnes().get(colonne).getCases().get(ligne-decalage).getJeton())) {
			alignes++;
			decalage++;
		}
		decalage = 1;
		while(ligne<grille.getNbLignes()-decalage && jeton.equals(grille.getColonnes().get(colonne).getCases().get(ligne+decalage).getJeton())) {
			alignes++;
			decalage++;
		}
		if(alignes >= nbJetonsAlignes) {
			return joueur;
		}
		//Alignement en +XY
		alignes = 1;
		decalage = 1;
		while(ligne>(decalage-1) && colonne>(decalage-1) && jeton.equals(grille.getColonnes().get(colonne-decalage).getCases().get(ligne-decalage).getJeton())) {
			alignes++;
			decalage++;
		}
		decalage = 1;
		while(ligne<grille.getNbLignes()-decalage && colonne<grille.getNbColonnes()-decalage && jeton.equals(grille.getColonnes().get(colonne+decalage).getCases().get(ligne+decalage).getJeton())) {
			alignes++;
			decalage++;
		}
		if(alignes >= nbJetonsAlignes) {
			return joueur;
		}
		//Alignement en -XY
		alignes = 1;
		decalage = 1;
		while(ligne>(decalage-1) && colonne<grille.getNbColonnes()-decalage && jeton.equals(grille.getColonnes().get(colonne+decalage).getCases().get(ligne-decalage).getJeton())) {
			alignes++;
			decalage++;
		}
		decalage = 1;
		while(ligne<grille.getNbLignes()-decalage && colonne>(decalage-1) && jeton.equals(grille.getColonnes().get(colonne-decalage).getCases().get(ligne+decalage).getJeton())) {
			alignes++;
			decalage++;
		}
		if(alignes >= nbJetonsAlignes) {
			return joueur;
		}
		
		//Si aucun gagnant
		return null;
	}
	
	public void tourSuivant() {
		if(!grille.isPleine()) {
			Joueur j1 = jeu.getJoueurs().get(0);
			Joueur j2 = jeu.getJoueurs().get(1);
			if(j1.isTour()) {
				j1.setTour(false);
				j2.setTour(true);
			}
			else {
				j2.setTour(false);
				j1.setTour(true);
			}
		}
		else {
			setTermine(true);
			System.out.println("Match nul !");
		}
	}
	
	@notUsed
	public void sauver() {
		if(!termine) {
			if(jeu.isAutoSave()) //sauvegarde automatique (par défaut)
				grille.sauver();
			else {
				//demander la sauvegarde
			}
		}
		grille.vider();
	}
	
	@notUsed
	public void restaurer() {
		grille.restaurer();
	}

	//------------------------------------------------------------------------------------------------------------
	//Getters et Setters
	public void setNbJetonsAlignes(int nbJetonsAlignes) {
		this.nbJetonsAlignes = nbJetonsAlignes;
	}
	public boolean isTermine() {
		return termine;
	}
	public void setTermine(boolean termine) {
		this.termine = termine;
	}
	public Grille getGrille() {
		return grille;
	}
	public void setGrille(Grille grille) {
		this.grille = grille;
	}
}

//Sous-classes
@Modele
class PartieDebutant extends Partie {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public PartieDebutant(Jeu jeu) {
		super(jeu);
		setNbJetonsAlignes(4);
		setGrille(new Grille(7,6,this));
	}
}

@Modele
class PartieIntermediaire extends Partie {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public PartieIntermediaire(Jeu jeu) {
		super(jeu);
		setNbJetonsAlignes(5);
		setGrille(new Grille(9,8,this));
	}
}

@Modele
class PartieConfirme extends Partie {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int timeout = 30; //Non implémenté par manque de solution graphique  (cf animation LacherJeton)
	public PartieConfirme(Jeu jeu, int timeout) {
		super(jeu);
		this.timeout = timeout;
		setNbJetonsAlignes(6);
		setGrille(new Grille(11,10,this));
	}

	//------------------------------------------------------------------------------------------------------------
	//Getters et Setters
	public int getTimeout() {
		return timeout;
	}
	public void setTimeout(int timeout) {
		this.timeout = timeout;
	}
}

