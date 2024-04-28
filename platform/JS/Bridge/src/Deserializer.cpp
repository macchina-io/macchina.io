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
#include "Poco/JS/Core/DateTimeWrapper.h"
#include "Poco/JS/Core/LocalDateTimeWrapper.h"
#include "Poco/JS/Core/UUIDWrapper.h"
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
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsObject())
		{
			_jsObjectStack.push_back(jsValue->ToObject(_pIsolate->GetCurrentContext()).ToLocalChecked());
			_jsIndexStack.push_back(-1);
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not an object");
	}
	else return false;
}


void Deserializer::deserializeStructEnd(const std::string& /*name*/)
{
	_jsObjectStack.pop_back();
	_jsIndexStack.pop_back();
}


bool Deserializer::deserializeSequenceBegin(const std::string& name, bool /*isMandatory*/, Poco::UInt32& lengthHint)
{
	lengthHint = 0;
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsObject())
		{
			_jsObjectStack.push_back(jsValue->ToObject(_pIsolate->GetCurrentContext()).ToLocalChecked());
			_jsIndexStack.push_back(0);
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not an object");
	}
	else return false;
}


void Deserializer::deserializeSequenceEnd(const std::string& /*name*/)
{
	_jsObjectStack.pop_back();
	_jsIndexStack.pop_back();
}


bool Deserializer::deserializeNullableBegin(const std::string& name, bool /*isMandatory*/, bool& isNull)
{
	v8::MaybeLocal<v8::Value> maybeValue = peekValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue))
	{
		isNull = jsValue->IsNull() || jsValue->IsUndefined();
		return true;
	}
	else return false;
}


void Deserializer::deserializeNullableEnd(const std::string& /*name*/)
{
}


bool Deserializer::deserializeOptionalBegin(const std::string& name, bool /*isMandatory*/, bool& isSpecified)
{
	v8::MaybeLocal<v8::Value> maybeValue = peekValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue))
	{
		isSpecified = !jsValue->IsNull() && !jsValue->IsUndefined();
		return true;
	}
	else return false;
}


void Deserializer::deserializeOptionalEnd(const std::string& name)
{
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, Poco::Int8& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsNumber())
		{
			value = static_cast<Poco::Int8>(jsValue->Int32Value(_pIsolate->GetCurrentContext()).FromMaybe(0));
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a number");
	}
	else return false;
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, Poco::UInt8& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsNumber())
		{
			value = static_cast<Poco::UInt8>(jsValue->Uint32Value(_pIsolate->GetCurrentContext()).FromMaybe(0));
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a number");
	}
	else return false;
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, Poco::Int16& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsNumber())
		{
			value = static_cast<Poco::Int16>(jsValue->Int32Value(_pIsolate->GetCurrentContext()).FromMaybe(0));
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a number");
	}
	else return false;
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, Poco::UInt16& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsNumber())
		{
			value = static_cast<Poco::Int16>(jsValue->Uint32Value(_pIsolate->GetCurrentContext()).FromMaybe(0));
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a number");
	}
	else return false;
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, Poco::Int32& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsNumber())
		{
			value = jsValue->Int32Value(_pIsolate->GetCurrentContext()).FromMaybe(0);
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a number");
	}
	else return false;
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, Poco::UInt32& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsNumber())
		{
			value = jsValue->Uint32Value(_pIsolate->GetCurrentContext()).FromMaybe(0);
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a number");
	}
	else return false;
}


#ifdef POCO_INT64_IS_LONG
bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, long& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsNumber())
		{
			value = jsValue->IntegerValue(_pIsolate->GetCurrentContext()).FromMaybe(0);
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a number");
	}
	else return false;
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, unsigned long& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsNumber())
		{
			value = static_cast<Poco::UInt64>(jsValue->IntegerValue(_pIsolate->GetCurrentContext()).FromMaybe(0));
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a number");
	}
	else return false;
}


#else


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, long& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsNumber())
		{
			value = jsValue->Int32Value(_pIsolate->GetCurrentContext()).FromMaybe(0);
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a number");
	}
	else return false;
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, unsigned long& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsNumber())
		{
			value = jsValue->Uint32Value(_pIsolate->GetCurrentContext()).FromMaybe(0);
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a number");
	}
	else return false;
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, Poco::Int64& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsNumber())
		{
			value = jsValue->IntegerValue(_pIsolate->GetCurrentContext()).FromMaybe(0);
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a number");
	}
	else return false;
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, Poco::UInt64& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsNumber())
		{
			value = static_cast<Poco::UInt64>(jsValue->IntegerValue(_pIsolate->GetCurrentContext()).FromMaybe(0));
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a number");
	}
	else return false;
}
#endif


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, float& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsNumber())
		{
			value = static_cast<float>(jsValue->NumberValue(_pIsolate->GetCurrentContext()).FromMaybe(0));
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a number");
	}
	else return false;
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, double& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsNumber())
		{
			value = jsValue->NumberValue(_pIsolate->GetCurrentContext()).FromMaybe(0);
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a number");
	}
	else return false;
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, bool& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsBoolean())
		{
			value = jsValue->BooleanValue(_pIsolate);
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a boolean");
	}
	else return false;
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, char& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsString())
		{
			std::string s = Core::Wrapper::toString(_pIsolate, jsValue);
			if (s.size() == 1)
			{
				value = s[0];
				return true;
			}
		}
		else if (jsValue->IsNumber())
		{
			Poco::Int32 i = jsValue->Int32Value(_pIsolate->GetCurrentContext()).FromMaybe(0);
			if (i >= 0 && i <= 255)
			{
				value = static_cast<char>(i);
				return true;
			}
		}
		throw Poco::RemotingNG::DeserializerException("value is not a one-character string or a byte value");
	}
	else return false;
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, std::string& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsString())
		{
			value = Core::Wrapper::toString(_pIsolate, jsValue);
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a string");
	}
	else return false;
}


bool Deserializer::deserialize(const std::string& name, bool /*isMandatory*/, std::vector<char>& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsObject() && Poco::JS::Core::Wrapper::isWrapper<Poco::JS::Core::BufferWrapper::Buffer>(_pIsolate, jsValue))
		{
			Poco::JS::Core::BufferWrapper::Buffer* pArgBuffer = Poco::JS::Core::Wrapper::unwrapNativeObject<Poco::JS::Core::BufferWrapper::Buffer>(jsValue);
			value.assign(pArgBuffer->begin(), pArgBuffer->end());
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a buffer");
	}
	else return false;
}


bool Deserializer::deserialize(const std::string& name, bool isMandatory, Poco::DateTime& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsObject() && Poco::JS::Core::Wrapper::isWrapper<Poco::DateTime>(_pIsolate, jsValue))
		{
			Poco::DateTime* pDateTime = Poco::JS::Core::Wrapper::unwrapNativeObject<Poco::DateTime>(jsValue);
			value = *pDateTime;
			return true;
		}
		else if (jsValue->IsDate())
		{
			v8::Local<v8::Date> jsDate = v8::Local<v8::Date>::Cast(jsValue);
			double millis = jsDate->ValueOf();
			Poco::Timestamp ts(static_cast<Poco::Timestamp::TimeVal>(millis*1000));
			value = Poco::DateTime(ts);
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a DateTime or Date");
	}
	else return false;
}


bool Deserializer::deserialize(const std::string& name, bool isMandatory, Poco::LocalDateTime& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsObject() && Poco::JS::Core::Wrapper::isWrapper<Poco::LocalDateTime>(_pIsolate, jsValue))
		{
			Poco::LocalDateTime* pDateTime = Poco::JS::Core::Wrapper::unwrapNativeObject<Poco::LocalDateTime>(jsValue);
			value = *pDateTime;
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a LocalDateTime");
	}
	else return false;
}


bool Deserializer::deserialize(const std::string& name, bool isMandatory, Poco::Timestamp& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsObject() && Poco::JS::Core::Wrapper::isWrapper<Poco::DateTime>(_pIsolate, jsValue))
		{
			Poco::DateTime* pDateTime = Poco::JS::Core::Wrapper::unwrapNativeObject<Poco::DateTime>(jsValue);
			value = pDateTime->timestamp();
			return true;
		}
		else if (jsValue->IsDate())
		{
			v8::Local<v8::Date> jsDate = v8::Local<v8::Date>::Cast(jsValue);
			double millis = jsDate->ValueOf();
			Poco::Timestamp ts(static_cast<Poco::Timestamp::TimeVal>(millis*1000));
			value = ts;
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a DateTime or Date");
	}
	else return false;
}


bool Deserializer::deserialize(const std::string& name, bool isMandatory, Poco::UUID& value)
{
	v8::MaybeLocal<v8::Value> maybeValue = deserializeValue(name);
	v8::Local<v8::Value> jsValue;
	if (maybeValue.ToLocal(&jsValue) && !jsValue->IsUndefined())
	{
		if (jsValue->IsObject() && Poco::JS::Core::Wrapper::isWrapper<Poco::UUID>(_pIsolate, jsValue))
		{
			UUID* pUUID = Poco::JS::Core::Wrapper::unwrapNativeObject<Poco::UUID>(jsValue);
			value = *pUUID;
			return true;
		}
		else if (jsValue->IsString())
		{
			std::string s = Core::Wrapper::toString(_pIsolate, jsValue);
			value.parse(s);
			return true;
		}
		else throw Poco::RemotingNG::DeserializerException("value is not a UUID");
	}
	else return false;
}


v8::MaybeLocal<v8::Value> Deserializer::deserializeValue(const std::string& name)
{
	if (_jsIndexStack.back() == -1)
	{
		return _jsObjectStack.back()->Get(_pIsolate->GetCurrentContext(), Core::Wrapper::toV8String(_pIsolate, name));
	}
	else
	{
		return _jsObjectStack.back()->Get(_pIsolate->GetCurrentContext(), _jsIndexStack.back()++);
	}
}


v8::MaybeLocal<v8::Value> Deserializer::peekValue(const std::string& name)
{
	if (_jsIndexStack.back() == -1)
	{
		return _jsObjectStack.back()->Get(_pIsolate->GetCurrentContext(), Core::Wrapper::toV8String(_pIsolate, name));
	}
	else
	{
		return _jsObjectStack.back()->Get(_pIsolate->GetCurrentContext(), _jsIndexStack.back());
	}
}


void Deserializer::resetImpl()
{
}


void Deserializer::setupImpl(std::istream&)
{
}


} } } // namespace Poco::JS::Bridge
