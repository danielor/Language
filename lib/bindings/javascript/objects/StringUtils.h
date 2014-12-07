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

#ifndef NODE_STRING_UTILS_H
#define NODE_STRING_UTILS_H

#include <node.h>

/**
 * The StringUtils class provide an interface to the Language
 * library through the V8 bindings provide by Node.js
 */
class StringUtils : public node::ObjectWrap{
public:
	// The tie in to the node module
	static void Init(v8::Handle<v8::Object> exports);


private:
	// The constructor/destructor of the class
	explicit StringUtils();
	~StringUtils();

	// The interface to the utils
	static v8::Handle<v8::Value> New(const v8::Arguments & args);
	static v8::Persistent<v8::Function> constructor;

	// The interface functions for the string utilities
	static v8::Handle<v8::Value> length(const v8::Arguments & args);
	static v8::Handle<v8::Value> lengthEscaped(const v8::Arguments & args);
	static v8::Handle<v8::Value> isNaturalNumber(const v8::Arguments & args);

	// Getters and setters
	static v8::Handle<v8::Value> getStringEncodings(v8::Local<v8::String> name, const v8::AccessorInfo & info);

	// Helper function to parse different variables
	static void _parseInt(const v8::Arguments & args, int index,  int * value);
	static void _parseString(const v8::Arguments & args, int index, const char * value);
};

#endif
