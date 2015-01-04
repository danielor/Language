package test.bindings.java;

import com.Language.LanguageCharUtils;
import com.Language.types.LanguageEncodings;
import com.Language.types.StringEncodings;
import static org.junit.Assert.assertEquals;
import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;

/**
 * A class that encapsulates different char utils
 * @author danielortiz
 */
public class CharUtilsTest{
	/**
	 * Test the is hex number char
	 */
	@Test
	public void testIsHexNumber(){
		LanguageCharUtils charUtils = new LanguageCharUtils();
		int asciiEncoding = StringEncodings.ASCII.getEncodingValue();

		boolean isHexNumberChar1 = charUtils.isHexNumberChar("a", asciiEncoding);
		boolean isHexNumberChar2 = charUtils.isHexNumberChar("A", asciiEncoding);
		boolean isHexNumberChar3 = charUtils.isHexNumberChar("3", asciiEncoding);
		boolean isHexNumberChar4 = charUtils.isHexNumberChar("Z", asciiEncoding);
		assertEquals("'a' is a hex character", isHexNumberChar1, true);
		assertEquals("'A' is a hex character", isHexNumberChar2, true);
		assertEquals("'3' is a hex character", isHexNumberChar3, true);
		assertEquals("'Z' is not a hex character", isHexNumberChar4, false);
	}
	
	/**
	 * Test the is number char
	 */
	@Test
	public void testIsNumber(){
		LanguageCharUtils charUtils = new LanguageCharUtils();
		int asciiEncoding = StringEncodings.ASCII.getEncodingValue();
		boolean isNumberChar = charUtils.isNaturalNumberChar("0", asciiEncoding);
		boolean isNumberChar2 = charUtils.isNaturalNumberChar("5", asciiEncoding);
		boolean isNumberChar3 = charUtils.isNaturalNumberChar("9", asciiEncoding);
		boolean isNumberChar4 = charUtils.isNaturalNumberChar("Z", asciiEncoding);
		assertEquals("'0' is a number", isNumberChar, true);
		assertEquals("'5' is a number", isNumberChar2, true);
		assertEquals("'9' is a number", isNumberChar3, true);
		assertEquals("'Z' is not a number", isNumberChar4, false);
	}
	
	/**
	 * Test the is valid char
	 */
	@Test
	public void testIsValidChar(){
		LanguageCharUtils charUtils = new LanguageCharUtils();
		int asciiEncoding = StringEncodings.ASCII.getEncodingValue();
		boolean isValidChar = charUtils.isValidChar("0", asciiEncoding);
		boolean isValidChar2 = charUtils.isValidChar("5", asciiEncoding);
		boolean isValidChar3 = charUtils.isValidChar("9", asciiEncoding);
		boolean isValidChar4 = charUtils.isValidChar("Z", asciiEncoding);
		assertEquals("'0' is a char", isValidChar, true);
		assertEquals("'5' is a char", isValidChar2, true);
		assertEquals("'9' is a char", isValidChar3, true);
		assertEquals("'Z' is a char", isValidChar4, true);
	}
	
	/**
	 * Test is in alphabet char
	 */
	@Test
	public void testInAlphabetChar(){
		LanguageCharUtils charUtils = new LanguageCharUtils();
		int asciiEncoding = StringEncodings.ASCII.getEncodingValue();
		int englishLanguage  = LanguageEncodings.ENGLISH.getEncodingValue();
		boolean isInAlphabetChar = charUtils.isInAlphabetChar("0", asciiEncoding, englishLanguage);
		boolean isInAlphabetChar2 = charUtils.isInAlphabetChar("5", asciiEncoding, englishLanguage);
		boolean isInAlphabetChar3 = charUtils.isInAlphabetChar("a", asciiEncoding, englishLanguage);
		boolean isInAlphabetChar4 = charUtils.isInAlphabetChar("Z", asciiEncoding, englishLanguage);
		assertEquals("'0' is not a char in the english alphabet", isInAlphabetChar, false);
		assertEquals("'5' is not a char in the english alphabet", isInAlphabetChar2, false);
		assertEquals("'a' is a char in the english alphabet", isInAlphabetChar3, true);
		assertEquals("'Z' is a char in the english alphabet", isInAlphabetChar4, true);
	}
	
	/**
	 * Test if a character is in the romance alphabet
	 */
	@Test
	public void testInRomanceChar(){
		LanguageCharUtils charUtils = new LanguageCharUtils();
		int asciiEncoding = StringEncodings.ASCII.getEncodingValue();
		boolean isRomanceChar = charUtils.isInRomanceAlphabetChar("0", asciiEncoding);
		boolean isRomanceChar2 = charUtils.isInRomanceAlphabetChar("5", asciiEncoding);
		boolean isRomanceChar3 = charUtils.isInRomanceAlphabetChar("a", asciiEncoding);
		boolean isRomanceChar4 = charUtils.isInRomanceAlphabetChar("Z", asciiEncoding);
		assertEquals("'0' is not a char in the romance alphabet", isRomanceChar, false);
		assertEquals("'5' is not a char in the romance alphabet", isRomanceChar2, false);
		assertEquals("'a' is a char in the romance alphabet", isRomanceChar3, true);
		assertEquals("'Z' is a char in the romance alphabet", isRomanceChar4, true);
	}
}