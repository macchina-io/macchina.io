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


#include "IoT/OPC/Server.h"
#include "Poco/Thread.h"
#include "Poco/Format.h"
#include "Poco/Dynamic/Var.h"
#include "IoT/OPC/UALogger.h"


using namespace Poco;


namespace IoT {
namespace OPC {


extern Poco::Logger* uaLogger;


Server::Server(int port, Poco::Message::Priority prio): _pServer(0),
	_logger(Poco::Logger::create("IoT_OPC_Server",
			Poco::AutoPtr<Poco::ConsoleChannel>(new Poco::ConsoleChannel),
			prio)),
	_pNetworkLayer(makeServerNetworkLayer(port)),
	_running(false),
	_done(false)
{
	_logger.setLevel(prio);
	init();
}


Server::Server(Poco::Logger& logger, int port): _pServer(0),
	_logger(logger),
	_pNetworkLayer(makeServerNetworkLayer(port)),
	_running(false),
	_done(false)
{
	init();
}


void Server::init()
{
	UA_ServerConfig config = UA_ServerConfig_standard;
	uaLogger = &_logger;
	config.logger = (UA_Logger) UA_Log_POCO;
	config.networkLayers = _pNetworkLayer;
	config.networkLayersSize = 1;
	_pServer = UA_Server_new(config);
	if(_pServer)
	{
		_logger.trace("OPC Server: succesfully created.");
	}
	else
	{
		throw Poco::NullPointerException("Can't create OPC server.");
	}
}


Server::~Server()
{
	stop();
	UA_Server_delete(_pServer);
	_pNetworkLayer->deleteMembers(_pNetworkLayer);
	delete _pNetworkLayer;
	_logger.trace("OPC Server: destroyed.");
}


void Server::run()
{
	_running = true;
	UA_StatusCode retval = UA_Server_run(_pServer, &_running);
	if(UA_STATUSCODE_GOOD != retval)
	{
		_error = getError(retval);
		_logger.error(_error);
	}
	_done = true;
	_logger.trace("OPC Server: stopped.");
}


void Server::stop()
{
	_running = false;
	while(!_done) Thread::sleep(10);
}


int Server::addNamespace(const std::string& name)
{
	int nsIndex = UA_Server_addNamespace(_pServer, name.c_str());
	_logger.trace(Poco::format("OPC Server: added namespace (%d, %s) to OPC Server.", nsIndex, name));
	return nsIndex;
}


void Server::addVariableNode(int nsIndex,
	const Poco::Dynamic::Var& id,
	const Any& value,
	int type,
	bool array,
	const std::string& qualifiedName,
	const std::string& displayName,
	const std::string& description,
	int parentID,
	int parentRefID,
	const std::string& loc)
{
	UA_VariableAttributes attr;
	UA_VariableAttributes_init(&attr);
	const void* pVal = 0;
	UA_String str = {0};
	std::vector<UA_String> strVec;
	std::size_t sz = 0;
	if(UA_TYPES_STRING == type)
	{
		if(!array)
		{
			pVal = convertString(value, str);
		}
		else
		{
			pVal = convertStringArray(value, strVec);
			sz = strVec.size();
		}
	}
	else
	{
		if(!array)
		{
			pVal = convertPOD(value, type);
		}
		else
		{
			pVal = convertPODArray(value, type, sz);
		}
	}
	if(!pVal) throw NullPointerException("Server::addVariableNode()");
	if(!array) UA_Variant_setScalarCopy(&attr.value, pVal, &UA_TYPES[type]);
	else UA_Variant_setArrayCopy(&attr.value, pVal, sz, &UA_TYPES[type]);
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
	UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, parentID);
	UA_NodeId parentRefNodeId = UA_NODEID_NUMERIC(0, parentRefID);
	UA_StatusCode retval = UA_Server_addVariableNode(_pServer, nodeId, parentNodeId,
			parentRefNodeId, qName, UA_NODEID_NULL, attr, NULL, NULL);
	UA_VariableAttributes_deleteMembers(&attr);
	UA_NodeId_deleteMembers(&nodeId);
	UA_QualifiedName_deleteMembers(&qName);
	if(UA_STATUSCODE_GOOD != retval)
	{
		throw RuntimeException("Error in Server::addVariableNode(): " +  getError(retval));
	}
	else if(_logger.getLevel() >= Poco::Message::PRIO_TRACE)
	{
		if(id.isString())
		{
			_logger.trace(Poco::format("OPC Server: added variable node (%d, %s).", nsIndex, id.toString()));
		}
		else if(id.isNumeric())
		{
			_logger.trace(Poco::format("OPC Server: added variable node (%d, %d).", nsIndex, id.convert<int>()));
		}
	}
	if(str.data && str.length)
	{
		UA_free(str.data);
	}
	for(auto& s : strVec)
	{
		UA_free(s.data);
	}
	if(nodeId.identifierType == UA_NODEIDTYPE_STRING)
	{
		UA_free(nodeId.identifier.string.data);
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


const void* Server::convertStringArray(const Any& value, std::vector<UA_String>& str)
{
	const std::vector<std::string>* pStr = UnsafeAnyCast<std::vector<std::string>>(&value);
	if(pStr)
	{
		for(auto& s : *pStr)
		{
			str.push_back(UA_STRING_ALLOC(s.c_str()));
		}
	}
	else
	{
		throw Poco::NullPointerException("OPC::Server::convertString()");
	}
	return &str[0];
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
	case UA_TYPES_DATETIME:
		return UnsafeAnyCast<UA_DateTime>(&value);
		break;
	}
	throw Poco::NotImplementedException("OPC::Server::convertPOD(value, " +
			Poco::NumberFormatter::format(type) + "): type not implemented");
}


const void* Server::convertPODArray(const Any& value, int type, std::size_t& sz)
{
	switch(type)
	{
	case UA_TYPES_BOOLEAN:
	{
		throw Poco::NotImplementedException("OPC::Server::convertPODArray(value, " +
			Poco::NumberFormatter::format(type) + "): boolean array not implemented");
	}
	case UA_TYPES_SBYTE:
	{
		const std::vector<UA_SByte>* ptr = UnsafeAnyCast<std::vector<UA_SByte>>(&value);
		poco_check_ptr(ptr);
		sz = ptr->size();
		return &(*ptr)[0];
	}
	case UA_TYPES_BYTE:
	{
		const std::vector<UA_Byte>* ptr = UnsafeAnyCast<std::vector<UA_Byte>>(&value);
		poco_check_ptr(ptr);
		sz = ptr->size();
		return &(*ptr)[0];
	}
	case UA_TYPES_INT16:
	{
		const std::vector<UA_Int16>* ptr = UnsafeAnyCast<std::vector<UA_Int16>>(&value);
		poco_check_ptr(ptr);
		sz = ptr->size();
		return &(*ptr)[0];
	}
	case UA_TYPES_UINT16:
	{
		const std::vector<UA_UInt16>* ptr = UnsafeAnyCast<std::vector<UA_UInt16>>(&value);
		poco_check_ptr(ptr);
		sz = ptr->size();
		return &(*ptr)[0];
	}
	case UA_TYPES_INT32:
	{
		const std::vector<UA_Int32>* ptr = UnsafeAnyCast<std::vector<UA_Int32>>(&value);
		poco_check_ptr(ptr);
		sz = ptr->size();
		return &(*ptr)[0];
	}
	case UA_TYPES_UINT32:
	{
		const std::vector<UA_UInt32>* ptr = UnsafeAnyCast<std::vector<UA_UInt32>>(&value);
		poco_check_ptr(ptr);
		sz = ptr->size();
		return &(*ptr)[0];
	}
	case UA_TYPES_INT64:
	{
		const std::vector<UA_Int64>* ptr = UnsafeAnyCast<std::vector<UA_Int64>>(&value);
		poco_check_ptr(ptr);
		sz = ptr->size();
		return &(*ptr)[0];
	}
	case UA_TYPES_UINT64:
	{
		const std::vector<UA_UInt64>* ptr = UnsafeAnyCast<std::vector<UA_UInt64>>(&value);
		poco_check_ptr(ptr);
		sz = ptr->size();
		return &(*ptr)[0];
	}
	case UA_TYPES_FLOAT:
	{
		const std::vector<UA_Float>* ptr = UnsafeAnyCast<std::vector<UA_Float>>(&value);
		poco_check_ptr(ptr);
		sz = ptr->size();
		return &(*ptr)[0];
	}
	case UA_TYPES_DOUBLE:
	{
		const std::vector<UA_Double>* ptr = UnsafeAnyCast<std::vector<UA_Double>>(&value);
		poco_check_ptr(ptr);
		sz = ptr->size();
		return &(*ptr)[0];
	}
	case UA_TYPES_DATETIME:
	{
		const std::vector<UA_DateTime>* ptr = UnsafeAnyCast<std::vector<UA_DateTime>>(&value);
		poco_check_ptr(ptr);
		sz = ptr->size();
		return &(*ptr)[0];
	}
	}
	throw Poco::NotImplementedException("OPC::Server::convertPODArray(value, " +
			Poco::NumberFormatter::format(type) + "): type not implemented");
}


} } // namespace IoT::OPC
