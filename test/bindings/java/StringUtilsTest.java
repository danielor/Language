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
	
	/**
	 * Test if a sequence is a valid sequence
	 */
	@Test
	public void testIsValid(){
		LanguageStringUtils stringUtils = new LanguageStringUtils();
		int asciiEncoding = StringEncodings.ASCII.getEncodingValue();
		int iso8859Encoding = StringEncodings.ISO_8859_1.getEncodingValue();
		String invalidString = new String(new char[]{0x19,0x78});
		boolean isValid1 = stringUtils.isValid("Howdy", asciiEncoding);
		boolean isValid2 = stringUtils.isValid("First", asciiEncoding);
		boolean isValid3 = stringUtils.isValid("0123456789", asciiEncoding);
		boolean isValid4 = stringUtils.isValid("g", asciiEncoding);
		boolean isValid5 = stringUtils.isValid(invalidString, iso8859Encoding);
		
		assertEquals("'Howdy' is a valid english string", isValid1, true);
		assertEquals("'First' is a valid english string", isValid2, true);
		assertEquals("'0123456789' is not a valid english string", isValid3, true);
		assertEquals("'g' is a valid english string", isValid4, true);
		assertEquals("'Añoro' is not a valid english string", isValid5, false);
	}
	
	/**
	 * Test if is a romance alphabet sequence
	 */
	@Test
	public void testIsRomanceAlphabet(){
		LanguageStringUtils stringUtils = new LanguageStringUtils();
		int asciiEncoding = StringEncodings.ASCII.getEncodingValue();
		int iso8859Encoding = StringEncodings.ISO_8859_1.getEncodingValue();
		String invalidString = new String(new char[]{0x19,0x78});
		boolean isValid1 = stringUtils.isInRomanceAlphabet("Howdy", asciiEncoding);
		boolean isValid2 = stringUtils.isInRomanceAlphabet("First", asciiEncoding);
		boolean isValid3 = stringUtils.isInRomanceAlphabet("0123456789", asciiEncoding);
		boolean isValid4 = stringUtils.isInRomanceAlphabet("g", asciiEncoding);
		boolean isValid5 = stringUtils.isInRomanceAlphabet(invalidString, iso8859Encoding);
		
		assertEquals("'Howdy' is a valid romance string", isValid1, true);
		assertEquals("'First' is a valid romance string", isValid2, true);
		assertEquals("'0123456789' is not a valid romance string", isValid3, false);
		assertEquals("'g' is a valid romance string", isValid4, true);
		assertEquals("'Añoro' is not a valid romance string", isValid5, false);
	}
	
	/**
	 * Test if an alphabet sequence
	 */
	@Test
	public void testIsInAlphabet(){
		LanguageStringUtils stringUtils = new LanguageStringUtils();
		int asciiEncoding = StringEncodings.ASCII.getEncodingValue();
		int iso8859Encoding = StringEncodings.ISO_8859_1.getEncodingValue();
		int englishLanguage = LanguageEncodings.ENGLISH.getEncodingValue();
		String invalidString = "Añoro";
		boolean isValid1 = stringUtils.isInAlphabet("Howdy", asciiEncoding,englishLanguage);
		boolean isValid2 = stringUtils.isInAlphabet("First", asciiEncoding, englishLanguage);
		boolean isValid3 = stringUtils.isInAlphabet("0123456789", asciiEncoding, englishLanguage);
		boolean isValid4 = stringUtils.isInAlphabet("g", asciiEncoding, englishLanguage);
		boolean isValid5 = stringUtils.isInAlphabet(invalidString, iso8859Encoding, englishLanguage);
		
		assertEquals("'Howdy' is a valid english string", isValid1, true);
		assertEquals("'First' is a valid english string", isValid2, true);
		assertEquals("'0123456789' is not a valid english string", isValid3, false);
		assertEquals("'g' is a valid english string", isValid4, true);
		assertEquals("'Añoro' is not a valid english string", isValid5, false);
	}
	
	/**
	 * Test if it is the lower case part of the alphabet sequence
	 */
	@Test
	public void testIsLowerCaseInAlphabet(){
		LanguageStringUtils stringUtils = new LanguageStringUtils();
		int asciiEncoding = StringEncodings.ASCII.getEncodingValue();
		int iso8859Encoding = StringEncodings.ISO_8859_1.getEncodingValue();
		int englishLanguage = LanguageEncodings.ENGLISH.getEncodingValue();
		String invalidString = "Añoro";
		boolean isValid1 = stringUtils.isLowerCaseInAlphabet("Howdy", asciiEncoding,englishLanguage);
		boolean isValid2 = stringUtils.isLowerCaseInAlphabet("First", asciiEncoding, englishLanguage);
		boolean isValid3 = stringUtils.isLowerCaseInAlphabet("0123456789", asciiEncoding, englishLanguage);
		boolean isValid4 = stringUtils.isLowerCaseInAlphabet("g", asciiEncoding, englishLanguage);
		boolean isValid5 = stringUtils.isLowerCaseInAlphabet(invalidString, iso8859Encoding, englishLanguage);
		
		assertEquals("'Howdy' is not a lower case english string", isValid1,false);
		assertEquals("'First' is not a lower case english string", isValid2, false);
		assertEquals("'0123456789' is not a lower case english string", isValid3, false);
		assertEquals("'g' is  a lower case english string", isValid4, true);
		assertEquals("'Añoro' is not a valid english string", isValid5, false);
	}
	
	/**
	 * Test if it is the upper case part of the alphabet sequence
	 */
	@Test
	public void testIsUpperCaseInAlphabet(){
		LanguageStringUtils stringUtils = new LanguageStringUtils();
		int asciiEncoding = StringEncodings.ASCII.getEncodingValue();
		int iso8859Encoding = StringEncodings.ISO_8859_1.getEncodingValue();
		int englishLanguage = LanguageEncodings.ENGLISH.getEncodingValue();
		String invalidString = "Añoro";
		boolean isValid1 = stringUtils.isUpperCaseInAlphabet("Howdy", asciiEncoding,englishLanguage);
		boolean isValid2 = stringUtils.isUpperCaseInAlphabet("First", asciiEncoding, englishLanguage);
		boolean isValid3 = stringUtils.isUpperCaseInAlphabet("0123456789", asciiEncoding, englishLanguage);
		boolean isValid4 = stringUtils.isUpperCaseInAlphabet("G", asciiEncoding, englishLanguage);
		boolean isValid5 = stringUtils.isUpperCaseInAlphabet(invalidString, iso8859Encoding, englishLanguage);
		
		assertEquals("'Howdy' is not a upper case english string", isValid1, false);
		assertEquals("'First' is not a upper case english string", isValid2, false);
		assertEquals("'0123456789' is not a upper case english string", isValid3, false);
		assertEquals("'G' is  a upper case english string", isValid4, true);
		assertEquals("'Añoro' is not an upper english string", isValid5, false);
	}
	
	/**
	 * Test if it is a punctuation mark in an alphabet sequence
	 */
	@Test
	public void testIsPunctuationMarkInAlphabet(){
		LanguageStringUtils stringUtils = new LanguageStringUtils();
		int asciiEncoding = StringEncodings.ASCII.getEncodingValue();
		int iso8859Encoding = StringEncodings.ISO_8859_1.getEncodingValue();
		int englishLanguage = LanguageEncodings.ENGLISH.getEncodingValue();
		String invalidString = "Añoro";
		boolean isValid1 = stringUtils.isPunctuationMarkInAlphabet("Howdy", asciiEncoding,englishLanguage);
		boolean isValid2 = stringUtils.isPunctuationMarkInAlphabet("First", asciiEncoding, englishLanguage);
		boolean isValid3 = stringUtils.isPunctuationMarkInAlphabet("0123456789", asciiEncoding, englishLanguage);
		boolean isValid4 = stringUtils.isPunctuationMarkInAlphabet(",", asciiEncoding, englishLanguage);
		boolean isValid5 = stringUtils.isPunctuationMarkInAlphabet(invalidString, iso8859Encoding, englishLanguage);
		
		assertEquals("'Howdy' is not a upper case english string", isValid1, false);
		assertEquals("'First' is not a upper case english string", isValid2, false);
		assertEquals("'0123456789' is not a upper case english string", isValid3, false);
		assertEquals("',' is  a upper case english string", isValid4, true);
		assertEquals("'Añoro' is not an upper english string", isValid5, false);
	}
}