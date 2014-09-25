import java.io.IOException;
import java.util.ArrayList;

import structure.*;


public class Application0 {
	public static void main(String[] args){
		//------ Forward Chaining -------------------------------------------
		try {
			KnowledgeBase kb = new KnowledgeBase("demo1.txt");
			kb.FC_Order1_V2(); //vrai ordre 1 cette fois
			System.out.println("==========================================================================\nQuestion 1)\n==========================================================================");
			ArrayList<Atom> Q = new ArrayList<Atom>(); //requête
			Q.add(new Atom("p('A','B')")); Q.add(new Atom("p('A','C')"));
			System.out.println("A-t-on p(A,B)^p(A,C) ? "+kb.request(Q)+"\n");
			ArrayList<Atom> q1 = new ArrayList<Atom>();
			q1.add(new Atom("p(x,y)"));
			//q1.add(new Atom("p(y,x)"));
			ArrayList<Term> q2 = new ArrayList<Term>();
			q2.add(new Term("x",false));
			//q2.add(new Term("y",false));
			System.out.println("Requete avancee :\n"+kb.advancedRequest(q1,q2));
			
			//------ Homomorphisme ----------------------------------------------
			System.out.println("==========================================================================\nQuestion 2)\n==========================================================================");
			ArrayList<Atom> A1 = kb.getRb().getRule(2).getHypothesis();
			ArrayList<Atom> A2 = kb.getFb().getAtoms();
			System.out.println("Pour les backtrack, BF* = "+A2);
			Homomorphisme h = new Homomorphisme(A1,A2);
			System.out.println("\nBacktrack : "+A1+" dans BF*\nRestriction des domaines : "+h.getdomaines());
			if(h.backTrack()) {
				System.out.println("Il existe au moins une solution\n");
			}
			else {
				System.out.println("Aucune solution");
			}
			System.out.println("Complexité totale des algorithmes : "+h.getComplexite());
			//------ Homomorphisme ----------------------------------------------
			System.out.println("\n==========================================================================\nQuestion 3)\n==========================================================================");
			A1 = kb.getRb().getRule(0).getHypothesis();
			h = new Homomorphisme(A1,A2);
			System.out.println("\nBacktrack : "+A1+" dans BF*\nRestriction des domaines : "+h.getdomaines());
			h.backTrackToutesSolutions();
			System.out.println("Il existe "+h.getS().size()+" solutions :");
			System.out.println(h);
			System.out.println("Complexité totale des algorithmes : "+h.getComplexite());
			//------ Homomorphisme ----------------------------------------------
			System.out.println("\n==========================================================================\nQuestion 4)\n==========================================================================");
			A1 = new ArrayList<Atom>(); A1.add(new Atom("s(x,y,z)"));
			h = new Homomorphisme(A1,A2);
			System.out.println("\nBacktrack : "+A1+" dans BF*\nRestriction des domaines : "+h.getdomaines());
			h.backTrackToutesSolutions();
			System.out.println("Il existe "+h.getS().size()+" solutions :");
			System.out.println(h);
			System.out.println("Complexité totale des algorithmes : "+h.getComplexite());
			//------ Homomorphisme ----------------------------------------------
			System.out.println("\n==========================================================================\nQuestion 5)\n==========================================================================");
			A1 = new ArrayList<Atom>();
			A1.add(new Atom("p(x,y)"));
			A1.add(new Atom("p(x,z)"));
			A1.add(new Atom("p(y,z)"));
			h = new Homomorphisme(A1,A2);
			System.out.println("\nBacktrack : "+A1+" dans BF*\nRestriction des domaines : "+h.getdomaines());
			h.backTrackToutesSolutions();
			System.out.println("Il existe "+h.getS().size()+" solutions :");
			System.out.println(h);
			System.out.println("Complexité totale des algorithmes : "+h.getComplexite());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//------ Unification ------------------------------------------------
		System.out.println("\n==========================================================================\nBonus\n==========================================================================");
		Atom a1 = new Atom("p(x1,y1,'A',x1)");
		Atom a2 = new Atom("p('B',x2,x2,y2)");
		System.out.println(a1+" et "+a2+" unifiables ? "+a1.unifiable(a2));
		a1 = new Atom("p(x,'A',x)");
		a2 = new Atom("p(y,y,'B')");
		System.out.println(a1+" et "+a2+" unifiables ? "+a1.unifiable(a2));
	}
}
