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
	public void setFb(FactBase fb) {
		this.fb = fb;
	}
	public void setRb(RuleBase rb) {
		this.rb = rb;
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
	
	public boolean request(ArrayList<Atom> A){
		this.ForwardChaining();
		for(Atom a : A) {
			if(!fb.belongsAtom(a)) {
				return false;
			}
		}
		return true;
	}
	
	public String advancedRequest(ArrayList<Atom> R, ArrayList<Term> T) {
		Homomorphisme h = new Homomorphisme(R, fb.getAtoms());
		h.backTrackToutesSolutions();
		Substitutions S = new Substitutions();
		for(Substitution s : h.getS()) {
			Substitution tmp = new Substitution();
			for(Term t : T) {
				for(CoupleTerms c : s.getCouples()) {
					if(c.getT1().equalsT(t)) {
						tmp.add(c);
					}
				}
			}
			boolean add = true;
			for(Substitution s2 : S.getSubs()) {
				if(s2.equalS(tmp)) {
					add = false;
				}
			}
			if(add) {
				S.addSub(tmp);
			}
		}
		return S.toString();
	}
	
	public void FC_Order1() {
		RuleBase rb_bak = rb; // ordre 1 (sauvegarde)
		RuleBase localRb = new RuleBase(); //ordre 0
		
		ArrayList<Term> E2 = new ArrayList<Term>(); //constantes
		for(Rule r : rb.getRules()) {
			for(Term t : r.getTerms()) {
				if(t.isConstant()) {
					boolean add = true;
					for(int i=0;i<E2.size();i++) {
						if(E2.get(i).equalsT(t))
							add = false;
					}
					if(add)
						E2.add(t);
				}
			}
		}
		for(Term t : fb.getTerms()) {
			if(t.isConstant()) {
				boolean add = true;
				for(int i=0;i<E2.size();i++) {
					if(E2.get(i).equalsT(t))
						add = false;
				}
				if(add)
					E2.add(t);
			}
		}
		
		for(Rule r : rb.getRules()) { //seconde fois la boucle, ayant besoin de toutes les constantes lors des substitutions
			ArrayList<Term> E1 = new ArrayList<Term>(); //variables
			for(Term t : r.getTerms()) {
				if(t.isVariable()) {
					boolean add = true;
					for(int i=0;i<E1.size();i++) {
						if(E1.get(i).equalsT(t))
							add = false;
					}
					if(add)
						E1.add(t);
				}
			}
			//générer les substitutions pour chaque règle
			Substitutions subs = new Substitutions(E1,E2);
			subs.generateAllSubs();
			for(Substitution s : subs.getSubs()) {
				Rule r2 = new Rule(r, s);
				localRb.addRule(r2);
			}
		}
		this.setRb(localRb); //fc ordre 0
		System.out.println(this.getRb());
		this.ForwardChaining();
		this.setRb(rb_bak); //retour à ordre 1
		System.out.println(this);
	}
	
	public void FC_Order1_V2() {
		System.out.println("Saturation d'ordre 1 :");
		int fbSize;
		do {
			fbSize = fb.getAtoms().size();
			for(Rule r : rb.getRules()) {
				Homomorphisme h = new Homomorphisme(r.getHypothesis(), fb.getAtoms());
				h.backTrackToutesSolutions();
				for(Substitution s : h.getS()) {
					fb.addAtom(new Atom(r.getConclusion(), s));
				}
			}
		} while(fbSize != fb.getAtoms().size());
		System.out.println(this);
	}
	
	public String toString() {
		return fb.toString()+rb.toString();
	}
}
