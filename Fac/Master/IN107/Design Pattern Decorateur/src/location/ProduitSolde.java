package location;

public class ProduitSolde extends Produit{

	public ProduitSolde(String s, double f) {
		super(s, f);
	}
	
	public double getPrice() {
		return super.getPrice()/2;
	}
}
