//
// Serializer.h
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


#ifndef JS_Bridge_Serializer_INCLUDED
#define JS_Bridge_Serializer_INCLUDED


#include "Poco/JS/Bridge/Bridge.h"
#include "Poco/RemotingNG/Serializer.h"
#include "v8.h"
#include "v8-util.h"


namespace Poco {
namespace JS {
namespace Bridge {


template <typename V>
class PersistentValueStack
	/// A helper class to keep a stack of JavaScript objects.
{
public:
	explicit PersistentValueStack(v8::Isolate* pIsolate): _pIsolate(pIsolate)
	{
	}

	~PersistentValueStack()
	{
		clear();
	}

	void push(const v8::Local<V>& value)
	{
		_vector.emplace_back(_pIsolate, value);
	}

	bool empty() const
	{
		return _vector.empty();
	}

	std::size_t size() const
	{
		return _vector.size();
	}

	void clear()
	{
		_vector.clear();
	}

	void pop()
	{
     	_vector.pop_back();
	}

	v8::Global<V>& front()
	{
		return _vector.front();
	}

	const v8::Global<V>& front() const
	{
		return _vector.front();
	}

	v8::Global<V>& back()
	{
		return _vector.back();
	}

	const v8::Global<V>& back() const
	{
		return _vector.back();
	}

	v8::Isolate* _pIsolate;
	std::vector<v8::Global<V>> _vector;
};


class JSBridge_API Serializer: public Poco::RemotingNG::Serializer
	/// This Serializer serializes to a V8 JavaScript object.
{
public:
	Serializer(v8::Isolate* pIsolate);
		/// Creates a Serializer.

	~Serializer();
		/// Destroys the Serializer.
		
	const v8::Global<v8::Object>& jsValue() const;
		/// Returns the resulting JavaScript object.
		
	Poco::Exception* exception() const;
		/// Returns a pointer to the exception object if one was thrown, or 
		/// null otherwise.
		
	const std::string& messageName() const;
		/// Returns the message name.
		
	int totalSerialized() const;
		/// Returns the number of serialized values.
		
	// Serializer
	void serializeMessageBegin(const std::string& name, SerializerBase::MessageType type);
	void serializeMessageEnd(const std::string& name, SerializerBase::MessageType type);
	void serializeFaultMessage(const std::string& name, Poco::Exception& exc);
	void serializeStructBegin(const std::string& name);
	void serializeStructEnd(const std::string& name);
	void serializeSequenceBegin(const std::string& name, Poco::UInt32 length);
	void serializeSequenceEnd(const std::string& name);
	void serializeNullableBegin(const std::string& name, bool isNull);
	void serializeNullableEnd(const std::string& name);
	void serializeOptionalBegin(const std::string& name, bool isSpecified);
	void serializeOptionalEnd(const std::string& name);
	void serialize(const std::string& name, Poco::Int8 value);
	void serialize(const std::string& name, Poco::UInt8 value);
	void serialize(const std::string& name, Poco::Int16 value);
	void serialize(const std::string& name, Poco::UInt16 value);
	void serialize(const std::string& name, Poco::Int32 value);
	void serialize(const std::string& name, Poco::UInt32 value);
	void serialize(const std::string& name, long value);
	void serialize(const std::string& name, unsigned long value);
#ifndef POCO_LONG_IS_64_BIT
	void serialize(const std::string& name, Poco::Int64 value);
	void serialize(const std::string& name, Poco::UInt64 value);
#endif
	void serialize(const std::string& name, float value);
	void serialize(const std::string& name, double value);
	void serialize(const std::string& name, bool value);
	void serialize(const std::string& name, char value);
	void serialize(const std::string& name, const std::string& value);
	void serialize(const std::string& name, const std::vector<char>& value);
	void serializeValue(const std::string& name, const v8::Local<v8::Value>& value);

protected:
	void resetImpl();
	void setupImpl(std::ostream&);
	
private:
	v8::Isolate* _pIsolate;
	PersistentValueStack<v8::Object> _jsObjectStack;
	std::vector<int> _jsIndexStack;
	std::string _messageName;
	Poco::Exception* _pException;
	int _totalSerialized;
};


//
// inlines
//
inline const v8::Global<v8::Object>& Serializer::jsValue() const
{
	poco_assert (!_jsObjectStack.empty());

	return _jsObjectStack.front();
}


inline Poco::Exception* Serializer::exception() const
{
	return _pException;
}


inline const std::string& Serializer::messageName() const
{
	return _messageName;
}


inline int Serializer::totalSerialized() const
{
	return _totalSerialized;
}


} } } // namespace Poco::JS::Bridge


#endif // JS_Bridge_Serializer_INCLUDED
