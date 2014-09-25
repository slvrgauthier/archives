package decorator;

import location.Client;
import location.Produit;
import location.ProduitSolde;

public class Main {
	public static void main(String[] args) {
		Produit lgv = new Produit("La grande vadrouille",10.0);
		Client cl = new Client("Dupont");
		Composite cmt = new Compte(cl);
		cmt.prixLocation(lgv);
		Composite cmt2 = new ForfaitReduction(cmt);
		System.out.println("CompteReduction : "+cmt2.prixLocation(lgv));
		Composite cmt3 = new ForfaitSeuil(cmt);
		System.out.println("CompteSeuil : "+cmt3.prixLocation(lgv));
		System.out.println("CompteSeuil : "+cmt3.prixLocation(lgv));
		System.out.println("CompteSeuil : "+cmt3.prixLocation(lgv));
		Produit r4 = new ProduitSolde("RockyIV",10.0);
		System.out.println("CompteNormal+ProduitSolde : "+cmt.prixLocation(r4));
		System.out.println("CompteReduction+ProduitSolde : "+cmt2.prixLocation(r4));
		
		Composite cmt4 = new ForfaitSeuil(new ForfaitReduction(cmt));
		System.out.println("\nCompteSeuilReduction : "+cmt4.prixLocation(lgv));
		System.out.println("CompteSeuilReduction : "+cmt4.prixLocation(lgv));
		System.out.println("CompteSeuilReduction : "+cmt4.prixLocation(lgv));
		
	}
}
