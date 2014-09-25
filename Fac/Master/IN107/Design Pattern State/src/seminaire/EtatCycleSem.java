package seminaire;

public abstract class EtatCycleSem {
	protected CycleSem cycle;
	
	public EtatCycleSem inscription(Adherent a) {
		System.out.println(this.getClass().toString()+" -> inscription -> "+this.getClass().toString());
		return this;
	}
	public EtatCycleSem desistement(Adherent a) {
		System.out.println(this.getClass().toString()+" -> desistement -> "+this.getClass().toString());
		return this;
	}
	public EtatCycleSem archiver() {
		System.out.println(this.getClass().toString()+" -> archiver -> "+this.getClass().toString());
		return this;
	}
	public EtatCycleSem abandon(Adherent a) {
		System.out.println(this.getClass().toString()+" -> abandon -> "+this.getClass().toString());
		return this;
	}
	public EtatCycleSem ouvertureReservation() {
		System.out.println(this.getClass().toString()+" -> ouvertureReservation -> "+this.getClass().toString());
		return this;
	}
	public EtatCycleSem clotureReservation() {
		System.out.println(this.getClass().toString()+" -> clotureReservation -> "+this.getClass().toString());
		return this;
	}
	public EtatCycleSem annuler() {
		System.out.println(this.getClass().toString()+" -> annuler -> "+this.getClass().toString());
		return this;
	}
	
	public EtatCycleSem setTitre(String titre) {
		System.out.println(this.getClass().toString()+" -> setTitre -> "+this.getClass().toString());
		return this;
	}
	public EtatCycleSem setResume(String resume) {
		System.out.println(this.getClass().toString()+" -> setResume -> "+this.getClass().toString());
		return this;
	}
	public EtatCycleSem setCapacite(int capacite) {
		System.out.println(this.getClass().toString()+" -> setCapacite -> "+this.getClass().toString());
		return this;
	}
	public EtatCycleSem setCreneaux(Creneau creneau) {
		System.out.println(this.getClass().toString()+" -> setCreneaux -> "+this.getClass().toString());
		return this;
	}
}
