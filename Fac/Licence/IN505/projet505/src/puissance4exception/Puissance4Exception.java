package puissance4exception;

import java.io.IOException;

public class Puissance4Exception extends IOException{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	String description = "Une erreur est survenue dans le jeu slvr-Puissance 4";
	
	public String getDescription() {
		return description;
	}
}
