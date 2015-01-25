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
#include "CharUtils.h"
#include "../../../lib/stringUtils.h"

// Setup the char utils constructor
v8::Persistent<v8::Function> CharUtils::constructor;

// The constructor/destructor
CharUtils::CharUtils(){

}

CharUtils::~CharUtils(){

}

// Initalize the CharUtils class object
void CharUtils::Init(v8::Handle<v8::Object> exports){
	// Prepare the constructor template
	v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(New);
	tpl->SetClassName(v8::String::NewSymbol("CharUtils"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Set the constructor and exporting of the v8 object
	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("isHexNumberChar"),
				v8::FunctionTemplate::New(isHexNumberChar)->GetFunction());
		tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("isNaturalNumberChar"),
				v8::FunctionTemplate::New(isNaturalNumberChar)->GetFunction());
		tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("isValidChar"),
					v8::FunctionTemplate::New(isValidChar)->GetFunction());
		tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("isInAlphabetChar"),
				v8::FunctionTemplate::New(isInAlphabetChar)->GetFunction());
		tpl->InstanceTemplate()->SetAccessor(v8::String::New("stringEncodings"), getStringEncodings);
		tpl->InstanceTemplate()->SetAccessor(v8::String::New("languageEncodings"), getLanguageEncodings);

	constructor = v8::Persistent<v8::Function>::New(tpl->GetFunction());
	exports->Set(v8::String::NewSymbol("CharUtils"), constructor);
}

// Setup the new operator
v8::Handle<v8::Value> CharUtils::New(const v8::Arguments & args){
	v8::HandleScope scope;

	// Split the argument constructor call by the two different modes
	// of constructing a class in javascript
	if(args.IsConstructCall()){
		CharUtils * utils = new CharUtils();
		utils->Wrap(args.This());
		return args.This();
	}else{
		return scope.Close(constructor->NewInstance());
	}
}

// The main interface for characters
v8::Handle<v8::Value> CharUtils::isHexNumberChar(const v8::Arguments & args){
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
		result = isHex(buffer, encoding);
	}

	return scope.Close(v8::Boolean::New(result == 1));
}

v8::Handle<v8::Value> CharUtils::isNaturalNumberChar(const v8::Arguments & args){
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
		result = isNumber(buffer, encoding);
	}

	return scope.Close(v8::Boolean::New(result == 1));
}


v8::Handle<v8::Value> CharUtils::isValidChar(const v8::Arguments & args){
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
		result = isValidCharacter(buffer, encoding);
	}

	return scope.Close(v8::Boolean::New(result == 1));
}

v8::Handle<v8::Value> CharUtils::isInAlphabetChar(const v8::Arguments & args){
	v8::HandleScope scope;

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
		result = isInAlphabet(buffer, encoding, language);
	}

	return scope.Close(v8::Boolean::New(result == 1));
}

v8::Handle<v8::Value> CharUtils::isInRomanceAlphabetChar(const v8::Arguments & args){
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
		result = isInRomanceAlphabet(buffer, encoding);
	}

	return scope.Close(v8::Boolean::New(result == 1));
}

// Getters and setters
v8::Handle<v8::Value> CharUtils::getStringEncodings(v8::Local<v8::String> name, const v8::AccessorInfo & info){
	v8::HandleScope scope;
	v8::Local<v8::Object> obj = v8::Object::New();

	// Set the different string encodings
	obj->Set(v8::String::New("ASCII"), v8::Integer::New(ASCII));
	obj->Set(v8::String::New("UTF8_BINARY"), v8::Integer::New(UTF8_BINARY));
	obj->Set(v8::String::New("ISO_8859_1"), v8::Integer::New(ISO_8859_1));
	return scope.Close(obj);
}

v8::Handle<v8::Value> CharUtils::getLanguageEncodings(v8::Local<v8::String> name, const v8::AccessorInfo & info){
	v8::HandleScope scope;
	v8::Local<v8::Object> obj = v8::Object::New();

	// Set the different string encodings
	obj->Set(v8::String::New("ENGLISH"), v8::Integer::New(ENGLISH));
	obj->Set(v8::String::New("SPANISH"), v8::Integer::New(SPANISH));
	obj->Set(v8::String::New("FRENCH"), v8::Integer::New(FRENCH));
	return scope.Close(obj);
}
