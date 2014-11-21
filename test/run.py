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
A generic testing framework for all of Language's bindings and source
files.
@author:  Daniel Ortiz
@version: 0.01
"""
import argparse, os, subprocess

def runTests(compile):
    """
    Run all of the tests associated with the language product
    @param compile: A compile flag that is true when 
    """
    # Get a list of tests to run from the file directory
    listOfJavascriptTests = []
    listOfCTests = []
    for root, dirs, list_of_files in os.walk(os.getcwd()):
        for f in list_of_files:
            fileName, fileExt = os.path.splitext(f)
            if fileExt == "c":
                
                # Save the actual file name and the executable associated with the filename
                listOfCTests.append((root + "/" + f, f.replace('Test.c', '')))
            elif fileExt == "js":
                listOfJavascriptTests.append(root + "/" + f)
    listOfCompiledExecutables =[]
    if compile:
        
        # Iterate over the tests and create a gcc executable for each test
        for testFile, executable in listOfCTests:
            cmd = ['gcc','-I../lib', '-o', executable, testFile]
            p = subprocess.Popen(cmd)
            p.wait()
    else:
        listOfCompiledExecutables.extend([executable for _, executable in listOfCTests])
    
    # Run the compiled executables
    for c in listOfCompiledExecutables:
        cmd = ["./" + c]
        p = subprocess.Popen(cmd)
        p.wait()
        
    # Run the javascript tests
    for f in listOfJavascriptTests:
        cmd = ["mocha %s" % f]
        p = subprocess.Popen(cmd)
        p.wait()
    
if __name__ == '__main__':
    parser = argparse.ArgumentParser("Language TestingFramework")
    parser.add_argument("-c", "--compile", help='Automatically compile the tests', action='store_true', default=False)
    args = parser.parse_args()
    
    # Run the tests in the language bindings
    runTests(args.compile)
    