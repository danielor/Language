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
A string utils class that wraps the Language C bindngs
@author: Daniel Ortiz
@version: 0.01
"""
from Language.stringUtils import length
from Language.stringUtils import lengthEscaped
from Language.stringUtils import isNaturalNumber
from Language.stringUtils import isHexNumber

class StringUtils(object):
    """
    An object that encapsulates the string Utils
    """
    def __init__(self, str, encoding):
        """
        @param str: The string to calculate the utils 
        @param encoding: The encoding of the string
        """
        self.str = str
        self.encoding = encoding
        
    def __len__(self):
        """
        Get the length of the string
        """
        return length(self.str, self.encoding)
    
    @classmethod
    def stringEncodings(cls):
        """
        Get the string encoding associated with the utilities
        """
        return {
            "UTF8_BINARY":0,
            "ASCII":1,
            "ISO_8859_1":2
        }
        
    @classmethod
    def languageEncodings(cls):
        """
        Get the language encodings associated with the utilities
        """
        return {
            'ENGLISH':0,
            'SPANISH':1,
            'FRENCH':2
        }
    
    def lenEscaped(self, escapedString = '\u', escapedEncoding = 0,
                   endString = ''):
        """
        @param escapedString: The escaped string 
        @param escapedEncoding: The encoding of the escaped
        @param endString: The end string of the escaped info
        """
        if endString == '':
            return lengthEscaped(self.str, self.encoding, escapedString, escapedEncoding)
        else:
            return lengthEscaped(self.str, self.encoding, escapedString, escapedEncoding, endString)
        
    def isNaturalNumber(self):
        """
        Return true if the string is a natural number
        """
        return isNaturalNumber(self.str, self.encoding)
    
    def isHexNumber(self):
        """
        Return true if the string is a hex Number
        """
        return isHexNumber(self.str, self.encoding)