package decorator;

import location.Client;
import location.Produit;

public class Compte extends Composite {
	private Client client;
	
	public Compte(Client cl) {
		client = cl;
	}
	
	//redéfinir cette méthode pour étendre les types de comptes
	public double prixLocation(Produit p) {
		return p.getPrice();
	}

}
