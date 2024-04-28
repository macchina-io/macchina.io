//
// UUIDWrapper.h
//
// Library: JS/Core
// Package: Wrappers
// Module:  UUIDWrapper
//
// Definition of the UUIDWrapper interface.
//
// Copyright (c) 2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Core_UUIDWrapper_INCLUDED
#define JS_Core_UUIDWrapper_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/UUID.h"


namespace Poco {
namespace JS {
namespace Core {


class JSCore_API UUIDWrapper: public Wrapper
	/// JavaScript wrapper for Poco::UUID.
{
public:
	UUIDWrapper();
		/// Creates the UUIDWrapper.

	~UUIDWrapper();
		/// Destroys the UUIDWrapper.

	v8::Handle<v8::FunctionTemplate> constructor(v8::Isolate* pIsolate);
		/// Creates and returns a V8 FunctionTemplate for the constructor function.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);

protected:
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void isUUID(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void createRandom(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void createTimeBased(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void create(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void version(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void variant(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void toString(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void toBuffer(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void equals(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void isNull(const v8::FunctionCallbackInfo<v8::Value>& args);
};


} } } // namespace Poco::JS::Core


#endif // JS_Core_UUIDWrapper_INCLUDED
