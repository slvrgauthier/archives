package seminaire;

public class PreparationSem extends Annulable {
	public EtatCycleSem ajoutDocument(Document d) {
		cycle.getDocuments().add(d);
		System.out.println(this.getClass().toString()+" -> ajoutDocument -> "+this.getClass().toString());
		return this;
	}
}
