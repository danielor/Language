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
	public native boolean isHexNumberChar(String str, int encoding);
	
	/**
	 * Check if the first character of a java string is a natural number
	 * @param str A java string to test first character
	 * @param encoding The encoding of the string
	 */
	public native boolean isNaturalNumberChar(String str, int encoding);
	
	/**
	 * Check if the first character of a java string is part of the Romance alphabet
	 * @param str A java string to test first character
	 * @param encoding The encoding of the string
	 */
	public native boolean isInRomanceAlphabetChar(String str, int encoding);
	
	/**
	 * Check if the first character of a java string is valid
	 * @param str A java string to test first character
	 * @param encoding The encoding of the string
	 */
	public native boolean isValidChar(String str, int encoding);
	
	/**
	 * Check if the first character of a character is in an alphabet
	 * @param str A java string to test first character
	 * @param encoding The encoding of the string
	 * @param language The language of the string
	 */
	public native boolean isInAlphabetChar(String str, int encoding, int language);
};
