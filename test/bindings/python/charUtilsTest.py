# Copyright 2014 by Daniel Ortiz
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""
A sequence of unit test for the char utils Bindings
used by Language.
@author: Daniel Ortiz
@version: 0.01
"""
import unittest
from Language.charUtils import isHexNumber
from Language.charUtils import isNaturalNumber
from Language.charUtils import isInRomanceAlphabet
from Language.charUtils import isValid
from Language.charUtils import isInAlphabet
from Language.charUtils import isUpperCaseInAlphabet
from Language.charUtils import isLowerCaseInAlphabet
from Language.charUtils import isPunctuationMarkInAlphabet
from LanguageUtils.CharUtils import CharUtils

class CharUtilsTestCase(unittest.TestCase):
    """
    The char unit test case
    """
    def test_isHexNumber(self):
        """
        Test the is hex char function 
        """
        encoding = CharUtils.stringEncodings()
        self.assertTrue(isHexNumber("a", encoding['ASCII'], 0))
        self.assertTrue(isHexNumber("F", encoding['ASCII'], 0))
        self.assertTrue(isHexNumber("3", encoding['ASCII'], 0))
        self.assertFalse(isHexNumber("z", encoding['ASCII'], 0))

    def test_IsNaturalChar(self):
        """
        Test the is natural char function
        """
        encoding = CharUtils.stringEncodings()
        self.assertTrue(isNaturalNumber("0", encoding['ASCII'], 0))
        self.assertTrue(isNaturalNumber("9", encoding['ASCII'], 0))
        self.assertFalse(isNaturalNumber("z", encoding['ASCII'], 0))
        
    def test_IsRomanceChar(self):
        """
        Test the is romance char function
        """
        encoding = CharUtils.stringEncodings()
        self.assertFalse(isInRomanceAlphabet("0", encoding['ASCII'], 0))
        self.assertFalse(isInRomanceAlphabet("9", encoding['ASCII'], 0))
        self.assertTrue(isInRomanceAlphabet("z", encoding['ASCII'], 0))
        self.assertFalse(isInRomanceAlphabet("-", encoding['ASCII'], 0))
        
    def test_IsValidChar(self):
        """
        Test the is valid char functoin
        """
        encoding = CharUtils.stringEncodings()
        self.assertTrue(isValid("0", encoding['ASCII'], 0))
        self.assertTrue(isValid("9", encoding['ASCII'], 0))
        self.assertTrue(isValid("z", encoding['ASCII'], 0))
        self.assertTrue(isValid("-", encoding['ASCII'], 0))
        
    def test_IsInAlphabetChar(self):
        """
        Test that the character is in an alphabet
        """
        encoding = CharUtils.stringEncodings()
        language = CharUtils.languageEncodings()
        self.assertFalse(isInAlphabet("0", encoding['ASCII'], language['ENGLISH'], 0))
        self.assertFalse(isInAlphabet("9", encoding['ASCII'], language['ENGLISH'], 0))
        self.assertTrue(isInAlphabet("z", encoding['ASCII'], language['ENGLISH'], 0))
        self.assertFalse(isInAlphabet("-", encoding['ASCII'], language['ENGLISH'], 0))
        
    def test_isUpperCaseInAlphabet(self):
        """
        Test if upper case characters are in different alphabet
        """
        encoding = CharUtils.stringEncodings()
        language = CharUtils.languageEncodings()
        self.assertFalse(isInAlphabet("0", encoding['ASCII'], language['ENGLISH'], 0))
        self.assertFalse(isInAlphabet("9", encoding['ASCII'], language['ENGLISH'], 0))
        self.assertTrue(isInAlphabet("Z", encoding['ASCII'], language['ENGLISH'], 0))
        self.assertFalse(isInAlphabet("-", encoding['ASCII'], language['ENGLISH'], 0))
        
    def test_isLowerCaseInAlphabet(self):
        """
        Test if upper case characters are in different alphabet
        """
        encoding = CharUtils.stringEncodings()
        language = CharUtils.languageEncodings()
        self.assertFalse(isLowerCaseInAlphabet("0", encoding['ASCII'], language['ENGLISH'], 0))
        self.assertFalse(isLowerCaseInAlphabet("9", encoding['ASCII'], language['ENGLISH'], 0))
        self.assertTrue(isLowerCaseInAlphabet("z", encoding['ASCII'], language['ENGLISH'], 0))
        self.assertFalse(isLowerCaseInAlphabet("-", encoding['ASCII'], language['ENGLISH'], 0))
      
    def test_isPunctuationMarkInAlphabet(self):
        """
        Test if upper case characters are in different alphabet
        """
        encoding = CharUtils.stringEncodings()
        language = CharUtils.languageEncodings()
        self.assertFalse(isPunctuationMarkInAlphabet("0", encoding['ASCII'], language['ENGLISH'], 0))
        self.assertFalse(isPunctuationMarkInAlphabet("9", encoding['ASCII'], language['ENGLISH'], 0))
        self.assertFalse(isPunctuationMarkInAlphabet("z", encoding['ASCII'], language['ENGLISH'], 0))
        self.assertTrue(isPunctuationMarkInAlphabet("-", encoding['ASCII'], language['ENGLISH'], 0))
    
    def test_charUtils(self):
        """
        Test the character utils class
        """
        encoding = CharUtils.stringEncodings()
        language = CharUtils.languageEncodings()
        charUtils = CharUtils("z", encoding['ASCII'], language['ENGLISH'])
        self.assertFalse(charUtils.isHexNumber(0))
        self.assertFalse(charUtils.isNaturalNumber(0))
        self.assertTrue(charUtils.isInRomanceAlphabet(0))
        self.assertTrue(charUtils.isValid(0))
        self.assertTrue(charUtils.isInAlphabet(0))
        self.assertFalse(charUtils.isUpperCaseInAlphabet(0))
        self.assertTrue(charUtils.isLowerCaseInAlphabet(0))
        self.assertFalse(charUtils.isPunctuationMarkInAlphabet(0))
        
if __name__ == '__main__':
    unittest.main()