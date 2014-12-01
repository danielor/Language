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
	ASCII_HEX_ESCAPE = 0,
	ASCII_DECIMAL_ESCAPE = 1
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
			if(effectiveUTFValue < 0x0300 || effectiveUTFValue > 0x036f){
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
			stringLength++;
			if(effectiveUTFValue >= 0x1ab0 && effectiveUTFValue <=0x1aff){
				stringLength--;
			}else if(effectiveUTFValue >= 0x20d0 && effectiveUTFValue <=0x20ff){
				stringLength--;
			}else if(effectiveUTFValue >= 0xfe20 && effectiveUTFValue <=0xfe2f){
				stringLength--;
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
 * Return the UTF8 binary string length. The format of these escaped sequences are
 * the following. At the moment, only ASCII escaping and certain ascii escape signatures
 * are allowed
 * {char in base encoding}{char * controlString in base encoding}[sequence length in sequencEncoding]{endString in base encoding}
 * e.g Happy \u0069 Mildew
 * 	buffer="Happy \u0069 Mildew\0"
 *	baseEncoding=ASCII{utf8BinaryParserStates}
 *	controlString= "\u\0"
 *	sequenceEncoding=ASCII_HEX_ESCAPE
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
		return 0;
	}

	// Check that the base encoding is correct
	if(baseEncoding != ASCII){
		return -1;
	}

	// Check that the sequence encoding is correct
	if(sequenceEncoding != ASCII_HEX_ESCAPE && != ASCII_DECIMAL_ESCAPE){
		return -1;
	}

	const char * characterPointer = buffer;				// A pointer to the correct position in the buffer
	while(*characterPointer != '\0'){

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

#ifdef __cplusplus
}
#endif

#endif
