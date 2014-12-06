package test.bindings.java;

import com.Language.LanguageStringUtils;
import static org.junit.Assert.assertEquals;
import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;

/**
 * A class that encaspulate different string utils
 * @author danielortiz
 */
public class StringUtilsTest{

	/**
	 * The test for the length of string
	 */
	@Test
	public void testLength(){
		LanguageStringUtils stringUtil = new LanguageStringUtils();
		int stringLength = stringUtil.length("Happy", 0);
		assertEquals("'Happy' must have string length 5", stringUtil.length("Happy", 0), 5);
	}
	
	/**
	 * The test for the length escaped of string
	 */
	@Test
	public void testLengthEscaped(){
		LanguageStringUtils stringUtil = new LanguageStringUtils();
		int stringLengthFirst = stringUtil.lengthEscaped("Healthy", 1, "YUM", 0);
		int stringLengthSecond = stringUtil.lengthEscaped("HealthyYUM2345N", 1, "YUM", 0);
		int stringLengthThird = stringUtil.lengthEscapedWithEnd("HealthyYUM2345NR", 1, "YUM", 0, "N");
		assertEquals("'Healthy' must have string length 7", stringLengthFirst, 7);
		assertEquals("'HealthyYUM2345N' with YUM escaped has string length 9", stringLengthSecond, 9);
		assertEquals("'HealthyYUM2345NR' with 'YUM' escaped and end string 'N'", stringLengthThird, 9);
	}
}