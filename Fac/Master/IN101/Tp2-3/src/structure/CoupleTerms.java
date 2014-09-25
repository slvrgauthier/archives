package structure;

public class CoupleTerms {
	private Term t1;
	private Term t2;
	
	public CoupleTerms(Term t1, Term t2) {
		this.t1 = t1;
		this.t2 = t2;
	}
	public CoupleTerms(CoupleTerms c) {
		t1 = new Term(c.getT1());
		t2 = new Term(c.getT2());
	}
	public Term getT1() {
		return t1;
	}
	public Term getT2() {
		return t2;
	}
	public String toString() {
		return "("+t1.toString()+";"+t2.toString()+")";
	}
}
