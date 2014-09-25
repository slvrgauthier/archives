package cercleSportif;

import java.util.Vector;

public class Planning {

	private Vector<Crenau> crenaux;
	private Vector<SGBD> sgbd;
	
	private int annee;

	public Planning() {
	}
	public Planning(int annee) {
		this.annee = annee;
	}

	public int getAnnee() {
		return annee;
	}
	public void setAnnee(int annee) {
		this.annee = annee;
	}
	
}
