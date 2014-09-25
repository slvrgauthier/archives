package dico;

import org.junit.Before;

public class testOrdered extends testAbstract {
	@Before
	public void setUp() throws Exception {
		dico = new OrderedDictionary();
	}
}
