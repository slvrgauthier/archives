package puissance4exception;

public class DifficulteDoesNotExistException extends Puissance4Exception {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	String description = "Le type de difficulté demandé n'existe pas.";

	public String getDescription() {
		return description;
	}
}
