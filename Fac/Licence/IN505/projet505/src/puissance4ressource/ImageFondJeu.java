package puissance4ressource;

import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

import puissance4enumeration.Difficulte;
import puissance4exception.DifficulteDoesNotExistException;

public class ImageFondJeu extends Puissance4Images {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public ImageFondJeu(int x, int y, Difficulte difficulte) {
		super(x,y);
		String path = "Images/Fond";
		try {
			switch(difficulte) {
			case Debutant :
				path+="Debutant";
				break;
			case Intermediaire :
				path+="Intermediaire";
				break;
			case Confirme :
				path+="Confirme";
				break;
			default :
				throw new DifficulteDoesNotExistException();
			}
		}catch(DifficulteDoesNotExistException e) {
			System.out.println(e.getDescription());
		}
		path+=".png";
		try {
			image = ImageIO.read(new File(path));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
