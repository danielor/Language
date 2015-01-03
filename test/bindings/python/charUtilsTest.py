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
from Language.charUtils import isHexChar
from Language.charUtils import isNaturalChar
from Language.charUtils import isRomanceChar
from Language.charUtils import isValidChar
from Language.charUtils import isInAlphabetChar
from LanguageUtils.CharUtils import CharUtils

class CharUtilsTestCase(unittest.TestCase):
    """
    The char unit test case
    """
    def test_IsHexChar(self):
        """
        Test the is hex char function 
        """
        encoding = CharUtils.stringEncodings()
        self.assertTrue(isHexChar("a", encoding['ASCII']))
        self.assertTrue(isHexChar("F", encoding['ASCII']))
        self.assertTrue(isHexChar("3", encoding['ASCII']))
        self.assertFalse(isHexChar("z", encoding['ASCII']))

    def test_IsNaturalChar(self):
        """
        Test the is natural char function
        """
        encoding = CharUtils.stringEncodings()
        self.assertTrue(isNaturalChar("0", encoding['ASCII']))
        self.assertTrue(isNaturalChar("9", encoding['ASCII']))
        self.assertFalse(isNaturalChar("z", encoding['ASCII']))
        
    def test_IsRomanceChar(self):
        """
        Test the is romance char function
        """
        encoding = CharUtils.stringEncodings()
        self.assertFalse(isRomanceChar("0", encoding['ASCII']))
        self.assertFalse(isRomanceChar("9", encoding['ASCII']))
        self.assertTrue(isRomanceChar("z", encoding['ASCII']))
        self.assertFalse(isRomanceChar("-", encoding['ASCII']))
        
    def test_IsValidChar(self):
        """
        Test the is valid char functoin
        """
        encoding = CharUtils.stringEncodings()
        self.assertTrue(isValidChar("0", encoding['ASCII']))
        self.assertTrue(isValidChar("9", encoding['ASCII']))
        self.assertTrue(isValidChar("z", encoding['ASCII']))
        self.assertTrue(isValidChar("-", encoding['ASCII']))
        
    def test_IsInAlphabetChar(self):
        """
        Test that the character is in an alphabet
        """
        encoding = CharUtils.stringEncodings()
        language = CharUtils.languageEncodings()
        self.assertFalse(isInAlphabetChar("0", encoding['ASCII'], language['ENGLISH']))
        self.assertFalse(isInAlphabetChar("9", encoding['ASCII'], language['ENGLISH']))
        self.assertTrue(isInAlphabetChar("z", encoding['ASCII'], language['ENGLISH']))
        self.assertFalse(isInAlphabetChar("-", encoding['ASCII'], language['ENGLISH']))
        
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