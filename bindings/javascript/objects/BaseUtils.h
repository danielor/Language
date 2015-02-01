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

#ifndef __NODE_BASE_UTILS_H__
#define __NODE_BASE_UTILS_H__

#include <node.h>
#include "../../../lib/stringUtils.h"

/**
 * A helper function that checks using func a string in a particular encoding
 * @param args The v8 arguments
 * @param func The funcion to be used on the v8:Arguments
 */
static int checkStringInEncoding(const v8::Arguments & args, int (*func)(const char *, int)){
	// The base encoding
	int encoding = UTF8_BINARY;
	const char * buffer;
	bool isValid = false;

	// Get the variables from the arguments
	if(args[0]->IsString()){
		buffer = *v8::String::Utf8Value(args[0]);
		isValid = true;
	}
	if(args[1]->IsNumber()){
		encoding = args[1]->Uint32Value();
	}

	// Find the length if we have a valid call. If not return 0
	int result = 0;
	if(isValid){
		result = func(buffer, encoding);
	}
	return result;
}

/**
 * A hlerp function that checks using a function if a string in particular encoding
 * and language has a certain characteristic
 * @param args The v8 arguments
 * @param func The function to be used on the v8:Arguments
 */
static int checkStringInEncodingAndLanguage(const v8::Arguments & args, int (*func)(const char *, int, int)){
	// The base encoding
	int encoding = UTF8_BINARY;
	int language = ENGLISH;
	const char * buffer;
	bool isValid = false;

	// Get the variables from the arguments
	if(args[0]->IsString()){
		buffer = *v8::String::Utf8Value(args[0]);
		isValid = true;
	}
	if(args[1]->IsNumber()){
		encoding = args[1]->Uint32Value();
	}
	if(args[2]->IsNumber()){
		language = args[2]->Uint32Value();
	}

	// Find the length if we have a valid call. If not return 0
	int result = 0;
	if(isValid){
		result = func(buffer, encoding, language);
	}
	return result;
}

#endif
