package FileSystem;

public class Main {
	public static void main(String[] args) {
		File f1 = new File("f1");
		File f2 = new File("f2");
		File f3 = new File("f3");
		File f4 = new File("f5");
		File f5 = new File("f5");

		Folder d1 = new Folder("d1");
		Folder d2 = new Folder("d2");
		Folder d3 = new Folder("d3");

		Link l1 = new Link("l1", f3);
		Link l2 = new Link("l2", f2);
		Link l3 = new Link("l3", d3);
		
		d1.add(d2);
		d1.add(d3);
		d1.add(f1);
		d1.add(f2);
		d1.add(l1);

		d2.add(l2);
		d2.add(f3);
		d2.add(f4);

		d3.add(f5);
		d3.add(l3);
		
		System.out.println(d1.findR("f5"));
		System.out.println(d1.tree());
	}
}
