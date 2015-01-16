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

// Type test struct
struct TypeTest{
	const char * buffer;			// The buffer string
	char expectedResult;			// The expected result
};

// Type test utf struct
struct TypeUTFTest{
	const char * buffer;			// The buffer string
	int expectedResult;				// The expected result
};

// Type test encoding struct
struct TypeEncodingTest{
	const char * buffer;			// The buffer string
	int encoding;					// The encoding of the buffer
	char expectedResult;			// The expected result of the buffer
};

// Test the code point
struct UTFTypeTest{
	int codePoint;					// The code point to test
	char expectedResult;			// The expected result of the code point
};

// Test the utf convert test
struct UTFConvertTest{
	const char * buffer;			// The buffer to test
	int codePoint;					// The code point to check
	char expectedResult;			// The expected result of the test
};

// Test a utf set test
struct UTFSetTest{
	const char * buffer;			// The buffer to test
	const int * codePoints;			// The code points in the set
	char expectedResult;			// The expected result
};

// Test language specific functionality
struct LanguageTest{
	const char * buffer;			// The buffer to test
	int encoding;					// The encoding of the string
	int language;					// The language to test
	char expectedResult;			// The expected result of the test
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

// Test is number sequence
int testIsNumberSequence(){
	int r;
	struct TypeTest typeTests[5] = {
		{"567",1},{"n",0},{"3",1}, {"5gd3",0},
		{"1de3g3dg3",0}
	};
	for(r=0; r < 5; r++){

		struct TypeTest test = typeTests[r];
		if(isNumberSequence(test.buffer, ASCII) != test.expectedResult){
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

// Test the string length escaped functionality
int testStringLengthEscaped(){

	// Test incorrect formatting
	if(lenEscaped(NULL, 0, NULL, 0, NULL) != -1){
		return 0;
	}
	if(lenEscaped("H", 13, NULL, 0, NULL) != -1){
		return 0;
	}
	if(lenEscaped("H", 1, NULL, 0, NULL) != 1){
		return 0;
	}
	if(lenEscaped("H", 1, "H", 35, NULL) != -1){
		return 0;
	}
	// Test the length with no escaped characters
	if(lenEscaped("Healthy", ASCII, "YUM", ASCII_HEX_UTF_ESCAPE, NULL) != 7){
		return 0;
	}
	if(lenEscaped("HealthyYUM2345N", ASCII, "YUM", ASCII_HEX_UTF_ESCAPE, NULL) != 9){
		return 0;
	}
	if(lenEscaped("HealthyYUM2345NR", ASCII, "YUM", ASCII_HEX_UTF_ESCAPE, "N") != 9){
		return 0;
	}
	return -1;
}

// A function that tests if the first byte of a utf code points
// is indicative of a diacritical mark
int testIsDiacriticalMarkUTF8(){
	int r;
	struct UTFTypeTest typeTests[20] = {
		{0x2ff,0},{0x300,1},{0x33f,1}, {0x36f,1},{0x370,0},
		{0x1aaf,0},{0x1ab0,1},{0x1abf,1}, {0x1aff,1},{0x1b00,0},
		{0x20cf,0},{0x20d0,1},{0x20f0,1}, {0x20ff,1},{0x2100,0},
		{0xfe1f,0},{0xfe20,1},{0xfe2f,1}, {0xfe2f,1},{0xfe30,0},
	};
	for(r = 0; r < 20; r++){
		struct UTFTypeTest test = typeTests[r];
		if(isDiacriticalMark(test.codePoint) != test.expectedResult){
			return 0;
		}
	}
	return -1;
}

// A function that checks if a utf8 binary encoded buffer is equal to
// an integer code point
int testIsUTF8BinaryCodePoint(){
	int r;

	// The buffers to test
	const unsigned char buffer[] = {0x56,'\0'};
	const unsigned char xbuffer[] = {0x57,'\0'};
	const unsigned char buffer2[] = {0xc3,0x80,'\0'};
	const unsigned char xbuffer2[] = {0xc3,0x81,'\0'};
	const unsigned char buffer3[] = {0xe0,0xa0,0x80,'\0'};
	const unsigned char xbuffer3[] = {0xe0,0xa0,0x81,'\0'};
	struct UTFConvertTest convertTest[9] = {
		{(const char *)buffer,86,1},{(const char *)buffer,87,0},{(const char *)xbuffer,86,0},
		{(const char *)buffer2,192,1},{(const char *)buffer2,193,0},{(const char *)xbuffer2,192,0},
		{(const char *)buffer3,2048,1},{(const char *)buffer3,2049,0},{(const char *)xbuffer3,2048,0}
	};
	for(r=0; r < 9; r++){
		struct UTFConvertTest test = convertTest[r];
		if(isUTF8BinaryCodePoint(test.buffer, test.codePoint) != test.expectedResult){
			return 0;
		}
	}
	return -1;
}

// A function that checks the conversion between utf8 binary and a utf code
// point functions correctly
int testConvertUTF8BinaryToCodePoint(){
	int r;

	// The buffers to test
	const unsigned char buffer[] = {0x56,'\0'};
	const unsigned char xbuffer[] = {0x57,'\0'};
	const unsigned char buffer2[] = {0xc3,0x80,'\0'};
	const unsigned char xbuffer2[] = {0xc3,0x81,'\0'};
	const unsigned char buffer3[] = {0xe0,0xa0,0x80,'\0'};
	const unsigned char xbuffer3[] = {0xe0,0xa0,0x81,'\0'};
	struct TypeUTFTest typeTests[6] = {
			{(const char *)buffer,86},{(const char *)xbuffer,87},
			{(const char *)buffer2,192},{(const char *)xbuffer2,193},
			{(const char *)buffer3,2048},{(const char *)xbuffer3,2049}
	};
	for(r=0; r < 6; r++){
		struct TypeUTFTest test = typeTests[r];
		if(convertUTF8BinaryToCodePoint(test.buffer) != test.expectedResult){
			return 0;
		}
	}
	return -1;
}

// A function that checks the conversion between a utf8 code point
// and utf8 binary is done correctly
int testConvertCodePointToUTF8Binary(){
	int r;
	int numberOfTests = 6;
	const unsigned char buffer[] = {0x56,'\0'};
	const unsigned char buffer2[] = {0x57,'\0'};
	const unsigned char buffer3[] = {0xc3,0x80,'\0'};
	const unsigned char buffer4[] = {0xc3,0x81,'\0'};
	const unsigned char buffer5[] = {0xe0,0xa0,0x80,'\0'};
	const unsigned char buffer6[] = {0xe0,0xa0,0x81,'\0'};
	const char * bufferResults[] = {(const char *)buffer,(const char*)buffer2,(const char*)buffer3,
			(const char*)buffer4,(const char*)buffer5, (const char*)buffer6
	};
	const int codePoints[] = {86,87,192,193,2048,2049};
	for(r = 0; r < numberOfTests; r++){
		const char * bufferResult = bufferResults[r];
		int codePoint = codePoints[r];
		const char * buffer  = convertCodePointToUTF8Binary(codePoint);
		if(strcmp(buffer, bufferResult) != 0){
			return 0;
		}
		free((void*)buffer);
	}
	return -1;
}

// A function that checks the conversion between a set of utf8 code points
// and utf8 binary
int testConvertCodePointListToUTF8Binary(){
	int r;
	int numberOfTests = 6;
	const int codePointLength[] = {1,2,2,3,3,4};
	const int codePoint[] = {86};
	const int codePoint2[] = {86,87};
	const int codePoint3[] = {192,86};
	const int codePoint4[] = {193,192,87};
	const int codePoint5[] = {2048,86,193};
	const int codePoint6[] = {2049,2048,192,87};
	const unsigned char buffer[] = {0x56,'\0'};
	const unsigned char buffer2[] = {0x56,0x57,'\0'};
	const unsigned char buffer3[] =  {0xc3,0x80,0x56,'\0'};
	const unsigned char buffer4[] = {0xc3,0x81,0xc3,0x80,0x57,'\0'};
	const unsigned char buffer5[] = {0xe0,0xa0,0x80,0x56,0xc3,0x81,'\0'};
	const unsigned char buffer6[] = {0xe0,0xa0,0x81,0xe0,0xa0,0x80,0xc3,0x80,0x57,'\0'};
	const char * bufferResults[] = {(const char *)buffer,(const char*)buffer2,(const char*)buffer3,
			(const char*)buffer4,(const char*)buffer5, (const char*)buffer6
	};
	const int * codePoints[] = {(const int*)codePoint,(const int*)codePoint2,
			(const int*)codePoint3,(const int*) codePoint4, (const int*) codePoint5,
			(const int*)codePoint6};
	for(r = 0; r < numberOfTests; r++){
		const char * bufferResult = bufferResults[r];
		int length = codePointLength[r];
		const int * codePoint = codePoints[r];
		const char * buffer  = converListOfCodePointsToUTF8Binary(codePoint, length);
		if(strcmp(buffer, bufferResult) != 0){
			return 0;
		}
		free((void*)buffer);
	}
	return -1;
}

// A function that checks if a utf8 binary character is in a utf set
// of code points
int testIsUTFBinaryCharacterInUTFSet(){
	int r;
	const unsigned char buffer[] = {0x56,'\0'};
	const unsigned char buffer2[] = {0x57,'\0'};
	const unsigned char buffer3[] = {0xc3,0x80,'\0'};
	const unsigned char buffer4[] = {0xc3,0x81,'\0'};
	const unsigned char buffer5[] = {0xe0,0xa0,0x80,'\0'};
	const unsigned char buffer6[] = {0xe0,0xa0,0x81,'\0'};
	const unsigned char xbuffer[] = {0x58,'\0'};
	const unsigned char xbuffer2[] = {0xc3,0x82,'\0'};
	const unsigned char xbuffer3[] = {0xe0,0xa0,0x82,'\0'};
	const int codePointList[] = {86,87,192,193,2048,2049};
	struct UTFSetTest typeTests[9] = {
			{(const char *)buffer,codePointList,1},{(const char *)buffer2,codePointList,1},
			{(const char *)buffer3,codePointList,1},{(const char *)buffer4,codePointList,1},
			{(const char *)buffer5,codePointList,1},{(const char *)buffer6,codePointList,1},
			{(const char *)xbuffer,codePointList,0},{(const char *)xbuffer2,codePointList, 0},
			{(const char *)xbuffer3,codePointList,0}
	};
	for(int r = 0; r < 9; r++){
		struct UTFSetTest test = typeTests[r];
		if(isUTF8BinaryCharacterInUTFSet(test.buffer,(int*)test.codePoints, 6) != test.expectedResult){
			return 0;
		}
	}

	return -1;
}

// A function that checks in different encodings if a characters is part
// of the Romance alphabet
int testIsInRomanceAlphabet(){
	int r;
	struct ConvertTest conversionTests[10] = {
		{64, 0},{65, 1},{70, 1},{90, 1},{91, 0},
		{96, 0},{97, 1},{110, 1},{122, 1},{123, 0}};
	for(r=0; r < 10; r++){
		struct ConvertTest test = conversionTests[r];
		if(isInRomanceAlphabet(&test.originalCharacter, ASCII) != test.expectedCharacter){
			return 0;
		}
	}
	return -1;
}

// A function that checks if an entire character sequence of characters
// is in the romance alphabet
int testInRomanceAlphabetSequence(){
	int r;
	struct TypeTest typeTests[5] = {
		{"abcdef",1},{"ABCDEF",1},{"0123456789",0}, {"g",1},
		{"G",1}
	};
	for(r=0; r < 5; r++){
		struct TypeTest test = typeTests[r];
		if(isInRomanceAlphabetSequence(test.buffer, ASCII) != test.expectedResult){
			return 0;
		}
	}
	return -1;
}

// A function that tests if characters are part of the hexadecimal
// subset of characters
int testIsHex(){
	int r;
	struct ConvertTest conversionTests[15] = {
		{47, 0},{48, 1},{50, 1},{57, 1},{58, 0},
		{64, 0},{65, 1},{67, 1},{70, 1},{71, 0},
		{96, 0},{97, 1},{100, 1},{102, 1},{103, 0}
	};
	for(r=0; r < 15; r++){
		struct ConvertTest test = conversionTests[r];
		if(isHex(&test.originalCharacter, ASCII) != test.expectedCharacter){
			return 0;
		}
	}
	return -1;
}

// A function that checks if a sequence of characters satisfy the hexadecimal
// range of characters
int testIsHexSequence(){
	int r;
	struct TypeTest typeTests[5] = {
		{"abcdef",1},{"ABCDEF",1},{"0123456789",1}, {"g",0},
		{"G",0}
	};
	for(r=0; r < 5; r++){

		struct TypeTest test = typeTests[r];
		if(isHexSequence(test.buffer, ASCII) != test.expectedResult){
			return 0;
		}
	}
	return -1;
}

// A function that checks if a character is a valid character in an encoding
int testIsValidCharacter(){
	int r;
	const unsigned char buffer[] = {0x0,'\0'};
	const unsigned char buffer2[] = {0x3f,'\0'};
	const unsigned char buffer3[] = {0x7e,'\0'};
	const unsigned char buffer4[] = {0x7f,'\0'};
	const unsigned char buffer5[] = {0x1f,'\0'};
	const unsigned char buffer6[] = {0x20,'\0'};
	const unsigned char buffer7[] = {0x5f,'\0'};
	const unsigned char buffer8[] = {0x7e,'\0'};
	const unsigned char buffer9[] = {0x7f,'\0'};
	const unsigned char buffer10[] = {0x9e,'\0'};
	const unsigned char buffer11[] = {0x9f,'\0'};
	const unsigned char buffer12[] = {0xff,'\0'};
	struct TypeEncodingTest typeTests[12] = {
		{(const char *)buffer, ASCII, 1},{(const char*)buffer2, ASCII, 1},{(const char *)buffer3,ASCII, 1}, {(const char *)buffer4, ASCII, 0},
		{(const char *)buffer5,ISO_8859_1,1},{(const char *)buffer6,ISO_8859_1,1},{(const char*)buffer7,ISO_8859_1,1},{(const char *)buffer8,ISO_8859_1,1},
		{(const char *)buffer9,ISO_8859_1,0},{(const char *)buffer10,ISO_8859_1,0},{(const char *)buffer11,ISO_8859_1,1},{(const char *)buffer12,ISO_8859_1,1}
	};
	for(r=0; r < 12; r++){
		struct TypeEncodingTest test = typeTests[r];
		if(isValidCharacter(test.buffer, test.encoding) != test.expectedResult){
			return 0;
		}
	}
	return -1;
}

// A function that checks if a string is a valid character in an encoding
int testIsValidCharacterSequence(){
	int r;
	const unsigned char buffer2[] = {0x0,0x3f,0x7e,'\0'};
	const unsigned char buffer3[] = {0x1f,0x20,0x5f,0x7e,'\0'};
	const unsigned char xbuffer[] = {0x0,0x3f,0x7e,0x7f,'\0'};
	const unsigned char xbuffer2[] = {0x1f,0x20,0x5f,0x7e,0x7f,'\0'};
	struct TypeEncodingTest typeTests[5] = {
		{"YES", ASCII, 1},{(const char*)buffer2, ASCII, 1},{(const char *)buffer3,ISO_8859_1, 0},
		{(const char *)xbuffer, ISO_8859_1, 1},{(const char *)xbuffer2,ISO_8859_1,0}
	};
	for(r=0; r < 5; r++){
		struct TypeEncodingTest test = typeTests[r];;
		if(isValidCharacterSequence(test.buffer, test.encoding) != test.expectedResult){
			return 0;
		}
	}
	return -1;
}

// A function that checks if a character is a spanish diacritical mark
int testIsSpanishExtendCharacter(){
	int r;

	// Check the ISO_8859_1 encoding
	struct ConvertTest conversionTests[15] = {
		{0xc1, 1},{0xe1, 1},{0xc9, 1},{0xe9, 1},{0xcd, 1},
		{0xed, 1},{0xd3, 1},{0xf3, 1},{0xda, 1},{0xfa, 1},
		{0xfc, 1},{0xd1, 1},{0xc2, 0},{0xe2, 0},{0xf2, 0}
	};
	for(r=0; r < 15; r++){
		struct ConvertTest test = conversionTests[r];
		if(isSpanishExtendedCharacter(&test.originalCharacter, ISO_8859_1) != test.expectedCharacter){
			return 0;
		}
	}

	// Check the uf8 binary encoding
	int bufferTestCount = 16;
	const char * buffer = convertCodePointToUTF8Binary(193);
	const char * buffer2 = convertCodePointToUTF8Binary(225);
	const char * buffer3 = convertCodePointToUTF8Binary(201);
	const char * buffer4 = convertCodePointToUTF8Binary(233);
	const char * buffer5 = convertCodePointToUTF8Binary(205);
	const char * buffer6 = convertCodePointToUTF8Binary(237);
	const char * buffer7 = convertCodePointToUTF8Binary(211);
	const char * buffer8 = convertCodePointToUTF8Binary(243);
	const char * buffer9 = convertCodePointToUTF8Binary(218);
	const char * buffer10 = convertCodePointToUTF8Binary(250);
	const char * buffer11 = convertCodePointToUTF8Binary(252);
	const char * buffer12 = convertCodePointToUTF8Binary(241);
	const char * buffer13 = convertCodePointToUTF8Binary(209);
	const char * xbuffer = convertCodePointToUTF8Binary(194);
	const char * xbuffer2 = convertCodePointToUTF8Binary(195);
	const char * xbuffer3 = convertCodePointToUTF8Binary(196);
	struct TypeUTFTest typeTests[16] = {{buffer,1},{buffer2,1},{buffer3,1},
			{buffer4,1},{buffer5,1},{buffer6,1},{buffer7,1},
			{buffer8,1},{buffer9,1},{buffer10,1},{buffer11,1},
			{buffer12,1},{buffer13,1},{xbuffer, 0}, {xbuffer2,0},
			{xbuffer3,0}
	};
	for(r =0; r < 16; r++){
		struct TypeUTFTest test = typeTests[r];
		if(isSpanishExtendedCharacter(test.buffer,UTF8_BINARY) != test.expectedResult){
			return 0;
		}

		free((void*)test.buffer);
	}

	return -1;
}

// A function that checks if a character is a french diacrtical mark
int testIsFrenchExtendCharacter(){
	int r;

	// Check the ISO_8859_1 encoding
	struct ConvertTest conversionTests[30] = {
		{0xc9, 1},{0xe9, 1},{0xc0, 1},{0xe0, 1},{0xc8, 1},
		{0xe8, 1},{0xd9, 1},{0xf9, 1},{0xc2, 1},{0xe2, 1},
		{0xca, 1},{0xe1, 1},{0xd4, 1},{0xf4, 1},{0xce, 1},
		{0xee, 1},{0xdb, 1},{0xfb, 1},{0xcb, 1},{0xeb, 1},
		{0xcc, 1},{0xec, 1},{0xdc, 1},{0xfc, 1},{0xff, 1},
		{0xc7, 1},{0xe7, 1},{0xd0, 0},{0xb0, 0},{0xd1, 0}
	};
	for(r=0; r < 30; r++){
		struct ConvertTest test = conversionTests[r];

		if(isFrenchExtendedCharacter(&test.originalCharacter, ISO_8859_1) != test.expectedCharacter){
			return 0;
		}
	}
	const char * buffer = convertCodePointToUTF8Binary(201);
	const char * buffer2 = convertCodePointToUTF8Binary(233);
	const char * buffer3 = convertCodePointToUTF8Binary(192);
	const char * buffer4 = convertCodePointToUTF8Binary(224);
	const char * buffer5 = convertCodePointToUTF8Binary(200);
	const char * buffer6 = convertCodePointToUTF8Binary(232);
	const char * buffer7 = convertCodePointToUTF8Binary(217);
	const char * buffer8 = convertCodePointToUTF8Binary(249);
	const char * buffer9 = convertCodePointToUTF8Binary(194);
	const char * buffer10 = convertCodePointToUTF8Binary(226);
	const char * buffer11 = convertCodePointToUTF8Binary(202);
	const char * buffer12 = convertCodePointToUTF8Binary(234);
	const char * buffer13 = convertCodePointToUTF8Binary(206);
	const char * buffer14 = convertCodePointToUTF8Binary(238);
	const char * buffer15 = convertCodePointToUTF8Binary(212);
	const char * buffer16 = convertCodePointToUTF8Binary(244);
	const char * buffer17 = convertCodePointToUTF8Binary(219);
	const char * buffer18 = convertCodePointToUTF8Binary(251);
	const char * buffer19 = convertCodePointToUTF8Binary(203);
	const char * buffer20 = convertCodePointToUTF8Binary(235);
	const char * buffer21 = convertCodePointToUTF8Binary(207);
	const char * buffer22 = convertCodePointToUTF8Binary(239);
	const char * buffer23 = convertCodePointToUTF8Binary(220);
	const char * buffer24 = convertCodePointToUTF8Binary(252);
	const char * buffer25 = convertCodePointToUTF8Binary(255);
	const char * buffer26 = convertCodePointToUTF8Binary(199);
	const char * buffer27 = convertCodePointToUTF8Binary(231);
	const char * xbuffer = convertCodePointToUTF8Binary(1000);
	const char * xbuffer2 = convertCodePointToUTF8Binary(300);
	const char * xbuffer3 = convertCodePointToUTF8Binary(1200);
	struct TypeUTFTest typeTests[30] = {{buffer,1},{buffer2,1},{buffer3,1},
			{buffer4,1},{buffer5,1},{buffer6,1},{buffer7,1},
			{buffer8,1},{buffer9,1},{buffer10,1},{buffer11,1},
			{buffer12,1},{buffer13,1},{buffer14,1},{buffer15,1},
			{buffer16,1},{buffer17,1},{buffer18,1},{buffer19,1},
			{buffer20,1},{buffer21,1},{buffer22,1},{buffer23,1},
			{buffer24,1},{buffer25,1},{buffer26,1},{buffer27,1},
			{xbuffer, 0}, {xbuffer2,0},{xbuffer3,0}
	};
	for(r =0; r < 30; r++){
		struct TypeUTFTest test = typeTests[r];
		if(isFrenchExtendedCharacter(test.buffer,UTF8_BINARY) != test.expectedResult){
			return 0;
		}

		free((void*)test.buffer);
	}

	return -1;
}

// A function that checks if a character is part of the alphabet of
// different languages
int testIsInAlphabet(){
	int r;
	const char * buffer = convertCodePointToUTF8Binary(201);
	const unsigned char buffer2[] = {0xc1,'\0'};
	struct LanguageTest languageTests[] = {
			{"a",ASCII,SPANISH,1},{"b",UTF8_BINARY,FRENCH,1},{"c",ISO_8859_1,ENGLISH,1},
			{buffer,UTF8_BINARY,FRENCH,1},{(const char*)buffer2,ISO_8859_1,SPANISH,1},
			{"0",ISO_8859_1,ENGLISH,0}
	};
	for(r = 0; r< 6; r++){
		struct LanguageTest test = languageTests[r];
		if(isInAlphabet(test.buffer, test.encoding, test.language) != test.expectedResult){
			return 0;
		}
	}
	return -1;
}

// A function that checks if a character is part of an alphabet
// sequence
int testInAphabetSequence(){
	int r;
	const unsigned char buffer2[] = {0x0,0x3f,0x7e,'\0'};
	const unsigned char buffer3[] = {0x1f,0x20,0x5f,0x7e,'\0'};
	const unsigned char xbuffer[] = {0x0,0x3f,0x7e,0x7f,'\0'};
	const unsigned char xbuffer2[] = {0x1f,0x20,0x5f,0x7e,0x7f,'\0'};
	struct TypeEncodingTest typeTests[5] = {
		{"YES", ASCII, 1},{(const char*)buffer2, ASCII, 1},{(const char *)buffer3,ISO_8859_1, 0},
		{(const char *)xbuffer, ISO_8859_1, 1},{(const char *)xbuffer2,ISO_8859_1,0}
	};
	for(r=0; r < 5; r++){
		struct TypeEncodingTest test = typeTests[r];;
		if(isValidCharacterSequence(test.buffer, test.encoding) != test.expectedResult){
			return 0;
		}
	}
	return -1;
}

// A function that tests the main points of functionality associated with the
int testStringUtils(){
	// The success/failure count
	int successCount = 0;
	int failureCount = 0;

	int testIter = 0;
	int numberOfTests = 21;
	int (*test_Array[21])() = {testGetUTF8State, testStringLength, testConvertHex, testIsNumber,
			testStringLengthEscaped, testIsNumberSequence,testIsDiacriticalMarkUTF8, testIsUTF8BinaryCodePoint,
			testIsUTFBinaryCharacterInUTFSet, testIsInRomanceAlphabet, testIsHex, testIsHexSequence,
			testIsSpanishExtendCharacter, testIsFrenchExtendCharacter, testConvertUTF8BinaryToCodePoint,testConvertCodePointToUTF8Binary,
			testIsInAlphabet,testConvertCodePointListToUTF8Binary,testIsValidCharacterSequence, testInRomanceAlphabetSequence,
			testInAphabetSequence};
	const char * testNames[21] = {"UTF8State test", "String Length test", "Convert hex test", "Is number test",
			"String Length Unescaped test", "IsNumberSequence test", "TestIsDiacriticalMarkUTF8 test", "IsUTF8BinaryCodePoint test",
			"Is UTF8 Character in Code Point Set test", "Is Romance Character test", "Is Hex Character test", "Is Hex Sequence test",
			"Is Spanish Extended Character Test","Is French Extend Character Set", "Convert UTF8 Binary To Code Point Test","Convert Code Point to UTF8 binary",
			"Is In Alphabet Test", "Convert Code Points to UTF8 binary","Test is valid Character sequence", "Test is In Romance Alphabet Sequence",
			"Test Is In Aphabet Sequence"};
	for(testIter = 0; testIter < numberOfTests; testIter++){
		const char * testName = testNames[testIter];
		int (*test)() = test_Array[testIter];
		if(test() == -1){
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
