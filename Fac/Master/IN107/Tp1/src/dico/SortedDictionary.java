package dico;

public class SortedDictionary extends OrderedDictionary {

	public SortedDictionary() {}
	public SortedDictionary(int size) {
		keyTab = new Object[size];
		valTab = new Object[size];
	}
	
	@SuppressWarnings("unchecked")
	public int newIndexOf(Object key) {
		Object ktab[],vtab[];
		if(this.size() == keyTab.length) {
			ktab = new Object[keyTab.length + 1];
			vtab = new Object[keyTab.length + 1];
		}
		else {
			ktab = new Object[keyTab.length];
			vtab = new Object[keyTab.length];
		}
		int i=0;
		if(this.size() > 0) {
			while(i < keyTab.length && keyTab[i] != null && ((Comparable<Object>)keyTab[i]).compareTo((Comparable<Object>)key) < 0) {
				ktab[i] = keyTab[i];
				vtab[i] = valTab[i];
				i++;
			}
			for(int j=i+1;j<keyTab.length;j++) {
				ktab[j] = keyTab[j-1];
				vtab[j] = valTab[j-1];
			}
		}
		ktab[i] = key;
		keyTab = ktab;
		valTab = vtab;
		return i;
	}
	@SuppressWarnings("unchecked")
	public int IndexOf(Object key) {
		if(this.size() > 2) {
			int deb = 0, fin = this.size() - 1;
			int mid = deb + fin / 2;
			while(deb < fin) {
				int test = ((Comparable<Object>)keyTab[mid]).compareTo((Comparable<Object>)key);
				if (test == 0) {
					return mid;
				}
				else if(test < 0) {
					deb = mid;
					mid = deb + fin / 2;
				}
				else {
					fin = mid;
					mid = deb + fin / 2;
				}
			}
			return -1;
		}
		else
			if(this.size() > 0 && ((Comparable<Object>)keyTab[0]).compareTo((Comparable<Object>)key) == 0)
				return 0;
			else if(this.size() > 1 && ((Comparable<Object>)keyTab[1]).compareTo((Comparable<Object>)key) == 0)
				return 1;
			else
				return -1;
	}
}
