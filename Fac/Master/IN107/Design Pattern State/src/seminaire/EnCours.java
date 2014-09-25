package seminaire;

public class EnCours extends Annulable {
	public EtatCycleSem abandon(Adherent a) {
		EtatCycleSem etatSuivant;
		if(cycle.getNbInscrits() > 5) {
			etatSuivant = this;
		}
		else {
			etatSuivant = new Abandonne();
		}
		System.out.println(this.getClass().toString()+" -> desistement -> "+etatSuivant.getClass().toString());
		return etatSuivant;
	}
}
