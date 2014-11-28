package test.bindings.java;

import Language.LanguageStringUtils.
import static org.junit.Assert.assertEquals;
import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;


public class StringUtilsTest{

	@Test
	public void testLength(){
		LanguageStringUtils stringUtil = new LanguageStringUtils();
		int stringLength = stringUtil.length("Happy", 0);
		assertEquals("'Happy' must have string length 5", stringUtil.length("Happy", 0), 5);
	}
}