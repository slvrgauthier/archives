package puissance4ressource;

import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

import puissance4annotation.notUsed;

@notUsed
public class ImageCase extends Puissance4Images { //Non utilisée par facilité, nécessaire si l'on peut paramétrer directement la taille de grille
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	public ImageCase(int x, int y) {
		super(x,y);
		try {
			image = ImageIO.read(new File("Images/case.png"));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
