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
	 * @memberof JavascriptUtilsTest
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
	 * @memberof JavascriptUtilsTest
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
	 * @memberof JavascriptUtilsTest
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
	 * @memberof JavascriptUtilsTest
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
	 * The public interface
	 */
	return {
		testStringLength:testStringLength,
		testStringLengthEscaped:testStringLengthEscaped,
		testIsNaturalNumber:testIsNaturalNumber,
		testStringEncodings:testStringEncodings,
		testIsHexNumber:testIsHexNumber
	}
})();

describe("Test the javascript string utils", function(){
	it('JavascriptStringUtils Length Test', JavascriptStringUtilsTest.testStringLength);
	it('JavascriptStringUtils Length Escaped Test', JavascriptStringUtilsTest.testStringLengthEscaped);
	it('JavascriptStringUtils Natural Number Test', JavascriptStringUtilsTest.testIsNaturalNumber);
	it('JavascriptStringUtils String Encodings Test', JavascriptStringUtilsTest.testStringEncodings);
	it('JavascriptStringUtils Is Hex Number Test', JavascriptStringUtilsTest.testIsHexNumber);
});

