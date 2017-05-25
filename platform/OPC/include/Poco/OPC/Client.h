//
// Client.h
//
// $Id$
//
// Library: OPC
// Package: OPC
// Module:  Client
//
// Definition of the Client class.
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef OPC_Client_INCLUDED
#define OPC_Client_INCLUDED


#include "Poco/OPC/OPC.h"
#include "Poco/OPC/Types.h"
#include "Poco/DateTime.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Dynamic/Var.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>


namespace Poco {
namespace OPC {
namespace open62541 {

#include "open62541.h"

}


class DateTime;


class OPC_API Client
	/// This class represents an OPC Client.
{
public:
	typedef std::vector<std::string> StringList;

	// Client statuses
	static const int OPC_CLIENT_READY;
	static const int OPC_CLIENT_CONNECTED;
	static const int OPC_CLIENT_FAULTED;
	static const int OPC_CLIENT_ERRORED;

	// Server statuses
	static const int OPC_SERVER_TIME;

	// Types
	static const int OPC_TYPE_BOOLEAN;
	static const int OPC_TYPE_SBYTE;
	static const int OPC_TYPE_BYTE;
	static const int OPC_TYPE_INT16;
	static const int OPC_TYPE_UINT16;
	static const int OPC_TYPE_INT32;
	static const int OPC_TYPE_UINT32;
	static const int OPC_TYPE_INT64;
	static const int OPC_TYPE_UINT64;
	static const int OPC_TYPE_FLOAT;
	static const int OPC_TYPE_DOUBLE;
	static const int OPC_TYPE_STRING;
	static const int OPC_TYPE_DATETIME;

	Client();
		/// Creates the Client.

	Client(const std::string& server,
		int port = 16664,
		const std::string& user = "",
		const std::string& pass = "",
		bool doConnect = true,
		const std::string& proto = "opc.tcp");
		/// Creates the Client. If `doConnect` is true, connects to the server.

	~Client();
		/// Destroys the Client.

	Client(const Client& other);
		/// Creates the Client.

	Client& operator = (Client& other);
		/// Assignment operator.

	void init(bool doConnect);
		/// Initializes the client. If `doConnect` is true, connects to the server.

	void setURL(const std::string& server, int port, const std::string& proto = "opc.tcp");
		/// Sets the server url.

	void printEndpointURLs(std::ostream& os) const;
		/// Prints the list of server endpoint URLs.

	void connect(const std::string& user = "", const std::string& pass = "");
		/// Connects to the server.

	int getState() const;

	const StringList& getEndpointURLs();
	void setEndpointURLs(const StringList& strList);

	Poco::DateTime readServerDateTime();
	std::string readServerDateTimeStr();

	void disconnect();

	bool readBoolByName(int nsIndex, const std::string& name) const;
	bool readBoolByID(int nsIndex, int id) const;

	char readSByteByName(int nsIndex, const std::string& name) const;
	char readSByteByID(int nsIndex, int id) const;

	unsigned char readByteByName(int nsIndex, const std::string& name) const;
	unsigned char readByteByID(int nsIndex, int id) const;

	Poco::Int16 readInt16ByName(int nsIndex, const std::string& name) const;
	Poco::Int16 readInt16ByID(int nsIndex, int id) const;

	Poco::UInt16 readUInt16ByName(int nsIndex, const std::string& name) const;
	Poco::UInt16 readUInt16ByID(int nsIndex, int id) const;

	Poco::Int32 readInt32ByName(int nsIndex, const std::string& name) const;
	Poco::Int32 readInt32ByID(int nsIndex, int id) const;

	Poco::UInt32 readUInt32ByName(int nsIndex, const std::string& name) const;
	Poco::UInt32 readUInt32ByID(int nsIndex, int id) const;

	Poco::Int64 readInt64ByName(int nsIndex, const std::string& name) const;
	Poco::Int64 readInt64ByID(int nsIndex, int id) const;

	Poco::UInt64 readUInt64ByName(int nsIndex, const std::string& name) const;
	Poco::UInt64 readUInt64ByID(int nsIndex, int id) const;

	float readFloatByName(int nsIndex, const std::string& name) const;
	float readFloatByID(int nsIndex, int id) const;

	double readDoubleByName(int nsIndex, const std::string& name) const;
	double readDoubleByID(int nsIndex, int id) const;

	std::string readStringByName(int nsIndex, const std::string& name) const;
	std::string readStringByID(int nsIndex, int id) const;

	Poco::DateTime readDateTimeByName(int nsIndex, const std::string& name) const;
	Poco::DateTime readDateTimeByID(int nsIndex, int id) const;

	std::string readStrDateTimeByName(int nsIndex, const std::string& name) const;
	std::string readStrDateTimeByID(int nsIndex, int id) const;

private:
	open62541::UA_StatusCode readValueAttribute(int nsIndex, const Poco::Dynamic::Var& id, open62541::UA_Variant* val) const
	{
		using namespace open62541;
		if(id.isString())
		{
			return UA_Client_readValueAttribute(_pClient, UA_NODEID_STRING(nsIndex, const_cast<char*>(id.toString().c_str())), val);
		}
		else
		{
			return UA_Client_readValueAttribute(_pClient, UA_NODEID_NUMERIC(nsIndex, id), val);
		}
	}

	template <typename T>
	void getValue(open62541::UA_Variant* val, T& value) const
	{
		using namespace open62541;
		if(UA_Variant_isScalar(val))
		{
			value = *(T*)val->data;
		}
		else // TODO: arrays
		{
			throw Poco::NotImplementedException("OPC::getValue(): Retrieval of array values not implemented");
		}
	}

	template <typename T, typename I>
	T readValueAttribute(int nsIndex, const I& id) const
	{
		using namespace open62541;
		T value = T();
		UA_Variant* val = UA_Variant_new();
		UA_StatusCode retval = readValueAttribute(nsIndex, id, val);
		if(retval == UA_STATUSCODE_GOOD)
		{
			getValue(val, value);
		}
		else
		{
			UA_Variant_delete(val);
			std::ostringstream os;
			os << "Error in OPC::readValueAttribute(" << id << "): " << getError(retval);
			throw RuntimeException(os.str());
		}
		UA_Variant_delete(val);
		return value;
	}

	template <typename I>
	std::string readStringValueAttribute(int nsIndex, const I& id) const
	{
		using namespace open62541;
		UA_Variant* val = UA_Variant_new();
		std::string value;
		UA_StatusCode retval = readValueAttribute(nsIndex, id, val);
		if(retval == UA_STATUSCODE_GOOD)
		{
			UA_String uaStr;
			getValue<UA_String>(val, uaStr);
			value = STDString(uaStr);
		}
		else
		{
			UA_Variant_delete(val);
			std::ostringstream os;
			os << "Error in OPC::readValueAttribute(" << id << "): " << getError(retval);
			throw RuntimeException(os.str());
		}
		UA_Variant_delete(val);
		return value;
	}

	void getDateTime(Poco::OPC::DateTime& dt);

	open62541::UA_Client* _pClient;
	std::string           _url;
	StringList            _endpointURLs;
	// following members needed to copy-construct the client (remoting requirement)
	std::string _server;
	int _port;
	std::string _user;
	std::string _pass;
	std::string _proto;
};


//
// inlines
//

inline bool Client::readBoolByName(int nsIndex, const std::string& name) const
{
	return readValueAttribute<bool>(nsIndex, name);
}


inline bool Client::readBoolByID(int nsIndex, int id) const
{
	return readValueAttribute<bool>(nsIndex, id);
}


inline char Client::readSByteByName(int nsIndex, const std::string& name) const
{
	return readValueAttribute<char>(nsIndex, name);
}


inline char Client::readSByteByID(int nsIndex, int id) const
{
	return readValueAttribute<char>(nsIndex, id);
}


inline unsigned char Client::readByteByName(int nsIndex, const std::string& name) const
{
	return readValueAttribute<unsigned char>(nsIndex, name);
}


inline unsigned char Client::readByteByID(int nsIndex, int id) const
{
	return readValueAttribute<unsigned char>(nsIndex, id);
}


inline Poco::Int16 Client::readInt16ByName(int nsIndex, const std::string& name) const
{
	return readValueAttribute<Poco::Int16>(nsIndex, name);
}


inline Poco::Int16 Client::readInt16ByID(int nsIndex, int id) const
{
	return readValueAttribute<Poco::Int16>(nsIndex, id);
}


inline Poco::UInt16 Client::readUInt16ByName(int nsIndex, const std::string& name) const
{
	return readValueAttribute<Poco::UInt16>(nsIndex, name);
}


inline Poco::UInt16 Client::readUInt16ByID(int nsIndex, int id) const
{
	return readValueAttribute<Poco::UInt16>(nsIndex, id);
}


inline Poco::Int32 Client::readInt32ByName(int nsIndex, const std::string& name) const
{
	return readValueAttribute<Poco::Int32>(nsIndex, name);
}


inline Poco::Int32 Client::readInt32ByID(int nsIndex, int id) const
{
	return readValueAttribute<Poco::Int32>(nsIndex, id);
}


inline Poco::UInt32 Client::readUInt32ByName(int nsIndex, const std::string& name) const
{
	return readValueAttribute<Poco::UInt32>(nsIndex, name);
}


inline Poco::UInt32 Client::readUInt32ByID(int nsIndex, int id) const
{
	return readValueAttribute<Poco::UInt32>(nsIndex, id);
}


inline Poco::Int64 Client::readInt64ByName(int nsIndex, const std::string& name) const
{
	return readValueAttribute<Poco::Int64>(nsIndex, name);
}


inline Poco::Int64 Client::readInt64ByID(int nsIndex, int id) const
{
	return readValueAttribute<Poco::Int64>(nsIndex, id);
}


inline Poco::UInt64 Client::readUInt64ByName(int nsIndex, const std::string& name) const
{
	return readValueAttribute<Poco::UInt64>(nsIndex, name);
}


inline Poco::UInt64 Client::readUInt64ByID(int nsIndex, int id) const
{
	return readValueAttribute<Poco::UInt64>(nsIndex, id);
}


inline float Client::readFloatByName(int nsIndex, const std::string& name) const
{
	return readValueAttribute<float>(nsIndex, name);
}


inline float Client::readFloatByID(int nsIndex, int id) const
{
	return readValueAttribute<float>(nsIndex, id);
}


inline double Client::readDoubleByName(int nsIndex, const std::string& name) const
{
	return readValueAttribute<double>(nsIndex, name);
}


inline double Client::readDoubleByID(int nsIndex, int id) const
{
	return readValueAttribute<double>(nsIndex, id);
}


inline std::string Client::readStringByName(int nsIndex, const std::string& name) const
{
	return readStringValueAttribute(nsIndex, name);
}


inline std::string Client::readStringByID(int nsIndex, int id) const
{
	return readStringValueAttribute(nsIndex, id);
}


} } // namespace Poco::OPC


#endif // OPC_Client_INCLUDED
