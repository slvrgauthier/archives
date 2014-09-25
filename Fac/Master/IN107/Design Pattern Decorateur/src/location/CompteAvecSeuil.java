package location;

public class CompteAvecSeuil extends Compte {
	private int cpt = 0;
	private int seuil = 2;
	
	public CompteAvecSeuil(Client cl) {
		super(cl);
	}

	public double prixLocation(Produit p) {
		cpt += 1;
		if(cpt > seuil) {
			cpt = 0;
			return (double)0;
		}
		else
			return super.prixLocation(p);
	}
}
