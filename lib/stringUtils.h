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

#include <string.h>
#include <stdlib.h>

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * An enum that encapsulates the different encodings
 * supported by the different functionality used by
 * Language
 */
typedef enum {
	UTF8_BINARY = 0,	// This version of the utf8 analyzes the bits of the characters
						// to guess the information associated with the string.
	ASCII = 1,
	ISO_8859_1 = 2,
} baseEncodings;

/**
 * An enum that encapsulates the different encodings and their
 * alphabets
 */
typedef enum{
	ENGLISH = 0,
	SPANISH = 1,
	FRENCH = 2
} Languages;

/**
 * An enum that encapsulates the different escape encodings
 * supported by different functionality in Language
 */
typedef enum {
	ASCII_HEX_UTF_ESCAPE = 0,
	ASCII_DECIMAL_UTF_ESCAPE = 1
} escapedEncodings;

/**
 * An enum that encpasulates the different parsing states
 * needed by the utf8 binary parsing
 */
typedef enum{
	UTF8_BINARY_ERROR_STATE = -1,		// The error state associated with the parsing
	UTF8_BINARY_START_PARSE_STATE = 0,	// The starting state of the utf8 parser
	UTF8_BINARY_7BIT_STATE = 1,			// The 7 bit encoding for utf8 binary
	UTF8_BINARY_11BIT_STATE = 2,		// The 11 bit encoding for utf8 binary
	UTF8_BINARY_16BIT_STATE = 3,		// The 16 bit encoding for utf8 binary
	UTF8_BINARY_21BIT_STATE = 4,		// The 21 bit encoding for utf8 binary
} utf8BinaryParserStates;

/**
 * An enum that encapsulates the different parsing states
 * needed for parsing encoded strings
 */
typedef enum{
	ENCODED_PARSE_STRING_START = -1, 		// The encoded parse string start state
	ENCODED_PARSE_STRING_CONTROL = 0,		// The encoded parse string control state
	ENCODED_PARSE_STRING_CODE_POINT = 1,	// The encoded parse string code point
	ENCODED_PARSE_STRING_END_STRING = 2,
	ENCODED_PARSE_STRING_END = 3			// The encoded parse string end state
} encodedParsedStringStates;




/**
 * A function that returns the utf8 state associated with a control
 * character. The control character is the first character after
 * a utf8 encoded string has ended
 * @param controlChar The control char to check
 */
int getUTF8State(const char controlChar){
	// Check the control character is
	if(!(controlChar & ((0x01) << 7))){
		return UTF8_BINARY_7BIT_STATE;
	}else if(controlChar & ((0x03) << 6) && !(controlChar & ((0x01) << 5))){
		return UTF8_BINARY_11BIT_STATE;
	}else if(controlChar & ((0x07) << 5) && !(controlChar & ((0x01) << 4))){
		return UTF8_BINARY_16BIT_STATE;
	}else if(controlChar & ((0x0f) << 4) && !(controlChar & ((0x01) << 3))){
		return UTF8_BINARY_21BIT_STATE;
	}else{
		return UTF8_BINARY_ERROR_STATE;
	}
}

/**
 * A function that checks if a code point is a diacritical mark.
 * @param codePoint A utf8 code point
 * @returns {0 = false, 1 = true}
 */
int isDiacriticalMark(int codePoint){
	if(codePoint >= 0x300 && codePoint <= 0x036f){
		return 1;
	}else if(codePoint >= 0x1ab0 && codePoint <=0x1aff){
		return 1;
	}else if(codePoint >= 0x20d0 && codePoint <=0x20ff){
		return 1;
	}else if(codePoint >= 0xfe20 && codePoint <=0xfe2f){
		return 1;
	}else{
		return 0;
	}
}

/**
 * Convert a code point to a utf8 binary character
 * @param codePoint The UTF8 code point
 */
const char * convertCodePointToUTF8Binary(int codePoint){
	if(codePoint < 0){
		return NULL;
	}else if(codePoint < 128){

		// Get the ascii range of utf8
		char c =  (char)codePoint;
		char * buffer = (char*)(malloc(2 * sizeof(char)));
		buffer[0] = c;
		buffer[1] = '\0';
		return buffer;
	}else if(codePoint < 2048){
		int firstByte = 0x000007c0 & codePoint;
		int secondByte = 0x0000003f & codePoint;
		char * buffer = (char*)(malloc(3 * sizeof(char)));
		buffer[0] = (char)(0xc0 | (firstByte >> 6));
		buffer[1] = (char)(0x80 | secondByte);
		buffer[2] = '\0';
		return buffer;
	}else if(codePoint < 65536){
		// Setup the first 3 bytes
		int firstByte = 0x0000f000 & codePoint;
		int secondByte = 0x00000fc0 & codePoint;
		int thirdByte = 0x0000003f & codePoint;
		char * buffer = (char*)(malloc(4 * sizeof(char)));
		buffer[0] = (char)(0xe0 | (firstByte >> 12));
		buffer[1] = (char)(0x80 | (secondByte >> 6));
		buffer[2] = (char)(0x80 | thirdByte);
		buffer[3] = '\0';
		return buffer;
	}else if(codePoint < 0x200000){
		int firstByte = 0x001c0000 & codePoint;
		int secondByte = 0x0003f000 & codePoint;
		int thirdByte = 0x00000fc0 & codePoint;
		int fourthByte = 0x0000003f & codePoint;
		char * buffer = (char*)(malloc(5 * sizeof(char)));
		buffer[0] = (char)(0xf0 | (firstByte >> 18));
		buffer[1] = (char)(0x80 | (secondByte >> 12));
		buffer[2] = (char)(0x80 | (thirdByte >> 6));
		buffer[4] = (char)(0x80 | fourthByte);
		buffer[5] = '\0';
		return buffer;
	}else{
		return NULL;
	}
}

/**
 * Covert a utf binary character into a code point
 * @param charValue The first character of a buffer to convert into a codepoint
 * @returns {A utf8 code point, or -1 for error}
 */
int convertUTF8BinaryToCodePoint(const char * charValue){
	char c = *charValue;
	const char * characterPointer = charValue;
	int utf8ParseState = getUTF8State(c);
	if(utf8ParseState == UTF8_BINARY_7BIT_STATE){
		return c;
	}else if(utf8ParseState == UTF8_BINARY_11BIT_STATE){
		characterPointer++;
		if(characterPointer == '\0'){
			return -1;
		}
		char firstBit = *characterPointer;
		return ((c & 0x1f) << 6) + (firstBit & 0x3f);
	}else if(utf8ParseState == UTF8_BINARY_16BIT_STATE){
		characterPointer++;
		if(characterPointer == '\0'){
			return -1;
		}
		char secondBit = *characterPointer;

		characterPointer++;
		if(characterPointer == '\0'){
			return -1;
		}
		char firstBit = *characterPointer;
		return ((c & 0xf) << 12) + ((secondBit & 0x3f) << 6) + (firstBit & 0x3f);
	}else if(utf8ParseState == UTF8_BINARY_21BIT_STATE){
		characterPointer++;
		if(characterPointer == '\0'){
			return -1;
		}
		char thirdBit = *characterPointer;

		characterPointer++;
		if(characterPointer == '\0'){
			return -1;
		}
		char secondBit = *characterPointer;

		characterPointer++;
		if(characterPointer == '\0'){
			return -1;
		}
		char firstBit = *characterPointer;
		return ((c & 0x7) << 18) + ((thirdBit & 0x3f) << 12) + ((secondBit & 0x3f) << 6) + (firstBit & 0x3f);
	}else{
		return -1;
	}
}

/**
 * Check if a utf8 binary character is equal to a code point.
 * A ut8 binary code point is passed in an integer.
 * @param charValue The first character associated with the character pointer
 * @param codePoint The code point to check
 * @returns {0 = false, 1 = true}
 */
int isUTF8BinaryCodePoint(const char * charValue, int codePoint){
	int convertedCodePoint = convertUTF8BinaryToCodePoint(charValue);

	if(convertedCodePoint == -1){
		return 0;
	}else{
		return codePoint == convertedCodePoint;
	}
}


/**
 * Check if a charcter is part of a set of unicode characters
 * @param charValue The character value to check
 * @param codePoints An array of code points
 * @param numberOfCodePoints The number of code points in the array
 * @returns {0=false, 1=true}
 */
int isUTF8BinaryCharacterInUTFSet(const char * charValue, int *codePoints, int numberOfCodePoints){
	int j;
	int * codePointer = codePoints;
	for(j=0; j < numberOfCodePoints; j++){
		int codePoint = *codePointer;
		int nCodePoint = convertUTF8BinaryToCodePoint(charValue);
		if(isUTF8BinaryCodePoint(charValue, codePoint) == 1){
			return 1;
		}
		codePointer++;
	}
	return 0;
}



/**
 * An function used to check in multiple encodings if the character is a romance
 * character
 * @param charValue The character to check
 * @param encoding The encoding to check
 * @returns {0 = false, 1 = true}
 */
int isInRomanceAlphabet(const char * charValue, int encoding){
	if(encoding == UTF8_BINARY || encoding == ASCII || encoding == ISO_8859_1){
		if(*charValue >= 65 && *charValue <= 90){
			return 1; // a-z
		}
		if(*charValue >= 97 && *charValue <= 122){
			return 1; // A-Z
		}
		return 0;
	}else{
		return 0;
	}
}



/**
 * Return the UTF8 binary string length
 * @param buffer The buffer that contains the string
 */
int _lenUTF8Binary(const char * buffer){
	// Handle the UTF8 encoding
	int stringLength = 0;								// The current length of the string
	int effectiveUTFValue = 0;							// The effective utf8 value as an integer
	int utf8ParseState = UTF8_BINARY_START_PARSE_STATE;	// The utf8 parser state
	const char * characterPointer = buffer;				// A pointer to the correct position in the buffer
	while(*characterPointer != '\0'){

		// Grab our character
		char c = *characterPointer;

		// Enter the UTF8 character state machine. The first portion of the
		// state machine is the extraction of the
		if(utf8ParseState == UTF8_BINARY_START_PARSE_STATE){
			utf8ParseState = getUTF8State(c);
		}
		// Switch between all of the different binary states for the UTF8
		// standard
		if(utf8ParseState == UTF8_BINARY_7BIT_STATE){
			// This state is simple as it an ASCII character. Increment the string length by one,
			// and return to the start parse state
			stringLength++;
			utf8ParseState = UTF8_BINARY_START_PARSE_STATE;
		}else if(utf8ParseState == UTF8_BINARY_11BIT_STATE){
			// This portion of UTF8 encodes the code points between 0x0080 and 0x7ff
			// This portion of the UTF8 contains the combining diacritical marks specified
			// in unicode version 1.0(0x0300 - 0x036f)
			characterPointer++;
			if(characterPointer == '\0'){
				return UTF8_BINARY_ERROR_STATE;
			}
			char firstBit = *characterPointer;

			effectiveUTFValue = ((c & 0x1f) << 6) + (firstBit & 0x3f);
			if(!isDiacriticalMark(effectiveUTFValue)){
				stringLength++;
			}

			utf8ParseState = UTF8_BINARY_START_PARSE_STATE;
		}else if(utf8ParseState == UTF8_BINARY_16BIT_STATE){
			// This portion of UTF8 encodes the code points between 0x0800 and 0xffff
			// This portion of the UTF8 contains the combining diacritical marks specified
			// in unicode version 7.0(0x1ab0-0x1aff), 1.0(0x20d0-0x20ff), 1.0(0xfe20-0xfe2f)
			characterPointer++;
			if(characterPointer == '\0'){
				return UTF8_BINARY_ERROR_STATE;
			}
			char secondBit = *characterPointer;

			characterPointer++;
			if(characterPointer == '\0'){
				return UTF8_BINARY_ERROR_STATE;
			}
			char firstBit = *characterPointer;


			// Get the effective utf8 value to check
			effectiveUTFValue = ((c & 0xf) << 10) + ((secondBit & 0x3f) << 6) + (firstBit & 0x3f);

			// Preincrement and decrement if it is a diacritical mark
			if(!isDiacriticalMark(effectiveUTFValue)){
				stringLength++;
			}

			utf8ParseState = UTF8_BINARY_START_PARSE_STATE;

		}else if(utf8ParseState == UTF8_BINARY_21BIT_STATE){
			int l;
			for(l=0; l < 3; l++){
				characterPointer++;
				if(*characterPointer == '\0'){
					return UTF8_BINARY_ERROR_STATE;
				}
			}
			utf8ParseState = UTF8_BINARY_START_PARSE_STATE;
		}else if(utf8ParseState == UTF8_BINARY_ERROR_STATE){
			return -1;
		}
		// Iterate the character pointer
		characterPointer++;
	}

	return stringLength;
}

/**
 * Check if a character is a number in different encodings
 * @param charValue The character to check
 * @param encoding The encoding of the character
 * @returns {0 = false, 1 = true}
 */
int isNumber(const char * charValue, int encoding){
	if(encoding == UTF8_BINARY || encoding == ASCII || encoding == ISO_8859_1){
		if(*charValue >= 48 && *charValue <= 57){
			return 1;
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}

/**
 * Check if a sequence of characters is a number in a different encodings
 * @param charSequence The character to check
 * @param encoding The encoding of the character
 * @returns {0 = false, 1 = true}
 */
int isNumberSequence(const char * charValueSequence, int encoding){
	const char * characterPointer = charValueSequence;
	while(*characterPointer != '\0'){
		if(isNumber(characterPointer, encoding) == 0){
			return 0;
		}
		characterPointer++;
	}
	return 1;
}

/**
 * Check if a characters is a hex number in different encodings
 * @param charValue The character to check
 * @param encoding The encoding of the character
 * @return {0=false, 1= true}
 */
int isHex(const char * charValue, int encoding){
	if(encoding == UTF8_BINARY || encoding == ASCII || encoding == ISO_8859_1){
		if(*charValue >= 48 && *charValue <= 57){
			return 1;
		}
		if(*charValue >= 65 && *charValue <= 70){
			return 1; // a-f
		}
		if(*charValue >= 97 && *charValue <= 102){
			return 1; // A-F
		}
		return 0;
	}else{
		return 0;
	}
}

/**
 * Check if a sequence of characeters is hex
 * @param charSequence The character to check
 * @param encoding The encoding of the character
 * @returns {0 = false, 1 = true}
 */
int isHexSequence(const char * charValueSequence, int encoding){
	const char * characterPointer = charValueSequence;
	while(*characterPointer != '\0'){
		if(isHex(characterPointer, encoding) == 0){
			return 0;
		}
		characterPointer++;
	}
	return 1;
}

/**
 * A function that checks if a character is a valid part of an
 * encoding. This will not work for encoding that require multiple
 * bytes
 * @param charValue The character to check
 * @param encoding The encoding to check
 * @returns {0 = false, 1 = true}
 */
int isValidCharacter(const char * charValue, int encoding){
	char value = *charValue;
	if(encoding == ASCII){
		if(value < 0x7f){
			return 1;
		}else{
			return 0;
		}
	}else if(encoding == ISO_8859_1){
		if((value > 0x20 && value < 0x7f) || (unsigned char)value > 0x9f){
			return 1;
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}

/**
 * Check if a character is part of the extended set of characters
 * that are observed in Spanish in a specific encoding
 * @param charValue The character associated with
 * @param encoding The encoding to check for
 * @return {0 = false, 1 = true}
 */
int isSpanishExtendedCharacter(const char * charValue, int encoding){
	if(encoding == ASCII){
		return 0;
	}else if(encoding == ISO_8859_1){
		unsigned char value = (unsigned char)(*charValue);
		// c1 = A(acute), e1 = a(acute), c9 = E(acute), e9 = e(acute),
		// cd = I(acute), ed = i(acute), d3 = O(acute), f3 = o(acute),
		// da = U(acute), fa = u(acute), fc = u(diaresis), d1 = N(tilde)
		// f1 = n(tilde)
		if(value == 0xc1 || value == 0xe1 || value == 0xc9 || value == 0xe9 ||
				value == 0xcd || value == 0xed || value == 0xd3 || value == 0xf3  ||
				value == 0xda || value == 0xfa || value == 0xfc || value == 0xd1 ||
				value == 0xf1){
			return 1;
		}else{
			return 0;
		}
	}else if(encoding == UTF8_BINARY){
		int i;
		// 193 = A(acute), 225 = a(acute), 201 = E(acute), 233 = e(acute)
		// 205 = I(acute), 237 = i(acute), 211 = O(acute), 243 = o(acute)
		// 218 = U(acute), 250 = u(acute), 252 = u(diaresis), 241 = n(tilde)
		// 209 = N(tilde)
		int spanishCodePointList[13] = {
			193,225,201,233,205,237,211,243,
			218,250,252,241,209
		};
		return isUTF8BinaryCharacterInUTFSet(charValue, spanishCodePointList, 13);
	}else{
		return 0;
	}
}

/**
 * Check if a character is pat of the extended set of characters
 * that are observed in French for a specific encoding
 * @param charValue The character to check
 * @param encoding The encoding to check in
 * @return {0 = false, 1 = true}
 */
int isFrenchExtendedCharacter(const char * charValue, int encoding){
	if(encoding == ASCII){
		return 0;
	}else if(encoding == ISO_8859_1){
		unsigned char value = (unsigned char)(*charValue);
		// c9 = E(acute), e9 = e(acute), c0 = A(grave), e0 = a(grave)
		// c8 = E(grave), e8 = e(grave), d9 = U(grave), f9 = u(grave)
		// c2 = A(circumflex), e2 = a(circumflex), ca = E(circumflex), ea = e(circumflex)
		// ce = I(circumflex), ee = i(circumflex), d4 = O(circumflex), f4 = o(circumflex)
		// db = U(circumflex), fb = u(circumflex), cb = E(diaresis), eb = e(diaresis)
		// cc = I(diaresis), ec = i(diaresis), dc = U(diaresis), fc = u(diaresis)
		// ff = y(diaresis), c7 = cedilla, e7 = cedilla
		if(value == 0xc9 || value == 0xe9 || value == 0xc0 || value == 0xe0 ||
				value == 0xc8 || value == 0xe8 || value == 0xd9 || value == 0xf9 ||
				value == 0xc2 || value == 0xe2 || value == 0xca || value == 0xe1 ||
				value == 0xd4 || value == 0xf4 || value == 0xce || value == 0xee ||
				value == 0xdb || value == 0xfb || value == 0xcb || value == 0xeb ||
				value == 0xcc || value == 0xec || value == 0xdc || value == 0xfc ||
				value == 0xff || value == 0xc7 || value == 0xe7){
			return 1;
		}else{
			return 0;
		}
	}else if(encoding == UTF8_BINARY){
		// 201 = e(acute), 233 = E(acute), 192 = A(grave), 224 = a(grave)
		// 200 = E(grave), 232 = e(grave), 217 = U(grave), 249 = u(grave)
		// 194 = A(circumflex), 226 = a(circumflex), 202 = E(circumflex), 234 = e(circumflex)
		// 206 = I(circumflex), 238 = i(circumflex),  212 = O(circumflex), 244 = o(circumflex)
		// 219 = U(circumflex), 251 = u(circumflex), 203 = E(diaresis), 235 = e(diaresis)
		// 207 = I(diaresis), 239 = i(diaresis), 220 = U(diaresis), 252 = u(diaresis)
		// 255 = y(diaresis), 199 = cedilla capital, 231 cedilla lower
		int frenchCodePointList[27] = {
				201,233,192,224,200,232,217,249,
				194,226,202,234,206,238,212,244,
				219,251,203,235,207,239,220,252,
				255,199,231
				};
		return isUTF8BinaryCharacterInUTFSet(charValue, frenchCodePointList, 27);
	}else{
		return 0;
	}
}

/**
 * Check if a character is part of the alphabet of different languages.
 * Different languages have added characters that go beyond the standard
 * ASCII characters.
 * @param charValue The character to check
 * @param encoding The encoding of the character
 * @param language The language of the character
 * @returns {0= false, 1 = true}
 */
int isInAlphabet(const char * charValue, int encoding, int language){
	// The ascii character set is limited. Make sure that irrespective of the language
	// that the character value has the romance core without the diacritical marks.
	if(isInRomanceAlphabet(charValue, encoding)){
		return 1;
	}else{
		// Each language has its own diacritical marks that are formally part
		// of the ortography of the language. For now, only romance languages
		// have been addresed.
		if(language == ENGLISH){
			return 0;					// Imported words are ignored.
		}else if(language == SPANISH){
			return isSpanishExtendedCharacter(charValue, encoding);
		}else if(language == FRENCH){
			return isFrenchExtendedCharacter(charValue, encoding);
		}else{
			return 0;
		}
	}
}

/**
 * Convert character encoding to a number. At the moment, encoding is ignored
 * @param charValue The character to convert
 * @returns {0-9}
 */
int convertToNumber(const char *charValue, int encoding){
	return *charValue - 48;
}

/**
 * Convert hex character into binary in a certain encoding(At the moment ASCII)
 * @param hexValue The hex value
 * @param encoding The encoding of the hexValue
 */
char convertHex(const char * hexValue, int encoding){
	if(encoding == UTF8_BINARY || encoding == ASCII || encoding == ISO_8859_1){
		// Handle 0-9
		if(*hexValue >= 48 && *hexValue <= 57){
			return *hexValue - 48;
		}

		// Handle A-F
		if(*hexValue >= 65 && *hexValue <= 70){
			return *hexValue - 55; // ([70,65] - 10)
		}

		// Handle a-f
		if(*hexValue >= 97 && *hexValue <= 102){
			return *hexValue - 87; // ([102, 97] - 10)
		}
		return -1;
	}else{
		return -1;
	}
}

/**
 * A C-style string length that handles different encodings found
 * in the wild. It analyzes the bytes in a char * and returns the
 * string length irrespective of the encoding.
 * @param buffer: The buffer that contains the string
 * @param encoding: The encoding used to find the byte length
 */
int len(const char * buffer, int encoding){

	// Handle an incorrectly structured buffer
	if(buffer == NULL){
		return 0;
	}

	// Deal with the simple ASCII/LATIN cases
	if(encoding == ASCII){
		return strlen(buffer);
	}else if(encoding == ISO_8859_1){
		return strlen(buffer);
	}else if(encoding == UTF8_BINARY){
		return _lenUTF8Binary(buffer);
	}else{
		return -1;
	}
}


/**
 * Return the UTF8 binary string length. The format of these escaped sequences are
 * the following. At the moment, only ASCII escaping and certain ascii escape signatures
 * are allowed
 * {char in base encoding}{char * controlString in base encoding}[sequence length in sequencEncoding]{endString in base encoding}
 * e.g Happy \u0069 Mildew
 * 	buffer="Happy \u0069 Mildew\0"
 *	baseEncoding=ASCII{utf8BinaryParserStates}
 *	controlString= "\u\0"
 *	sequenceEncoding=ASCII_HEX_UTF_ESCAPE
 *	endString=NULL
 * @param buffer The buffer that contains the string
 * @param baseEncoding The base encoding of the string{
 * @param controlString The control string in the base encoding
 * @param sequenceEncoding The encoding of the sequence
 * @param endString The end string of the sequence
 */
int lenEscaped(const char * buffer, int baseEncoding, const char * controlString,
		int sequenceEncoding, const char * endString){
	// Handle the incorrectly structured buffer
	if(buffer == NULL){
		return -1;
	}

	// Check that the base encoding is correct
	if(baseEncoding != ASCII){
		return -1;
	}

	// If we have no control string return the length of the unescaped buffer
	if(controlString == NULL){
		return len(buffer, baseEncoding);
	}

	// Check that the sequence encoding is correct
	if(sequenceEncoding != ASCII_HEX_UTF_ESCAPE && sequenceEncoding != ASCII_DECIMAL_UTF_ESCAPE){
		return -1;
	}

	int index = 0;
	int escapedState = ENCODED_PARSE_STRING_START;
	int controlCount = 0;								// The control string count
	int lenEscapedCount = 0;							// Return the length of the escaped count
	const char * controlPointer = controlString;		// Setup a pointer to the control string.
	const char * characterPointer = buffer;				// A pointer to the correct position in the buffer
	while(*characterPointer != '\0'){
		if(escapedState == ENCODED_PARSE_STRING_START){
			if(*controlPointer == *characterPointer){
				escapedState = ENCODED_PARSE_STRING_CONTROL;
				continue;
			}else{
				lenEscapedCount = lenEscapedCount + 1;
			}
		// Make sure that the entirety of the control string has been captured
		}else if(escapedState == ENCODED_PARSE_STRING_CONTROL){

			// We have reached the E
			if(*controlPointer == '\0'){
				controlPointer = controlString;
				controlCount = 0;
				escapedState = ENCODED_PARSE_STRING_CODE_POINT;
				continue;
			}
			if(*controlPointer != *characterPointer){
				controlPointer = controlString;
				escapedState = ENCODED_PARSE_STRING_START;
				lenEscapedCount += controlCount;
				controlCount=0;
				continue;
			}
			controlPointer++;
			controlCount++;

		}else if(escapedState == ENCODED_PARSE_STRING_CODE_POINT){
			if(sequenceEncoding == ASCII_HEX_UTF_ESCAPE){
				int codePoint = 0;
				for(;index < 4; index++){
					if(*characterPointer == '\0'){
						return -1;
					}
					char convertedHex = convertHex(characterPointer, ASCII);
					if(convertedHex == -1){
						return -1;
					}

					codePoint += convertedHex;
					codePoint <<= 4;
					characterPointer++;
				}
				if(!isDiacriticalMark(codePoint)){
					lenEscapedCount++;
				}

			}else{
				int codePoint = 0;

				// Consume all of the numbers until we reach a character that
				// is not a number
				while(1){
					if(*characterPointer == '\0'){
						break;
					}
					if(isNumber(characterPointer, ASCII)){
						codePoint *= 10;
						codePoint += convertToNumber(characterPointer, ASCII);
						characterPointer++;
					}else{
						break;
					}

				}
				if(!isDiacriticalMark(codePoint)){
					lenEscapedCount++;
				}

				if(*characterPointer == '\0'){
					break;
				}
			}
			// Dependent on whether the end string is null continue to
			// the start state
			if(endString == NULL){
				escapedState = ENCODED_PARSE_STRING_START;
				continue;
			}else{
				escapedState = ENCODED_PARSE_STRING_END_STRING;
				continue;
			}

		}else if(escapedState == ENCODED_PARSE_STRING_END_STRING){
			const char * endStringPointer = endString;
			while(*characterPointer == *endStringPointer){
				characterPointer++;
				endStringPointer++;
			}
			escapedState = ENCODED_PARSE_STRING_START;
			continue;
		}
		characterPointer++;
	}
	return lenEscapedCount;
}


#ifdef __cplusplus
}
#endif

#endif
