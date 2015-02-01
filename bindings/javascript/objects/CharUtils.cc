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
#include "BaseUtils.h"
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
	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("isHexNumber"),
				v8::FunctionTemplate::New(isHexNumber)->GetFunction());
	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("isNaturalNumber"),
			v8::FunctionTemplate::New(isNaturalNumber)->GetFunction());
	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("isValid"),
				v8::FunctionTemplate::New(isValid)->GetFunction());
	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("isInAlphabet"),
			v8::FunctionTemplate::New(isInAlphabet)->GetFunction());
	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("isLowerCaseInAlphabet"),
			v8::FunctionTemplate::New(isLowerCaseInAlphabet)->GetFunction());
	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("isUpperCaseInAlphabet"),
			v8::FunctionTemplate::New(isUpperCaseInAlphabet)->GetFunction());
	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("isPunctuationMarkInAlphabet"),
			v8::FunctionTemplate::New(isPunctuationMarkInAlphabet)->GetFunction());
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
v8::Handle<v8::Value> CharUtils::isHexNumber(const v8::Arguments & args){
	v8::HandleScope scope;
	int result = checkStringInEncoding(args, isHex);
	return scope.Close(v8::Boolean::New(result == 1));
}

v8::Handle<v8::Value> CharUtils::isNaturalNumber(const v8::Arguments & args){
	v8::HandleScope scope;
	int result = checkStringInEncoding(args, isNumber);
	return scope.Close(v8::Boolean::New(result == 1));
}


v8::Handle<v8::Value> CharUtils::isValid(const v8::Arguments & args){
	v8::HandleScope scope;
	int result = checkStringInEncoding(args, isValidCharacter);
	return scope.Close(v8::Boolean::New(result == 1));
}

v8::Handle<v8::Value> CharUtils::isInAlphabet(const v8::Arguments & args){
	v8::HandleScope scope;
	int result = checkStringInEncodingAndLanguage(args, ::isInAlphabet);
	return scope.Close(v8::Boolean::New(result == 1));
}

v8::Handle<v8::Value> CharUtils::isInRomanceAlphabet(const v8::Arguments & args){
	v8::HandleScope scope;
	int result = checkStringInEncoding(args, ::isInRomanceAlphabet);
	return scope.Close(v8::Boolean::New(result == 1));
}

v8::Handle<v8::Value> CharUtils::isLowerCaseInAlphabet(const v8::Arguments & args){
	v8::HandleScope scope;
	int result = checkStringInEncodingAndLanguage(args, ::isLowerCaseInAlphabet);
	return scope.Close(v8::Boolean::New(result == 1));
}

v8::Handle<v8::Value> CharUtils::isUpperCaseInAlphabet(const v8::Arguments & args){
	v8::HandleScope scope;
	int result = checkStringInEncodingAndLanguage(args, ::isUpperCaseInAlphabet);
	return scope.Close(v8::Boolean::New(result == 1));
}

v8::Handle<v8::Value> CharUtils::isPunctuationMarkInAlphabet(const v8::Arguments & args){
	v8::HandleScope scope;
	int result = checkStringInEncodingAndLanguage(args, ::isPunctuationMarkInAlphabet);
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
