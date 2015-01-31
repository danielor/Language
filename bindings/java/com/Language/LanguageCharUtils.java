package com.Language;

/**
 * The Language char utils interface
 * @author Daniel Ortiz
 */
public class LanguageCharUtils{
	static{
		System.loadLibrary("Language");
	}
	
	/**
	 * Check if the first character of a java string is a hex character
	 * @param str A java string to test first character
	 * @param encoding The encoding of the string
	 */
	public native boolean isHexNumber(String str, int encoding);
	
	/**
	 * Check if the first character of a java string is a natural number
	 * @param str A java string to test first character
	 * @param encoding The encoding of the string
	 */
	public native boolean isNaturalNumber(String str, int encoding);
	
	/**
	 * Check if the first character of a java string is part of the Romance alphabet
	 * @param str A java string to test first character
	 * @param encoding The encoding of the string
	 */
	public native boolean isInRomanceAlphabet(String str, int encoding);
	
	/**
	 * Check if the first character of a java string is valid
	 * @param str A java string to test first character
	 * @param encoding The encoding of the string
	 */
	public native boolean isValid(String str, int encoding);
	
	/**
	 * Check if the first character of a character is in an alphabet
	 * @param str A java string to test first character
	 * @param encoding The encoding of the string
	 * @param language The language of the string
	 */
	public native boolean isInAlphabet(String str, int encoding, int language);

	/**
	 * Check if the character of a string is in the lower part of an alphabet
	 * @param str A java string to test the first character
	 * @param encoding The encoding of the string
	 * @param language The language of the string
	 */
	public native boolean isLowerCaseInAlphabet(String str, int encoding, int language);

	/**
	 * Check if the character of a string is in the upper part of an alphabet
	 * @param str A java string to test the character
	 * @param encoding The encoding of the string
	 * @param language The language of the string
	 */
	public native boolean isUpperCaseInAlphabet(String str, int encoding, int language);
	
	/**
	 * Check if a character is a punctuation makr in an alphabet of a language
	 * for a specific encoding
	 * @param str A java string
	 * @param encoding The encoding of the str
	 * @param language The language of the str
	 */
	public native boolean isPunctuationMarkInAlphabet(String str, int encoding, int language);
};
