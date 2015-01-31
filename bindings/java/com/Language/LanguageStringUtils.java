package com.Language;
/**
 * The Language string utils interface
 * @author danielortiz
 */
public class LanguageStringUtils{
	static{
		System.loadLibrary("Language");			// Load the language string utils
	}
	

	/**
	 * Get the length of a java string
	 * @param str A java string to get the length
	 * @param enconding The encoding of the java string
	 */
	public native int length(String str, int encoding);
	
	/**
	 * Get the length of an escaped java string without an end string
	 * @param str A java string
	 * @param encoding The encoding of str
	 * @param escapedStr A java string that represents the escaped chars
	 * @param escapedEncoding The escaped encoding of the str
	 */
	public native int lengthEscaped(String str, int encoding, String escapedStr, int escapedEncoding);
	
	/**
	 * Get the length of an escaped java string with an end string
	 * @param str A java string
	 * @param encoding The encoding of str
	 * @param escapedStr A java string that represents the escaped chars
	 * @param escapedEncoding The escaped encoding of the str
	 * @param endStr The ending str
	 */
	public native int lengthEscapedWithEnd(String str, int encoding, String escapedStr, int escapedEncoding,
			String endStr);
	
	/**
	 * Check if a character sequence is a natural number
	 * @param str A java string
	 * @param encoding The encoding of str
	 */
	public native boolean isNaturalNumber(String str, int encoding);
	
	/**
	 * Check if a character sequence is a hex number
	 * @param str A java string
	 * @param encoding The encoding of str
	 */
	public native boolean isHexNumber(String str, int encoding);
	
	/**
	 * Check if a character sequence is a valid character sequence in
	 * an arbitrary encoding
	 * @param str A java string
	 * @param encoding The encoding of the str
	 */
	public native boolean isValid(String str, int encoding);
	
	/**
	 * Check if a character sequence is in the romance alphabet in an
	 * arbitrary encoding
	 * @param str A java string
	 * @param encoding The encoding of the str
	 */
	public native boolean isInRomanceAlphabet(String str, int encoding);
	
	/**
	 * Check if a character sequence is in the alphabet of a language
	 * @param str A java string
	 * @param encoding The encoding of the str
	 * @param language The language of the str
	 */
	public native boolean isInAlphabet(String str, int encoding, int language);
	
	/**
	 * Check if a character sequence is upper case in an alphabet of a language
	 * for a specific encoding
	 * @param str A java string
	 * @param encoding The encoding of the str
	 * @param language The language of the str
	 */
	public native boolean isUpperCaseInAlphabet(String str, int encoding, int language);
	
	/**
	 * Check if a character sequence is lower case in an alphabet of a language
	 * for a specific encoding
	 * @param str A java string
	 * @param encoding The encoding of the str
	 * @param language The language of the str
	 */
	public native boolean isLowerCaseInAlphabet(String str, int encoding, int language);
	
	/**
	 * Check if a character sequence is a punctuation makr in an alphabet of a language
	 * for a specific encoding
	 * @param str A java string
	 * @param encoding The encoding of the str
	 * @param language The language of the str
	 */
	public native boolean isPunctuationMarkInAlphabet(String str, int encoding, int language);
	
	public static void main(String[] args) {
		new LanguageStringUtils().length("Hello", 0);  // invoke the native method
	}
};