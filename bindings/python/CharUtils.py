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
A char utils class that wraps the Language C bindngs
@author: Daniel Ortiz
@version: 0.01
"""
from Language.charUtils import isHexNumber
from Language.charUtils import isNaturalNumber
from Language.charUtils import isInRomanceAlphabet
from Language.charUtils import isValid
from Language.charUtils import isInAlphabet
from Language.charUtils import isUpperCaseInAlphabet
from Language.charUtils import isLowerCaseInAlphabet
from Language.charUtils import isPunctuationMarkInAlphabet
from BaseUtils import BaseUtils

class CharUtils(BaseUtils):
    """
    An object that encapsulates the char utils 
    """
    def __init__(self, char, encoding, language = 0):
        """
        @param char The char to check 
        @param encoding: The encoding of the char 
        @param language: The language set of the char 
        """
        self.char = char 
        self.encoding = encoding
        self.language = language 
        
    def isHexNumber(self, index = 0):
        """
        Return true if the string is a hex character
        @param index: The index to check the character
        """
        return isHexNumber(self.char, self.encoding, index)
    
    def isNaturalNumber(self, index = 0):
        """
        Return true if the string is a natural character
        @param index: The index to check the character
        """
        return isNaturalNumber(self.char, self.encoding, index)
    
    def isInRomanceAlphabet(self, index = 0):
        """
        Return true if the string is a romance character
        @param index: The index to check the character
        """
        return isInRomanceAlphabet(self.char, self.encoding, index)
    
    def isValid(self, index):
        """
        Return true if the string is a valid character
        @param index: The index to check the character
        """
        return isValid(self.char, self.encoding, index)
    
    def isInAlphabet(self, index):
        """
        Return true if the string is in an alphabet character
        @param index: The index to check the character
        """
        return isInAlphabet(self.char, self.encoding, self.language, index)
    
    def isUpperCaseInAlphabet(self, index):
        """
        Return true if the string is upper case in alphabet character
        @param index: The index to check the character
        """
        return isUpperCaseInAlphabet(self.char, self.encoding, self.language, index)
    
    def isLowerCaseInAlphabet(self, index):
        """
        Return true if the string is lower case in alphabet character
        @param index: The index to check the character
        """
        return isLowerCaseInAlphabet(self.char, self.encoding, self.language, index)
    
    def isPunctuationMarkInAlphabet(self, index):
        """
        Return true if the string is a punctuation mark alphabet character
        """
        return isPunctuationMarkInAlphabet(self.char, self.encoding, self.language, index)