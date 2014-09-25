package puissance4ressource;

import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class ImageLacher extends Puissance4Images {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	public ImageLacher(int x, int y) {
		super(x,y);
		try {
			image = ImageIO.read(new File("Images/lacher.png"));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
