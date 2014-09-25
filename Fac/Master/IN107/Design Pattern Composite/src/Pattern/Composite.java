package Pattern;
import java.util.ArrayList;

public class Composite extends AbstractElement {
	private ArrayList<AbstractElement> composition;
	
	public Composite() {
		composition = new ArrayList<AbstractElement>();
	}

	public ArrayList<AbstractElement> getComposition() {
		return composition;
	}
	
	public void add(AbstractElement element) {
		composition.add(element);
	}
}
