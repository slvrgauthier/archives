package puissance4controleur;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import puissance4annotation.Controleur;
import puissance4enumeration.Difficulte;
import puissance4exception.DifficulteDoesNotExistException;
import puissance4vue.FenetreJeu;
import puissance4vue.PanneauJeu;

@Controleur
public class NouveauJeuListener implements ActionListener{
	private FenetreJeu fenetre;
	private Difficulte difficulte;
	
	public NouveauJeuListener(FenetreJeu fenetre, Difficulte difficulte) {
		this.fenetre = fenetre;
		this.difficulte = difficulte;
	}
	
	public void actionPerformed(ActionEvent event){
		//Nettoyage de la fenêtre
		fenetre.clear();
		
		//Mise à jour
		try {
			switch(difficulte) {
			case Debutant :
				if(!(fenetre.getPanneau().getNbColonnes()==7)) { //S'il est nécessaire de changer, sinon erreur
					fenetre.setPanneau(new PanneauJeu(7,6,fenetre.getJeu()));
					fenetre.setSize(7*64, 7*64+20);
					fenetre.repaint();
				}
				break;
			case Intermediaire :
				if(!(fenetre.getPanneau().getNbColonnes()==9)) { //S'il est nécessaire de changer, sinon erreur
					fenetre.setPanneau(new PanneauJeu(9,7,fenetre.getJeu()));
					fenetre.setSize(9*64, 8*64+20);
					fenetre.repaint();
				}
				break;
			case Confirme :
				if(!(fenetre.getPanneau().getNbColonnes()==11)) { //S'il est nécessaire de changer, sinon erreur
					fenetre.setPanneau(new PanneauJeu(11,9,fenetre.getJeu()));
					fenetre.setSize(11*64, 10*64+20);
					fenetre.repaint();
				}
				break;
			default :
				throw new DifficulteDoesNotExistException();
			}
			
			//Nouveau jeu
			fenetre.getJeu().setDifficulte(difficulte);
			fenetre.getJeu().nouveauJeu(fenetre.getJeu().getNbParties());
		
		}catch(DifficulteDoesNotExistException e) {
			System.out.println(e.getDescription());
		}
	}
}
