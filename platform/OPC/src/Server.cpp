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
	/*UA_StatusCode retval = */
	UA_Server_run(_pServer, &_running);
	_done = true;
}


void Server::stop()
{
	_running = false;
	while(!_done);
}


void Server::addVariableNode(int nsIndex, const std::string& id, const Any& value, int type)
{
	UA_VariableAttributes attr;
	UA_VariableAttributes_init(&attr);
	UA_Variant_setScalarCopy(&attr.value, convert(value, type), &UA_TYPES[type]);
	attr.description = UA_LOCALIZEDTEXT_ALLOC("en_US","the answer");
	attr.displayName = UA_LOCALIZEDTEXT_ALLOC("en_US","the answer");
	UA_NodeId nodeId = UA_NODEID_STRING_ALLOC(nsIndex, id.c_str());
	UA_QualifiedName qName = UA_QUALIFIEDNAME_ALLOC(nsIndex, "the answer");
	UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
	UA_NodeId parentRefNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
	UA_Server_addVariableNode(_pServer, nodeId, parentNodeId,
			parentRefNodeId, qName,
			UA_NODEID_NULL, attr, NULL, NULL);

	UA_VariableAttributes_deleteMembers(&attr);
	UA_NodeId_deleteMembers(&nodeId);
	UA_QualifiedName_deleteMembers(&qName);
}


const void* Server::convert(const Any& value, int type)
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
	//case UA_TYPES_STRING:
	//	return UnsafeAnyCast<Int32>(&value);
	//	break;
	}
	return 0;
}


} } // namespace Poco::OPC
