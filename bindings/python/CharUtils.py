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
from Language.charUtils import isHexChar
from Language.charUtils import isNaturalChar
from Language.charUtils import isRomanceChar
from Language.charUtils import isValidChar
from Language.charUtils import isInAlphabetChar
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
        
    def isHexNumberChar(self):
        """
        Return true if the string is a hex character
        """
        return isHexChar(self.char, self.encoding)
    
    def isNaturalNumberChar(self):
        """
        Return true if the string is a natural character 
        """
        return isNaturalChar(self.char, self.encoding)
    
    def isInRomanceAlphabetChar(self):
        """
        Return true if the string is a romance character
        """
        return isRomanceChar(self.char, self.encoding)
    
    def isValidChar(self):
        """
        Return true if the string is a valid character
        """
        return isValidChar(self.char, self.encoding)
    
    def isInAlphabetChar(self):
        """
        Return true if the string is in an alphabet character
        """
        return isInAlphabetChar(self.char, self.encoding, self.language)