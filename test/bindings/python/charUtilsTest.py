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
        self.assertTrue(isHexNumber("a", encoding['ASCII']))
        self.assertTrue(isHexNumber("F", encoding['ASCII']))
        self.assertTrue(isHexNumber("3", encoding['ASCII']))
        self.assertFalse(isHexNumber("z", encoding['ASCII']))

    def test_IsNaturalChar(self):
        """
        Test the is natural char function
        """
        encoding = CharUtils.stringEncodings()
        self.assertTrue(isNaturalNumber("0", encoding['ASCII']))
        self.assertTrue(isNaturalNumber("9", encoding['ASCII']))
        self.assertFalse(isNaturalNumber("z", encoding['ASCII']))
        
    def test_IsRomanceChar(self):
        """
        Test the is romance char function
        """
        encoding = CharUtils.stringEncodings()
        self.assertFalse(isInRomanceAlphabet("0", encoding['ASCII']))
        self.assertFalse(isInRomanceAlphabet("9", encoding['ASCII']))
        self.assertTrue(isInRomanceAlphabet("z", encoding['ASCII']))
        self.assertFalse(isInRomanceAlphabet("-", encoding['ASCII']))
        
    def test_IsValidChar(self):
        """
        Test the is valid char functoin
        """
        encoding = CharUtils.stringEncodings()
        self.assertTrue(isValid("0", encoding['ASCII']))
        self.assertTrue(isValid("9", encoding['ASCII']))
        self.assertTrue(isValid("z", encoding['ASCII']))
        self.assertTrue(isValid("-", encoding['ASCII']))
        
    def test_IsInAlphabetChar(self):
        """
        Test that the character is in an alphabet
        """
        encoding = CharUtils.stringEncodings()
        language = CharUtils.languageEncodings()
        self.assertFalse(isInAlphabet("0", encoding['ASCII'], language['ENGLISH']))
        self.assertFalse(isInAlphabet("9", encoding['ASCII'], language['ENGLISH']))
        self.assertTrue(isInAlphabet("z", encoding['ASCII'], language['ENGLISH']))
        self.assertFalse(isInAlphabet("-", encoding['ASCII'], language['ENGLISH']))
        
    def test_charUtils(self):
        """
        Test the character utils class
        """
        encoding = CharUtils.stringEncodings()
        language = CharUtils.languageEncodings()
        charUtils = CharUtils("z", encoding['ASCII'], language['ENGLISH'])
        self.assertFalse(charUtils.isHexNumberChar())
        self.assertFalse(charUtils.isNaturalNumberChar())
        self.assertTrue(charUtils.isInRomanceAlphabetChar())
        self.assertTrue(charUtils.isValidChar())
        self.assertTrue(charUtils.isInAlphabetChar())
if __name__ == '__main__':
    unittest.main()