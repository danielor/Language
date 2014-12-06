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
var JavascriptUtilsTest = (function(){
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
	 * The public interface
	 */
	return {
		testStringLength:testStringLength,
		testStringLengthEscaped:testStringLengthEscaped
	}
})();

describe("Test the javascript utils", function(){
	it('JavascriptUtils Length Test', JavascriptUtilsTest.testStringLength);
	it('JavascriptUtils Length Escaped Test', JavascriptUtilsTest.testStringLengthEscaped);
});
