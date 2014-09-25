package decorator;

import location.Produit;

public class ForfaitReduction extends Decorator {
	public ForfaitReduction(Composite c) {
		super(c);
	}
	public double prixLocation(Produit p) {
		return super.getDecore().prixLocation(p)*0.9;
	}
}
