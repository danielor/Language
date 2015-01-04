package test.bindings.java;

import com.Language.LanguageStringUtils;
import com.Language.types.LanguageEncodings;
import com.Language.types.StringEncodings;
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
	
	/**
	 * Test if the sequence is a natural number
	 */
	@Test
	public void testIsNaturalNumber(){
		LanguageStringUtils stringUtil = new LanguageStringUtils();
		boolean isNaturalNumber1 = stringUtil.isNaturalNumber("567", 1);
		boolean isNaturalNumber2 = stringUtil.isNaturalNumber("n", 1);
		boolean isNaturalNumber3 = stringUtil.isNaturalNumber("3", 1);
		boolean isNaturalNumber4 = stringUtil.isNaturalNumber("5gd3", 1);
		boolean isNaturalNumber5 = stringUtil.isNaturalNumber("1de3g3dg3", 1);
		
		// Assert equality
		assertEquals("'567' is a natural number", isNaturalNumber1, true);
		assertEquals("'n' is not a natural number", isNaturalNumber2, false);
		assertEquals("'3' is a natural number", isNaturalNumber1, true);
		assertEquals("'5gd3' is not a natural number", isNaturalNumber2, false);
		assertEquals("'1de3g3dg3' is not a natural number", isNaturalNumber2, false);
	}
	
	/**
	 * Test if a sequence is a hex number
	 */
	@Test
	public void testIsHexNumber(){
		LanguageStringUtils stringUtils = new LanguageStringUtils();
		int asciiEncoding = StringEncodings.ASCII.getEncodingValue();
		boolean isHexNumber1 = stringUtils.isHexNumber("abcdef", asciiEncoding);
		boolean isHexNumber2 = stringUtils.isHexNumber("ABCDEF", asciiEncoding);
		boolean isHexNumber3 = stringUtils.isHexNumber("0123456789", asciiEncoding);
		boolean isHexNumber4 = stringUtils.isHexNumber("g", asciiEncoding);
		boolean isHexNumber5 = stringUtils.isHexNumber("G", asciiEncoding);
		
		assertEquals("'abcdef' is a hex number", isHexNumber1, true);
		assertEquals("'ABCDEF' is a hex number", isHexNumber2, true);
		assertEquals("'0123456789' is a hex number", isHexNumber3, true);
		assertEquals("'g' is not a hex number", isHexNumber4, false);
		assertEquals("'G' is not a hex number", isHexNumber5, false);
	}
}