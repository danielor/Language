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

class StringUtilsTestCase(unittest.TestCase):
    """
    The string unit test case
    """
    def test_StringUtilsLength(self):
        """
        Test the string utils length
        """
        self.assertTrue(length("SixValue") == 8)
        
if __name__=='__main__':
    unittest.main()