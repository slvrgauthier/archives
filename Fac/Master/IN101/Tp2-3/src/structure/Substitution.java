package structure;

import java.util.ArrayList;

public class Substitution {
	private ArrayList<CoupleTerms> couples;
	
	public Substitution() {
		couples = new ArrayList<CoupleTerms>();
	}
	public Substitution(ArrayList<CoupleTerms> c) {
		couples = c;
	}
	public Substitution(Substitution s) { //constructeur par recopie
		couples = new ArrayList<CoupleTerms>();
		for(CoupleTerms c : s.getCouples()) {
			couples.add(new CoupleTerms(c));
		}
	}
	public ArrayList<CoupleTerms> getCouples() {
		return couples;
	}
	public void add(CoupleTerms c) {
		couples.add(c);
	}
	public boolean equalS(Substitution s) { //égalité entre substitutions
		if(s.getCouples().size() != couples.size()) {
			return false;
		}
		boolean result = true;
		for(CoupleTerms c1 : couples) {
			boolean r = false;
			for(CoupleTerms c2 : s.getCouples()) {
				if(c1.getT1().equalsT(c2.getT1()) && c1.getT2().equalsT(c2.getT2())) {
					r = true;
				}
			}
			result = r && result;
		}
		return result;
	}
	public String toString() {
		String str="{";
		for(CoupleTerms c : couples)
			str+= c.toString();
		return str+"}";
	}
}
