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
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Core/BufferWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/Buffer.h"
#include "Poco/Base64Encoder.h"
#include "Poco/Base64Decoder.h"
#include "Poco/MemoryStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/TextEncoding.h"
#include "Poco/TextConverter.h"
#include "Poco/UTF8Encoding.h"
#include "Poco/UTF16Encoding.h"
#include "Poco/BinaryReader.h"
#include "Poco/BinaryWriter.h"
#include "Poco/Exception.h"
#include "Poco/String.h"
#include "Poco/Format.h"
#include <sstream>
#include <cstdlib>


namespace Poco {
namespace JS {
namespace Core {


const std::string BufferWrapper::ENCODING_UTF8("UTF-8");
const std::string BufferWrapper::ENCODING_UTF16("UTF-16");
const std::string BufferWrapper::ENCODING_ASCII("ASCII");
const std::string BufferWrapper::ENCODING_BASE64("BASE64");


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
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "isBuffer"), v8::FunctionTemplate::New(pIsolate, isBuffer));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "UTF8"), v8::String::NewFromUtf8(pIsolate, ENCODING_UTF8.c_str()));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "UTF16"), v8::String::NewFromUtf8(pIsolate, ENCODING_UTF16.c_str()));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "ASCII"), v8::String::NewFromUtf8(pIsolate, ENCODING_ASCII.c_str()));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "BASE64"), v8::String::NewFromUtf8(pIsolate, ENCODING_BASE64.c_str()));
	return handleScope.Escape(funcTemplate);
}


v8::Handle<v8::ObjectTemplate> BufferWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	PooledIsolate* pPooledIso = PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("Core.Buffer"));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "length"), getLength, setLength);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "capacity"), getCapacity, setCapacity);
		objectTemplate->SetIndexedPropertyHandler(getAt, setAt);

		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "toBase64"), v8::FunctionTemplate::New(pIsolate, toBase64));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "fromBase64"), v8::FunctionTemplate::New(pIsolate, fromBase64));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "toString"), v8::FunctionTemplate::New(pIsolate, makeString));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "decodeString"), v8::FunctionTemplate::New(pIsolate, decodeString));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "encodeString"), v8::FunctionTemplate::New(pIsolate, encodeString));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "pack"), v8::FunctionTemplate::New(pIsolate, pack));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "unpack"), v8::FunctionTemplate::New(pIsolate, unpack));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "concat"), v8::FunctionTemplate::New(pIsolate, concat));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "slice"), v8::FunctionTemplate::New(pIsolate, slice));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "push"), v8::FunctionTemplate::New(pIsolate, push));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "pop"), v8::FunctionTemplate::New(pIsolate, pop));
		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> bufferTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(bufferTemplate);
}


void BufferWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
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
					encoding = toString(args[1]);
				else
					encoding = ENCODING_BASE64;

				pBuffer = new Buffer(0);
				encode(pBuffer, args[0], encoding);
			}
			else if (args[0]->IsArray())
			{
				v8::Local<v8::Array> array = v8::Local<v8::Array>::Cast(args[0]);
				std::size_t size = array->Length();
				pBuffer = new Buffer(size);
				for (std::size_t i = 0; i < size; i++)
				{
					v8::Local<v8::Value> value = array->Get(i);
					if (value->IsNumber())
					{
						(*pBuffer)[i] = static_cast<char>(value->Uint32Value());
					}
				}
			}
			else if (args[0]->IsObject())
			{
				if (Wrapper::isWrapper<Buffer>(args.GetIsolate(), args[0]))
				{
					Buffer* pArgBuffer = Wrapper::unwrapNativeObject<Buffer>(args[0]);

					Poco::Int32 begin = 0;
					Poco::Int32 end = static_cast<Poco::Int32>(pArgBuffer->size());

					if (args.Length() > 0)
					{
						if (args[1]->IsNumber())
						{
							Poco::Int32 index = args[1]->Int32Value();
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
							Poco::Int32 index = args[2]->Int32Value();
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
				Poco::UInt32 size = args[0]->Uint32Value();
				pBuffer = new Buffer(size);
				pBuffer->resize(0);
			}
		}
		BufferWrapper wrapper;
		v8::Persistent<v8::Object>& bufferObject(wrapper.wrapNativePersistent(args.GetIsolate(), pBuffer));
		args.GetReturnValue().Set(bufferObject);
	}
	catch (Poco::Exception& exc)
	{
		delete pBuffer;
		returnException(args, exc);
	}
	catch (std::exception&)
	{
		returnException(args, std::string("Out of memory"));
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
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(info);
	Poco::UInt32 size = value->Uint32Value();
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
		returnException(info, std::string("Out of memory"));
	}
}


void BufferWrapper::getCapacity(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(info);
	info.GetReturnValue().Set(static_cast<Poco::UInt32>(pBuffer->capacity()));
}


void BufferWrapper::setCapacity(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(info);
	Poco::UInt32 size = value->Uint32Value();
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
		returnException(info, std::string("Out of memory"));
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
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(info);
	std::size_t size = pBuffer->size();
	if (index < size)
	{
		(*pBuffer)[index] = static_cast<char>(value->Uint32Value());
		info.GetReturnValue().Set(value);
	}
	else
	{
		returnException(info, Poco::RangeException(Poco::format("buffer size=%z, index=%u", size, static_cast<unsigned>(index))));
	}
}


void BufferWrapper::toBase64(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		int lineLength = 0;
		if (args.Length() > 0)
		{
			lineLength = args[0]->Int32Value();
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


void BufferWrapper::fromBase64(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		if (args.Length() > 0)
		{
			std::string base64String = toString(args[0]);
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
		returnException(args, std::string("Out of memory"));
	}
}


void BufferWrapper::decodeString(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	try
	{
		std::string encoding;
		if (args.Length() > 0)
			encoding = toString(args[0]);
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
		returnException(args, std::string("Out of memory"));
	}
}


void BufferWrapper::encodeString(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() == 0) return;

	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		std::string encoding;
		if (args.Length() > 1)
			encoding = toString(args[1]);
		else
			encoding = ENCODING_UTF8;

		encode(pBuffer, args[0], encoding);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
	catch (std::exception&)
	{
		returnException(args, std::string("Out of memory"));
	}
}


void BufferWrapper::pack(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;

	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		if (!args[1]->IsArray()) throw Poco::InvalidArgumentException("Second argument to pack() must be array");

		v8::Local<v8::Array> array = v8::Local<v8::Array>::Cast(args[1]);
		std::string format(toString(args[0]));
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
					v8::Maybe<bool> hasIndex = array->Has(args.GetIsolate()->GetCurrentContext(), index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						utf8 = toString(array->Get(index));
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
					v8::Maybe<bool> hasIndex = array->Has(args.GetIsolate()->GetCurrentContext(), index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v = static_cast<Poco::Int8>(array->Get(index)->Int32Value());
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
					v8::Maybe<bool> hasIndex = array->Has(args.GetIsolate()->GetCurrentContext(), index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v = static_cast<Poco::UInt8>(array->Get(index)->Uint32Value());
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
					v8::Maybe<bool> hasIndex = array->Has(args.GetIsolate()->GetCurrentContext(), index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v = array->Get(index)->BooleanValue();
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
					v8::Maybe<bool> hasIndex = array->Has(args.GetIsolate()->GetCurrentContext(), index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v = static_cast<Poco::Int16>(array->Get(index)->Int32Value());
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
					v8::Maybe<bool> hasIndex = array->Has(args.GetIsolate()->GetCurrentContext(), index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v = static_cast<Poco::UInt16>(array->Get(index)->Uint32Value());
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
					v8::Maybe<bool> hasIndex = array->Has(args.GetIsolate()->GetCurrentContext(), index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v = array->Get(index)->Int32Value();
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
					v8::Maybe<bool> hasIndex = array->Has(args.GetIsolate()->GetCurrentContext(), index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v = array->Get(index)->Uint32Value();
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
					v8::Maybe<bool> hasIndex = array->Has(args.GetIsolate()->GetCurrentContext(), index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v = static_cast<Poco::Int64>(array->Get(index)->IntegerValue());
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
					v8::Maybe<bool> hasIndex = array->Has(args.GetIsolate()->GetCurrentContext(), index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v = static_cast<Poco::UInt64>(array->Get(index)->IntegerValue());
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
					v8::Maybe<bool> hasIndex = array->Has(args.GetIsolate()->GetCurrentContext(), index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v = static_cast<float>(array->Get(index)->NumberValue());
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
					v8::Maybe<bool> hasIndex = array->Has(args.GetIsolate()->GetCurrentContext(), index);
					if (hasIndex.IsJust() && hasIndex.FromJust())
					{
						v = array->Get(index)->NumberValue();
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
		returnException(args, std::string("Out of memory"));
	}
}


void BufferWrapper::unpack(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;

	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		v8::Local<v8::Array> array = v8::Array::New(args.GetIsolate());
		std::string format(toString(args[0]));
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
					array->Set(index, v8::String::NewFromUtf8(args.GetIsolate(), utf8.c_str()));
					index++;
					repeat = -1;
				}
				break;
			case 'b':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::Int8 v = 0;
					reader >> v;
					array->Set(index, v8::Integer::New(args.GetIsolate(), static_cast<Poco::Int32>(v)));
					index++;
				}
				repeat = -1;
				break;
			case 'B':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::UInt8 v = 0;
					reader >> v;
					array->Set(index, v8::Integer::NewFromUnsigned(args.GetIsolate(), static_cast<Poco::UInt32>(v)));
					index++;
				}
				repeat = -1;
				break;
			case '?':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					bool v = false;
					reader >> v;
					array->Set(index, v8::Boolean::New(args.GetIsolate(), v));
					index++;
				}
				repeat = -1;
				break;
			case 'h':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::Int16 v = 0;
					reader >> v;
					array->Set(index, v8::Integer::New(args.GetIsolate(), static_cast<Poco::Int32>(v)));
					index++;
				}
				repeat = -1;
				break;
			case 'H':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::UInt16 v = 0;
					reader >> v;
					array->Set(index, v8::Integer::NewFromUnsigned(args.GetIsolate(), static_cast<Poco::UInt32>(v)));
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
					array->Set(index, v8::Integer::New(args.GetIsolate(), v));
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
					array->Set(index, v8::Integer::NewFromUnsigned(args.GetIsolate(), v));
					index++;
				}
				repeat = -1;
				break;
			case 'q':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::Int64 v = 0;
					reader >> v;
					array->Set(index, v8::Number::New(args.GetIsolate(), static_cast<double>(v)));
					index++;
				}
				repeat = -1;
				break;
			case 'Q':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					Poco::UInt64 v = 0;
					reader >> v;
					array->Set(index, v8::Number::New(args.GetIsolate(), static_cast<double>(v)));
					index++;
				}
				repeat = -1;
				break;
			case 'f':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					float v = 0.0f;
					reader >> v;
					array->Set(index, v8::Number::New(args.GetIsolate(), v));
					index++;
				}
				repeat = -1;
				break;
			case 'd':
				for (int i = 0; i < std::abs(repeat); i++)
				{
					double v = 0.0;
					reader >> v;
					array->Set(index, v8::Number::New(args.GetIsolate(), v));
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
		returnException(args, std::string("Out of memory"));
	}
}


void BufferWrapper::concat(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		for (int i = 0; i < args.Length(); i++)
		{
			if (Wrapper::isWrapper<Buffer>(args.GetIsolate(), args[i]))
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
		returnException(args, std::string("Out of memory"));
	}
}


void BufferWrapper::slice(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		Poco::Int32 begin = 0;
		Poco::Int32 end = static_cast<Poco::UInt32>(pBuffer->size());
		if (args.Length() > 0)
		{
			if (args[0]->IsNumber())
			{
				Poco::Int32 index = args[0]->Int32Value();
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
				Poco::Int32 index = args[1]->Int32Value();
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
		v8::Persistent<v8::Object>& bufferObject(wrapper.wrapNativePersistent(args.GetIsolate(), pNewBuffer));
		args.GetReturnValue().Set(bufferObject);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
	catch (std::exception&)
	{
		returnException(args, std::string("Out of memory"));
	}
}


void BufferWrapper::push(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Buffer* pBuffer = Wrapper::unwrapNative<Buffer>(args);
	try
	{
		if (args.Length() > 0)
		{
			if (args[0]->IsNumber())
			{
				pBuffer->append(static_cast<char>(args[0]->Uint32Value()));
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
		returnException(args, std::string("Out of memory"));
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
	try
	{
		std::string encoding;
		if (args.Length() > 0)
			encoding = toString(args[0]);
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
		returnException(args, std::string("Out of memory"));
	}
}


void BufferWrapper::encode(Buffer* pBuffer, const v8::Local<v8::Value>& str, const std::string& encoding)
{
	if (Poco::icompare(encoding, ENCODING_UTF8) == 0)
	{
		v8::String::Utf8Value utf8(str);
		if (utf8.length() > 0)
			pBuffer->assign(*utf8, utf8.length());
		else
			pBuffer->resize(0);
	}
	else if (Poco::icompare(encoding, ENCODING_UTF16) == 0)
	{
		v8::String::Value utf16(str);
		if (utf16.length() > 0)
			pBuffer->assign(reinterpret_cast<const char*>(*utf16), 2*utf16.length());
		else
			pBuffer->resize(0);
	}
	else if (Poco::icompare(encoding, ENCODING_BASE64) == 0)
	{
		std::string base64String = toString(str);
		int size = static_cast<int>(base64String.size());
		int decodedSize = 3*size/4 + 16;
		pBuffer->resize(decodedSize, false);
		Poco::MemoryInputStream istr(base64String.data(), static_cast<std::streamsize>(size));
		Poco::MemoryOutputStream ostr(pBuffer->begin(), pBuffer->size());
		Poco::Base64Decoder decoder(istr);
		Poco::StreamCopier::copyStream(decoder, ostr);
		pBuffer->resize(static_cast<std::size_t>(ostr.charsWritten()));
	}
	else
	{
		v8::String::Value utf16(str);
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
	if (Poco::icompare(encoding, ENCODING_UTF8) == 0)
	{
		args.GetReturnValue().Set(v8::String::NewFromUtf8(args.GetIsolate(), pBuffer->begin(), v8::String::kNormalString, static_cast<int>(pBuffer->size())));
	}
	else if (Poco::icompare(encoding, ENCODING_UTF16) == 0)
	{
		args.GetReturnValue().Set(v8::String::NewFromTwoByte(args.GetIsolate(), reinterpret_cast<Poco::UInt16*>(pBuffer->begin()), v8::String::kNormalString, static_cast<int>(pBuffer->size()/2)));
	}
	else if (Poco::icompare(encoding, ENCODING_BASE64) == 0)
	{
		Poco::MemoryInputStream istr(pBuffer->begin(), pBuffer->size());
		std::stringstream ostr;
		Poco::Base64Encoder encoder(ostr);
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
		converter.convert(pBuffer->begin(), pBuffer->size(), result);
		args.GetReturnValue().Set(v8::String::NewFromUtf8(args.GetIsolate(), result.data(), v8::String::kNormalString, static_cast<int>(result.size())));
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
