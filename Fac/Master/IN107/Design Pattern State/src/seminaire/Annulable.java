package seminaire;

public abstract class Annulable extends EtatCycleSem {
	public EtatCycleSem annuler() {
		EtatCycleSem etatSuivant = new Annule();
		System.out.println(this.getClass().toString()+" -> annuler -> "+etatSuivant.getClass().toString());
		return etatSuivant;
	}
}
