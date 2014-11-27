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
Setup the files associated with the Lanaguage python package
@author: Daniel Ortiz
@version: 0.01
"""
from setuptools import setup, find_packages, Extension
from codecs import open
from os import path

def setupPythonLanguagePackage():
    """
    Setup the language package a distribution
    """
    currentDir = path.abspath(path.dirname(__file__))
    longDescription = ""
    with open(path.join(currentDir, "docs/DESCRIPTION_PYTHON.rst"), encoding='utf-8') as f:
        longDescription = f.read()

    # Create an extension
    languageExtension = Extension(
        "Language",
        include_dirs=['/usr/local/include', currentDir + "/lib"],
        library_dirs=['/usr/local/lib', currentDir + "/lib"],
        sources=[currentDir + "/lib/bindings/python/stringUtilsPython.c"]
    )
    
    # Setup the package
    setup(
        name='Language',                                # The name of the package
        version='0.0.1',                                # The version of the package
        description="Generic Language features",        # The generic language features
        url="https://github.com/danielor/Language.git", # The Git repository
        author='Daniel Ortiz',                          # The author :)
        author_email='danielor@umich.edu',              # My email :)
        license="Apache",                               # The license for Apache package
        classifiers = [
            "Development Status :: 1 - Planning",
            "Intended Audience :: Developers",
            "Topic :: Software Development :: Build Tools",
            "License :: OSI Approved :: Apache Software License",
            "Programming Language :: Python :: 2",
            "Programming Language :: Python :: 2.6",
            "Programming Language :: Python :: 2.7"
        ],                                              # The classifiers associated with the package
       keywords='Generics Language',                    # Keywords associated with the package
        ext_modules = [languageExtension]
    )
if __name__ == '__main__':
    setupPythonLanguagePackage()