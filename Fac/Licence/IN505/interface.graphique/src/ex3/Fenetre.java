package ex3;

import java.awt.event.*;
import javax.swing.*;

public class Fenetre extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public Fenetre() {
		setTitle("Petit sondage");
		setLocation(100,100);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		add(new JLabel("Aimez-vous les cours de Java ?"), "North");
		add(new PanFenetre());
		setVisible(true);
		pack();
	}
	public static void main(String args[]) {
		new Fenetre();
	}
}

class PanFenetre extends JPanel {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private JButton oui;
	private JButton non;
	private boolean change=true;
	public PanFenetre() {
		oui=new JButton("OUI");
		non=new JButton("NON");
		add(oui); add(non);
		oui.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JOptionPane.showMessageDialog(null, "c'est bien ce que nous pensions...", "Message", JOptionPane.YES_OPTION);
			}
		});
		non.addMouseListener(new MouseAdapter() {
			public void mouseEntered(MouseEvent e) {
				if(change) {
					remove(oui);
					remove(non);
					add(non);
					add(oui);
					validate();
					change=false;
				}
				else {
					remove(oui);
					remove(non);
					add(oui);
					add(non);
					validate();
					change=true;
				}
			}
		});
	}
}
