package puissance4vue;

import java.awt.Graphics;
import javax.swing.JPanel;

import puissance4annotation.Vue;
import puissance4controleur.ClickImageAccueil;
import puissance4enumeration.Difficulte;
import puissance4ressource.ImageBoutonAccueil;
import puissance4ressource.ImageFondAccueil;

@Vue
public class PanneauAccueil extends JPanel {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private ImageFondAccueil fond = new ImageFondAccueil(0,0);
	private ImageBoutonAccueil debutant = new ImageBoutonAccueil(Difficulte.Debutant);
	private ImageBoutonAccueil intermediaire = new ImageBoutonAccueil(Difficulte.Intermediaire);
	private ImageBoutonAccueil confirme = new ImageBoutonAccueil(Difficulte.Confirme);
	
	public PanneauAccueil(final FenetreAccueil accueil) {
		//Ecoute des trois boutons d'accueil
		addMouseListener(new ClickImageAccueil(accueil,Difficulte.Debutant,debutant));
		addMouseListener(new ClickImageAccueil(accueil,Difficulte.Intermediaire,intermediaire));
		addMouseListener(new ClickImageAccueil(accueil,Difficulte.Confirme,confirme));
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		fond.paintComponent(g);
		debutant.paintComponent(g);
		intermediaire.paintComponent(g);
		confirme.paintComponent(g);
	}
}
