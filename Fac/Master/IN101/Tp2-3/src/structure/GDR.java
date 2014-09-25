package structure;

import java.util.ArrayList;

public class GDR {
	private KnowledgeBase K;
	private ArrayList<RuleBase> G;
	
	public GDR(KnowledgeBase kb) {
		K = kb;
	}
	public KnowledgeBase getK() {
		return K;
	}
	public ArrayList<RuleBase> getG() {
		return G;
	}

	public void calculGDR() {
		for(int i=0;i<G.size();i++) {
			//toDo
		}
	}
	
	public String toString() {
		String str = "";
		for(int i=0;i<G.size();i++) {
			str = str+K.getRb().getRule(i)+" : ";
			for(int j=0;j<G.get(i).size();j++) {
				str = str+G.get(i).getRule(j)+" ; ";
			}
			str = str+"\n";
		}
		return str;
	}
}
