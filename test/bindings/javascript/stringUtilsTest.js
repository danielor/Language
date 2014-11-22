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
	 * The public interface
	 */
	return {
		testStringLength:testStringLength
	}
})();

describe("Test the javascript utils", function(){
	it('JavascriptUtils Test', JavascriptUtilsTest.testStringLength);
});
