package seminaire;

public abstract class ReservationOuverte extends Annulable {
	public EtatCycleSem clotureReservation() {
		EtatCycleSem etatSuivant;
		if(cycle.getNbInscrits() < 10) {
			etatSuivant = new Annule();
		}
		else {
			etatSuivant = new PreparationSem();
		}
		System.out.println(this.getClass().toString()+" -> clotureReservation ["+cycle.getNbInscrits()+"] -> "+etatSuivant.getClass().toString());
		return etatSuivant;
	}
}
