var expect = require('expect.js');
var _ = require('underscore');
var LanguageModule = require("../../..");

/**
 * This class contains tests for the javascript bindings for the utils
 * @constructor
 * @author Daniel Ortiz
 * @version 0.01
 */
var JavascriptCharUtilsTest = (function(){
	/**
	 * Test the string encoding functionality
	 * @function testStringEncodings
	 * @memberof JavascriptCharUtilsTest
	 */
	function testStringEncodings(){
		var CharUtils = LanguageModule.CharUtils;
		var charUtils = new CharUtils();
		var encodings = charUtils.stringEncodings;
		expect(_.isObject(encodings)).to.eql(true);
		expect(_.has(encodings, "ASCII")).to.eql(true);
		expect(_.has(encodings, "UTF8_BINARY")).to.eql(true);
		expect(_.has(encodings, "ISO_8859_1")).to.eql(true);
		expect(encodings.UTF8_BINARY).to.eql(0);
		expect(encodings.ASCII).to.eql(1);
		expect(encodings.ISO_8859_1).to.eql(2);
	}
	
	/**
	 * Test the language encoding functionality
	 * @function testLanguageEncodings
	 * @memberof JavascriptCharUtilsTest
	 */
	function testLanguageEncodings(){
		var CharUtils = LanguageModule.CharUtils;
		var charUtils = new CharUtils();
		var encodings = charUtils.languageEncodings;
		expect(_.isObject(encodings)).to.eql(true);
		expect(_.has(encodings, "ENGLISH")).to.eql(true);
		expect(_.has(encodings, "SPANISH")).to.eql(true);
		expect(_.has(encodings, "FRENCH")).to.eql(true);
		expect(encodings.ENGLISH).to.eql(0);
		expect(encodings.SPANISH).to.eql(1);
		expect(encodings.FRENCH).to.eql(2);
	}
	
	/**
	 * Test the is hex number character function
	 * @function testIsHexNumberChar
	 * @memberof JavascriptCharUtilsTest
	 */
	function testIsHexNumberChar(){
		var CharUtils = LanguageModule.CharUtils;
		var charUtils = new CharUtils();
		var encodings = charUtils.stringEncodings;
		var isHexChar = charUtils.isHexNumberChar("a");
		var isHexChar2 = charUtils.isHexNumberChar("A");
		var isHexChar3 = charUtils.isHexNumberChar("3");
		var isHexChar4 = charUtils.isHexNumberChar("Z");
		expect(isHexChar).to.eql(true);
		expect(isHexChar2).to.eql(true);
		expect(isHexChar3).to.eql(true);
		expect(isHexChar4).to.eql(false);
	}
	
	/**
	 * Test the is number character function
	 * @function testIsNumber
	 * @memberof JavascriptCharUtilsTest
	 */
	function testIsNumber(){
		var CharUtils = LanguageModule.CharUtils;
		var charUtils = new CharUtils();
		var isNumberChar = charUtils.isNaturalNumberChar("0");
		var isNumberChar2 = charUtils.isNaturalNumberChar("5");
		var isNumberChar3 = charUtils.isNaturalNumberChar("9");
		var isNumberChar4 = charUtils.isNaturalNumberChar("Z");
		expect(isNumberChar).to.eql(true);
		expect(isNumberChar2).to.eql(true);
		expect(isNumberChar3).to.eql(true);
		expect(isNumberChar4).to.eql(false);
	}
	
	/**
	 * Test if it is a valid character function
	 * @function testIsValidChar
	 * @memberof JavascriptCharUtilsTest
	 */
	function testIsValidChar(){
		var CharUtils = LanguageModule.CharUtils;
		var charUtils = new CharUtils();
		var encodings = charUtils.stringEncodings;
		var isNumberChar = charUtils.isValidChar("0",encodings.ASCII);
		var isNumberChar2 = charUtils.isValidChar("5", encodings.ISO_8859_1);
		var isNumberChar3 = charUtils.isValidChar("9", encodings.ASCII);
		var isNumberChar4 = charUtils.isValidChar("Z");
		expect(isNumberChar).to.eql(true);
		expect(isNumberChar2).to.eql(true);
		expect(isNumberChar3).to.eql(true);
		expect(isNumberChar4).to.eql(false);
	}
	
	/**
	 * Test the is in alphabet character function
	 * @function testIsInAlphabetChar
	 * @memberof JavascriptCharUtilsTest
	 */
	function testIsInAlphabetChar(){
		var CharUtils = LanguageModule.CharUtils;
		var charUtils = new CharUtils();
		var encodings = charUtils.stringEncodings;
		var lencodings = charUtils.languageEncodings;
		var isNumberChar = charUtils.isValidChar("0",encodings.ASCII, lencodings.FRENCH);
		var isNumberChar2 = charUtils.isValidChar("5", encodings.ISO_8859_1, lencodings.SPANISH);
		var isNumberChar3 = charUtils.isValidChar("9", encodings.ASCII, lencodings.ENGLISH);
		var isNumberChar4 = charUtils.isValidChar("Z", encodings.UTF8_BINARY, lencodings.ENGLISH);
		expect(isNumberChar).to.eql(true);
		expect(isNumberChar2).to.eql(true);
		expect(isNumberChar3).to.eql(true);
		expect(isNumberChar4).to.eql(false);
	}
	
	/**
	 * Test the is in romance alphabet character function
	 * @function testInRomanceAlphabetChar
	 * @memberof JavascriptCharUtilsTest#
	 */
	function testInRomanceAlphabetChar(){
		var CharUtils = LanguageModule.CharUtils;
		var charUtils = new CharUtils();
		var encodings = charUtils.stringEncodings;
		var isNumberChar = charUtils.isValidChar("0",encodings.ASCII);
		var isNumberChar2 = charUtils.isValidChar("5", encodings.ISO_8859_1);
		var isNumberChar3 = charUtils.isValidChar("9", encodings.ASCII);
		var isNumberChar4 = charUtils.isValidChar("Z", encodings.UTF8_BINARY);
		expect(isNumberChar).to.eql(true);
		expect(isNumberChar2).to.eql(true);
		expect(isNumberChar3).to.eql(true);
		expect(isNumberChar4).to.eql(false);
	}
	
	/**
	 * The public interface
	 */
	return {
		testStringEncodings:testStringEncodings,
		testLanguageEncodings:testLanguageEncodings,
		testIsHexNumberChar:testIsHexNumberChar,
		testIsNumber:testIsNumber,
		testIsValidChar:testIsValidChar,
		testIsInAlphabetChar:testIsInAlphabetChar,
		testInRomanceAlphabetChar:testInRomanceAlphabetChar
	}
})();

describe('Test the javascript char utils', function(){
	it('JavascriptCharUtils String Encodings Test',JavascriptCharUtilsTest.testStringEncodings);
	it('JavascriptCharUtils Language Encodings Test',JavascriptCharUtilsTest.testLanguageEncodings);
	it('JavascriptCharUtils Language Is Hex Char Test', JavascriptCharUtilsTest.testIsHexNumberChar);
	it('JavascriptCharUtils Language Is Number Test', JavascriptCharUtilsTest.testIsNumber);
	it('JavascriptCharUtils Language Is Valid Char Test', JavascriptCharUtilsTest.testIsValidChar);
	it('JavascriptCharUtils Language Is In Alphabet Test', JavascriptCharUtilsTest.testIsInAlphabetChar);
	it('JavascriptCharUtils Language Is In Romance Alphabet Test',JavascriptCharUtilsTest.testInRomanceAlphabetChar);
});


