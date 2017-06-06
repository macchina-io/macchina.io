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
#include <iostream>


using namespace Poco;


namespace IoT {
namespace OPC {


using namespace open62541;


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


Client::Client(): _pClient(UA_Client_new(UA_ClientConfig_standard))
{
}


Client::Client(const std::string& server,
	int port,
	const std::string& user,
	const std::string& pass,
	bool doConnect,
	const std::string& proto): _pClient(UA_Client_new(UA_ClientConfig_standard)),
		_server(server),
		_port(port),
		_user(user),
		_pass(pass),
		_proto(proto)
{
	init(doConnect);
}


Client::Client(const Client& other): _pClient(UA_Client_new(UA_ClientConfig_standard)),
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
	_pClient = UA_Client_new(UA_ClientConfig_standard);
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
	UA_BrowseRequest_deleteMembers(&_browseReq);
	disconnect();
	UA_Client_delete(_pClient);
}


void Client::init(bool doConnect)
{
	setURL(_server, _port, _proto);
	if(getState() != OPC_CLIENT_READY)
		throw IllegalStateException("OPC client not ready");
	getEndpointURLs();
	UA_BrowseRequest_init(&_browseReq);
	_browseReq.requestedMaxReferencesPerNode = 0;
	_browseReq.nodesToBrowse = UA_BrowseDescription_new();
	_browseReq.nodesToBrowseSize = 1;
	_browseReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; // return everything
	if(doConnect) connect(_user, _pass);
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


void Client::getDateTime(IoT::OPC::DateTime& dt)
{
	UA_Variant value;
	UA_Variant_init(&value);

	const UA_NodeId nodeId = UA_NODEID_NUMERIC(0, OPC_SERVER_TIME);

	UA_StatusCode retval = UA_Client_readValueAttribute(_pClient, nodeId, &value);
	if(retval != UA_STATUSCODE_GOOD ||
			!UA_Variant_hasScalarType(&value, &UA_TYPES[OPC_TYPE_DATETIME]))
	{
		throw RuntimeException("Error in getDateTime(): " +  getError(retval));
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
			//todo: proper logging
			std::cout << getError(retval) << std::endl;
		}
	}
}


} } // namespace IoT::OPC
