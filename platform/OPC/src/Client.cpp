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


#include "Poco/OPC/Client.h"
#include "Poco/Exception.h"
#include <iostream>


namespace Poco {
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


Client::Client(): _pClient(UA_Client_new(UA_ClientConfig_standard)),
	_connected(false)
{
}


Client::Client(const std::string& server,
	int port,
	bool doConnect,
	const std::string& user,
	const std::string& pass,
	const std::string& proto): _pClient(UA_Client_new(UA_ClientConfig_standard)),
	_connected(false)
{
	setServer(server, port, proto);
	if(getState() != OPC_CLIENT_READY)
		throw IllegalStateException("OPC client not ready");
	getEndpointURLs();
	if(doConnect) connect(user, pass);
}


void Client::setServer(const std::string& server, int port, const std::string& proto)
{
	_url = proto;
	_url.append("://").append(server).append(1, ':').append(NumberFormatter::format(port));
}


Client::~Client()
{
	disconnect();
	UA_Client_delete(_pClient);
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


int Client::getState() const
{
	return UA_Client_getState(_pClient);
}


std::string Client::getError(UInt32 val) const
{
	return std::string(UA_StatusCode_name(val)) + ": " + UA_StatusCode_explanation(val);
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


std::string Client::readServerDateTime()
{
	std::string dt;
	UA_Variant value;
	UA_Variant_init(&value);

	const UA_NodeId nodeId = UA_NODEID_NUMERIC(0, OPC_SERVER_TIME);

	UA_StatusCode retval = UA_Client_readValueAttribute(_pClient, nodeId, &value);
	if(retval == UA_STATUSCODE_GOOD &&
			UA_Variant_hasScalarType(&value, &UA_TYPES[OPC_TYPE_DATETIME]))
	{
		UA_DateTime raw_date = *(UA_DateTime*)value.data;
		UA_String string_date = UA_DateTime_toString(raw_date);
		dt.assign((const char*) string_date.data, string_date.length);
		UA_String_deleteMembers(&string_date);
	}

	UA_Variant_deleteMembers(&value);
	return dt;
}


void Client::disconnect()
{
	if(_connected)
	{
		UA_Client_disconnect(_pClient);
		_connected = false;
	}
}


} } // namespace Poco::OPC
