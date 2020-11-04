//
// Deserializer.cpp
//
// Library: JS/Bridge
// Package: Bridging
// Module:  Deserializer
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Bridge/Deserializer.h"
#include "Poco/JS/Core/BufferWrapper.h"
#include "Poco/RemotingNG/RemotingException.h"


namespace Poco {
namespace JS {
namespace Bridge {


Deserializer::Deserializer(const std::string& messageName, Poco::RemotingNG::SerializerBase::MessageType messageType, v8::Isolate* pIsolate, v8::Local<v8::Object> jsObject):
	_pIsolate(pIsolate),
	_messageName(messageName),
	_messageType(messageType)
{
	_jsObjectStack.push_back(jsObject);
	_jsIndexStack.push_back(0);
}


Deserializer::~Deserializer()
{
}


Poco::RemotingNG::SerializerBase::MessageType Deserializer::findMessage(std::string& name)
{
	name = _messageName;
	return _messageType;
}


void Deserializer::deserializeMessageBegin(const std::string& name, SerializerBase::MessageType type)
{
	poco_assert (name == _messageName && type == _messageType);
}


void Deserializer::deserializeMessageEnd(const std::string& /*name*/, SerializerBase::MessageType /*type*/)
{
}


bool Deserializer::deserializeStructBegin(const std::string& name, bool /*isMandatory*/)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsObject())
	{
		_jsObjectStack.push_back(jsValue->ToObject());
		_jsIndexStack.push_back(-1);
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not an object");
}


void Deserializer::deserializeStructEnd(const std::string& /*name*/)
{
	_jsObjectStack.pop_back();
	_jsIndexStack.pop_back();
}


bool Deserializer::deserializeSequenceBegin(const std::string& name, bool /*isMandatory*/, Poco::UInt32& lengthHint)
{
	lengthHint = 0;
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsObject())
	{
		_jsObjectStack.push_back(jsValue->ToObject());
		_jsIndexStack.push_back(0);
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not an object");
}


void Deserializer::deserializeSequenceEnd(const std::string& /*name*/)
{
	_jsObjectStack.pop_back();
	_jsIndexStack.pop_back();
}


bool Deserializer::deserializeNullableBegin(const std::string& name, bool /*isMandatory*/, bool& isNull)
{
	v8::Local<v8::Value> jsValue = peekValue(name);
	if (jsValue.IsEmpty()) return false;
	isNull = jsValue->IsNull() || jsValue->IsUndefined();
	return true;
}


void Deserializer::deserializeNullableEnd(const std::string& /*name*/)
{
}


bool Deserializer::deserializeOptionalBegin(const std::string& name, bool /*isMandatory*/, bool& isSpecified)
{
	v8::Local<v8::Value> jsValue = peekValue(name);
	if (jsValue.IsEmpty()) return false;
	isSpecified = !jsValue->IsNull() && !jsValue->IsUndefined();
	return true;
}


void Deserializer::deserializeOptionalEnd(const std::string& name)
{
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, Poco::Int8& value)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsNumber())
	{
		value = static_cast<Poco::Int8>(jsValue->Int32Value());
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not a number");
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, Poco::UInt8& value)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsNumber())
	{
		value = static_cast<Poco::UInt8>(jsValue->Uint32Value());
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not a number");
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, Poco::Int16& value)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsNumber())
	{
		value = static_cast<Poco::Int16>(jsValue->Int32Value());
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not a number");
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, Poco::UInt16& value)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsNumber())
	{
		value = static_cast<Poco::Int16>(jsValue->Uint32Value());
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not a number");
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, Poco::Int32& value)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsNumber())
	{
		value = jsValue->Int32Value();
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not a number");
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, Poco::UInt32& value)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsNumber())
	{
		value = jsValue->Uint32Value();
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not a number");
}


#ifdef POCO_INT64_IS_LONG
bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, long& value)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsNumber())
	{
		value = jsValue->IntegerValue();
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not a number");
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, unsigned long& value)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsNumber())
	{
		value = static_cast<Poco::UInt64>(jsValue->IntegerValue());
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not a number");
}
#else
bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, long& value)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsNumber())
	{
		value = jsValue->Int32Value();
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not a number");
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, unsigned long& value)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsNumber())
	{
		value = jsValue->Uint32Value();
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not a number");
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, Poco::Int64& value)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsNumber())
	{
		value = jsValue->IntegerValue();
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not a number");
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, Poco::UInt64& value)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsNumber())
	{
		value = static_cast<Poco::UInt64>(jsValue->IntegerValue());
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not a number");
}
#endif


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, float& value)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsNumber())
	{
		value = static_cast<float>(jsValue->NumberValue());
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not a number");
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, double& value)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsNumber())
	{
		value = jsValue->NumberValue();
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not a number");
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, bool& value)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsBoolean())
	{
		value = jsValue->BooleanValue();
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not a boolean");
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, char& value)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsString())
	{
		v8::String::Utf8Value utf8(jsValue);
		std::string s(*utf8);
		if (s.size() == 1)
		{
			value = s[0];
			return true;
		}
	}
	else if (jsValue->IsNumber())
	{
		Poco::Int32 i = jsValue->Int32Value();
		if (i >= 0 && i <= 255)
		{
			value = static_cast<char>(i);
			return true;
		}
	}
	throw Poco::RemotingNG::DeserializerException("value is not a one-character string or a byte value");
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, std::string& value)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsString())
	{
		v8::String::Utf8Value utf8(jsValue);
		value.assign(*utf8);
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not a string");
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, std::vector<char>& value)
{
	v8::Local<v8::Value> jsValue = deserializeValue(name);
	if (jsValue.IsEmpty() || jsValue->IsUndefined()) return false;
	if (jsValue->IsObject() && Poco::JS::Core::Wrapper::isWrapper<Poco::JS::Core::BufferWrapper::Buffer>(_pIsolate, jsValue))
	{
		Poco::JS::Core::BufferWrapper::Buffer* pArgBuffer = Poco::JS::Core::Wrapper::unwrapNativeObject<Poco::JS::Core::BufferWrapper::Buffer>(jsValue);
		value.assign(pArgBuffer->begin(), pArgBuffer->end());
		return true;
	}
	else throw Poco::RemotingNG::DeserializerException("value is not a buffer");
}


v8::Local<v8::Value> Deserializer::deserializeValue(const std::string& name)
{
	if (_jsIndexStack.back() == -1)
	{
		return _jsObjectStack.back()->Get(v8::String::NewFromUtf8(_pIsolate, name.c_str(), v8::String::kNormalString, static_cast<int>(name.size())));
	}
	else
	{
		return _jsObjectStack.back()->Get(_jsIndexStack.back()++);
	}
}


v8::Local<v8::Value> Deserializer::peekValue(const std::string& name)
{
	if (_jsIndexStack.back() == -1)
	{
		return _jsObjectStack.back()->Get(v8::String::NewFromUtf8(_pIsolate, name.c_str(), v8::String::kNormalString, static_cast<int>(name.size())));
	}
	else
	{
		return _jsObjectStack.back()->Get(_jsIndexStack.back());
	}
}


void Deserializer::resetImpl()
{
}


void Deserializer::setupImpl(std::istream&)
{
}


} } } // namespace Poco::JS::Bridge
