package puissance4ressource;

import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

import puissance4exception.CouleurDoesNotExistException;
import puissance4exception.FormeDoesNotExistException;
import puissance4modele.Jeton;

public class ImageJeton extends Puissance4Images{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	public ImageJeton(int x, int y, Jeton jeton) {
		super(x,y);
		String path = "Images/jeton";
		//Forme
		try {
			switch(jeton.getForme()) {
			case Rond : 
				path+="Rond";
				break;
			case Carre :
				path+="Carre";
				break;
			case RondDente :
				path+="RondDente";
				break;
			case CarreDente :
				path+="CarreDente";
				break;
			default :
				throw new FormeDoesNotExistException();
			}
		}catch(FormeDoesNotExistException e) {
			System.out.println(e.getDescription());
		}
		//Couleur
		try {
			switch(jeton.getCouleur()) {
			case Rouge : 
				path+="Red";
				break;
			case Bleu :
				path+="Blue";
				break;
			case Vert :
				path+="Green";
				break;
			case Jaune :
			path+="Yellow";
				break;
			case Violet :
				path+="Purple";
				break;
			case Gris :
				path+="Grey";
				break;
			default :
				throw new CouleurDoesNotExistException();
			}
		}catch(CouleurDoesNotExistException e) {
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
