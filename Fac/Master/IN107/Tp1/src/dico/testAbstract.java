package dico;

import static org.junit.Assert.*;
import org.junit.Before;
import org.junit.Test;

public abstract class testAbstract {
	protected AbstractDictionary dico;
	
	@Before
	public abstract void setUp() throws Exception;
	
	@Test
	public void testPut() {
		String k="key",v="value";
		dico.put(k, v);
		assertTrue(dico.containsKey(k));
	}
	
	@Test
	public void testAddOneElementToEmptyDico() {
		String k="key",v="value";
		dico.put(k, v);
		assertEquals(1,dico.size());
		assertTrue(dico.containsKey(k));
		assertTrue(dico.get(k) == v);
	}
	
	@Test
	public void testSizeDicoAfterAdding() {
		assertTrue(dico.size() == dico.getKeyTab().length);
		String k="key",v="value";
		dico.put(k, v);
		assertTrue(dico.size() == dico.getKeyTab().length);
	}

}
