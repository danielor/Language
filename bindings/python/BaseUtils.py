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
The base utils contains 
@author: Daniel Ortiz
@version: 0.01
"""

class BaseUtils(object):
    """
    The base utils object is the base class for different utilties.
    """
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