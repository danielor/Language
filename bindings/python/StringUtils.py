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
from twisted.trial.test.sample import AlphabetTest
"""
A string utils class that wraps the Language C bindngs
@author: Daniel Ortiz
@version: 0.01
"""
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
from BaseUtils import BaseUtils

class StringUtils(BaseUtils):
    """
    An object that encapsulates the string Utils
    """
    def __init__(self, str, encoding, language = 0):
        """
        @param str: The string to calculate the utils 
        @param encoding: The encoding of the string
        @param lanaguage: The language of the string(defaults to EnglisH)
        """
        self.str = str
        self.encoding = encoding
        self.language = language
        
    def __len__(self):
        """
        Get the length of the string
        """
        return length(self.str, self.encoding)
    
    
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
    
    def isValid(self):
        """
        Return true if the string is valid
        """
        return isValid(self.str, self.encoding)
    
    def isInRomanceAlphabet(self):
        """
        Return true if string is in romance alphabet 
        """
        return isInRomanceAlphabet(self.str, self.encoding)
    
    def isInAlphabet(self):
        """
        Return true if string is in alphabet 
        """
        return isInAlphabet(self.str, self.encoding, self.language)
    
    def isUpperCaseInAlphabet(self):
        """
        Return true if the string is upper case in alphaphet
        """
        return isUpperCaseInAlphabet(self.str, self.encoding, self.language)
    
    def isLowerCaseInAlphabet(self):
        """
        Return true if the string is lower case in alphabet 
        """
        return isLowerCaseInAlphabet(self.str, self.encoding, self.language)
    
    def isPunctuationMarkInAlphabet(self):
        """
        Return true if the string is a punctuation mark alphabet 
        """
        return isPunctuationMarkInAlphabet(self.str, self.encoding, self.language)