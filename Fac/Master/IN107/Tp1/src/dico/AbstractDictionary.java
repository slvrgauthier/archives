package dico;

public abstract class AbstractDictionary implements IDictionary{
	protected Object keyTab[] = new Object[0];
	protected Object valTab[] = new Object[0];
	
	// Interface
	public Object get(Object key) {
		return valTab[IndexOf(key)];
	}
	public Object put(Object key, Object value) {
		int i = IndexOf(key);
		if(i == -1) {
			int index = newIndexOf(key);
			valTab[index] = value;
		}
		else
			valTab[i] = value;
		return this;
	}
	public boolean isEmpty() {
		return (keyTab.length == 0);
	}
	public boolean containsKey(Object key) {
		return (IndexOf(key) != -1);
	}

	// Sous-classes
	abstract int newIndexOf(Object key);
	abstract int IndexOf(Object key);
	public int size(){
		int size = 0;
		for(int i=0;i<keyTab.length;i++)
			if(keyTab[i] != null)
				size ++;
		return size;
	}
	
	//Autre
	
	public String toString() {
		String str = "";
		for(int i=0;i<this.size();i++)
			str += "("+keyTab[i]+","+valTab[i]+") ";
		return str;
	}
	public Object[] getKeyTab() {
		return keyTab;
	}
	public Object[] getValTab() {
		return valTab;
	}
}
