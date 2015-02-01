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

#ifndef NODE_CHAR_UTILS_H
#define NODE_CHAR_UTILS_H

#include <node.h>

/**
 * The CharUtils class provide an interface to character transforms
 * provided by Language. These V8 bindings will only analyze the first
 * character of a string.
 */
class CharUtils : public node::ObjectWrap{
public:
	// The tie in to the node module
	static void Init(v8::Handle<v8::Object> exports);

private:
	// The constructor/destructor of the class
	explicit CharUtils();
	~CharUtils();

	// The basic interface of a wrapped object
	static v8::Handle<v8::Value> New(const v8::Arguments & args);
	static v8::Persistent<v8::Function> constructor;

	// Getters and setters
	static v8::Handle<v8::Value> getStringEncodings(v8::Local<v8::String> name, const v8::AccessorInfo & info);
	static v8::Handle<v8::Value> getLanguageEncodings(v8::Local<v8::String> name, const v8::AccessorInfo & info);

	// The character utils interface
	static v8::Handle<v8::Value> isHexNumber(const v8::Arguments & args);
	static v8::Handle<v8::Value> isNaturalNumber(const v8::Arguments & args);
	static v8::Handle<v8::Value> isValid(const v8::Arguments & args);
	static v8::Handle<v8::Value> isInAlphabet(const v8::Arguments & args);
	static v8::Handle<v8::Value> isInRomanceAlphabet(const v8::Arguments & args);
};

#endif
