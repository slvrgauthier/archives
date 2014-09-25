package dico;

import org.junit.runner.RunWith;
import org.junit.runners.Suite;
import org.junit.runners.Suite.SuiteClasses;

@RunWith(Suite.class)
@SuiteClasses({ testFast.class, testOrdered.class, testSorted.class })
public class AllTests {

}
