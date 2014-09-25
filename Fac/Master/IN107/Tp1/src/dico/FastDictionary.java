package dico;

public class FastDictionary extends AbstractDictionary {

	public FastDictionary() {}
	public FastDictionary(int size) {
		keyTab = new Object[size];
		valTab = new Object[size];
	}
	
	int newIndexOf(Object key) {
		while (mustGrow())
			grow();
		int i = 0;
		if(keyTab.length > 1)
			i = key.hashCode()%(keyTab.length - 1);
		while(keyTab[i] != null)
			i = (i+1)%keyTab.length;
		keyTab[i] = key;
		return i;
	}
	int IndexOf(Object key) {
		int i = 0;
		if(keyTab.length > 1)
			i = key.hashCode()%(keyTab.length - 1);
		int ref = i;
		while(keyTab.length != 0 && keyTab[i] != null)
			if(keyTab[i] == key)
				return i;
			else {
				i = (i+1)%keyTab.length;
				if(i==ref)
					return -1;
			}
		return -1;
	}
	
	boolean mustGrow() {
		return (keyTab.length == 0 || this.size()/keyTab.length > 3/4);
	}
	void grow() {
		Object ktab[] = new Object[keyTab.length + 1];
		Object vtab[] = new Object[keyTab.length + 1];
		for(int i=0;i<keyTab.length;i++) {
			ktab[i] = keyTab[i];
			vtab[i] = valTab[i];
		}
		keyTab = ktab;
		valTab = vtab;
	}
}
