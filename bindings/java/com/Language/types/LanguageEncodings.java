package com.Language.types;

/**
 * The Language string encoding types
 * @author danielortiz
 */
public enum LanguageEncodings{
	ENGLISH(0),
	SPANISH(1),
	FRENCH(2);
	
	private int state;
	private LanguageEncodings(int s){
		state = s;
	}
	
	/**
	 * Get the integer associated with the string encoding
	 */
	public int getEncodingValue(){
		return state;
	}
}
	