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
#include <iomanip>
#include <numeric>
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
		int port = OPC_STANDARD_PORT,
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

	void setURL(const std::string& server, int port = OPC_STANDARD_PORT, const std::string& proto = "opc.tcp");
		/// Sets the server url.

	void printEndpointURLs(std::ostream& os) const;
		/// Prints the list of server endpoint URLs.

	void printServerObjects(std::ostream& os)
	{
		printBrowse(os);
	}

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

	template <typename T>
	Poco::Dynamic::Var read(int nsIndex, const T& id) const
	{
		using namespace open62541;
		UA_Variant* val = UA_Variant_new();
		UA_StatusCode retval = readValueAttribute(nsIndex, id, val);
		if(retval == UA_STATUSCODE_GOOD)
		{
			if(UA_Variant_isScalar(val))
			{
				UInt16 type = val->type->typeIndex;
				switch(type)
				{
					case UA_TYPES_BOOLEAN:  { bool value;   return getValue(val, value); }
					case UA_TYPES_SBYTE:    { Int8 value;   return getValue(val, value); }
					case UA_TYPES_BYTE:     { UInt8 value;  return getValue(val, value); }
					case UA_TYPES_INT16:    { Int16 value;  return getValue(val, value); }
					case UA_TYPES_UINT16:   { UInt16 value; return getValue(val, value); }
					case UA_TYPES_INT32:    { Int32 value;  return getValue(val, value); }
					case UA_TYPES_UINT32:   { UInt32 value; return getValue(val, value); }
					case UA_TYPES_INT64:    { Int64 value;  return getValue(val, value); }
					case UA_TYPES_UINT64:   { UInt64 value; return getValue(val, value); }
					case UA_TYPES_FLOAT:    { float value;  return getValue(val, value); }
					case UA_TYPES_DOUBLE:   { double value; return getValue(val, value); }
					case UA_TYPES_DATETIME:
					{
						UA_DateTime dt;
						getValue<UA_DateTime>(val, dt);
						OPC::DateTime odt(dt);
						return odt;
					}
					case UA_TYPES_STRING:
					{
						std::string value;
						UA_String uaStr;
						getValue<UA_String>(val, uaStr);
						value = STDString(uaStr);
						return value;
					}
					default:
						UA_Variant_delete(val);
						throw Poco::NotImplementedException("Type not supported:" + Poco::NumberFormatter::format(type));
				}
			}
			else // TODO: arrays
			{
				UA_Variant_delete(val);
				throw Poco::NotImplementedException("OPC::Client::readValueAttribute(): Retrieval of array values not implemented");
			}
		}
		else
		{
			UA_Variant_delete(val);
			std::ostringstream os;
			os << "Error in OPC::Client::readValueAttribute(" << id << "): " << getError(retval);
			throw RuntimeException(os.str());
		}
		UA_Variant_delete(val);
		return 0;
	}

private:
	void printBrowse(std::ostream& os, int type = UA_NS0ID_OBJECTSFOLDER, std::vector<int> colWidths = std::vector<int>())
	{
		using namespace open62541;

		if(colWidths.size() < 1) colWidths.push_back(11);
		if(colWidths.size() < 2) colWidths.push_back(20);
		if(colWidths.size() < 3) colWidths.push_back(36);
		if(colWidths.size() < 4) colWidths.push_back(36);

		UA_BrowseRequest bReq;
		UA_BrowseRequest_init(&bReq);
		bReq.requestedMaxReferencesPerNode = 0;
		bReq.nodesToBrowse = UA_BrowseDescription_new();
		bReq.nodesToBrowseSize = 1;
		bReq.nodesToBrowse[0].nodeId = UA_NODEID_NUMERIC(0, type);
		bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; // return everything
		UA_BrowseResponse bResp = UA_Client_Service_browse(_pClient, bReq);
		os << std::setw(colWidths.at(0)) << "[NAMESPACE]" << std::setw(colWidths.at(1)) << "[NODEID]" <<
			std::setw(colWidths.at(2)) << "[BROWSE NAME]" << std::setw(colWidths.at(3)) << "[DISPLAY NAME]" << std::endl;
		std::string line(std::accumulate(colWidths.begin(), colWidths.end(), 0), '-');
		os << line << std::endl;
		for (size_t i = 0; i < bResp.resultsSize; ++i)
		{
			for (size_t j = 0; j < bResp.results[i].referencesSize; ++j)
			{
				UA_ReferenceDescription *ref = &(bResp.results[i].references[j]);
				if (ref->nodeId.nodeId.identifierType == UA_NODEIDTYPE_NUMERIC)
				{
					os << std::setw(colWidths.at(0)) << ref->browseName.namespaceIndex <<
						std::setw(colWidths.at(1)) << ref->nodeId.nodeId.identifier.numeric <<
						std::setw(colWidths.at(2)) << std::string((char*) ref->browseName.name.data, ref->browseName.name.length) <<
						std::setw(colWidths.at(3)) << std::string((char*) ref->displayName.text.data, ref->displayName.text.length) <<
						std::endl;
				}
				else if (ref->nodeId.nodeId.identifierType == UA_NODEIDTYPE_STRING)
				{
					os << std::setw(colWidths.at(0)) << ref->browseName.namespaceIndex << std::setw(11) <<
						std::setw(colWidths.at(1)) << std::string((char*) ref->nodeId.nodeId.identifier.string.data,
							ref->nodeId.nodeId.identifier.string.length) <<
						std::setw(colWidths.at(2)) << std::string((char*) ref->browseName.name.data, ref->browseName.name.length) << 
						std::setw(colWidths.at(3)) << std::string((char*) ref->displayName.text.data, ref->displayName.text.length) <<
						std::endl;
				}
				// TODO: distinguish further types
			}
		}
		UA_BrowseRequest_deleteMembers(&bReq);
		UA_BrowseResponse_deleteMembers(&bResp);
	}

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
	const T& getValue(open62541::UA_Variant* val, T& value) const
	{
		using namespace open62541;
		if(UA_Variant_isScalar(val))
		{
			value = *(T*)val->data;
		}
		else // TODO: arrays
		{
			throw Poco::NotImplementedException("OPC::Client::getValue(): Retrieval of array values not implemented");
		}
		return value;
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
			os << "Error in OPC::Client::readValueAttribute(" << id << "): " << getError(retval);
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
			os << "Error in OPC::Client::readValueAttribute(" << id << "): " << getError(retval);
			throw RuntimeException(os.str());
		}
		UA_Variant_delete(val);
		return value;
	}

	void getDateTime(Poco::OPC::DateTime& dt);

	open62541::UA_Client*         _pClient;
	std::string                   _url;
	StringList                    _endpointURLs;
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
