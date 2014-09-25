package puissance4vue;

import java.awt.Graphics;
import java.awt.event.MouseListener;
import java.io.*;
import java.util.ArrayList;
import javax.swing.*;

import puissance4annotation.Vue;
import puissance4controleur.ClickImageLacher;
import puissance4enumeration.Difficulte;
import puissance4modele.Case;
import puissance4modele.Colonne;
import puissance4modele.Grille;
import puissance4modele.Jeu;
import puissance4ressource.*;

@Vue
public class PanneauJeu extends JPanel {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private Jeu jeu;
	private int nbColonnes;
	private int nbLignes;
	private ImageFondJeu fond;
	private ImageGrille grille;
	private ArrayList<ImageJeton> jetons = new ArrayList<ImageJeton>(); //Liste des jetons à afficher
	
	public PanneauJeu(int nbColonnes, int nbLignes, Jeu jeu) {
		this.jeu = jeu;
		this.nbColonnes = nbColonnes;
		this.nbLignes = nbLignes;
		
		//Choix du fond et de la grille suivant la taille
		switch(nbColonnes) {
		case 7 :
			grille = new ImageGrille(0,0,Difficulte.Debutant);
			fond = new ImageFondJeu(0,0,Difficulte.Debutant);
			break;
		case 9 :
			grille = new ImageGrille(0,0,Difficulte.Intermediaire);
			fond = new ImageFondJeu(0,0,Difficulte.Intermediaire);
			break;
		case 11 :
			grille = new ImageGrille(0,0,Difficulte.Confirme);
			fond = new ImageFondJeu(0,0,Difficulte.Confirme);
			break;
		default :
			grille = new ImageGrille(0,0,Difficulte.Debutant);
			fond = new ImageFondJeu(0,0,Difficulte.Debutant);
			break;
		}
		
		//Listener des flèches de lâcher
		for(int i=0;i<nbColonnes;i++)
			addMouseListener(new ClickImageLacher(new ImageLacher(i*64,0),this,jeu));
	}
	
	
	//Fonctionnalités
	public void clear(){
		jetons.clear();
		repaint();
	}
	
	public void save(File Fic) throws IOException{
		//Sauvegarde de la classe principale du modèle
		ObjectOutputStream flotS=new ObjectOutputStream(new FileOutputStream(Fic));
		flotS.writeObject((Jeu)jeu);
		flotS.close();
	}
	
	public Jeu restore(File Fic, FenetreJeu fenetre) throws IOException,ClassNotFoundException{
		//Nettoyer le panneau courant
		clear();
		for(MouseListener ml: this.getMouseListeners())
			removeMouseListener(ml);
		
		//Charger un jeu à la place du jeu courant
		ObjectInputStream flotE = new ObjectInputStream(new FileInputStream(Fic));
		Object fig = flotE.readObject();
	    jeu = (Jeu) fig;
		flotE.close();
		
		//Mise à jour du panneau
		Grille g = jeu.getPartieCourante().getGrille();
		//fond et grille
		switch(g.getNbColonnes()) {
		case 7 :
			fenetre.setSize(7*64,7*64+20);
			fond = new ImageFondJeu(0,0,Difficulte.Debutant);
			grille = new ImageGrille(0,0,Difficulte.Debutant);
			break;
		case 9 :
			fenetre.setSize(9*64,8*64+20);
			fond = new ImageFondJeu(0,0,Difficulte.Intermediaire);
			grille = new ImageGrille(0,0,Difficulte.Intermediaire);
			break;
		case 11 :
			fenetre.setSize(11*64,10*64+20);
			fond = new ImageFondJeu(0,0,Difficulte.Confirme);
			grille = new ImageGrille(0,0,Difficulte.Confirme);
			break;
		}
		//jetons
		for(Colonne col: g.getColonnes()) {
			for(Case cas: col.getCases()) {
				if(cas.isOccupee()) {
					jetons.add(new ImageJeton(64*g.getColonnes().indexOf(col), grille.getHeight()-64*(1+cas.getLigne()), cas.getJeton()));
				}
			}
		}
		//flèches
		for(int i=0;i<nbColonnes;i++)
			addMouseListener(new ClickImageLacher(new ImageLacher(i*64,0),this,jeu));
		
		repaint();
		
		//Pour les besoins de la fenêtre
		return jeu;
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		fond.paintComponent(g);
		for(ImageJeton j: jetons)
			j.paintComponent(g);
		grille.paintComponent(g);
	}

	//---------------------------------------------------------------------------------------------
	//Getters et Setters
	public int getNbColonnes() {
		return nbColonnes;
	}
	public int getNbLignes() {
		return nbLignes;
	}
	public ImageFondJeu getFond() {
		return fond;
	}
	public ImageGrille getGrille() {
		return grille;
	}
	public ArrayList<ImageJeton> getJetons() {
		return jetons;
	}
}
