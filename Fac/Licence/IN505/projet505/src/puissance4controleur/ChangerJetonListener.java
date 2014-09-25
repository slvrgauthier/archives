package puissance4controleur;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.BorderFactory;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;

import puissance4annotation.Controleur;
import puissance4enumeration.Couleur;
import puissance4enumeration.Forme;
import puissance4exception.FormeDoesNotExistException;
import puissance4modele.Jeton;
import puissance4modele.Joueur;
import puissance4vue.FenetreJeu;

@Controleur
public class ChangerJetonListener implements ActionListener{
	private FenetreJeu fenetre;
	private ChangerJetonDialog dialog = null;

	public ChangerJetonListener(FenetreJeu fenetre) {
		this.fenetre = fenetre;
	}

	public void actionPerformed(ActionEvent e) {
		Joueur j1 = fenetre.getJeu().getJoueur(0), j2 = fenetre.getJeu().getJoueur(1);

		if(dialog == null)
			dialog = new ChangerJetonDialog(fenetre,true,j1.getJeton(),j2.getJeton());
		ChangerJetonDialogInfo info = dialog.showChangerJetonDialog();

		j1.getJeton().setCouleur(info.getCouleurJ1());
		j1.getJeton().setForme(info.getFormeJ1());
		j2.getJeton().setCouleur(info.getCouleurJ2());
		j2.getJeton().setForme(info.getFormeJ2());
		fenetre.saveProfile();
		fenetre.loadProfile();
		fenetre.setTitle("["+j1.getJeton().getCouleur()+","+j1.getJeton().getForme()+"] "+j1.getNom()+" vs "+j2.getNom()+" ["+j2.getJeton().getCouleur()+","+j2.getJeton().getForme()+"]");
	}
}

class ChangerJetonDialogInfo {
	private Couleur couleurJ1, couleurJ2;
	private Forme formeJ1, formeJ2;

	public ChangerJetonDialogInfo(){}
	public ChangerJetonDialogInfo(Couleur couleurJ1, Couleur couleurJ2, Forme formeJ1, Forme formeJ2){
		this.couleurJ1 = couleurJ1;
		this.couleurJ2 = couleurJ2;
		this.formeJ1 = formeJ1;
		this.formeJ2 = formeJ2;
	}
	
	//---------------------------------------------------------------------------------------------
	//Getters et Setters
	public Couleur getCouleurJ1() {
		return couleurJ1;
	}
	public Couleur getCouleurJ2() {
		return couleurJ2;
	}
	public Forme getFormeJ1() {
		return formeJ1;
	}
	public Forme getFormeJ2() {
		return formeJ2;
	}
}

class ChangerJetonDialog extends JDialog {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private Jeton j1, j2;
	private ChangerJetonDialogInfo info = new ChangerJetonDialogInfo();
	private JLabel couleurJ1, couleurJ2, formeJ1, formeJ2;
	private JRadioButton rond1, rond2, carre1, carre2, rdente1, rdente2, cdente1, cdente2;
	private JComboBox<Couleur> couleur1, couleur2;

	public ChangerJetonDialog(FenetreJeu fenetre, boolean modal, Jeton j1, Jeton j2){
		super(fenetre, "Paramétrage des jetons", modal);
		this.j1 = j1;
		this.j2 = j2;
		this.setSize(550, 270);
		this.setLocationRelativeTo(null);
		this.setResizable(false);
		this.setDefaultCloseOperation(JDialog.DO_NOTHING_ON_CLOSE);
		this.initComponent();
	}

	public ChangerJetonDialogInfo showChangerJetonDialog(){
		this.setVisible(true);      
		return this.info;      
	}

	private void initComponent(){
		//Joueur 1
		JPanel pan1 = new JPanel();
		pan1.setPreferredSize(new Dimension(220, 260));
		pan1.setBorder(BorderFactory.createTitledBorder("Jeton du joueur 1 :"));
		couleurJ1 = new JLabel("Choisir la couleur :");
		pan1.add(couleurJ1);
		couleur1 = new JComboBox<Couleur>();
		couleur1.addItem(Couleur.Bleu);
		couleur1.addItem(Couleur.Gris);
		couleur1.addItem(Couleur.Jaune);
		couleur1.addItem(Couleur.Rouge);
		couleur1.addItem(Couleur.Vert);
		couleur1.addItem(Couleur.Violet);
		//Activer la bonne couleur
		couleur1.setSelectedItem(j1.getCouleur());
		pan1.add(couleur1);
		formeJ1 = new JLabel("Choisir la forme :");
		pan1.add(formeJ1);
		rond1 = new JRadioButton("Rond");
		rdente1 = new JRadioButton("Rond Denté");
		carre1 = new JRadioButton("Carré");
		cdente1 = new JRadioButton("Carré Denté");
		//Activer le bon bouton
		try  {
			switch(j1.getForme()) {
			case Rond :
				rond1.setSelected(true);
				break;
			case RondDente :
				rdente1.setSelected(true);
				break;
			case Carre :
				carre1.setSelected(true);
				break;
			case CarreDente :
				cdente1.setSelected(true);
				break;
			default :
				throw new FormeDoesNotExistException();
			}
		}catch(FormeDoesNotExistException e) {
			System.out.println(e.getDescription());
		}
		ButtonGroup bg1 = new ButtonGroup();
		bg1.add(rond1);
		bg1.add(rdente1);
		bg1.add(carre1);
		bg1.add(cdente1);
		pan1.add(rond1);
		pan1.add(rdente1);
		pan1.add(carre1);
		pan1.add(cdente1);

		//Joueur 2
		JPanel pan2 = new JPanel();
		pan2.setPreferredSize(new Dimension(220, 260));
		pan2.setBorder(BorderFactory.createTitledBorder("Jeton du joueur 2 :"));
		couleurJ2 = new JLabel("Choisir la couleur :");
		pan2.add(couleurJ2);
		couleur2 = new JComboBox<Couleur>();
		couleur2.addItem(Couleur.Bleu);
		couleur2.addItem(Couleur.Gris);
		couleur2.addItem(Couleur.Jaune);
		couleur2.addItem(Couleur.Rouge);
		couleur2.addItem(Couleur.Vert);
		couleur2.addItem(Couleur.Violet);
		//Activer la bonne couleur
		couleur2.setSelectedItem(j2.getCouleur());
		pan2.add(couleur2);
		formeJ2 = new JLabel("Choisir la forme :");
		pan2.add(formeJ2);
		rond2 = new JRadioButton("Rond", true);
		rdente2 = new JRadioButton("Rond Denté");
		carre2 = new JRadioButton("Carré");
		cdente2 = new JRadioButton("Carré Denté");
		//Activer le bon bouton
		try  {
			switch(j2.getForme()) {
			case Rond :
				rond2.setSelected(true);
				break;
			case RondDente :
				rdente2.setSelected(true);
				break;
			case Carre :
				carre2.setSelected(true);
				break;
			case CarreDente :
				cdente2.setSelected(true);
				break;
			default :
				throw new FormeDoesNotExistException();
			}
		}catch(FormeDoesNotExistException e) {
			System.out.println(e.getDescription());
		}
		ButtonGroup bg2 = new ButtonGroup();
		bg2.add(rond2);
		bg2.add(rdente2);
		bg2.add(carre2);
		bg2.add(cdente2);
		pan2.add(rond2);
		pan2.add(rdente2);
		pan2.add(carre2);
		pan2.add(cdente2);

		JPanel content = new JPanel();
		content.add(pan1);
		content.add(pan2);

		JPanel control = new JPanel();
		JButton okBouton = new JButton("OK");

		okBouton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent arg0) {
				Forme f1, f2;
				f1 = (rond1.isSelected()) ? Forme.Rond : (rdente1.isSelected()) ? Forme.RondDente : (carre1.isSelected()) ? Forme.Carre : (cdente1.isSelected()) ? Forme.CarreDente : Forme.Rond;
				f2 = (rond2.isSelected()) ? Forme.Rond : (rdente2.isSelected()) ? Forme.RondDente : (carre2.isSelected()) ? Forme.Carre : (cdente2.isSelected()) ? Forme.CarreDente : Forme.Rond;
				info = new ChangerJetonDialogInfo((Couleur) couleur1.getSelectedItem(), (Couleur) couleur2.getSelectedItem(), f1, f2);
				setVisible(false);
			}  
		});

		JButton cancelBouton = new JButton("Annuler");
		cancelBouton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent arg0) {
				info = new ChangerJetonDialogInfo(j1.getCouleur(),j2.getCouleur(),j1.getForme(),j2.getForme());
				setVisible(false);
			}      
		});

		control.add(okBouton);
		control.add(cancelBouton);

		this.getContentPane().add(content, BorderLayout.CENTER);
		this.getContentPane().add(control, BorderLayout.SOUTH);
	}
}
