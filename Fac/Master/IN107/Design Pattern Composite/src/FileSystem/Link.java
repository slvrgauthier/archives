package FileSystem;

public class Link extends Element {
	private Element e;
	
	public Link(String name, Element e) {
		this.name = name;
		Link.basicSize = 0;
		this.e = e;
	}

	public int size() {
		return Link.basicSize;
	}
	
	public String cat() {
		return e.absoluteAdress();
	}

	public Element getE() {
		return e;
	}
}
