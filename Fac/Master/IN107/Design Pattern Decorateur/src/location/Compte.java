package location;

public class Compte {
	private Client client;
	
	public Compte(Client cl) {
		client = cl;
	}
	
	//redéfinir cette méthode pour étendre les types de comptes
	public double prixLocation(Produit p) {
		return p.getPrice();
	}
}
