package puissance4exception;

import puissance4annotation.notUsed;

@notUsed //cf Partie.java
public class TimeOutException extends Puissance4Exception {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	String description = "Le joueur n'a effectué aucune action dans le temps imparti";

	public String getDescription() {
		return description;
	}
}
