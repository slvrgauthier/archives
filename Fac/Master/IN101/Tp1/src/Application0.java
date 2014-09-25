import java.io.IOException;

import structure.Atom;
import structure.FactBase;
import structure.KnowledgeBase;
import structure.Rule;
import structure.RuleBase;


public class Application0 {
	public static void main(String[] args)
	{
		// creation de la base de faits de 2 facons differentes
		FactBase bf = new FactBase("P");
		bf.addAtom(new Atom("Q"));
//		System.out.println("Etat initial de la base de faits :\n"+bf);
	
		// creation de la base de regles
		RuleBase br = new RuleBase();
		br.addRule(new Rule("P;S"));
//		System.out.println("Base de regles :\n"+br);
		
		// chargement de base par fichier
		try {
			KnowledgeBase kb = new KnowledgeBase("sample.txt");
			System.out.println("Avant Forward Chaining :");
			System.out.println(kb.getFb());
			kb.ForwardChaining();
			System.out.println("Après Forward Chaining :");
			System.out.println(kb.getFb());
			Atom a1=new Atom("Cloé"),a2=new Atom("Félix");
			System.out.println("Requête pour l'atome "+a1+" : "+kb.request(a1));
			System.out.println("Requête pour l'atome "+a2+" : "+kb.request(a2));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
