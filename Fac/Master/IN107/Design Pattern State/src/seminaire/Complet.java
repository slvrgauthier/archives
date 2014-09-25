package seminaire;

public class Complet extends ReservationOuverte {
	public EtatCycleSem inscription(Adherent a) {
		System.out.println(this.getClass().toString()+" -> inscription -> "+this.getClass().toString());
		return this;
	}
	public EtatCycleSem desistement(Adherent a) {
		EtatCycleSem etatSuivant;
		if(cycle.getListeAttente().size() > 0) {
			etatSuivant = this;
		}
		else {
			etatSuivant = new PlacesDisponibles();
		}
		System.out.println(this.getClass().toString()+" -> desistement -> "+etatSuivant.getClass().toString());
		return etatSuivant;
	}
}
