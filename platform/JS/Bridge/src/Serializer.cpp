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
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Bridge/Serializer.h"
#include "Poco/JS/Core/BufferWrapper.h"
#include "Poco/JS/Core/DateTimeWrapper.h"
#include "Poco/JS/Core/LocalDateTimeWrapper.h"
#include "Poco/JS/Core/UUIDWrapper.h"


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


void Serializer::serializeFaultMessage(const std::string& name, const Poco::Exception& exc)
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
	if (!isSpecified)
	{
		serializeValue(name, v8::Undefined(_pIsolate));
	}
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


#ifndef POCO_INT64_IS_LONG
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
	serializeValue(name, Core::Wrapper::toV8String(_pIsolate, std::string(1, value)));
}


void Serializer::serialize(const std::string& name, const std::string& value)
{
	serializeValue(name, Core::Wrapper::toV8String(_pIsolate, value));
}


void Serializer::serialize(const std::string& name, const std::vector<char>& value)
{
	Poco::JS::Core::BufferWrapper::Buffer* pBuffer = new Poco::JS::Core::BufferWrapper::Buffer(&value[0], value.size());
	Poco::JS::Core::BufferWrapper wrapper;
	v8::Persistent<v8::Object>& bufferObject(wrapper.wrapNativePersistent(_pIsolate, pBuffer));
	v8::Local<v8::Object> localBufferObject = v8::Local<v8::Object>::New(_pIsolate, bufferObject);
	serializeValue(name, localBufferObject);
}


void Serializer::serialize(const std::string& name, const Poco::DateTime& value)
{
	Poco::DateTime* pDateTime = new Poco::DateTime(value);
	Poco::JS::Core::DateTimeWrapper wrapper;
	v8::Persistent<v8::Object>& dateTimeObject(wrapper.wrapNativePersistent(_pIsolate, pDateTime));
	v8::Local<v8::Object> localDateTimeObject = v8::Local<v8::Object>::New(_pIsolate, dateTimeObject);
	serializeValue(name, localDateTimeObject);
}


void Serializer::serialize(const std::string& name, const Poco::LocalDateTime& value)
{
	Poco::LocalDateTime* pDateTime = new Poco::LocalDateTime(value);
	Poco::JS::Core::LocalDateTimeWrapper wrapper;
	v8::Persistent<v8::Object>& dateTimeObject(wrapper.wrapNativePersistent(_pIsolate, pDateTime));
	v8::Local<v8::Object> localDateTimeObject = v8::Local<v8::Object>::New(_pIsolate, dateTimeObject);
	serializeValue(name, localDateTimeObject);
}


void Serializer::serialize(const std::string& name, const Poco::Timestamp& value)
{
	Poco::DateTime* pDateTime = new Poco::DateTime(value);
	Poco::JS::Core::DateTimeWrapper wrapper;
	v8::Persistent<v8::Object>& dateTimeObject(wrapper.wrapNativePersistent(_pIsolate, pDateTime));
	v8::Local<v8::Object> localDateTimeObject = v8::Local<v8::Object>::New(_pIsolate, dateTimeObject);
	serializeValue(name, localDateTimeObject);
}


void Serializer::serialize(const std::string& name, const Poco::UUID& value)
{
	Poco::UUID* pUUID = new Poco::UUID(value);
	Poco::JS::Core::UUIDWrapper wrapper;
	v8::Persistent<v8::Object>& uuidObject(wrapper.wrapNativePersistent(_pIsolate, pUUID));
	v8::Local<v8::Object> localUUIDObject = v8::Local<v8::Object>::New(_pIsolate, uuidObject);
	serializeValue(name, localUUIDObject);
}


void Serializer::serializeValue(const std::string& name, const v8::Local<v8::Value>& value)
{
	v8::HandleScope handleScope(_pIsolate);
	v8::Local<v8::Context> context(_pIsolate->GetCurrentContext());
	v8::Local<v8::Object> object(v8::Local<v8::Object>::New(_pIsolate, _jsObjectStack.back()));
	if (_jsIndexStack.back() == -1)
	{
		V8_CHECK_SET_RESULT(object->Set(context, Core::Wrapper::toV8String(_pIsolate, name), value));
	}
	else
	{
		V8_CHECK_SET_RESULT(object->Set(context, _jsIndexStack.back()++, value));
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
