//
// BufferWrapper.h
//
// Library: JS/Core
// Package: Wrappers
// Module:  BufferWrapper
//
// Definition of the BufferWrapper interface.
//
// Copyright (c) 2013-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef JS_Core_BufferWrapper_INCLUDED
#define JS_Core_BufferWrapper_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/Buffer.h"
#include "Poco/TextEncoding.h"
#include "Poco/StreamConverter.h"


namespace Poco {
namespace JS {
namespace Core {


class JSCore_API BufferWrapper: public Wrapper
	/// JavaScript wrapper for Poco::Buffer<char>.
{
public:
	typedef Poco::Buffer<char> Buffer;

	BufferWrapper();
		/// Creates the BufferWrapper.
	
	~BufferWrapper();
		/// Destroys the BufferWrapper.

	v8::Handle<v8::FunctionTemplate> constructor(v8::Isolate* pIsolate);
		/// Creates and returns a V8 FunctionTemplate for the constructor function.

	static void isBuffer(const v8::FunctionCallbackInfo<v8::Value>& args);
		/// Checks whether the given argument is a Buffer.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);
	
protected:
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getLength(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setLength(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getCapacity(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setCapacity(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getAt(uint32_t index, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setAt(uint32_t index, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void toBase64(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void fromBase64(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void decodeString(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void encodeString(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void pack(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void unpack(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void concat(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void slice(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void push(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void pop(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void makeString(const v8::FunctionCallbackInfo<v8::Value>& args);
	static std::size_t calculatePackBufferSize(const std::string& format);

	static void encode(Buffer* pBuffer, const v8::Local<v8::Value>& str, const std::string& encoding);
	static void decode(const v8::FunctionCallbackInfo<v8::Value>& args, const std::string& encoding);

	static const std::string ENCODING_UTF8;
	static const std::string ENCODING_UTF16;
	static const std::string ENCODING_ASCII;
	static const std::string ENCODING_BASE64;
};


} } } // namespace Poco::JS::Core


#endif // JS_Core_BufferWrapper_INCLUDED
