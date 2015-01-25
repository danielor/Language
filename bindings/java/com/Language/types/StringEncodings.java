package com.Language.types;

/**
 * The Language string encoding types
 * @author danielortiz
 */
public enum StringEncodings{
	UTF8_BINARY(0),
	ASCII(1),
	ISO_8859_1(2);
	
	private int state;
	private StringEncodings(int s){
		state = s;
	}
	
	/**
	 * Get the integer associated with the string encoding
	 */
	public int getEncodingValue(){
		return state;
	}
}
	