package puissance4controleur;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import puissance4annotation.Controleur;
import puissance4enumeration.Difficulte;
import puissance4exception.DifficulteDoesNotExistException;
import puissance4ressource.ImageBoutonAccueil;
import puissance4vue.FenetreAccueil;
import puissance4vue.FenetreJeu;

@Controleur
public class ClickImageAccueil implements MouseListener {
	private FenetreAccueil accueil;
	private Difficulte difficulte;
	private ImageBoutonAccueil bouton;

	public ClickImageAccueil(final FenetreAccueil accueil, Difficulte difficulte, final ImageBoutonAccueil bouton) {
		this.accueil = accueil;
		this.difficulte = difficulte;
		this.bouton = bouton;
	}

	public void mouseClicked(MouseEvent event) {
		int x = event.getX();
		int y = event.getY();
		//Si le click est sur l'image
		if(x > bouton.getX() && x < bouton.getX()+bouton.getWidth() && y > bouton.getY() && y < bouton.getY()+bouton.getHeight()) {
			accueil.setVisible(false);
			try {
				new FenetreJeu(accueil, difficulte).setVisible(true);
			} catch (DifficulteDoesNotExistException e) {
				System.out.println(e.getDescription());
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

	public void mousePressed(MouseEvent event) {
		int x = event.getX();
		int y = event.getY();
		//Si le click est sur l'image
		if(x > bouton.getX() && x < bouton.getX()+bouton.getWidth() && y > bouton.getY() && y < bouton.getY()+bouton.getHeight())
			bouton.setSurbrillance(true);
		accueil.repaint();
	}

	public void mouseReleased(MouseEvent event) {
		bouton.setSurbrillance(false);
		accueil.repaint();
	}

}
