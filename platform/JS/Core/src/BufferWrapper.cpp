//
// BufferWrapper.cpp
//
// Library: JS/Core
// Package: Wrappers
// Module:  BufferWrapper
//
// Copyright (c) 2013-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Core/BufferWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/Buffer.h"
#include "Poco/Base64Encoder.h"
#include "Poco/Base64Decoder.h"
#include "Poco/ByteOrder.h"
#include "Poco/HexBinaryEncoder.h"
#include "Poco/HexBinaryDecoder.h"
#include "Poco/MemoryStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/TextEncoding.h"
#include "Poco/TextConverter.h"
#include "Poco/UTF8Encoding.h"
#include "Poco/UTF16Encoding.h"
#include "Poco/BinaryReader.h"
#include "Poco/BinaryWriter.h"
#include "Poco/Optional.h"
#include "Poco/Exception.h"
#include "Poco/String.h"
#include "Poco/Format.h"
#include <sstream>
#include <cstdlib>


using namespace std::string_literals;


namespace Poco {
namespace JS {
namespace Core {


const std::string BufferWrapper::ENCODING_UTF8("UTF-8");
const std::string BufferWrapper::ENCODING_UTF16("UTF-16");
const std::string BufferWrapper::ENCODING_ASCII("ASCII");
const std::string BufferWrapper::ENCODING_BASE64("BASE64");
const std::string BufferWrapper::ENCODING_BASE64URL("BASE64URL");
const std::string BufferWrapper::ENCODING_HEXBIN("HEXBIN");


template <typename T>
void writeBuffer(const v8::FunctionCallbackInfo<v8::Value>& args, T value, Poco::BinaryWriter::StreamByteOrder byteOrder = Poco::BinaryWriter::NATIVE_BYTE_ORDER)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	BufferWrapper::Buffer* pBuffer = Wrapper::unwrapNative<BufferWrapper::Buffer>(args);
	std::size_t offset = 0;
	if (args.Length() > 1)
	{
		offset = args[1]->Int32Value(context).FromMaybe(0);
	}
	if (offset >= 0 && offset + sizeof(T) <= pBuffer->capacity())
	{
		if (offset + sizeof(T) > pBuffer->size()) 
		{
			pBuffer->resize(offset + sizeof(T));
		}

		Poco::MemoryOutputStream memoryOutputStream(pBuffer->begin() + offset, sizeof(T));
		Poco::BinaryWriter binaryWriter(memoryOutputStream, byteOrder);
		binaryWriter << value;
		args.GetReturnValue().Set(static_cast<Poco::Int32>(offset + sizeof(T)));
	}
	else
	{
		Poco::JS::Core::Wrapper::returnException(args, Poco::format("Out of bounds write of length %z to offset %z of a buffer with capacity %z"s, sizeof(T), offset, pBuffer->capacity()));
	}
}


template <typename T>
Poco::Optional<T> readBuffer(const v8::FunctionCallbackInfo<v8::Value>& args, Poco::BinaryReader::StreamByteOrder byteOrder = Poco::BinaryReader::NATIVE_BYTE_ORDER)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	BufferWrapper::Buffer* pBuffer = Wrapper::unwrapNative<BufferWrapper::Buffer>(args);
	std::size_t offset = 0;
	if (args.Length() > 0)
	{
		offset = args[0]->Int32Value(context).FromMaybe(0);
	}
	if (offset >= 0 && offset + sizeof(T) <= pBuffer->size())
	{
		Poco::MemoryInputStream memoryInputStream(pBuffer->begin() + offset, sizeof(T));
		Poco::BinaryReader binaryReader(memoryInputStream, byteOrder);
		T value;
		binaryReader >> value;
		return value;
	}
	return {};
}


BufferWrapper::BufferWrapper()
{
}


BufferWrapper::~BufferWrapper()
{
}


v8::Handle<v8::FunctionTemplate> BufferWrapper::constructor(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::FunctionTemplate> funcTemplate = v8::FunctionTemplate::New(pIsolate, construct);
	funcTemplate->Set(toV8String(pIsolate, "isBuffer"s), v8::FunctionTemplate::New(pIsolate, isBuffer));
	funcTemplate->Set(toV8String(pIsolate, "UTF8"s), toV8String(pIsolate, ENCODING_UTF8));
	funcTemplate->Set(toV8String(pIsolate, "UTF16"s), toV8String(pIsolate, ENCODING_UTF16));
	funcTemplate->Set(toV8String(pIsolate, "ASCII"s), toV8String(pIsolate, ENCODING_ASCII));
	funcTemplate->Set(toV8String(pIsolate, "BASE64"s), toV8String(pIsolate, ENCODING_BASE64));
	funcTemplate->Set(toV8String(pIsolate, "BASE64URL"s), toV8String(pIsolate, ENCODING_BASE64URL));
	funcTemplate->Set(toV8String(pIsolate, "HEXBIN"s), toV8String(pIsolate, ENCODING_HEXBIN));
	return handleScope.Escape(funcTemplate);
}


v8::Handle<v8::ObjectTemplate> BufferWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	PooledIsolate* pPooledIso = PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("Core.Buffer"s));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "length"s), getLength, setLength);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "capacity"s), getCapacity, setCapacity);
		objectTemplate->SetIndexedPropertyHandler(getAt, setAt);

		objectTemplate->Set(toV8Internalized(pIsolate, "toBase64"s), v8::FunctionTemplate::New(pIsolate, toBase64));
		objectTemplate->Set(toV8Internalized(pIsolate, "fromBase64"s), v8::FunctionTemplate::New(pIsolate, fromBase64));
		objectTemplate->Set(toV8Internalized(pIsolate, "toBase64URL"s), v8::FunctionTemplate::New(pIsolate, toBase64URL));
		objectTemplate->Set(toV8Internalized(pIsolate, "fromBase64URL"s), v8::FunctionTemplate::New(pIsolate, fromBase64URL));
		objectTemplate->Set(toV8Internalized(pIsolate, "toHexBinary"s), v8::FunctionTemplate::New(pIsolate, toHexBinary));
		objectTemplate->Set(toV8Internalized(pIsolate, "fromHexBinary"s), v8::FunctionTemplate::New(pIsolate, fromHexBinary));
		objectTemplate->Set(toV8Internalized(pIsolate, "toString"s), v8::FunctionTemplate::New(pIsolate, makeString));
		objectTemplate->Set(toV8Internalized(pIsolate, "toJSON"s), v8::FunctionTemplate::New(pIsolate, toBase64));
		objectTemplate->Set(toV8Internalized(pIsolate, "decodeString"s), v8::FunctionTemplate::New(pIsolate, decodeString));
		objectTemplate->Set(toV8Internalized(pIsolate, "encodeString"s), v8::FunctionTemplate::New(pIsolate, encodeString));
		objectTemplate->Set(toV8Internalized(pIsolate, "pack"s), v8::FunctionTemplate::New(pIsolate, pack));
		objectTemplate->Set(toV8Internalized(pIsolate, "unpack"s), v8::FunctionTemplate::New(pIsolate, unpack));
		objectTemplate->Set(toV8Internalized(pIsolate, "concat"s), v8::FunctionTemplate::New(pIsolate, concat));
		objectTemplate->Set(toV8Internalized(pIsolate, "slice"s), v8::FunctionTemplate::New(pIsolate, slice));
		objectTemplate->Set(toV8Internalized(pIsolate, "push"s), v8::FunctionTemplate::New(pIsolate, push));
		objectTemplate->Set(toV8Internalized(pIsolate, "pop"s), v8::FunctionTemplate::New(pIsolate, pop));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeUInt8"s), v8::FunctionTemplate::New(pIsolate, writeUInt8));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeInt8"s), v8::FunctionTemplate::New(pIsolate, writeInt8));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeUInt16LE"s), v8::FunctionTemplate::New(pIsolate, writeUInt16LE));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeInt16LE"s), v8::FunctionTemplate::New(pIsolate, writeInt16LE));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeUInt16BE"s), v8::FunctionTemplate::New(pIsolate, writeUInt16BE));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeInt16BE"s), v8::FunctionTemplate::New(pIsolate, writeInt16BE));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeUInt32LE"s), v8::FunctionTemplate::New(pIsolate, writeUInt32LE));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeInt32LE"s), v8::FunctionTemplate::New(pIsolate, writeInt32LE));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeUInt32BE"s), v8::FunctionTemplate::New(pIsolate, writeUInt32BE));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeInt32BE"s), v8::FunctionTemplate::New(pIsolate, writeInt32BE));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeUInt64LE"s), v8::FunctionTemplate::New(pIsolate, writeUInt64LE));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeInt64LE"s), v8::FunctionTemplate::New(pIsolate, writeInt64LE));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeUInt64BE"s), v8::FunctionTemplate::New(pIsolate, writeUInt64BE));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeInt64BE"s), v8::FunctionTemplate::New(pIsolate, writeInt64BE));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeFloatLE"s), v8::FunctionTemplate::New(pIsolate, writeFloatLE));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeFloatBE"s), v8::FunctionTemplate::New(pIsolate, writeFloatBE));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeDoubleLE"s), v8::FunctionTemplate::New(pIsolate, writeDoubleLE));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeDoubleBE"s), v8::FunctionTemplate::New(pIsolate, writeDoubleBE));
		objectTemplate->Set(toV8Internalized(pIsolate, "readUInt8"s), v8::FunctionTemplate::New(pIsolate, readUInt8));
		objectTemplate->Set(toV8Internalized(pIsolate, "readInt8"s), v8::FunctionTemplate::New(pIsolate, readInt8));
		objectTemplate->Set(toV8Internalized(pIsolate, "readUInt16LE"s), v8::FunctionTemplate::New(pIsolate, readUInt16LE));
		objectTemplate->Set(toV8Internalized(pIsolate, "readInt16LE"s), v8::FunctionTemplate::New(pIsolate, readInt16LE));
		objectTemplate->Set(toV8Internalized(pIsolate, "readUInt16BE"s), v8::FunctionTemplate::New(pIsolate, readUInt16BE));
		objectTemplate->Set(toV8Internalized(pIsolate, "readInt16BE"s), v8::FunctionTemplate::New(pIsolate, readInt16BE));
		objectTemplate->Set(toV8Internalized(pIsolate, "readUInt32LE"s), v8::FunctionTemplate::New(pIsolate, readUInt32LE));
		objectTemplate->Set(toV8Internalized(pIsolate, "readInt32LE"s), v8::FunctionTemplate::New(pIsolate, readInt32LE));
		objectTemplate->Set(toV8Internalized(pIsolate, "readUInt32BE"s), v8::FunctionTemplate::New(pIsolate, readUInt32BE));
		objectTemplate->Set(toV8Internalized(pIsolate, "readInt32BE"s), v8::FunctionTemplate::New(pIsolate, readInt32BE));
		objectTemplate->Set(toV8Internalized(pIsolate, "readUInt64LE"s), v8::FunctionTemplate::New(pIsolate, readUInt64LE));
		objectTemplate->Set(toV8Internalized(pIsolate, "readInt64LE"s), v8::FunctionTemplate::New(pIsolate, readInt64LE));
		objectTemplate->Set(toV8Internalized(pIsolate, "readUInt64BE"s), v8::FunctionTemplate::New(pIsolate, readUInt64BE));
		objectTemplate->Set(toV8Internalized(pIsolate, "readInt64BE"s), v8::FunctionTemplate::New(pIsolate, readInt64BE));
		objectTemplate->Set(toV8Internalized(pIsolate, "readFloatLE"s), v8::FunctionTemplate::New(pIsolate, readFloatLE));
		objectTemplate->Set(toV8Internalized(pIsolate, "readFloatBE"s), v8::FunctionTemplate::New(pIsolate, readFloatBE));
		objectTemplate->Set(toV8Internalized(pIsolate, "readDoubleLE"s), v8::FunctionTemplate::New(pIsolate, readDoubleLE));
		objectTemplate->Set(toV8Internalized(pIsolate, "readDoubleBE"s), v8::FunctionTemplate::New(pIsolate, readDoubleBE));

		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> bufferTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(bufferTemplate);
}


void BufferWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	Buffer* pBuffer = 0;
	try
	{
		if (args.Length() == 0)
		{
			pBuffer = new Buffer(0);
		}
		else
		{
			if (args[0]->IsString())
			{
				std::string encoding;
				if (args.Length() > 1)
					encoding = toString(pIsolate, args[1]);
				else
					encoding = ENCODING_BASE64;

				pBuffer = new Buffer(0);
				encode(pIsolate, pBuffer, args[0], encoding);
			}
			else if (args[0]->IsArray())
			{
				v8::Local<v8::Array> array = v8::Local<v8::Array>::Cast(args[0]);
				std::size_t size = array->Length();
				pBuffer = new Buffer(size);
				for (std::size_t i = 0; i < size; i++)
				{
					v8::MaybeLocal<v8::Value> maybeValue = array->Get(context, i);
					v8::Local<v8::Value> value;
					if (maybeValue.ToLocal(&value))
					{
						if (value->IsNumber())
						{
							(*pBuffer)[i] = static_cast<char>(value->Uint32Value(context).FromMaybe(0));
						}
					}
				}
			}
			else if (args[0]->IsObject())
			{
				if (Wrapper::isWrapper<Buffer>(pIsolate, args[0]))
				{
					Buffer* pArgBuffer = Wrapper::unwrapNativeObject<Buffer>(args[0]);

					Poco::Int32 begin = 0;
					Poco::Int32 end = static_cast<Poco::Int32>(pArgBuffer->size());

					if (args.Length() > 0)
					{
						if (args[1]->IsNumber())
						{
							Poco::Int32 index = args[1]->Int32Value(context).FromMaybe(0);
							if (index >= 0)
								begin = index;
							else
								begin = end + index;
							if (begin < 0 || begin > end) throw Poco::RangeException("Start index out of range");
						}
						else throw Poco::InvalidArgumentException("Start index of slice() must be an integer");
					}
					if (args.Length() > 1)
					{
						if (args[2]->IsNumber())
						{
							Poco::Int32 index = args[2]->Int32Value(context).FromMaybe(0);
							if (index < 0)
								index = end + index;
							if (index < 0 || index > end) throw Poco::RangeException("End index out of range");
							end = index;
							if (begin > end)
							{
								std::swap(begin, end);
							}
						}
						else throw Poco::InvalidArgumentException("End index of slice() must be an integer");
					}
					pBuffer = new Buffer(pArgBuffer->begin() + begin, end - begin);
				}
				else throw Poco::InvalidArgumentException("Object is not a Buffer");
			}
			else if (args[0]->IsNumber())
			{
				Poco::UInt32 size = args[0]->Uint32Value(context).FromMaybe(0);
				pBuffer = new Buffer(size);
				pBuffer->resize(0);
			}
		}
		
		if (!pBuffer) 
		{
			// fallback in case of undefined values as arguments
			pBuffer = new Buffer(0);
		}

		BufferWrapper wrapper;
		v8::Persistent<v8::Object>& bufferObject(wrapper.wrapNativePersistent(pIsolate, pBuffer));
		args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, bufferObject));
	}
	catch (Poco::Exception& exc)
	{
		delete pBuffer;
		returnException(args, exc);
	}
	catch (std::exception&)
	{
		returnException(args, "Out of memory"s);
	}
}


void BufferWrapper::isBuffer(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() > 0)
	{
		args.GetReturnValue().Set(Wrapper::isWrapper<Buffer>(args.GetIsolate(), args[0]));
	}
	else
	{
		args.GetReturnValue().Set(false);
	}
}


void BufferWrapper::getLength(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(info);
	info.GetReturnValue().Set(static_cast<Poco::UInt32>(pBuffer->size()));
}


void BufferWrapper::setLength(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(info);
	Poco::UInt32 size = value->Uint32Value(context).FromMaybe(0);
	try
	{
		pBuffer->resize(size);
	}
	catch (Poco::Exception& exc)
	{
		returnException(info, exc);
	}
	catch (std::exception&)
	{
		returnException(info, "Out of memory"s);
	}
}


void BufferWrapper::getCapacity(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(info);
	info.GetReturnValue().Set(static_cast<Poco::UInt32>(pBuffer->capacity()));
}


void BufferWrapper::setCapacity(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(info);
	Poco::UInt32 size = value->Uint32Value(context).FromMaybe(0);
	try
	{
		pBuffer->setCapacity(size);
	}
	catch (Poco::Exception& exc)
	{
		returnException(info, exc);
	}
	catch (std::exception&)
	{
		returnException(info, "Out of memory"s);
	}
}


void BufferWrapper::getAt(uint32_t index, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(info);
	std::size_t size = pBuffer->size();
	if (index < size)
	{
		info.GetReturnValue().Set(static_cast<Poco::UInt32>(static_cast<unsigned char>((*pBuffer)[index])));
	}
}


void BufferWrapper::setAt(uint32_t index, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(info);
	std::size_t size = pBuffer->size();
	if (index < size)
	{
		(*pBuffer)[index] = static_cast<char>(value->Uint32Value(context).FromMaybe(0));
		info.GetReturnValue().Set(value);
	}
	else
	{
		returnException(info, Poco::RangeException(Poco::format("buffer size=%z, index=%u"s, size, static_cast<unsigned>(index))));
	}
}


void BufferWrapper::toBase64(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		int lineLength = 0;
		if (args.Length() > 0)
		{
			lineLength = args[0]->Int32Value(context).FromMaybe(0);
		}
		Poco::MemoryInputStream istr(pBuffer->begin(), pBuffer->size());
		std::stringstream ostr;
		Poco::Base64Encoder encoder(ostr);
		encoder.rdbuf()->setLineLength(lineLength);
		Poco::StreamCopier::copyStream(istr, encoder);
		encoder.close();
		returnString(args, ostr.str());
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void BufferWrapper::toBase64URL(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		Poco::MemoryInputStream istr(pBuffer->begin(), pBuffer->size());
		std::stringstream ostr;
		Poco::Base64Encoder encoder(ostr, Poco::BASE64_URL_ENCODING | Poco::BASE64_NO_PADDING);
		Poco::StreamCopier::copyStream(istr, encoder);
		encoder.close();
		returnString(args, ostr.str());
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void BufferWrapper::fromBase64(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		if (args.Length() > 0)
		{
			std::string base64String = toString(pIsolate, args[0]);
			int size = static_cast<int>(base64String.size());
			int decodedSize = 3*size/4 + 16;
			pBuffer->resize(decodedSize, false);
			Poco::MemoryInputStream istr(base64String.data(), static_cast<std::streamsize>(size));
			Poco::MemoryOutputStream ostr(pBuffer->begin(), pBuffer->size());
			Poco::Base64Decoder decoder(istr);
			Poco::StreamCopier::copyStream(decoder, ostr);
			pBuffer->resize(static_cast<std::size_t>(ostr.charsWritten()));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
	catch (std::exception&)
	{
		returnException(args, "Out of memory"s);
	}
}


void BufferWrapper::fromBase64URL(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		if (args.Length() > 0)
		{
			std::string base64String = toString(pIsolate, args[0]);
			int size = static_cast<int>(base64String.size());
			int decodedSize = 3*size/4 + 16;
			pBuffer->resize(decodedSize, false);
			Poco::MemoryInputStream istr(base64String.data(), static_cast<std::streamsize>(size));
			Poco::MemoryOutputStream ostr(pBuffer->begin(), pBuffer->size());
			Poco::Base64Decoder decoder(istr, Poco::BASE64_URL_ENCODING | BASE64_NO_PADDING);
			Poco::StreamCopier::copyStream(decoder, ostr);
			pBuffer->resize(static_cast<std::size_t>(ostr.charsWritten()));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
	catch (std::exception&)
	{
		returnException(args, "Out of memory"s);
	}
}


void BufferWrapper::toHexBinary(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		int lineLength = 0;
		if (args.Length() > 0)
		{
			lineLength = args[0]->Int32Value(context).FromMaybe(0);
		}
		Poco::MemoryInputStream istr(pBuffer->begin(), pBuffer->size());
		std::stringstream ostr;
		Poco::HexBinaryEncoder encoder(ostr);
		encoder.rdbuf()->setLineLength(lineLength);
		Poco::StreamCopier::copyStream(istr, encoder);
		encoder.close();
		returnString(args, ostr.str());
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void BufferWrapper::fromHexBinary(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		if (args.Length() > 0)
		{
			std::string hexBinString = toString(pIsolate, args[0]);
			int size = static_cast<int>(hexBinString.size());
			int decodedSize = size/2;
			pBuffer->resize(decodedSize, false);
			Poco::MemoryInputStream istr(hexBinString.data(), static_cast<std::streamsize>(size));
			Poco::MemoryOutputStream ostr(pBuffer->begin(), pBuffer->size());
			Poco::HexBinaryDecoder decoder(istr);
			Poco::StreamCopier::copyStream(decoder, ostr);
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
	catch (std::exception&)
	{
		returnException(args, "Out of memory"s);
	}
}


void BufferWrapper::decodeString(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	try
	{
		std::string encoding;
		if (args.Length() > 0)
			encoding = toString(pIsolate, args[0]);
		else
			encoding = ENCODING_UTF8;

		decode(args, encoding);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
	catch (std::exception&)
	{
		returnException(args, "Out of memory"s);
	}
}


void BufferWrapper::encodeString(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() == 0) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);

	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		std::string encoding;
		if (args.Length() > 1)
			encoding = toString(pIsolate, args[1]);
		else
			encoding = ENCODING_UTF8;

		encode(pIsolate, pBuffer, args[0], encoding);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
	catch (std::exception&)
	{
		returnException(args, "Out of memory"s);
	}
}


void BufferWrapper::pack(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		if (!args[1]->IsArray()) throw Poco::InvalidArgumentException("Second argument to pack() must be array");

		v8::Local<v8::Array> array = v8::Local<v8::Array>::Cast(args[1]);
		std::string format(toString(pIsolate, args[0]));
		std::size_t size = calculatePackBufferSize(format);
		pBuffer->resize(size, false);
		Poco::BinaryWriter::StreamByteOrder byteOrder = Poco::BinaryWriter::NATIVE_BYTE_ORDER;
		std::string::const_iterator it = format.begin();
		std::string::const_iterator end = format.end();
		if (it != end)
		{
			switch (*it)
			{
			case '=':
				byteOrder = Poco::BinaryWriter::NATIVE_BYTE_ORDER;
				++it;
				break;
			case '>':
				byteOrder = Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER;
				++it;
				break;
			case '<':
				byteOrder = Poco::BinaryWriter::LITTLE_ENDIAN_BYTE_ORDER;
				++it;
				break;
			case '!':
				byteOrder = Poco::BinaryWriter::NETWORK_BYTE_ORDER;
				++it;
				break;
			default:
				break;
			}
		}

		Poco::BasicMemoryBinaryWriter<char> writer(*pBuffer, byteOrder);
		Poco::UInt32 index = 0;
		int repeat = -1;

		while (it != end)
		{
			switch (*it)
			{
			case ' ':
			case '\t':
			case '\r':
			case '\n':
				if (repeat != -1) throw Poco::SyntaxException("Repeat count must be followed by format character");
				break;
			case 'x':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					writer << static_cast<Poco::UInt8>(0);
				}
				repeat = -1;
				break;
			case 'c':
			case 's':
				{
					std::string utf8;
					std::size_t size = std::abs(repeat);
					v8::Maybe<bool> hasIndex = array->Has(context, index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						utf8 = toString(pIsolate, array->Get(context, index));
					}
					utf8.resize(size);
					writer.writeRaw(utf8);
					index++;
					repeat = -1;
				}
				break;
			case 'b':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::Int8 v = 0;
					v8::Maybe<bool> hasIndex = array->Has(context, index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v8::MaybeLocal<v8::Value> maybeValue = array->Get(context, index);
						v8::Local<v8::Value> value;
						if (maybeValue.ToLocal(&value))
						{
							v = static_cast<Poco::Int8>(value->Int32Value(context).FromMaybe(0));
						}
					}
					writer << v;
					index++;
				}
				repeat = -1;
				break;
			case 'B':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::UInt8 v = 0;
					v8::Maybe<bool> hasIndex = array->Has(context, index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v8::MaybeLocal<v8::Value> maybeValue = array->Get(context, index);
						v8::Local<v8::Value> value;
						if (maybeValue.ToLocal(&value))
						{
							v = static_cast<Poco::UInt8>(value->Uint32Value(context).FromMaybe(0));
						}
					}
					writer << v;
					index++;
				}
				repeat = -1;
				break;
			case '?':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					bool v = false;
					v8::Maybe<bool> hasIndex = array->Has(context, index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v8::MaybeLocal<v8::Value> maybeValue = array->Get(context, index);
						v8::Local<v8::Value> value;
						if (maybeValue.ToLocal(&value))
						{
							v = value->BooleanValue(pIsolate);
						}
					}
					writer << v;
					index++;
				}
				repeat = -1;
				break;
			case 'h':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::Int16 v = 0;
					v8::Maybe<bool> hasIndex = array->Has(context, index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v8::MaybeLocal<v8::Value> maybeValue = array->Get(context, index);
						v8::Local<v8::Value> value;
						if (maybeValue.ToLocal(&value))
						{
							v = static_cast<Poco::Int16>(value->Int32Value(context).FromMaybe(0));
						}
					}
					writer << v;
					index++;
				}
				repeat = -1;
				break;
			case 'H':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::UInt16 v = 0;
					v8::Maybe<bool> hasIndex = array->Has(context, index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v8::MaybeLocal<v8::Value> maybeValue = array->Get(context, index);
						v8::Local<v8::Value> value;
						if (maybeValue.ToLocal(&value))
						{
							v = static_cast<Poco::UInt16>(value->Uint32Value(context).FromMaybe(0));
						}
					}
					writer << v;
					index++;
				}
				repeat = -1;
				break;
			case 'i':
			case 'l':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::Int32 v = 0;
					v8::Maybe<bool> hasIndex = array->Has(context, index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v8::MaybeLocal<v8::Value> maybeValue = array->Get(context, index);
						v8::Local<v8::Value> value;
						if (maybeValue.ToLocal(&value))
						{
							v = value->Int32Value(context).FromMaybe(0);
						}
					}
					writer << v;
					index++;
				}
				repeat = -1;
				break;
			case 'I':
			case 'L':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::UInt32 v = 0;
					v8::Maybe<bool> hasIndex = array->Has(context, index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v8::MaybeLocal<v8::Value> maybeValue = array->Get(context, index);
						v8::Local<v8::Value> value;
						if (maybeValue.ToLocal(&value))
						{
							v = value->Uint32Value(context).FromMaybe(0);
						}
					}
					writer << v;
					index++;
				}
				repeat = -1;
				break;
			case 'q':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::Int64 v = 0;
					v8::Maybe<bool> hasIndex = array->Has(context, index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v8::MaybeLocal<v8::Value> maybeValue = array->Get(context, index);
						v8::Local<v8::Value> value;
						if (maybeValue.ToLocal(&value))
						{
							v = static_cast<Poco::Int64>(value->IntegerValue(context).FromMaybe(0));
						}
					}
					writer << v;
					index++;
				}
				repeat = -1;
				break;
			case 'Q':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::UInt64 v = 0;
					v8::Maybe<bool> hasIndex = array->Has(context, index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v8::MaybeLocal<v8::Value> maybeValue = array->Get(context, index);
						v8::Local<v8::Value> value;
						if (maybeValue.ToLocal(&value))
						{
							v = static_cast<Poco::UInt64>(value->IntegerValue(context).FromMaybe(0));
						}
					}
					writer << v;
					index++;
				}
				repeat = -1;
				break;
			case 'f':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					float v = 0.0f;
					v8::Maybe<bool> hasIndex = array->Has(context, index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v8::MaybeLocal<v8::Value> maybeValue = array->Get(context, index);
						v8::Local<v8::Value> value;
						if (maybeValue.ToLocal(&value))
						{
							v = static_cast<float>(value->NumberValue(context).FromMaybe(0.0));
						}
					}
					writer << v;
					index++;
				}
				repeat = -1;
				break;
			case 'd':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					double v = 0.0;
					v8::Maybe<bool> hasIndex = array->Has(context, index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v8::MaybeLocal<v8::Value> maybeValue = array->Get(context, index);
						v8::Local<v8::Value> value;
						if (maybeValue.ToLocal(&value))
						{
							v = value->NumberValue(context).FromMaybe(0.0);
						}
					}
					writer << v;
					index++;
				}
				repeat = -1;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (repeat == -1)
					repeat = *it - '0';
				else
					repeat = 10*repeat + (*it - '0');
				break;
			default:
				throw Poco::InvalidArgumentException("Invalid character in format string", format);
			}
			++it;
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
	catch (std::exception&)
	{
		returnException(args, "Out of memory"s);
	}
}


void BufferWrapper::unpack(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		v8::Local<v8::Array> array = v8::Array::New(pIsolate);
		std::string format(toString(pIsolate, args[0]));
		Poco::BinaryReader::StreamByteOrder byteOrder = Poco::BinaryReader::NATIVE_BYTE_ORDER;
		std::string::const_iterator it = format.begin();
		std::string::const_iterator end = format.end();
		if (it != end)
		{
			switch (*it)
			{
			case '=':
				byteOrder = Poco::BinaryReader::NATIVE_BYTE_ORDER;
				++it;
				break;
			case '>':
				byteOrder = Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER;
				++it;
				break;
			case '<':
				byteOrder = Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER;
				++it;
				break;
			case '!':
				byteOrder = Poco::BinaryReader::NETWORK_BYTE_ORDER;
				++it;
				break;
			default:
				break;
			}
		}

		Poco::BasicMemoryBinaryReader<char> reader(*pBuffer, byteOrder);
		Poco::UInt32 index = 0;
		int repeat = -1;

		while (it != end)
		{
			switch (*it)
			{
			case ' ':
			case '\t':
			case '\r':
			case '\n':
				if (repeat != -1) throw Poco::SyntaxException("Repeat count must be followed by format character");
				break;
			case 'x':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					char c;
					reader >> c;
				}
				repeat = -1;
				break;
			case 'c':
			case 's':
				{
					std::string utf8;
					std::size_t size = std::abs(repeat);
					reader.readRaw(size, utf8);
					V8_CHECK_SET_RESULT(array->Set(context, index, toV8String(pIsolate, utf8)));
					index++;
					repeat = -1;
				}
				break;
			case 'b':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::Int8 v = 0;
					reader >> v;
					V8_CHECK_SET_RESULT(array->Set(context, index, v8::Integer::New(pIsolate, static_cast<Poco::Int32>(v))));
					index++;
				}
				repeat = -1;
				break;
			case 'B':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::UInt8 v = 0;
					reader >> v;
					V8_CHECK_SET_RESULT(array->Set(context, index, v8::Integer::NewFromUnsigned(pIsolate, static_cast<Poco::UInt32>(v))));
					index++;
				}
				repeat = -1;
				break;
			case '?':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					bool v = false;
					reader >> v;
					V8_CHECK_SET_RESULT(array->Set(context, index, v8::Boolean::New(pIsolate, v)));
					index++;
				}
				repeat = -1;
				break;
			case 'h':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::Int16 v = 0;
					reader >> v;
					V8_CHECK_SET_RESULT(array->Set(context, index, v8::Integer::New(pIsolate, static_cast<Poco::Int32>(v))));
					index++;
				}
				repeat = -1;
				break;
			case 'H':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::UInt16 v = 0;
					reader >> v;
					V8_CHECK_SET_RESULT(array->Set(context, index, v8::Integer::NewFromUnsigned(pIsolate, static_cast<Poco::UInt32>(v))));
					index++;
				}
				repeat = -1;
				break;
			case 'i':
			case 'l':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::Int32 v = 0;
					reader >> v;
					V8_CHECK_SET_RESULT(array->Set(context, index, v8::Integer::New(pIsolate, v)));
					index++;
				}
				repeat = -1;
				break;
			case 'I':
			case 'L':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::UInt32 v = 0;
					reader >> v;
					V8_CHECK_SET_RESULT(array->Set(context, index, v8::Integer::NewFromUnsigned(pIsolate, v)));
					index++;
				}
				repeat = -1;
				break;
			case 'q':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::Int64 v = 0;
					reader >> v;
					V8_CHECK_SET_RESULT(array->Set(context, index, v8::Number::New(pIsolate, static_cast<double>(v))));
					index++;
				}
				repeat = -1;
				break;
			case 'Q':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::UInt64 v = 0;
					reader >> v;
					V8_CHECK_SET_RESULT(array->Set(context, index, v8::Number::New(pIsolate, static_cast<double>(v))));
					index++;
				}
				repeat = -1;
				break;
			case 'f':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					float v = 0.0f;
					reader >> v;
					V8_CHECK_SET_RESULT(array->Set(context, index, v8::Number::New(pIsolate, v)));
					index++;
				}
				repeat = -1;
				break;
			case 'd':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					double v = 0.0;
					reader >> v;
					V8_CHECK_SET_RESULT(array->Set(context, index, v8::Number::New(pIsolate, v)));
					index++;
				}
				repeat = -1;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (repeat == -1)
					repeat = *it - '0';
				else
					repeat = 10*repeat + (*it - '0');
				break;
			default:
				throw Poco::InvalidArgumentException("Invalid character in format string", format);
			}
			++it;
		}
		args.GetReturnValue().Set(array);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
	catch (std::exception&)
	{
		returnException(args, "Out of memory"s);
	}
}


void BufferWrapper::concat(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);

	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		for (int i = 0; i < args.Length(); i++)
		{
			if (Wrapper::isWrapper<Buffer>(pIsolate, args[i]))
			{
				Buffer* pArgBuffer = Wrapper::unwrapNativeObject<Buffer>(args[i]);
				pBuffer->append(pArgBuffer->begin(), pArgBuffer->size());
			}
			else throw Poco::InvalidArgumentException("Attempt to concat something that's not a Buffer");
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
	catch (std::exception&)
	{
		returnException(args, "Out of memory"s);
	}
}


void BufferWrapper::slice(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		Poco::Int32 begin = 0;
		Poco::Int32 end = static_cast<Poco::UInt32>(pBuffer->size());
		if (args.Length() > 0)
		{
			if (args[0]->IsNumber())
			{
				Poco::Int32 index = args[0]->Int32Value(context).FromMaybe(0);
				if (index >= 0)
					begin = index;
				else
					begin = end + index;
				if (begin < 0 || begin > end) throw Poco::RangeException("Start index out of range");
			}
			else throw Poco::InvalidArgumentException("Start index of slice() must be an integer");
		}
		if (args.Length() > 1)
		{
			if (args[1]->IsNumber())
			{
				Poco::Int32 index = args[1]->Int32Value(context).FromMaybe(0);
				if (index < 0)
					index = end + index;
				if (index < 0 || index > end) throw Poco::RangeException("End index out of range");
				end = index;
				if (begin > end)
				{
					std::swap(begin, end);
				}
			}
			else throw Poco::InvalidArgumentException("End index of slice() must be an integer");
		}

		Buffer* pNewBuffer = new Buffer(pBuffer->begin() + begin, end - begin);

		BufferWrapper wrapper;
		v8::Persistent<v8::Object>& bufferObject(wrapper.wrapNativePersistent(pIsolate, pNewBuffer));
		args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, bufferObject));
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
	catch (std::exception&)
	{
		returnException(args, "Out of memory"s);
	}
}


void BufferWrapper::push(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		if (args.Length() > 0)
		{
			if (args[0]->IsNumber())
			{
				pBuffer->append(static_cast<char>(args[0]->Uint32Value(context).FromMaybe(0)));
			}
			else throw Poco::InvalidArgumentException("Push to a Buffer requires a byte value");
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
	catch (std::exception&)
	{
		returnException(args, "Out of memory"s);
	}
}


void BufferWrapper::pop(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	if (pBuffer->size() > 0)
	{
		char value = (*pBuffer)[pBuffer->size() - 1];
		pBuffer->resize(pBuffer->size() - 1);
		args.GetReturnValue().Set(static_cast<Poco::UInt32>(static_cast<unsigned char>(value)));
	}
}


void BufferWrapper::makeString(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());

	try
	{
		std::string encoding;
		if (args.Length() > 0)
			encoding = toString(pIsolate, args[0]);
		else
			encoding = ENCODING_BASE64;

		decode(args, encoding);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
	catch (std::exception&)
	{
		returnException(args, "Out of memory"s);
	}
}


void BufferWrapper::encode(v8::Isolate* pIsolate, Buffer* pBuffer, const v8::Local<v8::Value>& str, const std::string& encoding)
{
	if (Poco::icompare(encoding, ENCODING_UTF8) == 0)
	{
		v8::String::Utf8Value utf8(pIsolate, str);
		if (utf8.length() > 0)
			pBuffer->assign(*utf8, utf8.length());
		else
			pBuffer->resize(0);
	}
	else if (Poco::icompare(encoding, ENCODING_UTF16) == 0)
	{
		v8::String::Value utf16(pIsolate, str);
		if (utf16.length() > 0)
			pBuffer->assign(reinterpret_cast<const char*>(*utf16), 2*utf16.length());
		else
			pBuffer->resize(0);
	}
	else if (Poco::icompare(encoding, ENCODING_BASE64) == 0 || Poco::icompare(encoding, ENCODING_BASE64URL) == 0)
	{
		int options = 0;
		if (encoding.length() == ENCODING_BASE64URL.length()) options = Poco::BASE64_URL_ENCODING | Poco::BASE64_NO_PADDING;
		std::string base64String = toString(pIsolate, str);
		int size = static_cast<int>(base64String.size());
		int decodedSize = 3*size/4 + 16;
		pBuffer->resize(decodedSize, false);
		Poco::MemoryInputStream istr(base64String.data(), static_cast<std::streamsize>(size));
		Poco::MemoryOutputStream ostr(pBuffer->begin(), pBuffer->size());
		Poco::Base64Decoder decoder(istr, options);
		Poco::StreamCopier::copyStream(decoder, ostr);
		pBuffer->resize(static_cast<std::size_t>(ostr.charsWritten()));
	}
	else if (Poco::icompare(encoding, ENCODING_HEXBIN) == 0)
	{
		std::string hexBinString = toString(pIsolate, str);
		int size = static_cast<int>(hexBinString.size());
		int decodedSize = size/2;
		pBuffer->resize(decodedSize, false);
		Poco::MemoryInputStream istr(hexBinString.data(), static_cast<std::streamsize>(size));
		Poco::MemoryOutputStream ostr(pBuffer->begin(), pBuffer->size());
		Poco::HexBinaryDecoder decoder(istr);
		Poco::StreamCopier::copyStream(decoder, ostr);
	}
	else
	{
		v8::String::Value utf16(pIsolate, str);
		if (utf16.length() > 0)
		{
			Poco::UTF16Encoding utf16Encoding;
			Poco::TextEncoding& targetEncoding = Poco::TextEncoding::byName(encoding);
			Poco::TextConverter converter(utf16Encoding, targetEncoding);
			std::string result;
			converter.convert(*utf16, 2*utf16.length(), result);
			pBuffer->assign(result.data(), result.size());
		}
		else
		{
			pBuffer->resize(0);
		}
	}
}


void BufferWrapper::decode(const v8::FunctionCallbackInfo<v8::Value>& args, const std::string& encoding)
{
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	decode(args, pBuffer->begin(), pBuffer->size(), encoding);
}


void BufferWrapper::decode(const v8::FunctionCallbackInfo<v8::Value>& args, const char* pBytes, std::size_t size, const std::string& encoding)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	if (Poco::icompare(encoding, ENCODING_UTF8) == 0)
	{
		v8::MaybeLocal<v8::String> maybeString = v8::String::NewFromUtf8(
			pIsolate,
			pBytes,
			v8::NewStringType::kNormal,
			static_cast<int>(size));
		v8::Local<v8::String> string;
		if (maybeString.ToLocal(&string))
		{
			args.GetReturnValue().Set(string);
		}
	}
	else if (Poco::icompare(encoding, ENCODING_UTF16) == 0)
	{
		v8::MaybeLocal<v8::String> maybeString = v8::String::NewFromTwoByte(
			pIsolate,
			reinterpret_cast<const Poco::UInt16*>(pBytes),
			v8::NewStringType::kNormal,
			static_cast<int>(size/2));
		v8::Local<v8::String> string;
		if (maybeString.ToLocal(&string))
		{
			args.GetReturnValue().Set(string);
		}
	}
	else if (Poco::icompare(encoding, ENCODING_BASE64) == 0 || Poco::icompare(encoding, ENCODING_BASE64URL) == 0)
	{
		int options = 0;
		if (encoding.length() == ENCODING_BASE64URL.length()) options = Poco::BASE64_URL_ENCODING | Poco::BASE64_NO_PADDING;
		Poco::MemoryInputStream istr(pBytes, size);
		std::stringstream ostr;
		Poco::Base64Encoder encoder(ostr, options);
		encoder.rdbuf()->setLineLength(0);
		Poco::StreamCopier::copyStream(istr, encoder);
		encoder.close();
		returnString(args, ostr.str());
	}
	else if (Poco::icompare(encoding, ENCODING_HEXBIN) == 0)
	{
		Poco::MemoryInputStream istr(pBytes, size);
		std::stringstream ostr;
		Poco::HexBinaryEncoder encoder(ostr);
		encoder.rdbuf()->setLineLength(0);
		Poco::StreamCopier::copyStream(istr, encoder);
		encoder.close();
		returnString(args, ostr.str());
	}
	else
	{
		Poco::UTF16Encoding utf8Encoding;
		Poco::TextEncoding& sourceEncoding = Poco::TextEncoding::byName(encoding);
		Poco::TextConverter converter(sourceEncoding, utf8Encoding);
		std::string result;
		converter.convert(pBytes, size, result);
		returnString(args, result);
	}
}


void BufferWrapper::writeUInt8(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0)
	{
		Poco::UInt8 value = static_cast<Poco::UInt8>(args[0]->Uint32Value(context).FromMaybe(0));
		writeBuffer(args, value);
	}
}


void BufferWrapper::writeInt8(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0)
	{
		Poco::Int8 value = static_cast<Poco::Int8>(args[0]->Int32Value(context).FromMaybe(0));
		writeBuffer(args, value);
	}
}


void BufferWrapper::writeUInt16LE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0)
	{
		Poco::UInt16 value = static_cast<Poco::UInt16>(args[0]->Uint32Value(context).FromMaybe(0));
		writeBuffer(args, value, Poco::BinaryWriter::LITTLE_ENDIAN_BYTE_ORDER);
	}
}


void BufferWrapper::writeInt16LE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0)
	{
		Poco::Int16 value = static_cast<Poco::Int16>(args[0]->Int32Value(context).FromMaybe(0));
		writeBuffer(args, value, Poco::BinaryWriter::LITTLE_ENDIAN_BYTE_ORDER);
	}
}


void BufferWrapper::writeUInt16BE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0)
	{
		Poco::UInt16 value = static_cast<Poco::UInt16>(args[0]->Uint32Value(context).FromMaybe(0));
		writeBuffer(args, value, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);
	}
}


void BufferWrapper::writeInt16BE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0)
	{
		Poco::Int16 value = static_cast<Poco::Int16>(args[0]->Int32Value(context).FromMaybe(0));
		writeBuffer(args, value, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);
	}
}


void BufferWrapper::writeUInt32LE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0)
	{
		Poco::UInt32 value = args[0]->Uint32Value(context).FromMaybe(0);
		writeBuffer(args, value, Poco::BinaryWriter::LITTLE_ENDIAN_BYTE_ORDER);
	}
}


void BufferWrapper::writeInt32LE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0)
	{
		Poco::Int32 value = args[0]->Int32Value(context).FromMaybe(0);
		writeBuffer(args, value, Poco::BinaryWriter::LITTLE_ENDIAN_BYTE_ORDER);
	}
}


void BufferWrapper::writeUInt32BE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0)
	{
		Poco::UInt32 value = args[0]->Uint32Value(context).FromMaybe(0);
		writeBuffer(args, value, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);
	}
}


void BufferWrapper::writeInt32BE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0)
	{
		Poco::Int32 value = args[0]->Int32Value(context).FromMaybe(0);
		writeBuffer(args, value, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);
	}
}


void BufferWrapper::writeUInt64LE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0)
	{
		Poco::UInt64 value = 0;
		if (args[0]->IsBigInt())
		{
			v8::Local<v8::BigInt> bigInt = args[0].As<v8::BigInt>();
			value = bigInt->Uint64Value();
		}
		else
		{
			value = static_cast<Poco::UInt64>(args[0]->NumberValue(context).FromMaybe(0));
		}
		writeBuffer(args, value, Poco::BinaryWriter::LITTLE_ENDIAN_BYTE_ORDER);
	}
}


void BufferWrapper::writeInt64LE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0)
	{
		Poco::Int64 value = 0;
		if (args[0]->IsBigInt())
		{
			v8::Local<v8::BigInt> bigInt = args[0].As<v8::BigInt>();
			value = bigInt->Int64Value();
		}
		else
		{
			value = static_cast<Poco::Int64>(args[0]->NumberValue(context).FromMaybe(0));
		}
		writeBuffer(args, value, Poco::BinaryWriter::LITTLE_ENDIAN_BYTE_ORDER);
	}
}


void BufferWrapper::writeUInt64BE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0)
	{
		Poco::UInt64 value = 0;
		if (args[0]->IsBigInt())
		{
			v8::Local<v8::BigInt> bigInt = args[0].As<v8::BigInt>();
			value = bigInt->Uint64Value();
		}
		else
		{
			value = static_cast<Poco::UInt64>(args[0]->NumberValue(context).FromMaybe(0));
		}
		writeBuffer(args, value, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);
	}
}


void BufferWrapper::writeInt64BE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0)
	{
		Poco::Int64 value = 0;
		if (args[0]->IsBigInt())
		{
			v8::Local<v8::BigInt> bigInt = args[0].As<v8::BigInt>();
			value = bigInt->Int64Value();
		}
		else
		{
			value = static_cast<Poco::Int64>(args[0]->NumberValue(context).FromMaybe(0));
		}
		writeBuffer(args, value, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);
	}
}


void BufferWrapper::writeFloatLE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0)
	{
		float value = static_cast<float>(args[0]->NumberValue(context).FromMaybe(0));
		writeBuffer(args, value, Poco::BinaryWriter::LITTLE_ENDIAN_BYTE_ORDER);
	}
}


void BufferWrapper::writeDoubleLE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0)
	{
		double value = args[0]->NumberValue(context).FromMaybe(0);
		writeBuffer(args, value, Poco::BinaryWriter::LITTLE_ENDIAN_BYTE_ORDER);
	}
}


void BufferWrapper::writeFloatBE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0)
	{
		float value = static_cast<float>(args[0]->NumberValue(context).FromMaybe(0));
		writeBuffer(args, value, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);
	}
}


void BufferWrapper::writeDoubleBE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0)
	{
		double value = args[0]->NumberValue(context).FromMaybe(0);
		writeBuffer(args, value, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);
	}
}


void BufferWrapper::readUInt8(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto value = readBuffer<Poco::UInt8>(args);
	if (value.isSpecified())
	{
		args.GetReturnValue().Set(static_cast<Poco::UInt32>(value.value()));
	}
}


void BufferWrapper::readInt8(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto value = readBuffer<Poco::Int8>(args);
	if (value.isSpecified())
	{
		args.GetReturnValue().Set(static_cast<Poco::Int32>(value.value()));
	}
}


void BufferWrapper::readUInt16LE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto value = readBuffer<Poco::UInt16>(args, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	if (value.isSpecified())
	{
		args.GetReturnValue().Set(static_cast<Poco::UInt32>(value.value()));
	}
}


void BufferWrapper::readInt16LE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto value = readBuffer<Poco::Int16>(args, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	if (value.isSpecified())
	{
		args.GetReturnValue().Set(static_cast<Poco::Int32>(value.value()));
	}
}


void BufferWrapper::readUInt16BE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto value = readBuffer<Poco::UInt16>(args, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);
	if (value.isSpecified())
	{
		args.GetReturnValue().Set(static_cast<Poco::UInt32>(value.value()));
	}
}


void BufferWrapper::readInt16BE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto value = readBuffer<Poco::Int16>(args, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);
	if (value.isSpecified())
	{
		args.GetReturnValue().Set(static_cast<Poco::Int32>(value.value()));
	}

}


void BufferWrapper::readUInt32LE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto value = readBuffer<Poco::UInt32>(args, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	if (value.isSpecified())
	{
		args.GetReturnValue().Set(value.value());
	}
}


void BufferWrapper::readInt32LE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto value = readBuffer<Poco::Int32>(args, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	if (value.isSpecified())
	{
		args.GetReturnValue().Set(value.value());
	}
}


void BufferWrapper::readUInt32BE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto value = readBuffer<Poco::UInt32>(args, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);
	if (value.isSpecified())
	{
		args.GetReturnValue().Set(value.value());
	}
}


void BufferWrapper::readInt32BE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto value = readBuffer<Poco::Int32>(args, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);
	if (value.isSpecified())
	{
		args.GetReturnValue().Set(value.value());
	}
}


void BufferWrapper::readUInt64LE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	auto value = readBuffer<Poco::UInt64>(args, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	if (value.isSpecified())
	{
		v8::Local<v8::BigInt> bigInt = v8::BigInt::New(pIsolate, value.value());
		args.GetReturnValue().Set(bigInt);
	}
}


void BufferWrapper::readInt64LE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	auto value = readBuffer<Poco::Int64>(args, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	if (value.isSpecified())
	{
		v8::Local<v8::BigInt> bigInt = v8::BigInt::New(pIsolate, value.value());
		args.GetReturnValue().Set(bigInt);
	}
}


void BufferWrapper::readUInt64BE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	auto value = readBuffer<Poco::UInt64>(args, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);
	if (value.isSpecified())
	{
		v8::Local<v8::BigInt> bigInt = v8::BigInt::New(pIsolate, value.value());
		args.GetReturnValue().Set(bigInt);
	}
}


void BufferWrapper::readInt64BE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	auto value = readBuffer<Poco::Int64>(args, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);
	if (value.isSpecified())
	{
		v8::Local<v8::BigInt> bigInt = v8::BigInt::New(pIsolate, value.value());
		args.GetReturnValue().Set(bigInt);
	}
}


void BufferWrapper::readFloatLE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto value = readBuffer<float>(args, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	if (value.isSpecified())
	{
		args.GetReturnValue().Set(value.value());
	}
}


void BufferWrapper::readDoubleLE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto value = readBuffer<double>(args, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	if (value.isSpecified())
	{
		args.GetReturnValue().Set(value.value());
	}
}


void BufferWrapper::readFloatBE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto value = readBuffer<float>(args, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);
	if (value.isSpecified())
	{
		args.GetReturnValue().Set(value.value());
	}
}


void BufferWrapper::readDoubleBE(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	auto value = readBuffer<double>(args, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);
	if (value.isSpecified())
	{
		args.GetReturnValue().Set(value.value());
	}
}


std::size_t BufferWrapper::calculatePackBufferSize(const std::string& format)
{
	std::size_t size = 0;
	int repeat = -1;
	std::string::const_iterator it = format.begin();
	std::string::const_iterator end = format.end();
	while (it != end)
	{
		switch (*it)
		{
		case '=':
		case '>':
		case '<':
		case '!':
			break;
		case ' ':
		case '\t':
		case '\r':
		case '\n':
			if (repeat != -1) throw Poco::SyntaxException("Repeat count must be followed by format character");
			break;
		case 'x':
		case 'c':
		case 's':
		case 'b':
		case 'B':
		case '?':
			size += std::abs(repeat);
			repeat = -1;
			break;
		case 'h':
		case 'H':
			size += 2*std::abs(repeat);
			repeat = -1;
			break;
		case 'i':
		case 'I':
		case 'l':
		case 'L':
		case 'f':
			size += 4*std::abs(repeat);
			repeat = -1;
			break;
		case 'q':
		case 'Q':
		case 'd':
			size += 8*std::abs(repeat);
			repeat = -1;
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if (repeat == -1)
				repeat = *it - '0';
			else
				repeat = 10*repeat + (*it - '0');
			break;
		default:
			throw Poco::InvalidArgumentException("Invalid character in format string", format);
		}
		++it;
	}
	return size;
}


} } } // namespace Poco::JS::Core
