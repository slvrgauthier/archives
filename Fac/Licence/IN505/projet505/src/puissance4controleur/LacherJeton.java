package puissance4controleur;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JPanel;
import javax.swing.Timer;

import puissance4annotation.Controleur;
import puissance4modele.Jeton;
import puissance4ressource.*;
import puissance4vue.PanneauJeu;

@Controleur
public class LacherJeton extends JPanel implements ActionListener {
	private static final long serialVersionUID = 1L;
	private int y = 0;
	private ImageJeton image;
    private Timer declencheur;
	private int hauteur;
	private PanneauJeu panneau;
	
	public LacherJeton(int x, int largeur, int hauteur, Jeton jeton, ImageFondJeu fond, ImageGrille grille, PanneauJeu panneau) {
		this.panneau = panneau;
		this.hauteur = hauteur;
		image = new ImageJeton(x,y,jeton);
		panneau.getJetons().add(image);
		setPreferredSize(new Dimension(fond.getWidth(), fond.getHeight()));
		declencheur = new Timer(25, this);
		declencheur.start();
	}

	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == declencheur) {
			y+= 10; //vitesse de l'animation
			image.setY(y);
			if (y > hauteur-64) { //arrivée à la case voulue
				image.setY(hauteur-64);
				declencheur.stop();
			}
			panneau.repaint();
		}
	}

	public void paintComponent(Graphics g) {
		image.paintComponent(g);
	}
}
