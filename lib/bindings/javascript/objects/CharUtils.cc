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
#include "../../../stringUtils.h"

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
