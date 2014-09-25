package FileSystem;

public abstract class Element {
	protected String name;
	protected static int basicSize;
	protected Folder parent;
	
	public String getName() {
		return name;
	}
	public Folder getParent() {
		return parent;
	}
	public void setParent(Folder d) {
		parent = d;
	}
	public abstract int size();
	public String absoluteAdress() {
		if(parent == null)
			return "";
		else
			return parent.absoluteAdress()+"/"+name;
	}
	public int level() {
		if(parent == null)
			return 0;
		else
			return 1 + parent.level();
	}
}
