//
// BinaryDeserializer.h
//
// $Id: //poco/1.7/RemotingNG/include/Poco/RemotingNG/BinaryDeserializer.h#4 $
//
// Library: RemotingNG
// Package: Serialization
// Module:  BinaryDeserializer
//
// Definition of the Deserializer class.
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef RemotingNG_BinaryDeserializer_INCLUDED
#define RemotingNG_BinaryDeserializer_INCLUDED


#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/BinaryReader.h"
#include <stack>
#include <memory>


namespace Poco {
namespace RemotingNG {


class RemotingNG_API BinaryDeserializer: public Deserializer
	/// A generic Deserializer using a proprietary binary
	/// serialization format based on the Poco::BinaryReader
	/// class. The BinaryDeserializer is used in conjunction
	/// with the BinarySerializer class.
	///
	/// Please see the BinarySerializer class for more information.
{
public:
	BinaryDeserializer();
		/// Creates a BinaryDeserializer.

	~BinaryDeserializer();
		/// Destroys the BinaryDeserializer.

	void deserializeEndPoint(std::string& oid, std::string& tid);
		/// Serializes the object and type ID of the service object.

	template <typename T>
	T deserializeToken()
		/// Deserializes the given value, which must be a type directly supported
		/// by Poco::BinaryReader.
	{
		T t;
		(*this->_pReader) >> t;
		return t;
	}

	// Deserializer
	SerializerBase::MessageType findMessage(std::string& name);
	void deserializeMessageBegin(const std::string& name, SerializerBase::MessageType type);
	void deserializeMessageEnd(const std::string& name, SerializerBase::MessageType type);
	bool deserializeStructBegin(const std::string& name, bool isMandatory);
	void deserializeStructEnd(const std::string& name);
	bool deserializeSequenceBegin(const std::string& name, bool isMandatory, Poco::UInt32& lengthHint);
	void deserializeSequenceEnd(const std::string& name);
	bool deserializeNullableBegin(const std::string& name, bool isMandatory, bool& isNull);
	void deserializeNullableEnd(const std::string& name);
	bool deserialize(const std::string& name, bool isMandatory, Poco::Int8& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::UInt8& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::Int16& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::UInt16& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::Int32& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::UInt32& value);
	bool deserialize(const std::string& name, bool isMandatory, long& value);
	bool deserialize(const std::string& name, bool isMandatory, unsigned long& value);
#ifndef POCO_LONG_IS_64_BIT
	bool deserialize(const std::string& name, bool isMandatory, Poco::Int64& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::UInt64& value);
#endif
	bool deserialize(const std::string& name, bool isMandatory, float& value);
	bool deserialize(const std::string& name, bool isMandatory, double& value);
	bool deserialize(const std::string& name, bool isMandatory, bool& value);
	bool deserialize(const std::string& name, bool isMandatory, char& value);
	bool deserialize(const std::string& name, bool isMandatory, std::string& value);
	bool deserialize(const std::string& name, bool isMandatory, std::vector<char>& value);

protected:
	void resetImpl();
	void setupImpl(std::istream& istr);

private:
	bool handleVector();
	bool checkStream();
	void findMessageImpl();

#if __cplusplus < 201103L
	typedef std::auto_ptr<Poco::BinaryReader> BinaryReaderPtr;
#else
	typedef std::unique_ptr<Poco::BinaryReader> BinaryReaderPtr;
#endif
	typedef std::pair<int, int> LengthLevelPair;
	typedef std::stack<LengthLevelPair> LevelLengthVec;

	BinaryReaderPtr _pReader;
	std::string _messageName;
	SerializerBase::MessageType _messageType;
	LevelLengthVec _sequenceLengths;
	int _curLevel;
};


//
// inlines
//
inline bool BinaryDeserializer::checkStream()
{
	if (_pReader->good())
		return true;
	else
		throw DeserializerException("unexpected end of, or bad stream");
}


} } // namespace Poco::RemotingNG


#endif // RemotingNG_BinaryDeserializer_INCLUDED
