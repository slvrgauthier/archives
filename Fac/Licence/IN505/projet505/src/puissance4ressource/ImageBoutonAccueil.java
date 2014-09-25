package puissance4ressource;

import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

import puissance4enumeration.Difficulte;
import puissance4exception.DifficulteDoesNotExistException;

public class ImageBoutonAccueil extends Puissance4Images {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public ImageBoutonAccueil(Difficulte difficulte) {
		//Disposition prédéfinie
		super(93,218);
		
		//Choix de l'image
		String path = "Images/BoutonAccueil";
		try {
			switch(difficulte) {
			case Debutant :
				path+="Debutant";
				break;
			case Intermediaire :
				path+="Intermediaire";
				setY(getY() + 85);
				break;
			case Confirme :
				path+="Confirme";
				setY(getY() + 170);
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
			imageSb = ImageIO.read(new File("Images/BoutonAccueilSb.png"));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
