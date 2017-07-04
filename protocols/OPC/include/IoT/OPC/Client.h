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


#ifndef IoT_OPC_Client_INCLUDED
#define IoT_OPC_Client_INCLUDED


#include "IoT/OPC/OPC.h"
#include "IoT/OPC/Types.h"
#include "IoT/OPC/TypeCache.h"
#include "IoT/OPC/DateTime.h"
#include "IoT/OPC/String.h"
#include "IoT/OPC/Variant.h"
#include "Poco/Logger.h"
#include "Poco/Message.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/AutoPtr.h"
#include "Poco/DateTime.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"
#include "Poco/Dynamic/Var.h"
#include "open62541.h"
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <unordered_map>


namespace IoT {
namespace OPC {


class DateTime;


class OPC_API Client
	/// This class represents an OPC Client.
	///
	/// The client can operate in a type-safe mode; this mode is default
	/// and can be disabled. When enabled, it ensures that client never
	/// writes a data type different from the original type as set on the
	/// server side; it implies type-caching, which occurs initially at
	/// connect time and subsequently, every time when data type for the
	/// value attribute being set is not cached.

{
public:
	typedef std::vector<std::string> StringList;

	static const int OPC_NODE_NOT_FOUND = -1;

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

	Client(const std::string& server,
		int port = OPC_STANDARD_PORT,
		Poco::Message::Priority prio = Poco::Message::PRIO_INFORMATION);
		/// Creates the Client.

	Client(const std::string& server,
		Poco::Logger* logger,
		int port = OPC_STANDARD_PORT,
		const std::string& user = "",
		const std::string& pass = "",
		bool doConnect = true,
		bool typeSafe = true,
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

	void connect(const std::string& user = "", const std::string& pass = "");
		/// Connects to the server.

	void disconnect();
		/// Disconnects from the server.


	//
	// config
	//

	bool getTypeSafe() const;
		/// Returns true if client is caching server types.

	void setTypeSafe(bool safe = true);
		/// Sets the type-safe flag. When this flag is set
		/// client will cache server data types and never write a
		/// value attribute of a type different from the original
		/// type set on the server side. Caching, however, imposes
		/// a performance penalty associated with server-side value
		/// attributes data type detection.


	//
	// state
	//

	int getState() const;
		/// Returns client state.

	bool isReady() const;
		/// Returns true if client is ready.

	bool isConnected() const;
		/// Returns true if client is connected.

	bool isErrored() const;
		/// Returns true if client has errored.

	bool isFaulted() const;
		/// Returns true if client has faulted.


	//
	// reading
	//

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

	Poco::UInt64 readTimestampByName(int nsIndex, const std::string& name) const;
	Poco::UInt64 readTimestampByID(int nsIndex, int id) const;

	template <typename T>
	Poco::Dynamic::Var read(int nsIndex, const T& id) const
	{
		OPC::Variant val;
		UA_StatusCode retval = readValueAttribute(nsIndex, id, val);
		if(retval == UA_STATUSCODE_GOOD)
		{
			UInt16 type = val.type().typeIndex;
			if(UA_Variant_isScalar(val))
			{
				switch(type)
				{
					case UA_TYPES_BOOLEAN:  { bool         value; return getValue(val, value); }
					case UA_TYPES_SBYTE:    { Poco::Int8   value; return getValue(val, value); }
					case UA_TYPES_BYTE:     { Poco::UInt8  value; return getValue(val, value); }
					case UA_TYPES_INT16:    { Poco::Int16  value; return getValue(val, value); }
					case UA_TYPES_UINT16:   { Poco::UInt16 value; return getValue(val, value); }
					case UA_TYPES_INT32:    { Poco::Int32  value; return getValue(val, value); }
					case UA_TYPES_UINT32:   { Poco::UInt32 value; return getValue(val, value); }
					case UA_TYPES_INT64:    { Poco::Int64  value; return getValue(val, value); }
					case UA_TYPES_UINT64:   { Poco::UInt64 value; return getValue(val, value); }
					case UA_TYPES_FLOAT:    { float        value; return getValue(val, value); }
					case UA_TYPES_DOUBLE:   { double       value; return getValue(val, value); }
					case UA_TYPES_DATETIME:
					{
						UA_DateTime dt;
						getValue(val, dt);
						OPC::DateTime odt(dt);
						return odt;
					}
					case UA_TYPES_STRING:
					{
						std::string value;
						UA_String uaStr;
						getValue(val, uaStr);
						value = STDString(uaStr);
						return value;
					}
					default:
						throw Poco::NotImplementedException("Type not supported:" + Poco::NumberFormatter::format(type));
				}
			}
			else
			{
				switch(type)
				{
					case UA_TYPES_BOOLEAN:  { std::vector<bool> value;         return getArrayValue(val, value); }
					case UA_TYPES_SBYTE:    { std::vector<Poco::Int8> value;   return getArrayValue(val, value); }
					case UA_TYPES_BYTE:     { std::vector<Poco::UInt8> value;  return getArrayValue(val, value); }
					case UA_TYPES_INT16:    { std::vector<Poco::Int16> value;  return getArrayValue(val, value); }
					case UA_TYPES_UINT16:   { std::vector<Poco::UInt16> value; return getArrayValue(val, value); }
					case UA_TYPES_INT32:    { std::vector<Poco::Int32> value;  return getArrayValue(val, value); }
					case UA_TYPES_UINT32:   { std::vector<Poco::UInt32> value; return getArrayValue(val, value); }
					case UA_TYPES_INT64:    { std::vector<Poco::Int64> value;  return getArrayValue(val, value); }
					case UA_TYPES_UINT64:   { std::vector<Poco::UInt64> value; return getArrayValue(val, value); }
					case UA_TYPES_FLOAT:    { std::vector<float> value;        return getArrayValue(val, value); }
					case UA_TYPES_DOUBLE:   { std::vector<double> value;       return getArrayValue(val, value); }
					case UA_TYPES_DATETIME:
					{
						std::vector<UA_DateTime> dt;
						getArrayValue(val, dt);
						std::vector<OPC::DateTime> odt;
						for(std::vector<UA_DateTime>::const_iterator it = dt.begin(),
							end = dt.end(); it != end; ++it)
						{
							odt.push_back(OPC::DateTime(*it));
						}
						return odt;
					}
					case UA_TYPES_STRING:
					{
						std::vector<UA_String> uaStr;
						getArrayValue(val, uaStr);
						std::vector<std::string> values;
						for(std::vector<UA_String>::const_iterator it = uaStr.begin(),
							end = uaStr.end(); it != end; ++it)
						{
							values.push_back(STDString(*it));
						}
						return values;
					}
					default:
						throw Poco::NotImplementedException("Type not supported:" + Poco::NumberFormatter::format(type));
				}
			}
		}
		else
		{
			std::ostringstream os;
			os << "Error in OPC::Client::readValueAttribute(" << id << "): " << getError(retval);
			throw Poco::RuntimeException(os.str());
		}
		return 0;
	}

	//
	// writing
	//

	void writeBoolByName(int nsIndex, const std::string& name, bool value);
	void writeBoolByID(int nsIndex, int id, bool value);

	void writeSByteByName(int nsIndex, const std::string& name, unsigned char value);
	void writeSByteByID(int nsIndex, int id, unsigned char value);

	void writeByteByName(int nsIndex, const std::string& name, char value);
	void writeByteByID(int nsIndex, int id, char value);

	void writeInt16ByName(int nsIndex, const std::string& name, Int16 value);
	void writeInt16ByID(int nsIndex, int id, Int16 value);

	void writeUInt16ByName(int nsIndex, const std::string& name, Poco::UInt16 value);
	void writeUInt16ByID(int nsIndex, int id, Poco::UInt16 value);

	void writeInt32ByName(int nsIndex, const std::string& name, Poco::Int32 value);
	void writeInt32ByID(int nsIndex, int id, Poco::Int32 value);

	void writeUInt32ByName(int nsIndex, const std::string& name, Poco::UInt32 value);
	void writeUInt32ByID(int nsIndex, int id, Poco::UInt32 value);

	void writeInt64ByName(int nsIndex, const std::string& name, Poco::Int64 value);
	void writeInt64ByID(int nsIndex, int id, Poco::Int64 value);

	void writeUInt64ByName(int nsIndex, const std::string& name, Poco::UInt64 value);
	void writeUInt64ByID(int nsIndex, int id, Poco::UInt64 value);

	void writeFloatByName(int nsIndex, const std::string& name, float value);
	void writeFloatByID(int nsIndex, int id, float value);

	void writeDoubleByName(int nsIndex, const std::string& name, double value);
	void writeDoubleByID(int nsIndex, int id, double value);

	void writeStringByName(int nsIndex, const std::string& name, const std::string& value);
	void writeStringByID(int nsIndex, int id, const std::string& value);

	void writeDateTimeByName(int nsIndex, const std::string& name, Poco::Int64 value = -1);
	void writeDateTimeByID(int nsIndex, int id, Poco::Int64 value = -1);

	void writeCurrentDateTimeByName(int nsIndex, const std::string& name);
	void writeCurrentDateTimeByID(int nsIndex, int id);

	template <typename I, typename T>
	void write(int nsIndex, const I& id, const T& value, bool isDateTime = false)
	{
		writeValue(nsIndex, id, value, isDateTime);
	}

	template <typename I, typename T>
	void writeArray(int nsIndex, const I& id, const T& value, bool isDateTime = false)
	{
		writeArrayValue(nsIndex, id, value, isDateTime);
	}

	const TypeCache& getTypeCache() const;

	template <typename N, typename T>
	NodeType getValueType(int nsIndex, const T& id)
	{
		try
		{
			return getValueNodeType<N>(nsIndex, id);
		}
		catch(Poco::NotFoundException&) {}
		return NodeType { OPC_NODE_NOT_FOUND, false };
	}

	//
	// browsing
	//

	const StringList& getEndpointURLs();
	void setEndpointURLs(const StringList& strList);

	Poco::DateTime readServerDateTime();
	std::string readServerDateTimeStr();

	void printEndpointURLs(std::ostream& os) const;
		/// Prints the list of server endpoint URLs.

	void printServerObjects(std::ostream& os);
		/// Prints all the server objects (with values for
		/// value attribute objects) to the provided stream.

private:

	//
	// browsing/caching
	//

	UA_BrowseResponse browse(int type);

	void cacheTypes();

	void printBrowse(std::ostream& os, int type, std::vector<int> colWidths = std::vector<int>());


	//
	// reading
	//

	template <typename N, typename T>
	const NodeType& getValueNodeType(int nsIndex, const T& id)
	{
		if(!_nodeTypeCache.has(N(nsIndex, id)))
		{
			OPC::Variant var;
			UA_StatusCode retval;
			if(getValueNodeType(nsIndex, id, var, retval))
			{
				_nodeTypeCache.add(N(nsIndex, id), var.type().typeIndex, var.isArray());
			}
			else
			{
				std::ostringstream os;
				os << "Node (" << nsIndex << ", " << id << ") error: " << getError(retval);
				throw Poco::RuntimeException(os.str());
			}
		}

		return _nodeTypeCache.type(N(nsIndex, id));
	}

	template <typename I>
	bool getValueNodeType(int nsIndex, const I& id, OPC::Variant& val, UA_StatusCode& retval) const
	{
		retval = readValueAttribute(nsIndex, id, val);
		return (retval == UA_STATUSCODE_GOOD);
	}

	UA_StatusCode readValueAttribute(int nsIndex, const Poco::Dynamic::Var& id, UA_Variant* val) const;

	template <typename T>
	const T& getValue(UA_Variant* val, T& value) const
	{
		if(UA_Variant_isScalar(val))
		{
			value = *(T*)val->data;
		}
		else
		{
			throw Poco::InvalidAccessException("OPC::Client::getValue(): "
				"attempt to retrieve array value using scalar function");
		}
		return value;
	}

	template <typename T>
	T& getTypedValue(OPC::Variant& val, T& value) const
	{
		getValue(val, value);
		return value;
	}

	std::string& getTypedValue(OPC::Variant& val, std::string& value) const;

	template <typename T, typename I>
	T readValueAttribute(int nsIndex, const I& id) const
	{
		T value = T();
		OPC::Variant val;
		UA_StatusCode retval = readValueAttribute(nsIndex, id, val);
		if(retval == UA_STATUSCODE_GOOD)
		{
			getTypedValue(val, value);
		}
		else
		{
			std::ostringstream os;
			os << "Error in OPC::Client::readValueAttribute(" << id << "): " << getError(retval);
			throw Poco::RuntimeException(os.str());
		}
		return value;
	}

	template <typename T>
	const std::vector<T>& getArrayValue(UA_Variant* val, std::vector<T>& values) const
	{
		if(!UA_Variant_isScalar(val))
		{
			values.reserve(val->arrayLength);
			T* ptr = (T*)val->data;
			for(unsigned i = 0; i < val->arrayLength; ++i, ++ptr)
			{
				values.push_back(*(T*)ptr);
			}
		}
		else
		{
			throw Poco::InvalidAccessException("OPC::Client::getValue(): "
				"attempt to retrieve scalar value using array function");
		}
		return values;
	}

	void getDateTime(IoT::OPC::DateTime& dt);


	//
	// writing
	//

	template <typename T>
	void checkTypeSafety(const T& nodeID, UA_Variant* val)
	{
		if(_typeSafe)
		{
			poco_check_ptr(val);
			poco_check_ptr(val->type);
			if(!_nodeTypeCache.has(nodeID, val->type->typeIndex, val->arrayLength))
			{
				OPC::Variant var;
				UA_StatusCode retval;
				if(getValueNodeType(nodeID.nsIndex(), nodeID.id(), var, retval))
				{
					if(!var.hasData())
					{
						std::ostringstream os;
						os << "OPC::Client::checkTypeSafety(): "
							"write to a non-existing or non-value node [" << nodeID.nsIndex() << ", " <<
							nodeID.id() << "] attempted.";
						throw Poco::InvalidAccessException(os.str());
					}
					else if(var.type().typeIndex != val->type->typeIndex || (val->arrayLength && !var.isArray()))
					{
						std::ostringstream os;
						os << "OPC::Client::checkTypeSafety(): "
							"type mismatch for node [" << nodeID.nsIndex() << ", " <<
							nodeID.id() << "] in type-safe mode (node/value type=" << var.type().typeIndex <<
							'/' << val->type->typeIndex << "; "
							"array=" << var.isArray() << '/' << val->arrayLength << ").";
						throw Poco::InvalidAccessException(os.str());
					}
					else
					{
						_nodeTypeCache.add(nodeID, var.type().typeIndex, var.isArray());
					}
				}
				else
				{
					std::ostringstream os;
					os << "Can not determine value node type for node ID " << nodeID.toString() <<
						", error: " << getError(retval);
					_pLogger->error(os.str());
				}
			}
		}
	}

	UA_StatusCode writeValueAttribute(int nsIndex, const Poco::Dynamic::Var& id, UA_Variant* val);

	template <typename T, typename I>
	void writeValue(int nsIndex, const I& id, const T& value, bool isDateTime = false)
	{
		if(isDateTime && typeid(value) != typeid(UA_DateTime))
		{
			std::ostringstream os;
			os << "OPC::Client::writeValue(): [" << typeid(value).name() <<
				"] not covertible to DateTime (" << typeid(UA_DateTime).name() << ')';
			throw Poco::InvalidArgumentException(os.str());
		}

		OPC::Variant var;
		Poco::Dynamic::Var val(value);
		UA_StatusCode retval;
		if(val.isString())
		{
			std::string strVal = val.toString();
			UA_String uaStr;
			uaStr.data = (UA_Byte*) strVal.data();
			uaStr.length = strVal.length();
			retval = UA_Variant_setScalarCopy(var, &uaStr, &UA_TYPES[UA_TYPES_STRING]);
			if(UA_STATUSCODE_GOOD == retval) retval = writeValueAttribute(nsIndex, id, var);
			else throw Poco::RuntimeException("OPC::Client::writeValue(): " + getError(retval));
		}
		else if(isDateTime)
		{
			Poco::Int64 dtVal = val;
			if(-1 == dtVal)
			{
				dtVal = OPC::DateTime::now();
			}
			retval = UA_Variant_setScalarCopy(var, &dtVal, &UA_TYPES[UA_TYPES_DATETIME]);
			if(UA_STATUSCODE_GOOD == retval) retval = writeValueAttribute(nsIndex, id, var);
			else throw Poco::RuntimeException("OPC::Client::writeValue(): " + getError(retval));
		}
		else
		{
			retval = UA_Variant_setScalarCopy(var, &value, &UA_TYPES[getUAType(value)]);
			if(UA_STATUSCODE_GOOD == retval) retval = writeValueAttribute(nsIndex, id, var);
			else throw Poco::RuntimeException("OPC::Client::writeValue(): " + getError(retval));
		}

		if(retval != UA_STATUSCODE_GOOD)
		{
			std::ostringstream os;
			os << "Error in OPC::Client::writeValueAttribute(" << val.toString() << "): " << getError(retval);
			throw Poco::RuntimeException(os.str());
		}
	}

	template <typename T, typename I>
	UA_StatusCode writeTypedArray(OPC::Variant& var, int nsIndex, const I& id, const T& value)
	{
		typename T::value_type valType = typename T::value_type();
		UA_Variant_setArrayCopy(var, &value[0], value.size(), &UA_TYPES[getUAType(valType)]);
		return writeValueAttribute(nsIndex, id, var);
	}

	UA_StatusCode writeTypedArray(OPC::Variant& var, int nsIndex, const int& id, const std::vector<std::string>& value);

	template <typename T, typename I>
	void writeArrayValue(int nsIndex, const I& id, const T& value, bool isDateTime = false)
	{
		if(isDateTime && typeid(value) != typeid(UA_DateTime))
		{
			std::ostringstream os;
			os << "OPC::Client::writeValue(): [" << typeid(value).name() <<
				"] not covertible to DateTime (" << typeid(UA_DateTime).name() << ')';
			throw Poco::InvalidArgumentException(os.str());
		}

		OPC::Variant var;
		Poco::Dynamic::Var val(value);
		if(val.isArray())
		{
			UA_StatusCode retval = writeTypedArray(var, nsIndex, id, value);
			if(UA_STATUSCODE_GOOD != retval)
			{
				std::ostringstream os;
				os << "Error in OPC::Client::writeTypedArray(" << val.toString() << "): " << getError(retval);
				throw Poco::RuntimeException(os.str());
			}
		}
		else
		{
			throw Poco::InvalidArgumentException("OPC::Client::writeArrayValue(): call to array function "
				"with non-aray value argument");
		}
	}

	UA_Client*       _pClient = nullptr;
	Poco::Logger*    _pLogger = nullptr;
	std::string      _url;
	StringList       _endpointURLs;
	UA_BrowseRequest _browseReq;
	bool             _typeSafe;
	TypeCache        _nodeTypeCache;
	// following members needed to copy-construct the client (remoting requirement)
	std::string _server;
	int         _port;
	std::string _user;
	std::string _pass;
	std::string _proto;
};


//
// inlines
//

//
// config
//

inline bool Client::getTypeSafe() const
{
	return _typeSafe;
}


inline void Client::setTypeSafe(bool safe)
{
	_typeSafe = safe;
	if(!_typeSafe) _nodeTypeCache.clear();
}


inline void Client::setURL(const std::string& server, int port, const std::string& proto)
{
	_url = proto;
	_url.append("://").append(server).append(1, ':').append(Poco::NumberFormatter::format(port));
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
	return readValueAttribute<std::string>(nsIndex, name);
}


inline std::string Client::readStringByID(int nsIndex, int id) const
{
	return readValueAttribute<std::string>(nsIndex, id);
}


inline Poco::DateTime Client::readDateTimeByName(int nsIndex, const std::string& name) const
{
	return IoT::OPC::DateTime(readInt64ByName(nsIndex, name));
}


inline Poco::DateTime Client::readDateTimeByID(int nsIndex, int id) const
{
	return IoT::OPC::DateTime(readInt64ByID(nsIndex, id));
}


inline std::string Client::readStrDateTimeByName(int nsIndex, const std::string& name) const
{
	return IoT::OPC::DateTime(readInt64ByName(nsIndex, name)).toString();
}


inline std::string Client::readStrDateTimeByID(int nsIndex, int id) const
{
	Int64 ts = readInt64ByID(nsIndex, id);
	return IoT::OPC::DateTime(ts).toString();
}


inline Poco::UInt64 Client::readTimestampByName(int nsIndex, const std::string& name) const
{
	return readInt64ByName(nsIndex, name);
}


inline Poco::UInt64 Client::readTimestampByID(int nsIndex, int id) const
{
	return  readInt64ByID(nsIndex, id);
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


inline void Client::writeInt16ByName(int nsIndex, const std::string& name, Poco::Int16 value)
{
	writeValue(nsIndex, name, value);
}


inline void Client::writeInt16ByID(int nsIndex, int id, Poco::Int16 value)
{
	writeValue(nsIndex, id, value);
}


inline void Client::writeUInt16ByName(int nsIndex, const std::string& name, Poco::UInt16 value)
{
	writeValue(nsIndex, name, value);
}


inline void Client::writeUInt16ByID(int nsIndex, int id, Poco::UInt16 value)
{
	writeValue(nsIndex, id, value);
}


inline void Client::writeInt32ByName(int nsIndex, const std::string& name, Poco::Int32 value)
{
	writeValue(nsIndex, name, value);
}


inline void Client::writeInt32ByID(int nsIndex, int id, Poco::Int32 value)
{
	writeValue(nsIndex, id, value);
}


inline void Client::writeUInt32ByName(int nsIndex, const std::string& name, Poco::UInt32 value)
{
	writeValue(nsIndex, name, value);
}


inline void Client::writeUInt32ByID(int nsIndex, int id, Poco::UInt32 value)
{
	writeValue(nsIndex, id, value);
}


inline void Client::writeInt64ByName(int nsIndex, const std::string& name, Poco::Int64 value)
{
	writeValue(nsIndex, name, value);
}


inline void Client::writeInt64ByID(int nsIndex, int id, Poco::Int64 value)
{
	writeValue(nsIndex, id, value);
}


inline void Client::writeUInt64ByName(int nsIndex, const std::string& name, Poco::UInt64 value)
{
	writeValue(nsIndex, name, value);
}


inline void Client::writeUInt64ByID(int nsIndex, int id, Poco::UInt64 value)
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


inline void Client::writeDateTimeByName(int nsIndex, const std::string& name, Poco::Int64 value)
{
	writeValue(nsIndex, name, value, true);
}


inline void Client::writeDateTimeByID(int nsIndex, int id, Poco::Int64 value)
{
	writeValue(nsIndex, id, value, true);
}


inline void Client::writeCurrentDateTimeByName(int nsIndex, const std::string& name)
{
	writeValue(nsIndex, name, (Int64) -1, true);
}


inline void Client::writeCurrentDateTimeByID(int nsIndex, int id)
{
	writeValue(nsIndex, id, (Int64) -1, true);
}


inline void Client::printServerObjects(std::ostream& os)
{
	printBrowse(os, UA_NS0ID_OBJECTSFOLDER);
}


} } // namespace IoT::OPC


#endif // IoT_OPC_Client_INCLUDED
