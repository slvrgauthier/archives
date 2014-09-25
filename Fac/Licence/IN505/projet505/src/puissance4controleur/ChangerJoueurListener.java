package puissance4controleur;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import puissance4annotation.Controleur;
import puissance4modele.Joueur;
import puissance4vue.FenetreJeu;

@Controleur
public class ChangerJoueurListener implements ActionListener{
	private FenetreJeu fenetre;
	private ChangerJoueurDialog dialog = null;

	public ChangerJoueurListener(FenetreJeu fenetre) {
		this.fenetre = fenetre;
	}

	public void actionPerformed(ActionEvent e) {
		fenetre.saveProfile();

		Joueur j1 = fenetre.getJeu().getJoueur(0), j2 = fenetre.getJeu().getJoueur(1);
		if(dialog == null)
			dialog = new ChangerJoueurDialog(fenetre,true,j1.getNom(),j2.getNom());
		ChangerJoueurDialogInfo info = dialog.showChangerJoueurDialog();

		//Mise à jour des joueurs
		j1 = new Joueur(info.getNomJ1(), fenetre.getJeu(), j1.getJeton());
		fenetre.getJeu().setJoueur(0,j1);
		j2 = new Joueur(info.getNomJ2(), fenetre.getJeu(), j2.getJeton());
		fenetre.getJeu().setJoueur(1,j2);

		fenetre.loadProfile();
		fenetre.setTitle("["+j1.getJeton().getCouleur()+","+j1.getJeton().getForme()+"] "+j1.getNom()+" vs "+j2.getNom()+" ["+j2.getJeton().getCouleur()+","+j2.getJeton().getForme()+"]");

	}
}

class ChangerJoueurDialogInfo {
	private String nomJ1, nomJ2;

	public ChangerJoueurDialogInfo(){
		nomJ1 = "Joueur 1";
		nomJ2 = "Joueur 2";
	}

	public ChangerJoueurDialogInfo(String nomJ1, String nomJ2){
		this.nomJ1 = nomJ1;
		this.nomJ2 = nomJ2;
	}

	//-------------------------------------------------------------------------------------------
	//Getters et Setters
	public String getNomJ1() {
		return nomJ1;
	}

	public String getNomJ2() {
		return nomJ2;
	}
}

class ChangerJoueurDialog extends JDialog {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String n1, n2;
	private ChangerJoueurDialogInfo info = new ChangerJoueurDialogInfo();
	private JLabel nomJ1, nomJ2;
	private JTextField field1, field2;

	public ChangerJoueurDialog(FenetreJeu fenetre, boolean modal, String n1, String n2){
		super(fenetre, "Paramétrage des joueurs", modal);
		this.n1 = n1;
		this.n2 = n2;
		this.setSize(550, 270);
		this.setLocationRelativeTo(null);
		this.setResizable(false);
		this.setDefaultCloseOperation(JDialog.DO_NOTHING_ON_CLOSE);
		this.initComponent();
	}

	public ChangerJoueurDialogInfo showChangerJoueurDialog(){
		this.setVisible(true);      
		return this.info;      
	}

	private void initComponent(){

		//Le nom du joueur 1
		JPanel panNom1 = new JPanel();
		panNom1.setPreferredSize(new Dimension(220, 80));
		field1 = new JTextField();
		field1.setPreferredSize(new Dimension(100, 25));
		panNom1.setBorder(BorderFactory.createTitledBorder("Nom du joueur 1 :"));
		nomJ1 = new JLabel("Saisir un nom :");
		panNom1.add(nomJ1);
		panNom1.add(field1);

		//Le nom du joueur 2
		JPanel panNom2 = new JPanel();
		panNom2.setPreferredSize(new Dimension(220, 80));
		field2 = new JTextField();
		field2.setPreferredSize(new Dimension(100, 25));
		panNom2.setBorder(BorderFactory.createTitledBorder("Nom du joueur 2 :"));
		nomJ2 = new JLabel("Saisir un nom :");
		panNom2.add(nomJ2);
		panNom2.add(field2);

		JPanel content = new JPanel();
		content.add(panNom1);
		content.add(panNom2);

		JPanel control = new JPanel();
		JButton okBouton = new JButton("OK");

		okBouton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent arg0) {
				if(!field1.getText().equals(""))
					n1 = field1.getText();
				if(!field2.getText().equals(""))
					n2 = field2.getText();
				info = new ChangerJoueurDialogInfo(n1, n2);
				setVisible(false);
			}     
		});

		JButton cancelBouton = new JButton("Annuler");
		cancelBouton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent arg0) {
				setVisible(false);
			}      
		});

		control.add(okBouton);
		control.add(cancelBouton);

		this.getContentPane().add(content, BorderLayout.CENTER);
		this.getContentPane().add(control, BorderLayout.SOUTH);
	}  
}
