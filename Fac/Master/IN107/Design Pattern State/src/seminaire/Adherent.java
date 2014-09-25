package seminaire;

public class Adherent {
	private String nom;
	private String prenom;
	
	public Adherent(String n, String p) {
		nom = n;
		prenom = p;
	}

	public String getNom() {
		return nom;
	}

	public String getPrenom() {
		return prenom;
	}
}
