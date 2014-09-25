package decorator;

import location.Produit;

public abstract class Decorator extends Composite {
	private Composite decore;
	
	public Decorator(Composite c) {
		decore = c;
	}
	public Composite getDecore() {
		return decore;
	}
	public abstract double prixLocation(Produit p);
}
