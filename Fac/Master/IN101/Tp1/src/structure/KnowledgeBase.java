package structure;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class KnowledgeBase {
	private FactBase fb = new FactBase();
	private RuleBase rb = new RuleBase();
	
	public KnowledgeBase() {}
	public KnowledgeBase(String path) throws IOException {
		// Fichier contenant :
		//  - les faits sur la première ligne
		//  - une règle sur chaque ligne suivante
		BufferedReader reader = new BufferedReader( new FileReader(path));
		System.out.println("Lecture du fichier "+path+"...");
		fb = new FactBase(reader.readLine());
		String s = reader.readLine();
		while(s != null) {
			rb.addRule(new Rule(s));
			s = reader.readLine();
		}
		reader.close();
		System.out.println("Fin de lecture\n\n"+this.toString());
	}
	// Getters
	public FactBase getFb() {
		return fb;
	}
	public RuleBase getRb() {
		return rb;
	}
	// Adders
	public void addRule(Rule r) { rb.addRule(r); }
	public void addFact(Atom a) { fb.addAtom(a); }
	
	
	public void ForwardChaining() {
		// Compteurs
		int count[] = new int[rb.size()];
		// BF à explorer
		FactBase toDo = new FactBase();
		// Copie de rb dans toDo
		for(int i=0;i<fb.size();i++)
			toDo.addAtom(fb.getAtoms().get(i));
		// Initialisation des compteurs
		for(int i=0;i<rb.size();i++){
			count[i] = rb.getRule(i).getHypothesis().size();
		}
		// Atome courant
		Atom a;
		// Algorithme non-naïf du Forward Chaining
		while(!toDo.isEmpty()) {
			a = toDo.getAtoms().get(0);
			toDo.getAtoms().remove(0);
			for(int i=0;i<rb.size();i++){
				Rule r = rb.getRule(i);
				ArrayList<Atom> h = r.getHypothesis();
				int j=0;
				while(j<h.size() && !(h.get(j).equalsA(a))){
					j++;
				}
				if(j!=h.size()) {
					count[i]--;
					if(count[i] == 0){
						Atom c = r.getConclusion();
						if(!(fb.belongsAtom(c))) {
							fb.addAtom(c);
							toDo.addAtom(c);
						}
					}
				}
			}
		}
	}
	
	public boolean request(Atom a){
		this.ForwardChaining();
		return fb.belongsAtom(a);
	}
	public String toString() {
		return fb.toString()+rb.toString();
	}
}
