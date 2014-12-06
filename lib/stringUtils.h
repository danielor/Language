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
			char firstBit = *characterPointer;
			if(firstBit == '\0'){
				return UTF8_BINARY_ERROR_STATE;
			}
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
			char secondBit = *characterPointer;
			if(secondBit == '\0'){
				return UTF8_BINARY_ERROR_STATE;
			}
			characterPointer++;
			char firstBit = *characterPointer;
			if(firstBit == '\0'){
				return UTF8_BINARY_ERROR_STATE;
			}

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
