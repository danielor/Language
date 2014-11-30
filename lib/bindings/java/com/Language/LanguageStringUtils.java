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
	
	public static void main(String[] args) {
		new LanguageStringUtils().length("Hello", 0);  // invoke the native method
	}
};