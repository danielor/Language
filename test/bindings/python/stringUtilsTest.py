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
        
    def test_stringUtils(self):
        """
        Test the string utils around the Language functional interface
        """
        s = StringUtils('567', 1)
        self.assertTrue(len(s) == 3)
        self.assertTrue(s.lenEscaped() == 3)
        self.assertTrue(s.isNaturalNumber() == True)
      
if __name__=='__main__':
    unittest.main()