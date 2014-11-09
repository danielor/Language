//Copyright 2014 by Daniel Ortiz
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
#include <stdio.h>
#include "stringUtils.h"

// A function that test the functionality associated with the utf8 state test.
// This should handle all possible states of the UTF8 specification.
int testGetUTF8State(){

	// Test the ASCII portion(7bit) of the UTF8 range
	char asciiTest[3] = {0x7f,0x1f,0x0f};
	for(int i = 0; i < 3; i++){
		char ascii = asciiTest[i];
		int state = getUTF8State(ascii);
		if(state != UTF8_BINARY_7BIT_STATE){
			return 0;
		}
	}

	// Test the 11 bit UTF8 portion of the utf encoding. This
	// only considers whether the control string returns the
	// correct parser state.
	char utf8Test11[3] = {0xc0,0xcf,0xdf};
	for(int i = 0; i < 3; i++){
		char utf = utf8Test11[i];
		int state = getUTF8State(utf);
		if(state != UTF8_BINARY_11BIT_STATE){
			return 0;
		}
	}

	// Test the 16 bit UTF8 portion of the utf encoding. This
	// only considers whether the control string returns the
	// correct parser state.
	char utf8Test16[3] = {0xe0,0xe7,0xef};
	for(int i = 0; i < 3; i++){
		char utf = utf8Test16[i];
		int state = getUTF8State(utf);
		if(state != UTF8_BINARY_16BIT_STATE){
			return 0;
		}
	}

	// Test the 21 bit UTF8 portion of the utf encoding. This
	// only considers whether the control string returns the
	// correct parser state.
	char utf8Test21[3] = {0xf0,0xf3,0xf7};
	for(int i = 0; i < 3; i++){
		char utf = utf8Test21[i];
		int state = getUTF8State(utf);

		if(state != UTF8_BINARY_21BIT_STATE){
			return 0;
		}
	}
	// Test that unacceptable UTF8 characters produce errors
	char utf8TestError[3] = {0xf8,0xfc,0xff};
	for(int i = 0; i < 3; i++){
		char utf = utf8TestError[i];
		int state = getUTF8State(utf);

		if(state != UTF8_BINARY_ERROR_STATE){
			return 0;
		}
	}

	return -1;
}

// A function that tests the main points of functionality associated with the
int testStringUtils(){

	// Test the get UTF8 state
	if(testGetUTF8State() == -1){
		printf("*SUCCESS - UTF8State test passed\n");
	}else{
		printf("*FAILURE - UTF8State test failed\n");
	}

	return 0;
}

int main(int argc, char ** argv){
	return testStringUtils();
}
