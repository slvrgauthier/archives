package structure;

import java.util.ArrayList;

public class Substitutions {
	private ArrayList<Substitution> subs;
	private ArrayList<Term> E1;
	private ArrayList<Term> E2;
	
	public Substitutions() {
		subs = new ArrayList<Substitution>();
		E1 = new ArrayList<Term>();
		E2 = new ArrayList<Term>();
	}
	public Substitutions(ArrayList<Term> e1, ArrayList<Term> e2){
		subs = new ArrayList<Substitution>();
		E1 = e1;
		E2 = e2;
	}
	public ArrayList<Substitution> getSubs() {
		return subs;
	}
	public ArrayList<Term> getE1() {
		return E1;
	}
	public ArrayList<Term> getE2() {
		return E2;
	}
	public void addSub(Substitution s) {
		subs.add(s);
	}
	
	public void generateAllSubs() {
		genererRec(new Substitution(), E1);
	}
	
	public void genererRec(Substitution s, ArrayList<Term> e) {
		if(!(e.isEmpty())) {
			Term t = e.get(0);
			e.remove(0);
			for(int i=0;i<E2.size();i++) {
				Substitution s2 = new Substitution(s);
				s2.add(new CoupleTerms(new Term(t),new Term(E2.get(i))));
				genererRec(s2, new ArrayList<Term>(e)); //récursif
			}		
		}
		else
			subs.add(s);
	}
	
	public String toString() {
		String str="";
		for(Substitution s : subs)
			str+= s.toString()+" ; ";
		return str+"\n";
	}
}
