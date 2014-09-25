package dico;

public class OrderedDictionary extends AbstractDictionary {

	public OrderedDictionary() {}
	public OrderedDictionary(int size) {
		keyTab = new Object[size];
		valTab = new Object[size];
	}
	
	public int newIndexOf(Object key) {
		for(int i=0;i<keyTab.length;i++){
			if(keyTab[i] == null) {
				keyTab[i] = key;
				return i;
			}
		}
		Object ktab[] = new Object[keyTab.length + 1];
		Object vtab[] = new Object[keyTab.length + 1];
		for(int i=0;i<keyTab.length;i++) {
			ktab[i] = keyTab[i];
			vtab[i] = valTab[i];
		}
		keyTab = ktab;
		valTab = vtab;
		keyTab[keyTab.length - 1] = key;
		return keyTab.length - 1;
	}
	int IndexOf(Object key) {
		for(int i=0;i<keyTab.length;i++)
			if(keyTab[i] == key)
				return i;
		return -1;
	}
}
