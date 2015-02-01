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
#include <node.h>
#include "StringUtils.h"
#include "BaseUtils.h"
#include "../../../lib/stringUtils.h"

// Setup the string utils v8 constructor
v8::Persistent<v8::Function> StringUtils::constructor;

// The constructor/destructor
StringUtils::StringUtils(){

}

StringUtils::~StringUtils(){

}

// Intialize the StringUtils class object
void StringUtils::Init(v8::Handle<v8::Object> exports){
	// Prepare the constructor template
	v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(New);
	tpl->SetClassName(v8::String::NewSymbol("StringUtils"));
	tpl->InstanceTemplate()->SetInternalFieldCount(2);

	// Prototype

	// The length function
	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("length"),
			v8::FunctionTemplate::New(length)->GetFunction());
	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("lengthEscaped"),
			v8::FunctionTemplate::New(lengthEscaped)->GetFunction());
	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("isNaturalNumber"),
			v8::FunctionTemplate::New(isNaturalNumber)->GetFunction());
	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("isHexNumber"),
			v8::FunctionTemplate::New(isHexNumber)->GetFunction());
	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("isValid"),
			v8::FunctionTemplate::New(isValid)->GetFunction());
	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("isInRomanceAlphabet"),
			v8::FunctionTemplate::New(isInRomanceAlphabet)->GetFunction());
	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("isInAlphabet"),
			v8::FunctionTemplate::New(isInAlphabet)->GetFunction());
	tpl->InstanceTemplate()->SetAccessor(v8::String::New("stringEncodings"), getStringEncodings);
	tpl->InstanceTemplate()->SetAccessor(v8::String::New("languageEncodings"), getLanguageEncodings);

	constructor = v8::Persistent<v8::Function>::New(tpl->GetFunction());
	exports->Set(v8::String::NewSymbol("StringUtils"), constructor);

}


// Setup the handle for the new operator
v8::Handle<v8::Value> StringUtils::New(const v8::Arguments & args){
	v8::HandleScope scope;

	// Split the argument constructor call by the two different modes
	// of constructing a class in javascript
	if(args.IsConstructCall()){
		StringUtils * utils = new StringUtils();
		utils->Wrap(args.This());
		return args.This();
	}else{
		// No arguments for now.
		return scope.Close(constructor->NewInstance());
	}
}

// Find the length of the string
v8::Handle<v8::Value> StringUtils::length(const v8::Arguments & args){
	v8::HandleScope scope;


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
		result = len(buffer, encoding);
	}else{
		result = -1;
	}

	// Return the string length
	return scope.Close(v8::Number::New(result));
}

// Find the length of an escape string
v8::Handle<v8::Value> StringUtils::lengthEscaped(const v8::Arguments & args){
	v8::HandleScope scope;

	// The information need to find the length of escaped characterså
	const char * buffer = NULL;
	v8::String::Utf8Value bufferStr(args[0]->ToString());
	if(args[0]->IsString()){
		buffer = *bufferStr;
	}
	int encoding = args[1]->IsNumber() ? args[1]->Uint32Value() : ASCII;
	const char * controlString = NULL;
	v8::String::Utf8Value controlStr(args[2]->ToString());
	if(args[2]->IsString()){
		controlString = *controlStr;
	}

	int escapeEncoding = args[3]->IsNumber() ? args[3]->Uint32Value() : ASCII_HEX_UTF_ESCAPE;
	const char * endString = NULL;
	v8::String::Utf8Value end(args[4]->ToString());
	if(args[4]->IsString()){
		endString = *end;
	}

	int result = lenEscaped(buffer, encoding, controlString, escapeEncoding, endString);
	return scope.Close(v8::Number::New(result));
}

v8::Handle<v8::Value> StringUtils::isNaturalNumber(const v8::Arguments & args){
	v8::HandleScope scope;
	int result = checkStringInEncoding(args, isNumberSequence);
	return scope.Close(v8::Boolean::New(result == 1));
}

v8::Handle<v8::Value> StringUtils::isHexNumber(const v8::Arguments & args){
	v8::HandleScope scope;
	int result = checkStringInEncoding(args, isHexSequence);
	return scope.Close(v8::Boolean::New(result == 1));
}

v8::Handle<v8::Value> StringUtils::isValid(const v8::Arguments & args){
	v8::HandleScope scope;
	int result = checkStringInEncoding(args, isValidCharacterSequence);
	return scope.Close(v8::Boolean::New(result == 1));
}

v8::Handle<v8::Value> StringUtils::isInRomanceAlphabet(const v8::Arguments & args){
	v8::HandleScope scope;
	int result = checkStringInEncoding(args, isInRomanceAlphabetSequence);
	return scope.Close(v8::Boolean::New(result == 1));
}


v8::Handle<v8::Value> StringUtils::isInAlphabet(const v8::Arguments & args){
	v8::HandleScope scope;
	int result = checkStringInEncodingAndLanguage(args, isInAlphabetSequence);
	return scope.Close(v8::Boolean::New(result == 1));
}


// Getters and setters
v8::Handle<v8::Value> StringUtils::getStringEncodings(v8::Local<v8::String> name, const v8::AccessorInfo & info){
	v8::HandleScope scope;
	v8::Local<v8::Object> obj = v8::Object::New();

	// Set the different string encodings
	obj->Set(v8::String::New("ASCII"), v8::Integer::New(ASCII));
	obj->Set(v8::String::New("UTF8_BINARY"), v8::Integer::New(UTF8_BINARY));
	obj->Set(v8::String::New("ISO_8859_1"), v8::Integer::New(ISO_8859_1));
	return scope.Close(obj);
}

v8::Handle<v8::Value> StringUtils::getLanguageEncodings(v8::Local<v8::String> name, const v8::AccessorInfo & info){
	v8::HandleScope scope;
	v8::Local<v8::Object> obj = v8::Object::New();

	// Set the different string encodings
	obj->Set(v8::String::New("ENGLISH"), v8::Integer::New(ENGLISH));
	obj->Set(v8::String::New("SPANISH"), v8::Integer::New(SPANISH));
	obj->Set(v8::String::New("FRENCH"), v8::Integer::New(FRENCH));
	return scope.Close(obj);
}


