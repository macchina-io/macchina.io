//
// Deserializer.h
//
// Library: JS/Bridge
// Package: Bridging
// Module:  Deserializer
//
// Definition of the Deserializer class.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Bridge_Deserializer_INCLUDED
#define JS_Bridge_Deserializer_INCLUDED


#include "Poco/JS/Bridge/Bridge.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "v8.h"


namespace Poco {
namespace JS {
namespace Bridge {


class JSBridge_API Deserializer: public Poco::RemotingNG::Deserializer
	/// This Deserializer deserializes from a V8 JavaScript object.
{
public:
	Deserializer(const std::string& messageName, Poco::RemotingNG::SerializerBase::MessageType messageType, v8::Isolate* pIsolate, v8::Local<v8::Object> jsObject);
		/// Creates a Deserializer.

	~Deserializer();
		/// Destroys the Deserializer.

	// Deserializer
	Poco::RemotingNG::SerializerBase::MessageType findMessage(std::string& name);
	void deserializeMessageBegin(const std::string& name, SerializerBase::MessageType type);
	void deserializeMessageEnd(const std::string& name, SerializerBase::MessageType type);
	bool deserializeStructBegin(const std::string& name, bool isMandatory);
	void deserializeStructEnd(const std::string& name);
	bool deserializeSequenceBegin(const std::string& name, bool isMandatory, Poco::UInt32& lengthHint);
	void deserializeSequenceEnd(const std::string& name);
	bool deserializeNullableBegin(const std::string& name, bool isMandatory, bool& isNull);
	void deserializeNullableEnd(const std::string& name);
	bool deserializeOptionalBegin(const std::string& name, bool isMandatory, bool& isSpecified);
	void deserializeOptionalEnd(const std::string& name);
	bool deserialize(const std::string& name, bool isMandatory, Poco::Int8& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::UInt8& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::Int16& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::UInt16& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::Int32& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::UInt32& value);
	bool deserialize(const std::string& name, bool isMandatory, long& value);
	bool deserialize(const std::string& name, bool isMandatory, unsigned long& value);
#ifndef POCO_INT64_IS_LONG
	bool deserialize(const std::string& name, bool isMandatory, Poco::Int64& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::UInt64& value);
#endif
	bool deserialize(const std::string& name, bool isMandatory, float& value);
	bool deserialize(const std::string& name, bool isMandatory, double& value);
	bool deserialize(const std::string& name, bool isMandatory, bool& value);
	bool deserialize(const std::string& name, bool isMandatory, char& value);
	bool deserialize(const std::string& name, bool isMandatory, std::string& value);
	bool deserialize(const std::string& name, bool isMandatory, std::vector<char>& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::DateTime& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::LocalDateTime& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::Timestamp& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::UUID& value);
	v8::MaybeLocal<v8::Value> deserializeValue(const std::string& name);
	v8::MaybeLocal<v8::Value> peekValue(const std::string& name);

protected:
	void resetImpl();
	void setupImpl(std::istream& istr);

private:
	v8::Isolate* _pIsolate;
	std::vector<v8::Local<v8::Object> > _jsObjectStack;
	std::vector<int> _jsIndexStack;
	std::string _messageName;
	Poco::RemotingNG::SerializerBase::MessageType _messageType;
};


} } } // namespace Poco::JS::Bridge


#endif // JS_Bridge_Deserializer_INCLUDED
