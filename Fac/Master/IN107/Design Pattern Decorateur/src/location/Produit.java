package location;

public class Produit {
	private String ref;
	private double price;
	
	public Produit(String s, double d) {
		ref = s;
		price = d;
	}

	//redéfinir cette méthode pour étendre les types de produits
	public double getPrice() {
		return price;
	}
}
