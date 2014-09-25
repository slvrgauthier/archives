package puissance4exception;

public class FormeDoesNotExistException extends Puissance4Exception {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	String description = "La forme de jeton demandée n'existe pas.";

	public String getDescription() {
		return description;
	}
}
