package puissance4controleur;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;

import puissance4annotation.Controleur;
import puissance4modele.Jeu;
import puissance4vue.FenetreJeu;

@Controleur
public class OptionListener implements ActionListener{
	private FenetreJeu fenetre;
	private OptionDialog dialog = null;

	public OptionListener(FenetreJeu fenetre) {
		this.fenetre = fenetre;
	}

	public void actionPerformed(ActionEvent e) {
		if(dialog == null)
			dialog = new OptionDialog(fenetre,true);
		OptionDialogInfo info = dialog.showOptionDialog();
		Jeu jeu = fenetre.getJeu();
		jeu.setAutoSave(info.isAutoSave());
		jeu.setNbParties(info.getNbParties());
		jeu.setTimeOut(info.getTimeOut()); //timeOut non implémenté (cf Partie.java)
	}
}

class OptionDialogInfo {
	private boolean autoSave;
	private int nbParties;
	private int timeOut;
	
	public OptionDialogInfo(){}
	public OptionDialogInfo(boolean autoSave, int nbParties, int timeOut){
		this.autoSave = autoSave;
		this.nbParties = nbParties;
		this.timeOut = timeOut;
	}

	//------------------------------------------------------------------------------------------------------------
	//Getters et Setters
	public boolean isAutoSave() {
		return autoSave;
	}
	public int getNbParties() {
		return nbParties;
	}
	public int getTimeOut() {
		return timeOut;
	}
}

class OptionDialog extends JDialog {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private OptionDialogInfo info = new OptionDialogInfo();
	private JLabel part, time;
	private JCheckBox autosave;
	private JComboBox<Integer> nbPart, timeout;

	public OptionDialog(FenetreJeu fenetre, boolean modal){
		super(fenetre, "Paramétrage des options", modal);
		this.setSize(300, 160);
		this.setLocationRelativeTo(null);
		this.setResizable(false);
		this.setDefaultCloseOperation(JDialog.DO_NOTHING_ON_CLOSE);
		this.initComponent();
	}

	public OptionDialogInfo showOptionDialog(){
		this.setVisible(true);      
		return this.info;      
	}

	private void initComponent(){
		JPanel pan = new JPanel();
		pan.setPreferredSize(new Dimension(280, 140));
		pan.setBorder(BorderFactory.createTitledBorder("Options :"));
		autosave = new JCheckBox("Activer la sauvegarde automatique", true);
		pan.add(autosave);
		part = new JLabel("Nombre de parties par jeu :");
		pan.add(part);
		nbPart = new JComboBox<Integer>();
		for(int i=3;i<11;i++)
			nbPart.addItem(i);
		nbPart.setSelectedItem(3);
		pan.add(nbPart);
		time = new JLabel("Limite de temps :");
		pan.add(time);
		timeout = new JComboBox<Integer>();
		for(int i=10;i<61;i+=5)
			timeout.addItem(i);
		timeout.setSelectedItem(30);
		pan.add(timeout);
		

		JPanel content = new JPanel();
		content.add(pan);

		JPanel control = new JPanel();
		JButton okBouton = new JButton("OK");

		okBouton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent arg0) {
				info = new OptionDialogInfo(autosave.isSelected(), ((Integer)nbPart.getSelectedItem()).intValue(), ((Integer)timeout.getSelectedItem()).intValue());
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
