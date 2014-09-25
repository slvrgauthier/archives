package decorator;

import location.Produit;

public class ForfaitSeuil extends Decorator {
	private int seuil = 2;
	private int cpt = 0;
	
	public ForfaitSeuil(Composite c) {
		super(c);
	}
	public double prixLocation(Produit p) {
		cpt += 1;
		if(cpt > seuil) {
			cpt = 0;
			return (double)0;
		}
		else
			return super.getDecore().prixLocation(p);
	}

}
