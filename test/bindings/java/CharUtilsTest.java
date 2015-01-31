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

		boolean isHexNumberChar1 = charUtils.isHexNumber("a", asciiEncoding);
		boolean isHexNumberChar2 = charUtils.isHexNumber("A", asciiEncoding);
		boolean isHexNumberChar3 = charUtils.isHexNumber("3", asciiEncoding);
		boolean isHexNumberChar4 = charUtils.isHexNumber("Z", asciiEncoding);
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
		boolean isNumberChar = charUtils.isNaturalNumber("0", asciiEncoding);
		boolean isNumberChar2 = charUtils.isNaturalNumber("5", asciiEncoding);
		boolean isNumberChar3 = charUtils.isNaturalNumber("9", asciiEncoding);
		boolean isNumberChar4 = charUtils.isNaturalNumber("Z", asciiEncoding);
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
		boolean isValidChar = charUtils.isValid("0", asciiEncoding);
		boolean isValidChar2 = charUtils.isValid("5", asciiEncoding);
		boolean isValidChar3 = charUtils.isValid("9", asciiEncoding);
		boolean isValidChar4 = charUtils.isValid("Z", asciiEncoding);
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
		boolean isInAlphabetChar = charUtils.isInAlphabet("0", asciiEncoding, englishLanguage);
		boolean isInAlphabetChar2 = charUtils.isInAlphabet("5", asciiEncoding, englishLanguage);
		boolean isInAlphabetChar3 = charUtils.isInAlphabet("a", asciiEncoding, englishLanguage);
		boolean isInAlphabetChar4 = charUtils.isInAlphabet("Z", asciiEncoding, englishLanguage);
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
		boolean isRomanceChar = charUtils.isInRomanceAlphabet("0", asciiEncoding);
		boolean isRomanceChar2 = charUtils.isInRomanceAlphabet("5", asciiEncoding);
		boolean isRomanceChar3 = charUtils.isInRomanceAlphabet("a", asciiEncoding);
		boolean isRomanceChar4 = charUtils.isInRomanceAlphabet("Z", asciiEncoding);
		assertEquals("'0' is not a char in the romance alphabet", isRomanceChar, false);
		assertEquals("'5' is not a char in the romance alphabet", isRomanceChar2, false);
		assertEquals("'a' is a char in the romance alphabet", isRomanceChar3, true);
		assertEquals("'Z' is a char in the romance alphabet", isRomanceChar4, true);
	}
	
	/**
	 * Test if a character is in the upper case part of an alphabet
	 */
	@Test
	public void testIsLowerCaseInAlphabet(){
		LanguageCharUtils charUtils = new LanguageCharUtils();
		int asciiEncoding = StringEncodings.ASCII.getEncodingValue();
		int englishEncoding = LanguageEncodings.ENGLISH.getEncodingValue();
		boolean isLowerCaseChar = charUtils.isLowerCaseInAlphabet("0", asciiEncoding, englishEncoding);
		boolean isLowerCaseChar2 = charUtils.isLowerCaseInAlphabet("5", asciiEncoding, englishEncoding);
		boolean isLowerCaseChar3 = charUtils.isLowerCaseInAlphabet("a", asciiEncoding, englishEncoding);
		boolean isLowerCaseChar4 = charUtils.isLowerCaseInAlphabet("Z", asciiEncoding, englishEncoding);
		assertEquals("'0' is not lower case in the english alphabet", isLowerCaseChar, false);
		assertEquals("'5' is not lower case in the english alphabet", isLowerCaseChar2, false);
		assertEquals("'a' is lower case in the english alphabet", isLowerCaseChar3, true);
		assertEquals("'Z' is not lower case in the english alphabet", isLowerCaseChar4, false);
	}
	
	/**
	 * Test if a character is in the upper case part of an alphabet
	 */
	@Test
	public void testIsUpperCaseInAlphabet(){
		LanguageCharUtils charUtils = new LanguageCharUtils();
		int asciiEncoding = StringEncodings.ASCII.getEncodingValue();
		int englishEncoding = LanguageEncodings.ENGLISH.getEncodingValue();
		boolean isUpperCaseChar = charUtils.isUpperCaseInAlphabet("0", asciiEncoding, englishEncoding);
		boolean isUpperCaseChar2 = charUtils.isUpperCaseInAlphabet("5", asciiEncoding, englishEncoding);
		boolean isUpperCaseChar3 = charUtils.isUpperCaseInAlphabet("a", asciiEncoding, englishEncoding);
		boolean isUpperCaseChar4 = charUtils.isUpperCaseInAlphabet("Z", asciiEncoding, englishEncoding);
		assertEquals("'0' is not upper case in the english alphabet", isUpperCaseChar, false);
		assertEquals("'5' is not upper case in the english alphabet", isUpperCaseChar2, false);
		assertEquals("'a' is not upper case in the english alphabet", isUpperCaseChar3, false);
		assertEquals("'Z' is upper case in the english alphabet", isUpperCaseChar4, true);
	}
	
	/**
	 * Test if a character is a punctuation mark of an alphabet
	 */
	@Test
	public void testIsPunctuationMarkInAlphabet(){
		LanguageCharUtils charUtils = new LanguageCharUtils();
		int asciiEncoding = StringEncodings.ASCII.getEncodingValue();
		int englishEncoding = LanguageEncodings.ENGLISH.getEncodingValue();
		boolean isUpperCaseChar = charUtils.isLowerCaseInAlphabet(",", asciiEncoding, englishEncoding);
		boolean isUpperCaseChar2 = charUtils.isLowerCaseInAlphabet("5", asciiEncoding, englishEncoding);
		boolean isUpperCaseChar3 = charUtils.isLowerCaseInAlphabet("a", asciiEncoding, englishEncoding);
		boolean isUpperCaseChar4 = charUtils.isLowerCaseInAlphabet("Z", asciiEncoding, englishEncoding);
		assertEquals("',' is not a punctuation mark in the english alphabet", isUpperCaseChar, false);
		assertEquals("'5' is not punctuation mark in the english alphabet", isUpperCaseChar2, false);
		assertEquals("'a' is not punctuation mark in the english alphabet", isUpperCaseChar3, true);
		assertEquals("'Z' is not punctuation mark in the english alphabet", isUpperCaseChar4, false);
	}
}