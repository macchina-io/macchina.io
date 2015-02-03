//
// JSONEventSerializer.h
//
// $Id: //poco/1.4/JS/Bridge/include/Poco/JS/Bridge/JSONEventSerializer.h#3 $
//
// Library: JSBridge
// Package: Bridge
// Module:  JSONEventSerializer
//
// Definition of the JSONEventSerializer class.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef JS_Bridge_JSONEventSerializer_INCLUDED
#define JS_Bridge_JSONEventSerializer_INCLUDED


#include "Poco/JS/Bridge/Bridge.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/NumberFormatter.h"
#include <vector>


namespace Poco {
namespace JS {
namespace Bridge {


class JSBridge_API JSONEventSerializer: public Poco::RemotingNG::Serializer
	/// A Serializer for event data.
{
public:
	static const std::string JSON_TRUE;
	static const std::string JSON_FALSE;
	static const std::string JSON_NULL;
	
	enum State
	{
		ST_MESSAGE,
		ST_OBJECT,
		ST_OBJECT_FIRST,
		ST_ARRAY,
		ST_ARRAY_FIRST
	};

	JSONEventSerializer();
		/// Creates the Serializer. 

	~JSONEventSerializer();
		/// Destroys the Serializer.

	// Poco::RemotingNG::Serializer
	void serializeMessageBegin(const std::string& name, Poco::RemotingNG::SerializerBase::MessageType type);
	void serializeMessageEnd(const std::string& name, Poco::RemotingNG::SerializerBase::MessageType type);
	void serializeFaultMessage(const std::string& name, Poco::Exception& exc);
	void serializeStructBegin(const std::string& name);
	void serializeStructEnd(const std::string& name);
	void serializeSequenceBegin(const std::string& name, Poco::UInt32 numElems);
	void serializeSequenceEnd(const std::string& name);
	void serializeNullableBegin(const std::string& name, bool isNull);
	void serializeNullableEnd(const std::string& name);
	void serialize(const std::string& name, Poco::Int8 val);
	void serialize(const std::string& name, Poco::UInt8 val);
	void serialize(const std::string& name, Poco::Int16 val);
	void serialize(const std::string& name, Poco::UInt16 val);
	void serialize(const std::string& name, Poco::Int32 val);
	void serialize(const std::string& name, Poco::UInt32 val);
	void serialize(const std::string& name, long val);
	void serialize(const std::string& name, unsigned long val);
#ifndef POCO_LONG_IS_64_BIT
	void serialize(const std::string& name, Poco::Int64 val);
	void serialize(const std::string& name, Poco::UInt64 val);
#endif
	void serialize(const std::string& name, float val);
	void serialize(const std::string& name, double val);
	void serialize(const std::string& name, bool val);
	void serialize(const std::string& name, char val);
	void serialize(const std::string& name, const char* pVal);
	void serialize(const std::string& name, const std::string& val);
	void serialize(const std::string& name, const std::vector<char>& val);
	
protected:
	void resetImpl();
	void setupImpl(std::ostream& out);

private:
	JSONEventSerializer(const Serializer&);
	JSONEventSerializer& operator=(const Serializer&);

	void serializeData(const std::string& name, const std::string& val);
		/// Serializes string data.
		
	void writeSeparator();

private:
	std::ostream* _pStream;
	int _indent;
	std::vector<int> _state;
};


//
// inlines
//
inline void JSONEventSerializer::serialize(const std::string& name, Poco::Int8 val)
{
	serializeData(name, Poco::NumberFormatter::format(val));
}


inline void JSONEventSerializer::serialize(const std::string& name, Poco::UInt8 val)
{
	serializeData(name, Poco::NumberFormatter::format(val));
}


inline void JSONEventSerializer::serialize(const std::string& name, Poco::Int16 val)
{
	serializeData(name, Poco::NumberFormatter::format(val));
}


inline void JSONEventSerializer::serialize(const std::string& name, Poco::UInt16 val)
{
	serializeData(name, Poco::NumberFormatter::format(val));
}


inline void JSONEventSerializer::serialize(const std::string& name, Poco::Int32 val)
{
	serializeData(name, Poco::NumberFormatter::format(val));
}


inline void JSONEventSerializer::serialize(const std::string& name, Poco::UInt32 val)
{
	serializeData(name, Poco::NumberFormatter::format(val));
}


inline void JSONEventSerializer::serialize(const std::string& name, long val)
{
	serializeData(name, Poco::NumberFormatter::format(val));
}


inline void JSONEventSerializer::serialize(const std::string& name, unsigned long val)
{
	serializeData(name, Poco::NumberFormatter::format(val));
}


#ifndef POCO_LONG_IS_64_BIT
inline void JSONEventSerializer::serialize(const std::string& name, Poco::Int64 val)
{
	serializeData(name, Poco::NumberFormatter::format(val));
}


inline void JSONEventSerializer::serialize(const std::string& name, Poco::UInt64 val)
{
	serializeData(name, Poco::NumberFormatter::format(val));
}
#endif


inline void JSONEventSerializer::serialize(const std::string& name, float val)
{
	serializeData(name, Poco::NumberFormatter::format(val));
}


inline void JSONEventSerializer::serialize(const std::string& name, double val)
{
	serializeData(name, Poco::NumberFormatter::format(val));
}


inline void JSONEventSerializer::serialize(const std::string& name, bool val)
{
	serializeData(name, val? JSON_TRUE : JSON_FALSE);
}


inline void JSONEventSerializer::serialize(const std::string& name, const char* pVal)
{
	std::string str(pVal);
	serialize(name, str);
}


} } } // namespace Poco::JS::Bridge


#endif // JS_Bridge_JSONEventSerializer_INCLUDED
