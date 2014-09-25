package FileSystem;

public class File extends Element {
	protected String contain;
	
	public File(String name) {
		this.name = name;
		File.basicSize = 0;
	}

	public int size() {
		return File.basicSize + contain.length();
	}
	
	public String cat() {
		return contain;
	}
	
	public int nbElements() {
		return contain.length();
	}
}
