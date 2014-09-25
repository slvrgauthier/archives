package puissance4vue;

import javax.swing.JFrame;

import puissance4annotation.*;
import puissance4modele.*;

@Vue
public class FenetreAccueil extends JFrame{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private PanneauAccueil panneau = new PanneauAccueil(this);

	public FenetreAccueil() {
		super();

		setTitle("Slvr - Puissance 4");
		setSize(400,500);
		setResizable(false);
		setLocationRelativeTo(null); //Milieu de l'écran
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		add(panneau);
	}
	public static void main(String args[]) {
		FenetreAccueil f=new FenetreAccueil();
		f.setVisible(true);
		
		//Invariant d'annotation
		assert ((Case.class.isAnnotationPresent(Modele.class)
					&& Colonne.class.isAnnotationPresent(Modele.class)
					&& Grille.class.isAnnotationPresent(Modele.class)
					&& Jeton.class.isAnnotationPresent(Modele.class)
					&& Jeu.class.isAnnotationPresent(Modele.class)
					&& Joueur.class.isAnnotationPresent(Modele.class)
					&& Partie.class.isAnnotationPresent(Modele.class))
				&&
				!(Case.class.isAnnotationPresent(Vue.class)
						|| Colonne.class.isAnnotationPresent(Vue.class)
						|| Grille.class.isAnnotationPresent(Vue.class)
						|| Jeton.class.isAnnotationPresent(Vue.class)
						|| Jeu.class.isAnnotationPresent(Vue.class)
						|| Joueur.class.isAnnotationPresent(Vue.class)
						|| Partie.class.isAnnotationPresent(Vue.class))) 
				: "Main : le Modèle fait référence à la Vue";
	}
}
