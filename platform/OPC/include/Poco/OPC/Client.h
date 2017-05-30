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

	bool isReady() const;

	bool isConnected() const;

	bool isErrored() const;

	bool isFaulted() const;

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

	void writeBoolByName(int nsIndex, const std::string& name, bool value);
	void writeBoolByID(int nsIndex, int id, bool value);

	void writeSByteByName(int nsIndex, const std::string& name, unsigned char value);
	void writeSByteByID(int nsIndex, int id, unsigned char value);

	void writeByteByName(int nsIndex, const std::string& name, char value);
	void writeByteByID(int nsIndex, int id, char value);

	void writeInt16ByName(int nsIndex, const std::string& name, Int16 value);
	void writeInt16ByID(int nsIndex, int id, Int16 value);

	void writeUInt16ByName(int nsIndex, const std::string& name, UInt16 value);
	void writeUInt16ByID(int nsIndex, int id, UInt16 value);

	void writeInt32ByName(int nsIndex, const std::string& name, Int32 value);
	void writeInt32ByID(int nsIndex, int id, Int32 value);

	void writeUInt32ByName(int nsIndex, const std::string& name, UInt32 value);
	void writeUInt32ByID(int nsIndex, int id, UInt32 value);

	void writeInt64ByName(int nsIndex, const std::string& name, Int64 value);
	void writeInt64ByID(int nsIndex, int id, Int64 value);

	void writeUInt64ByName(int nsIndex, const std::string& name, UInt64 value);
	void writeUInt64ByID(int nsIndex, int id, UInt64 value);

	void writeFloatByName(int nsIndex, const std::string& name, float value);
	void writeFloatByID(int nsIndex, int id, float value);

	void writeDoubleByName(int nsIndex, const std::string& name, double value);
	void writeDoubleByID(int nsIndex, int id, double value);

	void writeStringByName(int nsIndex, const std::string& name, const std::string& value);
	void writeStringByID(int nsIndex, int id, const std::string& value);
/*
	void writeDateTimeByName(int nsIndex, const std::string& name, Int64 value);
	void writeDateTimeByID(int nsIndex, int id, Int64 value);

	void writeStrDateTimeByName(int nsIndex, const std::string& name, boconst std::string& ol value);
	void writeStrDateTimeByID(int nsIndex, int id, const std::string&  value);
*/

	template <typename I, typename T>
	void write(int nsIndex, I id, const T& value)
	{
		writeValue(nsIndex, id, value);
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

	// reading
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
		else if(val->arrayLength > 0)
		{
			throw Poco::NotImplementedException("OPC::Client::getValue(): Retrieval of array values not implemented");
		}
		else
		{
			std::ostringstream os;
			os << "OPC::Client::getValue(): Retrieval of a ";
			if(val->type)
			{
				if(val->type->typeIndex)
				{
					os << "non-suported value type (" << val->type->typeIndex << ") attempted";
					throw Poco::NotImplementedException(os.str());
				}
			}
			else
			{
				os << "NULL type attempted";
				throw Poco::NullPointerException(os.str());
			}
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

	// writing
	open62541::UA_StatusCode writeValueAttribute(int nsIndex, const Poco::Dynamic::Var& id, open62541::UA_Variant* val) const
	{
		using namespace open62541;
		if(id.isString())
		{
			return UA_Client_writeValueAttribute(_pClient, UA_NODEID_STRING(nsIndex, const_cast<char*>(id.toString().c_str())), val);
		}
		else
		{
			return UA_Client_writeValueAttribute(_pClient, UA_NODEID_NUMERIC(nsIndex, id), val);
		}
	}

	template <typename T, typename I>
	void writeValue(int nsIndex, const I& id, const T& value)
	{
		using namespace open62541;
		UA_Variant* var = UA_Variant_new();
		Poco::Dynamic::Var val(value);
		UA_StatusCode retval;
		if(val.isString())
		{
			std::string strVal = val.toString();
			UA_String uaStr;
			uaStr.data = (UA_Byte*) strVal.data();
			uaStr.length = strVal.length();
			UA_Variant_setScalarCopy(var, &uaStr, &UA_TYPES[getUAType(strVal)]);
			retval = writeValueAttribute(nsIndex, id, var);
		}
		else
		{
			UA_Variant_setScalarCopy(var, &value, &UA_TYPES[getUAType(value)]);
			retval = writeValueAttribute(nsIndex, id, var);
		}
		UA_Variant_delete(var);
		if(retval != UA_STATUSCODE_GOOD)
		{
			std::ostringstream os;
			os << "Error in OPC::Client::writeValueAttribute(" << val.toString() << "): " << getError(retval);
			throw RuntimeException(os.str());
		}
	}

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

inline void Client::setURL(const std::string& server, int port, const std::string& proto)
{
	_url = proto;
	_url.append("://").append(server).append(1, ':').append(NumberFormatter::format(port));
}


inline void Client::setEndpointURLs(const StringList& strList)
{
	_endpointURLs = strList;
}


//
// state
//


inline int Client::getState() const
{
	return UA_Client_getState(_pClient);
}


inline bool Client::isReady() const
{
	return (getState() == OPC_CLIENT_READY || isConnected()) && !isErrored() && !isFaulted();
}


inline bool Client::isConnected() const
{
	return getState() == OPC_CLIENT_CONNECTED;
}


inline bool Client::isErrored() const
{
	return getState() == OPC_CLIENT_ERRORED;
}


inline bool Client::isFaulted() const
{
	return getState() == OPC_CLIENT_FAULTED;
}


//
// reading
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


inline Poco::DateTime Client::readDateTimeByName(int nsIndex, const std::string& name) const
{
	return Poco::OPC::DateTime(readInt64ByName(nsIndex, name));
}


inline Poco::DateTime Client::readDateTimeByID(int nsIndex, int id) const
{
	return Poco::OPC::DateTime(readInt64ByID(nsIndex, id));
}


inline std::string Client::readStrDateTimeByName(int nsIndex, const std::string& name) const
{
	return Poco::OPC::DateTime(readInt64ByName(nsIndex, name)).toString();
}


inline std::string Client::readStrDateTimeByID(int nsIndex, int id) const
{
	Int64 ts = readInt64ByID(nsIndex, id);
	return Poco::OPC::DateTime(ts).toString();
}


//
// writing
//

inline void Client::writeBoolByName(int nsIndex, const std::string& name, bool value)
{
	writeValue(nsIndex, name, value);
}


inline void Client::writeBoolByID(int nsIndex, int id, bool value)
{
	writeValue(nsIndex, id, value);
}


inline void Client::writeSByteByName(int nsIndex, const std::string& name, unsigned char value)
{
	writeValue(nsIndex, name, value);
}


inline void Client::writeSByteByID(int nsIndex, int id, unsigned char value)
{
	writeValue(nsIndex, id, value);
}


inline void Client::writeByteByName(int nsIndex, const std::string& name, char value)
{
	writeValue(nsIndex, name, value);
}


inline void Client::writeByteByID(int nsIndex, int id, char value)
{
	writeValue(nsIndex, id, value);
}


inline void Client::writeInt16ByName(int nsIndex, const std::string& name, Int16 value)
{
	writeValue(nsIndex, name, value);
}


inline void Client::writeInt16ByID(int nsIndex, int id, Int16 value)
{
	writeValue(nsIndex, id, value);
}


inline void Client::writeUInt16ByName(int nsIndex, const std::string& name, UInt16 value)
{
	writeValue(nsIndex, name, value);
}


inline void Client::writeUInt16ByID(int nsIndex, int id, UInt16 value)
{
	writeValue(nsIndex, id, value);
}


inline void Client::writeInt32ByName(int nsIndex, const std::string& name, Int32 value)
{
	writeValue(nsIndex, name, value);
}


inline void Client::writeInt32ByID(int nsIndex, int id, Int32 value)
{
	writeValue(nsIndex, id, value);
}


inline void Client::writeUInt32ByName(int nsIndex, const std::string& name, UInt32 value)
{
	writeValue(nsIndex, name, value);
}


inline void Client::writeUInt32ByID(int nsIndex, int id, UInt32 value)
{
	writeValue(nsIndex, id, value);
}


inline void Client::writeInt64ByName(int nsIndex, const std::string& name, Int64 value)
{
	writeValue(nsIndex, name, value);
}


inline void Client::writeInt64ByID(int nsIndex, int id, Int64 value)
{
	writeValue(nsIndex, id, value);
}


inline void Client::writeUInt64ByName(int nsIndex, const std::string& name, UInt64 value)
{
	writeValue(nsIndex, name, value);
}


inline void Client::writeUInt64ByID(int nsIndex, int id, UInt64 value)
{
	writeValue(nsIndex, id, value);
}


inline void Client::writeFloatByName(int nsIndex, const std::string& name, float value)
{
	writeValue(nsIndex, name, value);
}


inline void Client::writeFloatByID(int nsIndex, int id, float value)
{
	writeValue(nsIndex, id, value);
}


inline void Client::writeDoubleByName(int nsIndex, const std::string& name, double value)
{
	writeValue(nsIndex, name, value);
}


inline void Client::writeDoubleByID(int nsIndex, int id, double value)
{
	writeValue(nsIndex, id, value);
}


inline void Client::writeStringByName(int nsIndex, const std::string& name, const std::string& value)
{
	writeValue(nsIndex, name, value);
}


inline void Client::writeStringByID(int nsIndex, int id, const std::string& value)
{
	writeValue(nsIndex, id, value);
}


/*
	void Client::writeDateTimeByName(int nsIndex, const std::string& name, Int64 value) const;
	void Client::writeDateTimeByID(int nsIndex, int id, Int64 value) const;

	void Client::writeStrDateTimeByName(int nsIndex, const std::string& name, boconst std::string& ol value) const;
	void Client::writeStrDateTimeByID(int nsIndex, int id, const std::string&  value) const;
*/


} } // namespace Poco::OPC


#endif // OPC_Client_INCLUDED
