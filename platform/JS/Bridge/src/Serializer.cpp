//
// Serializer.cpp
//
// Library: JS/Bridge
// Package: Bridging
// Module:  Serializer
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Bridge/Serializer.h"
#include "Poco/JS/Core/BufferWrapper.h"


namespace Poco {
namespace JS {
namespace Bridge {


Serializer::Serializer(v8::Isolate* pIsolate):
	_pIsolate(pIsolate),
	_jsObjectStack(pIsolate),
	_pException(0),
	_totalSerialized(0)
{
}


Serializer::~Serializer()
{
	delete _pException;
}


void Serializer::serializeMessageBegin(const std::string& name, SerializerBase::MessageType /*type*/)
{
	_messageName = name;
	_jsObjectStack.push(v8::Object::New(_pIsolate));
	_jsIndexStack.push_back(-1);
}


void Serializer::serializeMessageEnd(const std::string& /*name*/, SerializerBase::MessageType /*type*/)
{
}


void Serializer::serializeFaultMessage(const std::string& name, Poco::Exception& exc)
{
	_pException = exc.clone();
}


void Serializer::serializeStructBegin(const std::string& name)
{
	_jsObjectStack.push(v8::Object::New(_pIsolate));
	_jsIndexStack.push_back(-1);
}


void Serializer::serializeStructEnd(const std::string& name)
{
	v8::Local<v8::Object> object(v8::Local<v8::Object>::New(_pIsolate, _jsObjectStack.back()));
	_jsObjectStack.pop();
	_jsIndexStack.pop_back();
	serializeValue(name, object);
}


void Serializer::serializeSequenceBegin(const std::string& name, Poco::UInt32 length)
{
	v8::Local<v8::Object> object = v8::Array::New(_pIsolate, length);
	_jsObjectStack.push(object);
	_jsIndexStack.push_back(0);
}


void Serializer::serializeSequenceEnd(const std::string& name)
{
	v8::Local<v8::Object> object(v8::Local<v8::Object>::New(_pIsolate, _jsObjectStack.back()));
	_jsObjectStack.pop();
	_jsIndexStack.pop_back();
	serializeValue(name, object);
}


void Serializer::serializeNullableBegin(const std::string& name, bool isNull)
{
	if (isNull)
	{
		serializeValue(name, v8::Null(_pIsolate));
	}
}


void Serializer::serializeNullableEnd(const std::string& name)
{
}


void Serializer::serializeOptionalBegin(const std::string& name, bool isSpecified)
{
}


void Serializer::serializeOptionalEnd(const std::string& name)
{
}


void Serializer::serialize(const std::string& name, Poco::Int8 value)
{
	serializeValue(name, v8::Integer::New(_pIsolate, static_cast<Poco::Int32>(value)));
}


void Serializer::serialize(const std::string& name, Poco::UInt8 value)
{
	serializeValue(name, v8::Integer::NewFromUnsigned(_pIsolate, static_cast<Poco::UInt32>(value)));
}


void Serializer::serialize(const std::string& name, Poco::Int16 value)
{
	serializeValue(name, v8::Integer::New(_pIsolate, static_cast<Poco::Int32>(value)));
}


void Serializer::serialize(const std::string& name, Poco::UInt16 value)
{
	serializeValue(name, v8::Integer::NewFromUnsigned(_pIsolate, static_cast<Poco::UInt32>(value)));
}


void Serializer::serialize(const std::string& name, Poco::Int32 value)
{
	serializeValue(name, v8::Integer::New(_pIsolate, value));
}


void Serializer::serialize(const std::string& name, Poco::UInt32 value)
{
	serializeValue(name, v8::Integer::NewFromUnsigned(_pIsolate, value));
}


void Serializer::serialize(const std::string& name, long value)
{
	serializeValue(name, v8::Number::New(_pIsolate, value));
}


void Serializer::serialize(const std::string& name, unsigned long value)
{
	serializeValue(name, v8::Number::New(_pIsolate, value));
}


#ifndef POCO_LONG_IS_64_BIT
void Serializer::serialize(const std::string& name, Poco::Int64 value)
{
	serializeValue(name, v8::Number::New(_pIsolate, static_cast<double>(value)));
}


void Serializer::serialize(const std::string& name, Poco::UInt64 value)
{
	serializeValue(name, v8::Number::New(_pIsolate, static_cast<double>(value)));
}
#endif


void Serializer::serialize(const std::string& name, float value)
{
	serializeValue(name, v8::Number::New(_pIsolate, value));
}


void Serializer::serialize(const std::string& name, double value)
{
	serializeValue(name, v8::Number::New(_pIsolate, value));
}


void Serializer::serialize(const std::string& name, bool value)
{
	serializeValue(name, v8::Boolean::New(_pIsolate, value));
}


void Serializer::serialize(const std::string& name, char value)
{
	serializeValue(name, v8::String::NewFromUtf8(_pIsolate, &value, v8::String::kNormalString, 1));
}


void Serializer::serialize(const std::string& name, const std::string& value)
{
	serializeValue(name, v8::String::NewFromUtf8(_pIsolate, value.c_str(), v8::String::kNormalString, static_cast<int>(value.size())));
}


void Serializer::serialize(const std::string& name, const std::vector<char>& value)
{
	Poco::JS::Core::BufferWrapper::Buffer* pBuffer = new Poco::JS::Core::BufferWrapper::Buffer(&value[0], value.size());
	Poco::JS::Core::BufferWrapper wrapper;
	v8::Persistent<v8::Object>& bufferObject(wrapper.wrapNativePersistent(_pIsolate, pBuffer));
	v8::Local<v8::Object> localBufferObject = v8::Local<v8::Object>::New(_pIsolate, bufferObject);
	serializeValue(name, localBufferObject);
}


void Serializer::serializeValue(const std::string& name, const v8::Local<v8::Value>& value)
{
	v8::Local<v8::Object> object(v8::Local<v8::Object>::New(_pIsolate, _jsObjectStack.back()));
	if (_jsIndexStack.back() == -1)
	{
		object->Set(
			v8::String::NewFromUtf8(_pIsolate, name.c_str(), v8::String::kNormalString, static_cast<int>(name.size())),
			value);
	}
	else
	{
		object->Set(_jsIndexStack.back()++, value);
	}
	if (_jsObjectStack.size() == 1) _totalSerialized++;
}


void Serializer::resetImpl()
{	
	_jsObjectStack.clear();
	_jsIndexStack.clear();
	delete _pException;
	_pException = 0;
}


void Serializer::setupImpl(std::ostream&)
{
}


} } } // namespace Poco::JS::Bridge
