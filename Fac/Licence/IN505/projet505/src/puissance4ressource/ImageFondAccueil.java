package puissance4ressource;

import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class ImageFondAccueil extends Puissance4Images {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public ImageFondAccueil(int x, int y) {
		super(x,y);
		try {
			image = ImageIO.read(new File("Images/FondAccueil.png"));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
