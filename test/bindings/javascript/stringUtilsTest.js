var expect = require('expect.js');
var _ = require('underscore');
var LanguageModule = require("../../..");

/**
 * This class contains tests for the javascript bindings for the string
 * utils 
 * @constructor
 * @author Daniel Ortiz
 * @version 0.01
 */
var JavascriptStringUtilsTest = (function(){
	/**
	 * Test the string length function
	 * @function testStringLength
	 * @memberof JavascriptStringUtilsTest
	 */
	function testStringLength(){
		var StringUtils = LanguageModule.StringUtils;
		var stringUtils = new StringUtils();
		var length = stringUtils.length("hiccup", 0);
		expect(length).to.eql(6);
	}
	
	/**
	 * Test the string length unescaped function
	 * @function testStringLengthEscaped
	 * @memberof JavascriptStringUtilsTest
	 */
	function testStringLengthEscaped(){
		var StringUtils = LanguageModule.StringUtils;
		var stringUtils = new StringUtils();
		
		// Run the relevant tests
		var lengthEscapedFirst = stringUtils.lengthEscaped("Healthy", 1, "YUM", 0);
		var lengthEscapedSecond = stringUtils.lengthEscaped("HealthyYUM2345N", 1, "YUM", 0);
		var lengthEscapedThird = stringUtils.lengthEscaped("HealthyYUM2345NR", 1, "YUM", 0, "N");
		expect(lengthEscapedFirst).to.eql(7);
		expect(lengthEscapedSecond).to.eql(9);
		expect(lengthEscapedThird).to.eql(9);
	}
	
	/**
	 * Test the isNumber sequence functionality
	 * @function testIsNumberSequence
	 * @memberof JavascriptStringUtilsTest
	 */
	function testIsNaturalNumber(){
		var StringUtils = LanguageModule.StringUtils;
		var stringUtils = new StringUtils();
		
		// Test the isNumberSequence
		var numberSequenceTest1 = stringUtils.isNaturalNumber("567", 1);
		var numberSequenceTest2 = stringUtils.isNaturalNumber("n", 0);
		var numberSequenceTest3 = stringUtils.isNaturalNumber("5gd3", 2);
		var numberSequenceTest4 = stringUtils.isNaturalNumber("1de3g3dg3", 0);
		expect(numberSequenceTest1).to.eql(true);
		expect(numberSequenceTest2).to.eql(false);
		expect(numberSequenceTest3).to.eql(false);
		expect(numberSequenceTest4).to.eql(false);
	}
	
	/**
	 * Test the string encoding functionality
	 * @function testStringEncodings
	 * @memberof JavascriptStringUtilsTest
	 */
	function testStringEncodings(){
		var StringUtils = LanguageModule.StringUtils;
		var stringUtils = new StringUtils();
		var encodings = stringUtils.stringEncodings;
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
	 * @memberof JavascriptStringUtilsTest
	 */
	function testLanguageEncodings(){
		var StringUtils = LanguageModule.StringUtils;
		var stringUtils = new StringUtils();
		var encodings = stringUtils.languageEncodings;
		expect(_.isObject(encodings)).to.eql(true);
		expect(_.has(encodings, "ENGLISH")).to.eql(true);
		expect(_.has(encodings, "SPANISH")).to.eql(true);
		expect(_.has(encodings, "FRENCH")).to.eql(true);
		expect(encodings.ENGLISH).to.eql(0);
		expect(encodings.SPANISH).to.eql(1);
		expect(encodings.FRENCH).to.eql(2);
	}
	
	/**
	 * Test the hex number functionality
	 * @function testIsHexNumber
	 * @memberof JavascriptUtilsTest
	 */
	function testIsHexNumber(){
		var StringUtils = LanguageModule.StringUtils;
		var stringUtils = new StringUtils();
		var encodings = stringUtils.stringEncodings;
		
		// Get the hex number
		var hexSequenceTest1 = stringUtils.isHexNumber("abcdef", encodings.ASCII);
		var hexSequenceTest2 = stringUtils.isHexNumber("ABCDEF", encodings.ASCII);
		var hexSequenceTest3 = stringUtils.isHexNumber("0123456789", encodings.ASCII);
		var hexSequenceTest4 = stringUtils.isHexNumber("g", encodings.ASCII);
		var hexSequenceTest5 = stringUtils.isHexNumber("G", encodings.ASCII);
		expect(hexSequenceTest1).to.eql(true);
		expect(hexSequenceTest2).to.eql(true);
		expect(hexSequenceTest3).to.eql(true);
		expect(hexSequenceTest4).to.eql(false);
		expect(hexSequenceTest5).to.eql(false);
	}
	
	/**
	 * Test the is valid functionality
	 * @function testIsValid
	 * @memberof JavascriptStringUtilsTest
	 */
	function testIsValid(){
		var StringUtils = LanguageModule.StringUtils;
		var stringUtils = new StringUtils();
		var encodings = stringUtils.stringEncodings;
		
		var invalidString = "G" + String.fromCharCode(13);
		var validTest1 = stringUtils.isValid("abcdef", encodings.ASCII);
		var validTest2 = stringUtils.isValid("ABCDEF", encodings.ASCII);
		var validTest3 = stringUtils.isValid("0123456789", encodings.ASCII);
		var validTest4 = stringUtils.isValid("g", encodings.ASCII);
		var validTest5 = stringUtils.isValid(invalidString, encodings.ISO_8859_1);
		expect(validTest1).to.eql(true);
		expect(validTest2).to.eql(true);
		expect(validTest3).to.eql(true);
		expect(validTest4).to.eql(true);
		expect(validTest5).to.eql(false);
	}
	
	/**
	 * Test the is in romance alphabet functionality
	 * @function testIsInRomanceAlphabet
	 * @memberof JavascriptStringUtilsTest
	 */
	function testIsInRomanceAlphabet(){
		var StringUtils = LanguageModule.StringUtils;
		var stringUtils = new StringUtils();
		var encodings = stringUtils.stringEncodings;
		var romanceTest1 = stringUtils.isInRomanceAlphabet("abcdef", encodings.ASCII);
		var romanceTest2 = stringUtils.isInRomanceAlphabet("ABCDEF", encodings.ASCII);
		var romanceTest3 = stringUtils.isInRomanceAlphabet("0123456789", encodings.ASCII);
		var romanceTest4 = stringUtils.isInRomanceAlphabet("g", encodings.ASCII);
		var romanceTest5 = stringUtils.isInRomanceAlphabet("->?", encodings.ASCII);
		expect(romanceTest1).to.eql(true);
		expect(romanceTest2).to.eql(true);
		expect(romanceTest3).to.eql(false);
		expect(romanceTest4).to.eql(true);
		expect(romanceTest5).to.eql(false);
	}
	
	/**
	 * Test the is in alphabet functionality
	 * @function testIsInAlphabet
	 * @memberof JavascriptStringUtilsTest
	 */
	function testIsInAlphabet(){
		var StringUtils = LanguageModule.StringUtils;
		var stringUtils = new StringUtils();
		var encodings = stringUtils.stringEncodings;
		var lencodings = stringUtils.languageEncodings;
		var romanceTest1 = stringUtils.isInAlphabet("abcdef", encodings.ASCII, lencodings.ENGLISH);
		var romanceTest2 = stringUtils.isInAlphabet("ABCDEF", encodings.ASCII, lencodings.ENGLISH);
		var romanceTest3 = stringUtils.isInAlphabet("0123456789", encodings.ASCII, lencodings.ENGLISH);
		var romanceTest4 = stringUtils.isInAlphabet("g", encodings.ASCII, lencodings.ENGLISH);
		var romanceTest5 = stringUtils.isInAlphabet("->?", encodings.ASCII, lencodings.ENGLISH);
		expect(romanceTest1).to.eql(true);
		expect(romanceTest2).to.eql(true);
		expect(romanceTest3).to.eql(false);
		expect(romanceTest4).to.eql(true);
		expect(romanceTest5).to.eql(false);
	}
	
	/**
	 * Test the is lower cause in alphabet string functionality
	 * @function testInLowerCaseAlphabet
	 * @memberof JavascriptStringUtilsTest
	 */
	function testInLowerCaseAlphabet(){
		var StringUtils = LanguageModule.StringUtils;
		var stringUtils = new StringUtils();
		var encodings = stringUtils.stringEncodings;
		var lencodings = stringUtils.languageEncodings;
		var isLowerCaseInAlphabet1 = stringUtils.isLowerCaseInAlphabet("abcdef", encodings.ASCII, lencodings.ENGLISH);
		var isLowerCaseInAlphabet2 = stringUtils.isLowerCaseInAlphabet("ABCDEF", encodings.ASCII, lencodings.ENGLISH);
		var isLowerCaseInAlphabet3 = stringUtils.isLowerCaseInAlphabet("0123456789", encodings.ASCII, lencodings.ENGLISH);
		var isLowerCaseInAlphabet4 = stringUtils.isLowerCaseInAlphabet("g", encodings.ASCII, lencodings.ENGLISH);
		var isLowerCaseInAlphabet5 = stringUtils.isLowerCaseInAlphabet("->?", encodings.ASCII, lencodings.ENGLISH);
		expect(isLowerCaseInAlphabet1).to.eql(true);
		expect(isLowerCaseInAlphabet2).to.eql(false);
		expect(isLowerCaseInAlphabet3).to.eql(false);
		expect(isLowerCaseInAlphabet4).to.eql(true);
		expect(isLowerCaseInAlphabet5).to.eql(false);
	}
	
	/**
	 * Test the is upper cause in alphabet string functionality
	 * @function testInLowerCaseAlphabet
	 * @memberof JavascriptStringUtilsTest
	 */
	function testInUpperCaseAlphabet(){
		var StringUtils = LanguageModule.StringUtils;
		var stringUtils = new StringUtils();
		var encodings = stringUtils.stringEncodings;
		var lencodings = stringUtils.languageEncodings;
		var isUpperCaseInAlphabet1 = stringUtils.isUpperCaseInAlphabet("abcdef", encodings.ASCII, lencodings.ENGLISH);
		var isUpperCaseInAlphabet2 = stringUtils.isUpperCaseInAlphabet("ABCDEF", encodings.ASCII, lencodings.ENGLISH);
		var isUpperCaseInAlphabet3 = stringUtils.isUpperCaseInAlphabet("0123456789", encodings.ASCII, lencodings.ENGLISH);
		var isUpperCaseInAlphabet4 = stringUtils.isUpperCaseInAlphabet("g", encodings.ASCII, lencodings.ENGLISH);
		var isUpperCaseInAlphabet5 = stringUtils.isUpperCaseInAlphabet("->?", encodings.ASCII, lencodings.ENGLISH);
		expect(isUpperCaseInAlphabet1).to.eql(false);
		expect(isUpperCaseInAlphabet2).to.eql(true);
		expect(isUpperCaseInAlphabet3).to.eql(false);
		expect(isUpperCaseInAlphabet4).to.eql(false);
		expect(isUpperCaseInAlphabet5).to.eql(false);
	}
	
	/**
	 * Test the is punctuaion mark string functionality
	 * @function testInPunctuationMarkAlphabet
	 * @memberof JavascriptStringUtilsTest
	 */
	function testInPunctuationMarkAlphabet(){
		var StringUtils = LanguageModule.StringUtils;
		var stringUtils = new StringUtils();
		var encodings = stringUtils.stringEncodings;
		var lencodings = stringUtils.languageEncodings;
		var isPunctuationMarkInAlphabet1 = stringUtils.isPunctuationMarkInAlphabet("abcdef", encodings.ASCII, lencodings.ENGLISH);
		var isPunctuationMarkInAlphabet2 = stringUtils.isPunctuationMarkInAlphabet("ABCDEF", encodings.ASCII, lencodings.ENGLISH);
		var isPunctuationMarkInAlphabet3 = stringUtils.isPunctuationMarkInAlphabet("0123456789", encodings.ASCII, lencodings.ENGLISH);
		var isPunctuationMarkInAlphabet4 = stringUtils.isPunctuationMarkInAlphabet("g", encodings.ASCII, lencodings.ENGLISH);
		var isPunctuationMarkInAlphabet5 = stringUtils.isPunctuationMarkInAlphabet("-,?", encodings.ASCII, lencodings.ENGLISH);
		expect(isPunctuationMarkInAlphabet1).to.eql(false);
		expect(isPunctuationMarkInAlphabet2).to.eql(false);
		expect(isPunctuationMarkInAlphabet3).to.eql(false);
		expect(isPunctuationMarkInAlphabet4).to.eql(false);
		expect(isPunctuationMarkInAlphabet5).to.eql(true);
	}
	
	/**
	 * The public interface
	 */
	return {
		testStringLength:testStringLength,
		testStringLengthEscaped:testStringLengthEscaped,
		testIsNaturalNumber:testIsNaturalNumber,
		testStringEncodings:testStringEncodings,
		testLanguageEncodings:testLanguageEncodings,
		testIsHexNumber:testIsHexNumber,
		testIsValid:testIsValid,
		testIsInRomanceAlphabet:testIsInRomanceAlphabet,
		testIsInAlphabet:testIsInAlphabet,
		testInLowerCaseAlphabet:testInLowerCaseAlphabet,
		testInUpperCaseAlphabet:testInUpperCaseAlphabet,
		testInPunctuationMarkAlphabet:testInPunctuationMarkAlphabet
	}
})();

describe("Test the javascript string utils", function(){
	it('JavascriptStringUtils Length Test', JavascriptStringUtilsTest.testStringLength);
	it('JavascriptStringUtils Length Escaped Test', JavascriptStringUtilsTest.testStringLengthEscaped);
	it('JavascriptStringUtils Natural Number Test', JavascriptStringUtilsTest.testIsNaturalNumber);
	it('JavascriptStringUtils String Encodings Test', JavascriptStringUtilsTest.testStringEncodings);
	it('JavascriptStringUtils Language Encodings Test', JavascriptStringUtilsTest.testLanguageEncodings);
	it('JavascriptStringUtils Is Hex Number Test', JavascriptStringUtilsTest.testIsHexNumber);
	it('JavascriptStringUtils Is Valid Test', JavascriptStringUtilsTest.testIsValid);
	it('JavascriptStrignUtils Is Romance Alphabet Test', JavascriptStringUtilsTest.testIsInRomanceAlphabet);
	it('JavascriptStringUtils Is In Alphabet Test', JavascriptStringUtilsTest.testIsInAlphabet);
	it('JavascriptStringUtils Is In LowerCase Alphabet Test', JavascriptStringUtilsTest.testInLowerCaseAlphabet);
	it('JavascriptStringUtils Is In UpperCase Alphabet Test', JavascriptStringUtilsTest.testInUpperCaseAlphabet);
	it('JavascriptStringUtils Is Punctiona Mark Alphabet Test', JavascriptStringUtilsTest.testInPunctuationMarkAlphabet);
});

