//
// Server.cpp
//
// $Id$
//
// Library: OPC
// Package: OPC
// Module:  Server
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/OPC/Server.h"
#include "Poco/Dynamic/Var.h"
#include <iostream>


namespace Poco {
namespace OPC {
namespace open62541 {

#include "open62541.h"

}


using namespace open62541;


Server::Server(int port): _pServer(0),
	_pNetworkLayer(new UA_ServerNetworkLayer(UA_ServerNetworkLayerTCP(UA_ConnectionConfig_standard, static_cast<UA_UInt16>(port)))),
	_running(false),
	_done(false)
{
	UA_ServerConfig config = UA_ServerConfig_standard;
	config.networkLayers = _pNetworkLayer;
	config.networkLayersSize = 1;
	_pServer = UA_Server_new(config);
}


Server::~Server()
{
	stop();
	UA_Server_delete(_pServer);
	_pNetworkLayer->deleteMembers(_pNetworkLayer);
	delete _pNetworkLayer;
}


void Server::run()
{
	_running = true;
	UA_StatusCode retval = UA_Server_run(_pServer, &_running);
	if(UA_STATUSCODE_GOOD != retval)
	{
		std::cout << getError(retval) << std::endl;
		//throw RuntimeException("Error in Server::run(): " +  getError(retval));
	}
	_done = true;
}


void Server::stop()
{
	_running = false;
	while(!_done);
}


int Server::addNamespace(const std::string& name)
{
	return UA_Server_addNamespace(_pServer, name.c_str());
}


void Server::addVariableNode(int nsIndex,
	const Poco::Dynamic::Var& id,
	const Any& value,
	int type,
	const std::string& qualifiedName,
	const std::string& displayName,
	const std::string& description,
	const std::string& loc)
{
	UA_VariableAttributes attr;
	UA_VariableAttributes_init(&attr);
	const void* pVal = 0;
	UA_String str = {0};
	if(UA_TYPES_STRING == type)
	{
		pVal = convertString(value, str);
	}
	else
	{
		pVal = convertPOD(value, type);
	}
	if(!pVal) throw NullPointerException("Server::addVariableNode()");
	UA_Variant_setScalarCopy(&attr.value, pVal, &UA_TYPES[type]);
	attr.description = UA_LOCALIZEDTEXT_ALLOC(loc.c_str(),description.c_str());
	attr.displayName = UA_LOCALIZEDTEXT_ALLOC(loc.c_str(),displayName.c_str());
	UA_NodeId nodeId;
	if(id.isString())
	{
		nodeId = UA_NODEID_STRING_ALLOC(nsIndex, id.toString().c_str());
	}
	else if(id.isNumeric())
	{
		nodeId = UA_NODEID_NUMERIC(nsIndex, id);
	}
	else
	{
		throw Poco::NotImplementedException("OPC::Server::addVariableNode() - type not implemented.");
	}
	UA_QualifiedName qName = UA_QUALIFIEDNAME_ALLOC(nsIndex, qualifiedName.c_str());
	UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);//FIXME - parameterize
	UA_NodeId parentRefNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);//FIXME - parameterize
	UA_StatusCode retval = UA_Server_addVariableNode(_pServer, nodeId, parentNodeId,
			parentRefNodeId, qName, UA_NODEID_NULL, attr, NULL, NULL);
	UA_VariableAttributes_deleteMembers(&attr);
	UA_NodeId_deleteMembers(&nodeId);
	UA_QualifiedName_deleteMembers(&qName);
	if(UA_STATUSCODE_GOOD != retval)
	{
		throw RuntimeException("Error in Server::addVariableNode(): " +  getError(retval));
	}
}


const void* Server::convertString(const Any& value, UA_String& str)
{
	const std::string* pStr = UnsafeAnyCast<std::string>(&value);
	if(pStr)
	{
		str = UA_STRING_ALLOC(pStr->c_str());
	}
	else
	{
		throw Poco::NullPointerException("OPC::Server::convertString()");
	}
	return &str;
}


const void* Server::convertPOD(const Any& value, int type)
{
	switch(type)
	{
	case UA_TYPES_BOOLEAN:
		return UnsafeAnyCast<UA_Boolean>(&value);
		break;
	case UA_TYPES_SBYTE:
		return UnsafeAnyCast<UA_SByte>(&value);
		break;
	case UA_TYPES_BYTE:
		return UnsafeAnyCast<UA_Byte>(&value);
		break;
	case UA_TYPES_INT16:
		return UnsafeAnyCast<UA_Int16>(&value);
		break;
	case UA_TYPES_UINT16:
		return UnsafeAnyCast<UA_UInt16>(&value);
		break;
	case UA_TYPES_INT32:
		return UnsafeAnyCast<UA_Int32>(&value);
		break;
	case UA_TYPES_UINT32:
		return UnsafeAnyCast<UA_UInt32>(&value);
		break;
	case UA_TYPES_INT64:
		return UnsafeAnyCast<UA_Int64>(&value);
		break;
	case UA_TYPES_UINT64:
		return UnsafeAnyCast<UA_UInt64>(&value);
		break;
	case UA_TYPES_FLOAT:
		return UnsafeAnyCast<UA_Float>(&value);
		break;
	case UA_TYPES_DOUBLE:
		return UnsafeAnyCast<UA_Double>(&value);
		break;
	case UA_TYPES_STRING:
		return UnsafeAnyCast<std::string>(&value);
		break;
	case UA_TYPES_DATETIME:
		return UnsafeAnyCast<UA_DateTime>(&value);
		break;
	}
	throw Poco::NotImplementedException("OPC::Server::convertPOD(value, " +
			Poco::NumberFormatter::format(type) + "): type not implemented");
}


} } // namespace Poco::OPC
