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
// SPDX-License-Identifier: GPL-3.0-only
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
	using Buffer = Poco::Buffer<char>;

	BufferWrapper();
		/// Creates the BufferWrapper.

	~BufferWrapper();
		/// Destroys the BufferWrapper.

	v8::Handle<v8::FunctionTemplate> constructor(v8::Isolate* pIsolate);
		/// Creates and returns a V8 FunctionTemplate for the constructor function.

	static void isBuffer(const v8::FunctionCallbackInfo<v8::Value>& args);
		/// Checks whether the given argument is a Buffer.

	static void encode(v8::Isolate* pIsolate, Buffer* pBuffer, const v8::Local<v8::Value>& str, const std::string& encoding);
	static void decode(const v8::FunctionCallbackInfo<v8::Value>& args, const std::string& encoding);
	static void decode(const v8::FunctionCallbackInfo<v8::Value>& args, const char* pBytes, std::size_t size, const std::string& encoding);

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);

	static const std::string ENCODING_UTF8;
	static const std::string ENCODING_UTF16;
	static const std::string ENCODING_ASCII;
	static const std::string ENCODING_BASE64;
	static const std::string ENCODING_BASE64URL;
	static const std::string ENCODING_HEXBIN;

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
	static void toBase64URL(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void fromBase64URL(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void toHexBinary(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void fromHexBinary(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void decodeString(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void encodeString(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void pack(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void unpack(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void concat(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void slice(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void push(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void pop(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void makeString(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeUInt8(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeInt8(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeUInt16LE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeInt16LE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeUInt16BE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeInt16BE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeUInt32LE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeInt32LE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeUInt32BE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeInt32BE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeUInt64LE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeInt64LE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeUInt64BE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeInt64BE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeFloatLE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeDoubleLE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeFloatBE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeDoubleBE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readUInt8(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readInt8(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readUInt16LE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readInt16LE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readUInt16BE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readInt16BE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readUInt32LE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readInt32LE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readUInt32BE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readInt32BE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readUInt64LE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readInt64LE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readUInt64BE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readInt64BE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readFloatLE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readDoubleLE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readFloatBE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readDoubleBE(const v8::FunctionCallbackInfo<v8::Value>& args);
	static std::size_t calculatePackBufferSize(const std::string& format);
};


} } } // namespace Poco::JS::Core


#endif // JS_Core_BufferWrapper_INCLUDED
