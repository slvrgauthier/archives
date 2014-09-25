package structure;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;

public class Homomorphisme {
	private ArrayList<Atom> A1;
	private ArrayList<Atom> A2; //candidats
	private ArrayList<Substitution> S; //homomorphismes
	private HashMap<Term,HashSet<Term>> domaines; //map<vars,map<consts>>
	private int complexite = 0; //estimation de la complexité totale
	
	public Homomorphisme(ArrayList<Atom> a1, ArrayList<Atom> a2) {
		A1 = a1;
		A2 = a2;
		S = new ArrayList<Substitution>();
		domaines = new HashMap<Term,HashSet<Term>>();                              complexite = 4;
		ArrayList<Term> vars=variables(A1), consts=constantes(A2);                              complexite += 2;
		for(Term v : vars) {
			domaines.put(v, new HashSet<Term>());
			HashSet<Term> set = domaines.get(v);                              complexite += 2;
			for(Term c : consts) {
				set.add(c);                              complexite += 1;
			}
		}
		restrictionDomaines(); //restriction des domaines
	}
	
	public void restrictionDomaines() {
		//soit for A1 for i for A2 for j -> plus de parcours mais hashMap découpée (pour chaque variable)
		//soit for A1 for A2 for i -> moins de parcours mais hashMap complète (pour chaque atome)
		for(Atom a1 : A1) {                              complexite += 1;
			ArrayList<Term> args1 = a1.getArgs();                              complexite += 1;
 			for(int i=0;i<args1.size();i++) {                              complexite += 1;
 				//hashmap temporaire pour récupérer les termes validés
 				HashSet<Term> mapi = new HashSet<Term>();                              complexite += 1;
				for(Atom a2 : A2) {                              complexite += 1;
					if(a1.equalsP(a2) && a1.getArity() == a2.getArity()) {
						ArrayList<Term> args2 = a2.getArgs();
						boolean put = true;                              complexite += 2;
			 			for(int j=i;j<args1.size();j++) {                              complexite += 1;
						  if(!domaines.get(args1.get(i)).contains(args2.get(j))) {
							  put = false;                              complexite += 1;
						  }                              complexite += 4;
						}                              complexite += 1;
			 			if(put) { //si le terme est validé
							mapi.add(args2.get(i));                              complexite += 1;
			 			}
					}                              complexite += 4;
				}
				//mettre à jour la liste de termes
				domaines.put(args1.get(i), mapi);                              complexite += 2;
			}
		}
	}
	
	public boolean backTrack() {
		Substitution s = backTrackRec(new Substitution(), variables(A1), constantes(A2));                              complexite += 3;
		if(s.getCouples().size() > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	private Substitution backTrackRec(Substitution s, ArrayList<Term> vars, ArrayList<Term> consts) {
		if(s.getCouples().size() == vars.size()) {
			return s;
		}
		else {
			Term x = choisirVariableNonAffectee(s, vars);                              complexite += 1;
			HashSet<Term> candidats = domaines.get(x);                              complexite += 2;
			for(Term c : candidats) {                              complexite += 1;
				Substitution s2 = new Substitution(s); //constructeur par recopie
				s2.add(new CoupleTerms(x, c));                              complexite += 2;
				if(homomorphismePartiel(s2)) {
					s = backTrackRec(s2, vars, consts);                              complexite += 1;
					if(s != null) {
						return s;
					}                              complexite += 1;
				}                              complexite += 1;
			}                              complexite += 1;
			return new Substitution();
		}
	}
	
	private boolean homomorphismePartiel(Substitution s) {
		if(s.getCouples().size() == 0) {
			return true;
		}                              complexite += 1;
		boolean result = true;                              complexite += 1;
		for(Atom a1 : A1) {                              complexite += 1;
			boolean r = false;                              complexite += 1;
			for(Atom a2 : A2) {                              complexite += 1;
				if(new Atom(a1, s).unifiable(a2)) { //atome partiellement instancié unifiable avec l'atome entièrement instancié
					r = true;                              complexite += 1;
					break;
				}                              complexite += 1;
			}
			result = (result && r);                              complexite += 1;
		}
		return result;
	}
	
	public ArrayList<Term> variables(ArrayList<Atom> A) { //récupérer toutes les variables d'un ensemble d'atomes
		ArrayList<Term> vars = new ArrayList<Term>();                              complexite += 1;
		for(Atom a : A) {                              complexite += 1;
			for(Term t : a.getArgs()) {                              complexite += 1;
				if(t.isVariable()) {
					boolean add = true;                              complexite += 1;
					for(Term t2 : vars) {                              complexite += 1;
						if(t.equalsT(t2)) {
							add = false;                              complexite += 1;
						}                              complexite += 1;
					}
					if(add) {
						vars.add(t);                              complexite += 1;
					}
				}                              complexite += 1;
			}
		}
		return vars;
	}
	public ArrayList<Term> constantes(ArrayList<Atom> A) { //récupérer toutes les constantes d'un ensemble d'atomes
		ArrayList<Term> consts = new ArrayList<Term>();                              complexite += 1;
		for(Atom a : A) {                              complexite += 1;
			for(Term t : a.getArgs()) {                              complexite += 1;
				if(t.isConstant()) {
					boolean add = true;                              complexite += 1;
					for(Term t2 : consts) {                              complexite += 1;
						if(t.equalsT(t2)) {
							add = false;                              complexite += 1;
						}                              complexite += 1;
					}
					if(add) {
						consts.add(t);                              complexite += 1;
					}
				}                              complexite += 1;
			}
		}
		return consts;
	}
	
	public Term choisirVariableNonAffectee(Substitution s, ArrayList<Term> vars) {
		Term x = null;                              complexite += 1;
		for(Term t : vars) {                              complexite += 1;
			boolean add = true;                              complexite += 1;
			for(CoupleTerms c : s.getCouples()) {                              complexite += 1;
				if(t.equalsT(c.getT1())) {
					add = false;                              complexite += 1;
				}                              complexite += 1;
			}
			if(add) {
				x = t;                              complexite += 1;
				break; //premier trouvé
			}
		}
		return x;
	}
	
	public void backTrackToutesSolutions() {
		ArrayList<Term> vars=variables(A1), consts=constantes(A2);
		S = new ArrayList<Substitution>();                              complexite += 3;
		backTrackAllRec(new Substitution(), vars, consts);
	}

	private void backTrackAllRec(Substitution s, ArrayList<Term> vars, ArrayList<Term> consts) {
		if(s.getCouples().size() == vars.size()) {
			S.add(s);                              complexite += 1;
		}
		else {
			Term x = choisirVariableNonAffectee(s, vars);                              complexite += 1;
			HashSet<Term> candidats = domaines.get(x);                              complexite += 2;
			for(Term c : candidats) {                              complexite += 1;
				Substitution s2 = new Substitution(s);
				s2.add(new CoupleTerms(x, c));                              complexite += 3;
				if(homomorphismePartiel(s2)) {
					backTrackAllRec(s2, vars, consts);
				}
			}
		}                              complexite += 3;
	}

	public ArrayList<Atom> getA1() {
		return A1;
	}

	public void setA1(ArrayList<Atom> a1) {
		A1 = a1;
	}

	public ArrayList<Atom> getA2() {
		return A2;
	}

	public void setA2(ArrayList<Atom> a2) {
		A2 = a2;
	}

	public ArrayList<Substitution> getS() {
		return S;
	}

	public void setS(ArrayList<Substitution> s) {
		S = s;
	}

	public HashMap<Term, HashSet<Term>> getdomaines() {
		return domaines;
	}

	public void setdomaines(HashMap<Term, HashSet<Term>> domaines) {
		this.domaines = domaines;
	}

	public int getComplexite() {
		return complexite;
	}

	public void setComplexite(int complexite) {
		this.complexite = complexite;
	}
	public String toString() {
		if(S.size() == 0) {
			return "{}";
		}
		else {
			String str = "{ "+S.get(0).toString();
			for(int i=1;i<S.size();i++) {
				str = str+", "+S.get(i).toString();
			}
			return str+" }";
		}
	}
}
