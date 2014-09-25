package dico;

public class Main {
	public static void main(String[] args) {
		System.out.println("Yop les gens !\n");
		OrderedDictionary o = new OrderedDictionary();
		System.out.println("Oredered :");
		System.out.println("-> "+o);
		o.put("bla","blate");
		o.put("gha","ghate");
		System.out.println("-> "+o);
		System.out.println("["+o.size()+"]");
		FastDictionary f = new FastDictionary();
		System.out.println("\nFast :");
		System.out.println("-> "+f);
		f.put("bla","blate");
		f.put("gha","ghate");
		System.out.println("-> "+f);
		System.out.println("["+f.size()+"]");
		SortedDictionary s = new SortedDictionary();
		System.out.println("\nSorted :");
		System.out.println("-> "+s);
		s.put("bla","blate");
		s.put("gha","ghate");
		System.out.println("-> "+s);
		System.out.println("["+s.size()+"]");
		OrderedDictionary os = new OrderedDictionary(10);
		System.out.println("\nOredered[10] :");
		System.out.println("-> "+os);
		os.put("bla","blate");
		os.put("gha","ghate");
		System.out.println("-> "+os);
		FastDictionary fs = new FastDictionary(10);
		System.out.println("\nFast[10] :");
		System.out.println("-> "+fs);
		fs.put("bla","blate");
		fs.put("gha","ghate");
		System.out.println("-> "+fs);
		SortedDictionary ss = new SortedDictionary(10);
		System.out.println("\nSorted[10] :");
		System.out.println("-> "+ss);
		ss.put("bla","blate");
		ss.put("gha","ghate");
		System.out.println("-> "+ss);
		System.out.println(ss.IndexOf("gha") != -1);
	}
}
