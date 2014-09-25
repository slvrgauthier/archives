package puissance4exception;

public class CouleurDoesNotExistException extends Puissance4Exception {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	String description = "La couleur de jeton demandée n'existe pas.";

	public String getDescription() {
		return description;
	}
}
