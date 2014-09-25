package puissance4vue;

import java.awt.event.*;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;

import puissance4annotation.Vue;
import puissance4controleur.*;
import puissance4enumeration.*;
import puissance4exception.*;
import puissance4modele.*;
import puissance4ressource.Profile;

@Vue
public class FenetreJeu extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private PanneauJeu panneau;
	private Jeu jeu;
	private ArrayList<Profile> profiles = new ArrayList<Profile>();
	
	public FenetreJeu(final FenetreAccueil accueil, Difficulte difficulte) throws DifficulteDoesNotExistException {
		//Fenetre
		super();
		jeu = new Jeu(difficulte);
		
		switch(difficulte) {
			case Debutant : 
				setSize(7*64,7*64+20);
				panneau = new PanneauJeu(7,6,jeu);
				break;
			case Intermediaire : 
				setSize(9*64,8*64+20);
				panneau = new PanneauJeu(9,7,jeu);
				break;
			case Confirme :
				setSize(11*64,10*64+20);
				panneau = new PanneauJeu(11,9,jeu);
				break;
			default :
				throw new DifficulteDoesNotExistException();
		}

		Joueur j1 = jeu.getJoueur(0), j2 = jeu.getJoueur(1);
		setTitle("["+j1.getJeton().getCouleur()+","+j1.getJeton().getForme()+"] "+j1.getNom()+" vs "+j2.getNom()+" ["+j2.getJeton().getCouleur()+","+j2.getJeton().getForme()+"]");
		setResizable(false);
		setLocationRelativeTo(null); //Milieu de l'écran
		
		//Opérations d'ouverture et fermeture de la fenêtre
		addWindowListener(new WindowAdapter() {
			//fermeture
			public void windowClosing(WindowEvent e) {
				if(jeu.isAutoSave())
					try {
						panneau.save(new File("Sauvegardes/auto_save.sp4"));
					} catch (IOException ex) {
						JOptionPane.showMessageDialog(null, "Erreur de sauvegarde automatique");
					}
				else
					save();
				saveProfile();
			}

			//ouverture
			public void windowOpened(WindowEvent arg0) {
				loadProfile();
			}
		});
		
		//Panneau contenant la grille
		add(panneau);

		//Menu
		JMenuBar menuBar=new JMenuBar();
		
		JMenu menuPartie=new JMenu("Partie");
		/**/JMenu menuNouvellePartie=new JMenu("Nouvelle Partie");
		/*----*/JMenuItem menuItemPartieDebutant=new JMenuItem("Débutant");
		/*----*/JMenuItem menuItemPartieIntermediaire=new JMenuItem("Intermédiaire");
		/*----*/JMenuItem menuItemPartieConfirme=new JMenuItem("Confirmé");
		/**/JMenuItem menuItemOuvrirPartie=new JMenuItem("Ouvrir");
		/**/JMenuItem menuItemSauverPartie=new JMenuItem("Sauver");
		/**/JMenuItem menuItemAccueil=new JMenuItem("Accueil");
		
		menuPartie.add(menuNouvellePartie);
		/**/menuNouvellePartie.add(menuItemPartieDebutant);
		/**/menuNouvellePartie.add(menuItemPartieIntermediaire);
		/**/menuNouvellePartie.add(menuItemPartieConfirme);
		menuPartie.add(menuItemOuvrirPartie);
		menuPartie.addSeparator();
		menuPartie.add(menuItemSauverPartie);
		menuPartie.addSeparator();
		menuPartie.add(menuItemAccueil);
		
		JMenu menuJeu=new JMenu("Jeu");
		/**/JMenuItem menuNouveauJeu=new JMenu("Nouveau Jeu");
		/*----*/JMenuItem menuItemJeuDebutant=new JMenuItem("Débutant");
		/*----*/JMenuItem menuItemJeuIntermediaire=new JMenuItem("Intermédiaire");
		/*----*/JMenuItem menuItemJeuConfirme=new JMenuItem("Confirmé");
		/**/JMenuItem menuItemChangerJoueur=new JMenuItem("Changer de joueurs");
		/**/JMenuItem menuItemChangerJeton=new JMenuItem("Changer de jeton");
		/**/JMenuItem menuItemOption=new JMenuItem("Options");
		
		menuJeu.add(menuNouveauJeu);
		/**/menuNouveauJeu.add(menuItemJeuDebutant);
		/**/menuNouveauJeu.add(menuItemJeuIntermediaire);
		/**/menuNouveauJeu.add(menuItemJeuConfirme);
		menuJeu.addSeparator();
		menuJeu.add(menuItemChangerJoueur);
		menuJeu.add(menuItemChangerJeton);
		menuJeu.addSeparator();
		menuJeu.add(menuItemOption);
		
		menuBar.add(menuPartie);
		menuBar.add(menuJeu);
		setJMenuBar(menuBar);
		
		//Actions du menu
		menuItemPartieDebutant.addActionListener(new NouvellePartieListener(this,Difficulte.Debutant));
		menuItemPartieIntermediaire.addActionListener(new NouvellePartieListener(this,Difficulte.Intermediaire));
		menuItemPartieConfirme.addActionListener(new NouvellePartieListener(this,Difficulte.Confirme));
		
		menuItemOuvrirPartie.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent event){
				restore();
			}
		});
		menuItemSauverPartie.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent event){
				save();
			}
		});
		menuItemAccueil.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent event){
				setVisible(false);
				if(jeu.isAutoSave())
					try {
						panneau.save(new File("Sauvegardes/auto_save.sp4"));
					} catch (IOException e) {
						JOptionPane.showMessageDialog(null, "Erreur de sauvegarde automatique");
					}
				saveProfile();
				accueil.setVisible(true);
			}
		});

		menuItemJeuDebutant.addActionListener(new NouveauJeuListener(this,Difficulte.Debutant));
		menuItemJeuIntermediaire.addActionListener(new NouveauJeuListener(this,Difficulte.Intermediaire));
		menuItemJeuConfirme.addActionListener(new NouveauJeuListener(this,Difficulte.Confirme));
		
		menuItemChangerJoueur.addActionListener(new ChangerJoueurListener(this));
		menuItemChangerJeton.addActionListener(new ChangerJetonListener(this));
		menuItemOption.addActionListener(new OptionListener(this));
	}
	
	//Fonctionnalités
	public void clear(){
		panneau.clear();
	}
	
	public void save(){
		File Fic = null;
		JFileChooser chooser = new JFileChooser();
		boolean overwrite = true;
		//paramétrage du JFileChooser
        chooser.setDialogTitle("Sauvegarder le jeu");
        chooser.setCurrentDirectory(new File("Sauvegardes/"));
		chooser.setFileFilter(new FileNameExtensionFilter("Slvr-Puissance4 Save File (*.sp4)", "sp4"));
		//lancement et traitement
		int rep = chooser.showSaveDialog(this);
		if(rep == JFileChooser.APPROVE_OPTION) {
			Fic = chooser.getSelectedFile();
			if(!Fic.getName().toLowerCase().endsWith(".sp4")) { //Ajout auto de l'extension
				Fic = new File(Fic.getPath()+".sp4");
			}
			if(Fic.exists()) { //Confirmation de réécriture
				if(JOptionPane.showConfirmDialog(chooser,"Voulez-vous écraser le fichier existant ?","Attention",JOptionPane.YES_NO_OPTION) == JOptionPane.NO_OPTION)
					overwrite = false;
			}
		}
		if(rep != JFileChooser.CANCEL_OPTION && overwrite) { //Aucune erreur si cancel
			try {
				panneau.save(Fic);
			} catch(IOException e) {
				JOptionPane.showMessageDialog(null, "Erreur de sauvegarde");
			}
		}
	}
	
	public void restore(){
		//Données à sauver
		saveProfile();
		if(jeu.isAutoSave())
			try {
				panneau.save(new File("Sauvegardes/auto_save.sp4"));
			} catch (IOException ex) {
				JOptionPane.showMessageDialog(null, "Erreur de sauvegarde automatique");
			}
		
		//Restauration du jeu
		File Fic = null;
		JFileChooser chooser = new JFileChooser();
		//paramétrage du JFileChooser
        chooser.setDialogTitle("Restaurer un jeu");
        chooser.setCurrentDirectory(new File("Sauvegardes/"));
		chooser.setFileFilter(new FileNameExtensionFilter("Slvr-Puissance4 Save File (*.sp4)", "sp4"));
		//lancement et traitement
		int rep = chooser.showOpenDialog(this);
		if(rep == JFileChooser.APPROVE_OPTION)
			Fic = chooser.getSelectedFile();
		if(rep != JFileChooser.CANCEL_OPTION) { //Aucune erreur si cancel
			try {
				jeu = panneau.restore(Fic, this);
			} catch(Exception e) {
				JOptionPane.showMessageDialog(null, "Erreur de restauration");
			}
		}
		
		//Chargement des profiles (utile pour joueurs courants)
		loadProfile();

		//Mise à jour du titre
		setTitle("["+jeu.getJoueur(0).getJeton().getCouleur()+","+jeu.getJoueur(0).getJeton().getForme()+"] "+jeu.getJoueur(0).getNom()+" vs "+jeu.getJoueur(1).getNom()+" ["+jeu.getJoueur(1).getJeton().getCouleur()+","+jeu.getJoueur(1).getJeton().getForme()+"]");
	}
	
	public void saveProfile() {
		//Ajout si les profiles n'existent pas
		if(!new File("Sauvegardes/Profiles/"+jeu.getJoueur(0).getNom()).exists())
			profiles.add(new Profile(jeu.getJoueur(0)));
		if(!new File("Sauvegardes/Profiles/"+jeu.getJoueur(1).getNom()).exists())
			profiles.add(new Profile(jeu.getJoueur(1)));
		
		//Mise à jour des profiles
		for(Profile p: profiles) {
			for(Joueur j: jeu.getJoueurs())
				if(j.getNom().equals(p.getJoueur().getNom())) {
					p.setJoueur(j);
				}
		}

		//Sauvegarde de tous les profiles
		for(Profile p: profiles) {
			if(!(p.getJoueur().getNom().equals("Joueur 1") || p.getJoueur().getNom().equals("Joueur 2"))) {
				ObjectOutputStream flotS;
				try {
					flotS = new ObjectOutputStream(new FileOutputStream("Sauvegardes/Profiles/"+p.getJoueur().getNom()));
					flotS.writeObject((Profile)p);
					flotS.close();
				} catch (FileNotFoundException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}
	
	public void loadProfile() {
		profiles.clear();
		
		//Charger tous les profiles existants
		File Fic[] = new File("Sauvegardes/Profiles/").listFiles();
		for(File f: Fic) {
			ObjectInputStream flotE;
			try {
				flotE = new ObjectInputStream(new FileInputStream(f));
				profiles.add((Profile)flotE.readObject());
				flotE.close();
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (ClassNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		//Charger les profiles des joueurs courants
		for(Profile p: profiles) {
			for(Joueur j: jeu.getJoueurs())
				if(j.getNom().equals(p.getJoueur().getNom())) {
					p.load(jeu, jeu.getJoueurs().indexOf(j));					
				}
		}
	}
	
	//---------------------------------------------------------------------------------------------
	//Getters et Setters
	public PanneauJeu getPanneau() {
		return panneau;
	}
	public void setPanneau(PanneauJeu panneau) {
		this.panneau = panneau;
		setContentPane(panneau);
		repaint();
	}
	public Jeu getJeu() {
		return jeu;
	}
}
