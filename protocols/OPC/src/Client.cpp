//
// Client.cpp
//
// $Id$
//
// Library: OPC
// Package: OPC
// Module:  Client
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "IoT/OPC/Client.h"
#include "IoT/OPC/UALogger.h"


using namespace Poco;


namespace IoT {
namespace OPC {


extern Poco::Logger* uaLogger;


// Client statuses
const int Client::OPC_CLIENT_READY = UA_CLIENTSTATE_READY;
const int Client::OPC_CLIENT_CONNECTED = UA_CLIENTSTATE_CONNECTED;
const int Client::OPC_CLIENT_FAULTED = UA_CLIENTSTATE_FAULTED;
const int Client::OPC_CLIENT_ERRORED = UA_CLIENTSTATE_ERRORED;


// Server statuses
const int Client::OPC_SERVER_TIME = UA_NS0ID_SERVER_SERVERSTATUS_CURRENTTIME;


// Types
const int Client::OPC_TYPE_BOOLEAN = UA_TYPES_BOOLEAN;
const int Client::OPC_TYPE_SBYTE = UA_TYPES_SBYTE;
const int Client::OPC_TYPE_BYTE = UA_TYPES_BYTE;
const int Client::OPC_TYPE_INT16 = UA_TYPES_INT16;
const int Client::OPC_TYPE_UINT16 = UA_TYPES_UINT16;
const int Client::OPC_TYPE_INT32 = UA_TYPES_INT32;
const int Client::OPC_TYPE_UINT32 = UA_TYPES_UINT32;
const int Client::OPC_TYPE_INT64 = UA_TYPES_INT64;
const int Client::OPC_TYPE_UINT64 = UA_TYPES_UINT64;
const int Client::OPC_TYPE_FLOAT = UA_TYPES_FLOAT;
const int Client::OPC_TYPE_DOUBLE = UA_TYPES_DOUBLE;
const int Client::OPC_TYPE_STRING = UA_TYPES_STRING;
const int Client::OPC_TYPE_DATETIME = UA_TYPES_DATETIME;


Client::Client(const std::string& server,
	int port,
	Poco::Message::Priority prio): _pClient(nullptr),
		_pLogger(&Poco::Logger::create("IoT_OPC_Client",
				Poco::AutoPtr<Poco::ConsoleChannel>(new Poco::ConsoleChannel),
				prio)),
		_typeSafe(true),
		_server(server),
		_port(port),
		_proto("opc.tcp")
{
	init(true);
}


Client::Client(const std::string& server,
	Poco::Logger* logger,
	int port,
	const std::string& user,
	const std::string& pass,
	bool doConnect,
	bool typeSafe,
	const std::string& proto): _pClient(nullptr),
		_pLogger(logger),
		_typeSafe(typeSafe),
		_server(server),
		_port(port),
		_user(user),
		_pass(pass),
		_proto(proto)
{
	init(doConnect);
}


Client::Client(const Client& other): _pClient(nullptr),
	_pLogger(other._pLogger),
	_typeSafe(other._typeSafe),
	_server(other._server),
	_port(other._port),
	_user(other._user),
	_pass(other._pass),
	_proto(other._proto)
{
	init(other.getState() == OPC_CLIENT_CONNECTED);
}


Client& Client::operator = (Client& other)
{
	_pLogger = other._pLogger;
	_typeSafe = other._typeSafe;
	_server = other._server;
	_port = other._port;
	_user = other._user;
	_pass = other._pass;
	_proto = other._proto;

	init(other.getState() == OPC_CLIENT_CONNECTED);
	return *this;
}


Client::~Client()
{
	disconnect();
	UA_Client_delete(_pClient);
}


void Client::init(bool doConnect)
{
	UA_ClientConfig config = UA_ClientConfig_standard;
	uaLogger = _pLogger;
	config.logger = (UA_Logger) UA_Log_POCO;
	_pClient = UA_Client_new(config);
	if(getState() != OPC_CLIENT_READY)
		throw IllegalStateException("OPC client not ready");
	setURL(_server, _port, _proto);
	getEndpointURLs();
	if(doConnect) connect(_user, _pass);
	if(_typeSafe) cacheTypes();
}


void Client::connect(const std::string& user, const std::string& pass)
{
	UA_StatusCode retval;
	if(!user.empty())
	{
		retval = UA_Client_connect_username(_pClient, _url.c_str(), user.c_str(), pass.c_str());
	}
	else
	{
		retval = UA_Client_connect(_pClient, _url.c_str());
	}

	if(getState() != OPC_CLIENT_CONNECTED)
		throw IllegalStateException(getError(retval));

	_pLogger->information("OPC Client: connected.");
}


void Client::disconnect()
{
	if(_pClient && (getState() == OPC_CLIENT_CONNECTED))
	{
		UA_StatusCode retval = UA_Client_disconnect(_pClient);
		if(UA_STATUSCODE_GOOD == retval)
		{
			UA_Client_reset(_pClient);
		}
		else
		{
			_pLogger->error(getError(retval));
		}

		_pLogger->information("OPC Client: disconnected.");
	}
}


const Client::StringList& Client::getEndpointURLs()
{
	_endpointURLs.clear();
	UA_EndpointDescription* endpointArray = NULL;
	size_t endpointArraySize = 0;
	UA_StatusCode retval = UA_Client_getEndpoints(_pClient, _url.c_str(), &endpointArraySize, &endpointArray);
	if(retval != UA_STATUSCODE_GOOD)
	{
		UA_Array_delete(endpointArray, endpointArraySize, &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);
		throw RuntimeException(getError(retval));
	}

	for(size_t i = 0; i < endpointArraySize; ++i)
	{
		_endpointURLs.push_back(std::string((const char*) endpointArray[i].endpointUrl.data,
				endpointArray[i].endpointUrl.length));
	}
	UA_Array_delete(endpointArray,endpointArraySize, &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);
	return _endpointURLs;
}


void Client::printEndpointURLs(std::ostream& os) const
{
	std::size_t count = _endpointURLs.size();
	if(count)
	{
		os << count << " endpoint" << (count != 1 ? "s" : "") << " found." << std::endl;
		int i = 0;
		for(StringList::const_iterator it = _endpointURLs.begin(), end = _endpointURLs.end();it != end;++it, ++i)
		{
			os << "Endpoint [" << i << "]: " << *it << std::endl;
		}
	}
}


//
// reading
//

void Client::getDateTime(IoT::OPC::DateTime& dt)
{
	UA_Variant value;
	UA_Variant_init(&value);

	const UA_NodeId nodeId = UA_NODEID_NUMERIC(0, OPC_SERVER_TIME);

	UA_StatusCode retval = UA_Client_readValueAttribute(_pClient, nodeId, &value);
	if(retval != UA_STATUSCODE_GOOD ||
			!UA_Variant_hasScalarType(&value, &UA_TYPES[OPC_TYPE_DATETIME]))
	{
		std::ostringstream os;
		os << "Error in getDateTime(): " << retval << " (" << getError(retval) << ')';
		throw RuntimeException(os.str());
	}
	dt = *(UA_DateTime*)value.data;
	UA_Variant_deleteMembers(&value);
}


std::string Client::readServerDateTimeStr()
{
	IoT::OPC::DateTime dt;
	getDateTime(dt);
	return dt.toString();
}


Poco::DateTime Client::readServerDateTime()
{
	IoT::OPC::DateTime dt;
	getDateTime(dt);
	return dt;
}


UA_StatusCode Client::readValueAttribute(int nsIndex, const Poco::Dynamic::Var& id, UA_Variant* val) const
{
	UA_StatusCode retval;
	if(id.isString())
	{
		retval = UA_Client_readValueAttribute(_pClient, UA_NODEID_STRING(nsIndex, const_cast<char*>(id.toString().c_str())), val);
	}
	else
	{
		retval = UA_Client_readValueAttribute(_pClient, UA_NODEID_NUMERIC(nsIndex, id.convert<Poco::UInt32>()), val);
	}
	//TODO: guid and bytestring
	return retval;
}


std::string& Client::getTypedValue(OPC::Variant& val, std::string& value) const
{
	UA_String uaStr;
	getValue(val, uaStr);
	value = STDString(uaStr);
	return value;
}


//
// writing
//

const TypeCache& Client::getTypeCache() const
{
	return _nodeTypeCache;
}


UA_StatusCode Client::writeValueAttribute(int nsIndex, const Poco::Dynamic::Var& id, UA_Variant* val)
{
	if(id.isString())
	{
		checkTypeSafety(StringNodeID(nsIndex, id.toString()), val);
		return UA_Client_writeValueAttribute(_pClient, UA_NODEID_STRING(nsIndex, const_cast<char*>(id.toString().c_str())), val);
	}

	checkTypeSafety(IntNodeID(nsIndex, id.convert<int>()), val);
	return UA_Client_writeValueAttribute(_pClient, UA_NODEID_NUMERIC(nsIndex, id), val);
}


UA_StatusCode Client::writeTypedArray(OPC::Variant& var, int nsIndex, const int& id, const std::vector<std::string>& value)
{
	UA_String uaStr[value.size()];
	unsigned i = 0;
	for(std::vector<std::string>::const_iterator it = value.begin(),
		end = value.end(); it != end; ++it, ++i)
	{
		uaStr[i].data = (UA_Byte*) it->data();
		uaStr[i].length = it->length();
	}
	UA_Variant_setArrayCopy(var, uaStr, value.size(), &UA_TYPES[UA_TYPES_STRING]);
	return writeValueAttribute(nsIndex, id, var);
}


//
// browsing/caching
//


UA_BrowseResponse Client::browse(const BrowseDescVec& desc)
{
	UA_BrowseRequest browseReq;
	UA_BrowseRequest_init(&browseReq);
	if(desc.size())
	{
		browseReq.requestedMaxReferencesPerNode = 0;
		browseReq.nodesToBrowse = const_cast<UA_BrowseDescription*>(&desc[0]);
		browseReq.nodesToBrowseSize = desc.size();
	}
	UA_BrowseResponse bResp = UA_Client_Service_browse(_pClient, browseReq);
	return bResp;
}


UA_BrowseDescription Client::getBrowseDesc(UA_NodeId id, UA_UInt32 mask)
{
	UA_BrowseDescription desc = {0};
	desc.resultMask = mask;
	desc.nodeId = id;
	return desc;
}


} } // namespace IoT::OPC
