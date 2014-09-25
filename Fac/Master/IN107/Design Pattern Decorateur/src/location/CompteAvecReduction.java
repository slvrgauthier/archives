package location;

public class CompteAvecReduction extends Compte{

	public CompteAvecReduction(Client cl) {
		super(cl);
	}
	public double prixLocation(Produit p) {
		return super.prixLocation(p)*0.9;
	}
}
