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

// Conversion test struct.
struct ConvertTest{
	char originalCharacter;			// The original character
	char expectedCharacter;			// The new character
};

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

// Test the conversion of characters to hex.
int testConvertHex(){
	int r;
	struct ConvertTest conversionTests[28] = {
		{48, 0},{49, 1},{50, 2},{51, 3},{52, 4},
		{53, 5},{54, 6},{55, 7},{56, 8},{57, 9},
		{65, 10},{66, 11},{67, 12},{68, 13}, {69, 14},
		{70, 15}, {97, 10}, {98, 11}, {99, 12}, {100, 13},
		{101, 14}, {102, 15}, {47, -1}, {58, -1}, {64, -1},
		{71, -1}, {96, -1}, {103, -1}
	};
	for(r = 0; r < 28; r++){
		struct ConvertTest test = conversionTests[r];
		if(convertHex(&test.originalCharacter, ASCII) != test.expectedCharacter){
			return 0;
		}
	}
	return -1;
}

// Test the isNumber function
int testIsNumber(){
	int r;
	struct ConvertTest conversionTests[12] = {
		{47, 0},{48, 1},{49, 1},{50, 1},{51, 1},
		{52, 1},{53, 1},{54, 1},{55, 1},{56, 1},
		{57, 1},{58, 0}
	};
	for(r=0; r < 12; r++){
		struct ConvertTest test = conversionTests[r];
		if(isNumber(&test.originalCharacter, ASCII) != test.expectedCharacter){
			return 0;
		}
	}
	return -1;
}

// Test the string length in different encodings
int testStringLength(){
	// Test a few ascii strings
	char ascii[10] = "Wedding";
	char ascii2[10] = "1234 3533";
	int asciiLen = len(ascii, ASCII);
	int asciiLen2 = len(ascii2, ASCII);
	if(asciiLen != 7){
		return 0;
	}
	if(asciiLen2 != 9){
		return 0;
	}

	// Test a few iso 8859-1 strings
	// iso8859 = "As you were"
	// iso88502 = "Como estas?"
	char iso8859[12] = {0x41, 0x73, 0xa0, 0x79, 0x6f, 0x75, 0xa0,0x77,0x65,0x72,0x65};
	char iso88592[12] = {0xbf,0xd3,0x6d,0x6f,0xa0,0x65,0x73,0x74,0xe1,0x73,0x3f};
	int iso8859Len = len(iso8859, ISO_8859_1);
	int iso88592Len = len(iso88592, ISO_8859_1);
	if(iso8859Len != 11){
		return 0;
	}
	if(iso88592Len != 11){
		return 0;
	}

	// Test a few ut8 strings
	char utf8[12] = "Wedding";			// This should undertand the ascii encoding
	char utf82[20] = {0xc2,0xbf,0x43,0xc3,0xb2,0x6d,0x6f,0x20,0x65,0x74,0xc3,0xa1,0x73,0x3f};
	int utf8len = len(utf8, UTF8_BINARY);
	int utf82len = len(utf82, UTF8_BINARY);

	if(utf8len != 7){
		return 0;
	}
	if(utf82len != 11){
		return 0;
	}

	// Passed all of the string length tests
	return -1;
}

// A function that tests the main points of functionality associated with the
int testStringUtils(){
	// The success/failure count
	int successCount = 0;
	int failureCount = 0;

	int testIter = 0;
	int numberOfTests = 4;
	int (*test_Array[4])() = {testGetUTF8State, testStringLength, testConvertHex, testIsNumber};
	const char * testNames[4] = {"UTF8State", "String Length test", "Convert hex test", "Is number test"};
	for(testIter = 0; testIter < numberOfTests; testIter++){
		const char * testName = testNames[testIter];
		if(test_Array[testIter]() == -1){
			printf("*SUCCESS - %s passed\n", testName);
		}else{
			printf("*FAILURE - %s failed\n", testName);
		}
	}

	return 0;
}

int main(int argc, char ** argv){
	return testStringUtils();
}
