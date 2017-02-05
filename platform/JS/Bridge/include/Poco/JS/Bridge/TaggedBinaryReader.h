//
// TaggedBinaryReader.h
//
// $Id$
//
// Library: JSBridge
// Package: Bridge
// Module:  TaggedBinaryReader
//
// Definition of the TaggedBinaryReader class.
//
// Copyright (c) 2013-2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef JS_Bridge_TaggedBinaryReader_INCLUDED
#define JS_Bridge_TaggedBinaryReader_INCLUDED


#include "Poco/JS/Bridge/Bridge.h"
#include "Poco/JS/Bridge/Serializer.h"
#include "Poco/RemotingNG/Deserializer.h"


namespace Poco {
namespace JS {
namespace Bridge {


class JSBridge_API TaggedBinaryReader
	/// This class creates a JavaScript object from a tagged binary stream produced
	/// by TaggedBinarySerializer.
{
public:
	TaggedBinaryReader(v8::Isolate* pIsolate);
		/// Creates the TaggedBinaryReader.
		
	~TaggedBinaryReader();
		/// Destroys the TaggedBinaryReader.
		
	v8::Local<v8::Object> read(std::istream& istream);
		/// Reads a JavaScript object from the given stream.

protected:
	template <typename T>
	void read(Poco::RemotingNG::Deserializer& deserializer)
	{
		std::string name;
		std::string unused;
		deserializer.deserialize(unused, true, name);
		T value;
		deserializer.deserialize(name, true, value);
		_serializer.serialize(name, value); 
	}
	
private:
	Serializer _serializer;
};


} } } // namespace Poco::JS::Bridge


#endif // JS_Bridge_TaggedBinaryReader_INCLUDED
