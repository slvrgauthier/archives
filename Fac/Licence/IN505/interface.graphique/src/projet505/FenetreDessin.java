package projet505;

import java.util.ArrayList;
import java.io.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.filechooser.*;

public class FenetreDessin extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private PanneauRect panneau=new PanneauRect();
	
	public FenetreDessin() {
		//Fenetre
		super();
		setTitle("Slvr-app");
		setSize(500,500);
		setLocation(100,100);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		//Panneau de dessin
		add(panneau);
		
		//Menu
		JMenuBar menuBar=new JMenuBar();
		
		JMenu menu1=new JMenu("Fichier");
		
		JMenuItem menuItem1_1=new JMenuItem("Nouveau");
		JMenuItem menuItem1_2=new JMenuItem("Ouvrir");
		JMenuItem menuItem1_3=new JMenuItem("Sauver");
		JMenuItem menuItem1_4=new JMenuItem("Fermer");
		
		menu1.add(menuItem1_1);
		menu1.add(menuItem1_2);
		menu1.addSeparator();
		menu1.add(menuItem1_3);
		menu1.addSeparator();
		menu1.add(menuItem1_4);
		
		JMenu menu2=new JMenu("Edition");
		
		JMenuItem menuItem2_1=new JMenuItem("Défaire");
		JMenuItem menuItem2_2=new JMenuItem("Refaire");
		JMenuItem menuItem2_3=new JMenuItem("Options");
		
		menu2.add(menuItem2_1);
		menu2.add(menuItem2_2);
		menu2.addSeparator();
		menu2.add(menuItem2_3);
		
		menuBar.add(menu1);
		menuBar.add(menu2);
		setJMenuBar(menuBar);
		
		//Actions du menu (seul le menu "Fichier" est implémenté)
		menuItem1_1.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent event){
				clear();
			}
		});
		menuItem1_2.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent event){
				restore();
			}
		});
		menuItem1_3.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent event){
				save();
			}
		});
		menuItem1_4.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent event){
				System.exit(0);
			}
		});
	}
	
	//Fonctionnalités
	public void clear(){
		//Sauvegarde automatique du dessin en cours
		File Fic = new File("./bin/projet505/sauvegardes/auto_save.ssf");
		try {
			panneau.save(Fic);
		} catch(IOException e) {
			JOptionPane.showMessageDialog(null, "Erreur de sauvegarde automatique");
		}
		//Effacement du dessin
		panneau.clear();
	}
	
	public void save(){
		File Fic = null;
		JFileChooser chooser = new JFileChooser();
		boolean overwrite = false;
		//Paramétrage du JFileChooser
        chooser.setDialogTitle("Sauver la figure");
        chooser.setCurrentDirectory(new File("./bin/projet505/sauvegardes/"));
		chooser.setFileFilter(new FileNameExtensionFilter("Slvr-app Save File (*.ssf)", "ssf"));
		//Lancement et traitement
		int rep = chooser.showSaveDialog(this);
		if(rep == JFileChooser.APPROVE_OPTION) {
			Fic = chooser.getSelectedFile();
			if(!Fic.getName().toLowerCase().endsWith(".ssf")) { //Ajout auto de l'extension
				Fic = new File(Fic.getPath()+".ssf");
			}
			if(Fic.exists()) { //Confirmation de réécriture
				if(JOptionPane.showConfirmDialog(chooser,"Voulez-vous écraser le fichier existant ?","Attention",JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION)
					overwrite = true;
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
		File Fic = null;
		JFileChooser chooser = new JFileChooser();
		//Paramétrage du JFileChooser
        chooser.setDialogTitle("Restaurer une figure");
        chooser.setCurrentDirectory(new File("./bin/projet505/sauvegardes/"));
		chooser.setFileFilter(new FileNameExtensionFilter("Slvr-app Save File (*.ssf)", "ssf"));
		//Lancement et traitement
		int rep = chooser.showOpenDialog(this);
		if(rep == JFileChooser.APPROVE_OPTION)
			Fic = chooser.getSelectedFile();
		if(rep != JFileChooser.CANCEL_OPTION) { //Aucune erreur si cancel
			try {
				panneau.restore(Fic);
			} catch(Exception e) {
				JOptionPane.showMessageDialog(null, "Erreur de restauration");
			}
		}
	}
	
	public static void main(String args[]) {
		FenetreDessin f=new FenetreDessin();
		f.setVisible(true);
	}
}

class PanneauRect extends JPanel {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private ArrayList<Rectangle> figures=new ArrayList<Rectangle>();
	private boolean _canDrag=false, _doubleClick=false;
	private int _posRect=-1, _posDoubleClick=-1, _dragFromX=0, _dragFromY=0;
	
	public PanneauRect() {
		addMouseListener( new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				int x=e.getX(), y=e.getY();
				
				for(Rectangle r: figures) {
					if(x>=r.x && x<=r.x+25 && y>=r.y && y<=r.y+25) {
						if(e.getClickCount()==2) {
							_posDoubleClick=figures.indexOf(r);
							_doubleClick=true;
						}
						else {
							_doubleClick=false;
						}
						_canDrag=true; 
						_posRect=figures.indexOf(r);
						_dragFromX = x - r.x;
						_dragFromY = y - r.y;
					}
				}
				if(_doubleClick) {
					figures.remove(_posDoubleClick);
				}
				if(_canDrag==false) {
					figures.add(new Rectangle(x-12, y-12, 25, 25));
				}
				repaint();
			}
			public void mouseReleased(MouseEvent e) {
				_canDrag=false;
				_posRect=-1;
				_doubleClick=false;
			}
		});
		addMouseMotionListener(new MouseMotionAdapter() {
			public void mouseDragged(MouseEvent e) {
				if (_canDrag) {
					int x=e.getX(), y=e.getY();
					
					Rectangle rectDrag=figures.get(_posRect);
		            rectDrag.x = x - _dragFromX;
		            rectDrag.y = y - _dragFromY;
		            
		            rectDrag.x = Math.max(rectDrag.x, 0);
		            rectDrag.x = Math.min(rectDrag.x, getWidth() - 25);
		            
		            rectDrag.y = Math.max(rectDrag.y, 0);
		            rectDrag.y = Math.min(rectDrag.y, getHeight() - 25);
		            
		            repaint();
		        }
			}
		});
	}
	
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		for(Rectangle r: figures) {
			g.drawRect((int)r.getX(), (int)r.getY(), (int)r.getWidth(), (int)r.getHeight());
		}
	}
	
	//Fonctionnalités
	public void clear(){
		figures.clear();
		repaint();
	}
	
	public void save(File Fic) throws IOException{
		ObjectOutputStream flotS=new ObjectOutputStream(new FileOutputStream(Fic));
		flotS.writeObject(figures);
		flotS.close();
	}
	
	@SuppressWarnings("unchecked")
	public void restore(File Fic) throws IOException,ClassNotFoundException{
		ObjectInputStream flotE = new ObjectInputStream(new FileInputStream(Fic));
		Object fig = flotE.readObject();
	    figures = (ArrayList<Rectangle>) fig;
		flotE.close();
		repaint();
	}
}