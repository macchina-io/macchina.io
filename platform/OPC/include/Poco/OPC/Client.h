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
#include "Poco/NumberFormatter.h"
#include <vector>
#include <string>


namespace Poco {
namespace OPC {
namespace open62541 {

#include "open62541.h"

}


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
		bool connect = true,
		const std::string& user = "",
		const std::string& pass = "",
		const std::string& proto = "opc.tcp");
		/// Creates the Client. If `connect` is true, connects to the server.

	~Client();
		/// Destroys the Client.

	void setServer(const std::string& server, int port, const std::string& proto = "opc.tcp");
		/// Sets the server url.

	void printEndpointURLs(std::ostream& os) const;
		/// Prints the list of server endpoint URLs.

	void connect(const std::string& user = "", const std::string& pass = "");
		/// Connects to the server.

	int getState() const;
	std::string getError(UInt32 val) const;

	const StringList& getEndpointURLs();

	std::string readServerDateTime();

	void disconnect();

	bool readBool(int nsIndex, const std::string& name) const;
	char readSByte(int nsIndex, const std::string& name) const;
	unsigned char readByte(int nsIndex, const std::string& name) const;
	Poco::Int16 readInt16(int nsIndex, const std::string& name) const;
	Poco::UInt16 readUint16(int nsIndex, const std::string& name) const;
	Poco::Int32 readInt32(int nsIndex, const std::string& name) const;
	Poco::UInt32 readUINT32(int nsIndex, const std::string& name) const;
	Poco::Int64 readInt64(int nsIndex, const std::string& name) const;
	Poco::UInt64 readUInt64(int nsIndex, const std::string& name) const;
	float readFloat(int nsIndex, const std::string& name) const;
	double readDouble(int nsIndex, const std::string& name) const;
	std::string readString(int nsIndex, const std::string& name) const;
	//std::string readDateTime(int nsIndex, const std::string& name) const;

private:
	template <typename T>
	T readValueAttribute(int nsIndex, const std::string& name, int type) const
	{
		using namespace open62541;
		T value = T();
		UA_Variant *val = UA_Variant_new();
		UA_StatusCode retval =
				UA_Client_readValueAttribute(_pClient, UA_NODEID_STRING(nsIndex, const_cast<char*>(name.c_str())), val);
		if(retval == UA_STATUSCODE_GOOD)
		{
			if(UA_Variant_isScalar(val) && val->type == &UA_TYPES[type])
			{
				value = *(T*)val->data;
			}
		}
		else
		{
			throw RuntimeException("Error in readValueAttribute(" + name + "):" +  getError(retval));
		}
		UA_Variant_delete(val);
		return value;
	}

	open62541::UA_Client* _pClient;
	std::string           _url;
	bool                  _connected;
	StringList            _endpointURLs;
};


//
// inlines
//

inline bool Client::readBool(int nsIndex, const std::string& name) const
{
	return readValueAttribute<bool>(nsIndex, name, OPC_TYPE_BOOLEAN);
}


inline char Client::readSByte(int nsIndex, const std::string& name) const
{
	return readValueAttribute<char>(nsIndex, name, OPC_TYPE_SBYTE);
}


inline unsigned char Client::readByte(int nsIndex, const std::string& name) const
{
	return readValueAttribute<unsigned char>(nsIndex, name, OPC_TYPE_BYTE);
}


inline Poco::Int16 Client::readInt16(int nsIndex, const std::string& name) const
{
	return readValueAttribute<Poco::Int16>(nsIndex, name, OPC_TYPE_INT16);
};


inline Poco::UInt16 Client::readUint16(int nsIndex, const std::string& name) const
{
	return readValueAttribute<Poco::UInt16>(nsIndex, name, OPC_TYPE_UINT16);
}


inline Poco::Int32 Client::readInt32(int nsIndex, const std::string& name) const
{
	return readValueAttribute<Poco::Int32>(nsIndex, name, OPC_TYPE_INT32);
}


inline Poco::UInt32 Client::readUINT32(int nsIndex, const std::string& name) const
{
	return readValueAttribute<Poco::UInt32>(nsIndex, name, OPC_TYPE_UINT32);
}


inline Poco::Int64 Client::readInt64(int nsIndex, const std::string& name) const
{
	return readValueAttribute<Poco::Int64>(nsIndex, name, OPC_TYPE_INT64);
}


inline Poco::UInt64 Client::readUInt64(int nsIndex, const std::string& name) const
{
	return readValueAttribute<Poco::UInt64>(nsIndex, name, OPC_TYPE_UINT64);
}


inline float Client::readFloat(int nsIndex, const std::string& name) const
{
	return readValueAttribute<float>(nsIndex, name, OPC_TYPE_FLOAT);
}


inline double Client::readDouble(int nsIndex, const std::string& name) const
{
	return readValueAttribute<double>(nsIndex, name, OPC_TYPE_DOUBLE);
}


inline std::string Client::readString(int nsIndex, const std::string& name) const
{
	return readValueAttribute<std::string>(nsIndex, name, OPC_TYPE_STRING);
}

/*TODO
inline std::string Client::readDateTime(int nsIndex, const std::string& name) const
{
	return readValueAttribute<std::string>(nsIndex, name, OPC_TYPE_DateTime);
}
*/

} } // namespace Poco::OPC


#endif // OPC_Client_INCLUDED
