package seminaire;

public class Planification extends Annulable {
	public EtatCycleSem setTitre(String titre) {
		cycle.setT(titre);
		System.out.println(this.getClass().toString()+" -> setTitre -> "+this.getClass().toString());
		return this;
	}
	public EtatCycleSem setResume(String resume) {
		cycle.setR(resume);
		System.out.println(this.getClass().toString()+" -> setResume -> "+this.getClass().toString());
		return this;
	}
	public EtatCycleSem setCapacite(int capacite) {
		cycle.setCa(capacite);
		System.out.println(this.getClass().toString()+" -> setCapacite -> "+this.getClass().toString());
		return this;
	}
	public EtatCycleSem setCreneaux(Creneau creneau) {
		cycle.setCr(creneau);
		System.out.println(this.getClass().toString()+" -> setCreaneaux -> "+this.getClass().toString());
		return this;
	}
	public EtatCycleSem ouvertureReservation() {
		EtatCycleSem etatSuivant = new PlacesDisponibles();
		System.out.println(this.getClass().toString()+" -> ouvertureReservation -> "+etatSuivant.getClass().toString());
		return etatSuivant;
	}
}
