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
A sequence of unit test for the string utils Bindings
used by Language.
@author: Daniel Ortiz
@version: 0.01
"""
import unittest
from Language.stringUtils import length
from Language.stringUtils import lengthEscaped
from Language.stringUtils import isNaturalNumber
from Language.stringUtils import isHexNumber
from Language.stringUtils import isValid
from Language.stringUtils import isInRomanceAlphabet
from Language.stringUtils import isInAlphabet
from Language.stringUtils import isUpperCaseInAlphabet
from Language.stringUtils import isLowerCaseInAlphabet
from Language.stringUtils import isPunctuationMarkInAlphabet
from LanguageUtils.StringUtils import StringUtils

class StringUtilsTestCase(unittest.TestCase):
    """
    The string unit test case
    """
    def test_StringUtilsLength(self):
        """
        Test the string utils length
        """
        self.assertTrue(length("SixValue") == 8)
        
    def test_StringUtilsLengthEscaped(self):
        """
        Test the string utils length escaped
        """
        self.assertTrue(lengthEscaped("Healthy", 1, "YUM", 0) == 7)
        self.assertTrue(lengthEscaped("HealthyYUM2345N", 1, "YUM", 0) == 9)
        self.assertTrue(lengthEscaped("HealthyYUM2345NR", 1, "YUM", 0, "N") == 9)
    
    def test_isNaturalNumber(self):
        """
        Test the string utils natural number
        """
        self.assertTrue(isNaturalNumber("567", 1) == True)
        self.assertTrue(isNaturalNumber("n", 1) == False)
        self.assertTrue(isNaturalNumber("3", 1) == True)
        self.assertTrue(isNaturalNumber("5gd3", 1) == False)
        self.assertTrue(isNaturalNumber("1de3g3dg3", 1) == False)
    
    def test_isHexNumber(self):
        """
        Test the string utils hex number
        """
        sEncodings = StringUtils.stringEncodings()
        self.assertTrue(isHexNumber("abcdef", sEncodings['ASCII']))
        self.assertTrue(isHexNumber("ABCDEF", sEncodings['ASCII']))
        self.assertTrue(isHexNumber("0123456789", sEncodings['ASCII']))
        self.assertFalse(isHexNumber("g", sEncodings['ASCII']))
        self.assertFalse(isHexNumber("G", sEncodings['ASCII']))
        
    def test_isValid(self):
        """
        Test the string utils is valid
        """
        sEncodings = StringUtils.stringEncodings()
        invalidString = ''.join(map(unichr, [13, 14, 5]))
        self.assertTrue(isValid("abcdef", sEncodings['ASCII']))
        self.assertTrue(isValid("ABCDEF", sEncodings['ASCII']))
        self.assertTrue(isValid("0123456789", sEncodings['ASCII']))
        self.assertTrue(isValid("g", sEncodings['ASCII']))
        self.assertTrue(isValid("G", sEncodings['ASCII']))
        self.assertFalse(isValid(invalidString, sEncodings['ISO_8859_1']))

    def test_isInRomanceAlphabet(self):
        """
        Test the string utils is romance alphabet
        """
        sEncodings = StringUtils.stringEncodings()
        self.assertTrue(isInRomanceAlphabet("abcdef", sEncodings['ASCII']))
        self.assertTrue(isInRomanceAlphabet("ABCDEF", sEncodings['ASCII']))
        self.assertFalse(isInRomanceAlphabet("0123456789", sEncodings['ASCII']))
        self.assertTrue(isInRomanceAlphabet("g", sEncodings['ASCII']))
        self.assertTrue(isInRomanceAlphabet("G", sEncodings['ASCII']))
    
    def test_isInAlphabet(self):
        """
        Test the string utils is in alphabet
        """
        sEncodings = StringUtils.stringEncodings()
        lEncodings = StringUtils.languageEncodings()
        
        self.assertTrue(isInAlphabet("Howdy", sEncodings['ASCII'],lEncodings['ENGLISH']))
        self.assertTrue(isInAlphabet("First", sEncodings['ASCII'], lEncodings['ENGLISH']))
        self.assertFalse(isInAlphabet("0123456789", sEncodings['ASCII'], lEncodings['ENGLISH']))
        self.assertTrue(isInAlphabet("g", sEncodings['ASCII'], lEncodings['ENGLISH']))
    
    def test_isUpperCaseInAlphabet(self):
        """
        Test the string utils is in alphabet
        """
        sEncodings = StringUtils.stringEncodings()
        lEncodings = StringUtils.languageEncodings()
        
        self.assertFalse(isUpperCaseInAlphabet("abcdef", sEncodings['ASCII'], lEncodings['ENGLISH']))
        self.assertTrue(isUpperCaseInAlphabet("ABCDEF", sEncodings['ASCII'], lEncodings['ENGLISH']))
        self.assertFalse(isUpperCaseInAlphabet("0123456789", sEncodings['ASCII'], lEncodings['ENGLISH']))
        self.assertFalse(isUpperCaseInAlphabet("g", sEncodings['ASCII'], lEncodings['ENGLISH']))
        self.assertTrue(isUpperCaseInAlphabet("G", sEncodings['ASCII'], lEncodings['ENGLISH']))
        
    def test_isLowerCaseInAlphabet(self):
        """
        Test the string utils is in alphabet
        """
        sEncodings = StringUtils.stringEncodings()
        lEncodings = StringUtils.languageEncodings()
        
        self.assertTrue(isLowerCaseInAlphabet("abcdef", sEncodings['ASCII'], lEncodings['ENGLISH']))
        self.assertFalse(isLowerCaseInAlphabet("ABCDEF", sEncodings['ASCII'], lEncodings['ENGLISH']))
        self.assertFalse(isLowerCaseInAlphabet("0123456789", sEncodings['ASCII'], lEncodings['ENGLISH']))
        self.assertTrue(isLowerCaseInAlphabet("g", sEncodings['ASCII'], lEncodings['ENGLISH']))
        self.assertFalse(isLowerCaseInAlphabet("G", sEncodings['ASCII'], lEncodings['ENGLISH']))
    
    def test_isPunctuationMarkInAlphabet(self):
        """
        Test the string utils is in alphabet
        """
        sEncodings = StringUtils.stringEncodings()
        lEncodings = StringUtils.languageEncodings()
        
        self.assertFalse(isPunctuationMarkInAlphabet("abcdef", sEncodings['ASCII'], lEncodings['ENGLISH']))
        self.assertFalse(isPunctuationMarkInAlphabet("ABCDEF", sEncodings['ASCII'], lEncodings['ENGLISH']))
        self.assertFalse(isPunctuationMarkInAlphabet("0123456789", sEncodings['ASCII'], lEncodings['ENGLISH']))
        self.assertFalse(isPunctuationMarkInAlphabet("g", sEncodings['ASCII'], lEncodings['ENGLISH']))
        self.assertFalse(isPunctuationMarkInAlphabet("G", sEncodings['ASCII'], lEncodings['ENGLISH']))
        self.assertTrue(isPunctuationMarkInAlphabet(",", sEncodings['ASCII'], lEncodings['ENGLISH']))
    
    def test_stringUtils(self):
        """
        Test the string utils around the Language functional interface
        """
        s = StringUtils('567', 1)
        self.assertTrue(len(s) == 3)
        self.assertTrue(s.lenEscaped() == 3)
        self.assertTrue(s.isNaturalNumber())
        self.assertTrue(s.isHexNumber())
        self.assertTrue(s.isValid())
        self.assertFalse(s.isInRomanceAlphabet())
        self.assertFalse(s.isInAlphabet())
        self.assertFalse(s.isUpperCaseInAlphabet())
        self.assertFalse(s.isLowerCaseInAlphabet())
        self.assertFalse(s.isPunctuationMarkInAlphabet())
        
if __name__=='__main__':
    unittest.main()