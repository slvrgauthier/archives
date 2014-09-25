package puissance4controleur;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JPanel;

import puissance4annotation.Controleur;
import puissance4modele.Jeu;
import puissance4modele.Joueur;
import puissance4ressource.ImageLacher;
import puissance4vue.PanneauJeu;

@Controleur
public class ClickImageLacher extends JPanel implements MouseListener {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private ImageLacher lacher;
	private PanneauJeu panneau;
	private Jeu jeu;

	public ClickImageLacher(ImageLacher lacher, PanneauJeu panneau, Jeu jeu) {
		this.lacher = lacher;
		this.panneau = panneau;
		this.jeu = jeu;
	}
	
	public void mouseClicked(MouseEvent event) {
		int x = event.getX();
		int y = event.getY();
		//Si le click est sur l'image
		if(x > lacher.getX() && x < lacher.getX()+lacher.getWidth() && y > lacher.getY() && y < lacher.getY()+lacher.getHeight()) {
			int ligne = -1; //erreur
			Joueur actif;
			if(jeu.getJoueur(0).isTour())
				actif = jeu.getJoueur(0);
			else
				actif = jeu.getJoueur(1);
			ligne = actif.lacherJeton(lacher.getX()/64);
			if(ligne != -1) {
				//Animation du jeton qui tombe
				panneau.add(new LacherJeton(lacher.getX(), panneau.getGrille().getWidth(), panneau.getGrille().getHeight()-(ligne*64), actif.getJeton(), panneau.getFond(), panneau.getGrille(),panneau));
				panneau.repaint();
			}
		}
	}

	@Override
	public void mouseEntered(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

}
