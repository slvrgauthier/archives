package FileSystem;

import java.util.ArrayList;

public class Folder extends Element {
	private ArrayList<Element> composition;
	
	public Folder(String name) {
		this.name = name;
		Folder.basicSize = 4;
		composition = new ArrayList<Element>();
	}

	public void add(Element e) {
		if(e != this) {
			composition.add(e);
			e.setParent(this);
		}
	}
	public int size() {
		int count = Folder.basicSize;
		for(Element e : composition)
			count += e.size();
		return count;
	}
	public String ls() {
		String s = "";
		for(Element e : composition)
			s += e.name + " ";
		return s;
	}
	public int nbElements() {
		return composition.size();
	}
	public ArrayList<String> find(String name) {
		ArrayList<String> l = new ArrayList<String>();
		for(Element e : composition)
			if(e.name.equals(name))
				l.add(e.absoluteAdress());
		return l;
	}
	public ArrayList<String> findR(String name) {
		ArrayList<String> l = new ArrayList<String>();
		fR(l, name);
		return l;
	}
	private void fR(ArrayList<String> l, String name) {
		for(Element e : composition) {
			if(e.name.equals(name))
				l.add(e.absoluteAdress());
			if(e instanceof Folder)
				((Folder) e).fR(l, name);
		}
	}
	public String tree() {
		String s = new String(name+"\n");
		return tR(s);
	}
	public String tR(String s) {
		String s2 = new String(s);
		for(Element e : composition) {
			for(int i=0; i<e.level(); i++)
				s2 = s2 + "__";
			s2 = s2 + e.name + "\n";
			if(e instanceof Folder) {
				s2 = ((Folder) e).tR(s2);
			}
		}
		return s2;
	}
}
