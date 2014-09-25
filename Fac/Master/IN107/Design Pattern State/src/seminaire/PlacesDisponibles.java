package seminaire;

public class PlacesDisponibles extends ReservationOuverte {
	public EtatCycleSem inscription(Adherent a) {
		EtatCycleSem etatSuivant;
		if(cycle.getNbInscrits() < cycle.getCapacite()-1) {
			etatSuivant = this;
		}
		else {
			etatSuivant = new Complet();
		}
		System.out.println(this.getClass().toString()+" -> inscription ["+cycle.getNbInscrits()+" / "+cycle.getCapacite()+"] -> "+etatSuivant.getClass().toString());
		return etatSuivant;
	}
}
