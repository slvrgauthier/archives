package dico;

import static org.junit.Assert.assertTrue;

import org.junit.Before;
import org.junit.Test;

public class testFast extends testAbstract {

	@Before
	public void setUp() throws Exception {
		dico = new FastDictionary();
	}

	@Test
	public void testSizeDicoAfterAdding() {
		String k="key",v="value";
		dico.put(k, v);
		assertTrue(dico.size()/dico.getKeyTab().length > 3/4);
	}

}
