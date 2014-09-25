package puissance4ressource;

import java.awt.Graphics;
import java.awt.Image;
import javax.swing.JPanel;

public class Puissance4Images extends JPanel {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int x;
	private int y;
	protected Image image;
	protected Image imageSb;
	private boolean surbrillance = false;
	
	public Puissance4Images(int x, int y) {
		this.x = x;
		this.y = y;
	}
	
	public void paintComponent(Graphics g) {
		//pas de super car le panneau ne doit pas être paint, seulement son image 
        if(surbrillance)
        	g.drawImage(imageSb, x, y, imageSb.getWidth(this), imageSb.getHeight(this), this);
		g.drawImage(image, x, y, image.getWidth(this), image.getHeight(this), this);
    }

	//Getters et Setters
	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}

	public int getY() {
		return y;
	}

	public void setY(int y) {
		this.y = y;
	}
	
	public int getWidth() {
		return image.getWidth(this);
	}
	
	public int getHeight() {
		return image.getHeight(this);
	}
	
	public void setSurbrillance(boolean surbrillance) {
		this.surbrillance = surbrillance;
		repaint();
	}
}