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
	UA_BrowseRequest_deleteMembers(&_browseReq);
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
	UA_BrowseRequest_init(&_browseReq);
	_browseReq.requestedMaxReferencesPerNode = 0;
	_browseReq.nodesToBrowse = UA_BrowseDescription_new();
	_browseReq.nodesToBrowseSize = 1;
	_browseReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; // return everything
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


UA_StatusCode Client::readValueAttribute(int nsIndex, const Poco::Dynamic::Var& id, UA_Variant* val) const
{
	if(id.isString())
	{
		return UA_Client_readValueAttribute(_pClient, UA_NODEID_STRING(nsIndex, const_cast<char*>(id.toString().c_str())), val);
	}
	else
	{
		return UA_Client_readValueAttribute(_pClient, UA_NODEID_NUMERIC(nsIndex, id), val);
	}
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

UA_BrowseResponse Client::browse(int type)
{
	_browseReq.nodesToBrowse[0].nodeId = UA_NODEID_NUMERIC(0, type);
	return UA_Client_Service_browse(_pClient, _browseReq);
}


void Client::cacheTypes()
{
	_nodeTypeCache.clear();
	UA_BrowseResponse bResp = browse(UA_NS0ID_OBJECTSFOLDER);
	for (size_t i = 0; i < bResp.resultsSize; ++i)
	{
		for (size_t j = 0; j < bResp.results[i].referencesSize; ++j)
		{
			UA_ReferenceDescription* ref = &(bResp.results[i].references[j]);
			poco_check_ptr(ref);
			int nsIndex = ref->browseName.namespaceIndex;
			OPC::Variant var;
			if (ref->nodeId.nodeId.identifierType == UA_NODEIDTYPE_NUMERIC)
			{
				int nodeID = ref->nodeId.nodeId.identifier.numeric;
				if(getValueNodeType(nsIndex, nodeID, var))
				{
					std::ostringstream os;
					os << "Caching Node: (" << nsIndex << ", " << nodeID << "), TYPE: ";
					if(var.isArray()) { os << "[" << var.type().typeIndex << ']' << std::endl; }
					else { os << var.type().typeIndex << std::endl; }
					_pLogger->trace(os.str());
					_nodeTypeCache.add(IntNodeID(nsIndex, nodeID), var.type().typeIndex, var.isArray());
				}
			}
			else if (ref->nodeId.nodeId.identifierType == UA_NODEIDTYPE_STRING)
			{
				UA_String nodeID = ref->nodeId.nodeId.identifier.string;
				std::string nID = std::string((char*) nodeID.data, nodeID.length);
				if(getValueNodeType(nsIndex, nID, var))
				{
					std::ostringstream os;
					os << "Caching Node: (" << nsIndex << ", " << nID << "), TYPE: ";
					if(var.isArray()) { os << "[" << var.type().typeIndex << ']' << std::endl; }
					else { os << var.type().typeIndex << std::endl; }
					_pLogger->trace(os.str());
					_nodeTypeCache.add(StringNodeID(nsIndex, nID), var.type().typeIndex, var.isArray());
				}
			}
			// TODO: distinguish further types
		}
	}
	UA_BrowseResponse_deleteMembers(&bResp);
}


void Client::printBrowse(std::ostream& os, int type, std::vector<int> colWidths)
{
	if(colWidths.size() < 1) colWidths.push_back(11);
	if(colWidths.size() < 2) colWidths.push_back(20);
	if(colWidths.size() < 3) colWidths.push_back(36);
	if(colWidths.size() < 4) colWidths.push_back(36);
	if(colWidths.size() < 5) colWidths.push_back(36);
	UA_BrowseResponse bResp = browse(type);
	os << std::setw(colWidths.at(0)) << "[NAMESPACE]" << std::setw(colWidths.at(1)) << "[NODEID]" <<
		std::setw(colWidths.at(2)) << "[BROWSE NAME]" << std::setw(colWidths.at(3)) << "[DISPLAY NAME]" <<
		std::setw(colWidths.at(3)) << "[VALUE]" << std::endl;
	std::string line(std::accumulate(colWidths.begin(), colWidths.end(), 0), '-');
	os << line << std::endl;
	for (size_t i = 0; i < bResp.resultsSize; ++i)
	{
		for (size_t j = 0; j < bResp.results[i].referencesSize; ++j)
		{
			UA_ReferenceDescription *ref = &(bResp.results[i].references[j]);
			int nsIndex = ref->browseName.namespaceIndex;
			UA_String bName = ref->browseName.name;
			UA_String dName = ref->displayName.text;
			OPC::Variant var;
			if (ref->nodeId.nodeId.identifierType == UA_NODEIDTYPE_NUMERIC)
			{
				int nodeID = ref->nodeId.nodeId.identifier.numeric;
				getValueNodeType(nsIndex, nodeID, var);
				//os << "TYPE: [" << getValueNodeType(nsIndex, nodeID) << ']' << std::endl;
				os << std::setw(colWidths.at(0)) << nsIndex
					<< std::setw(colWidths.at(1)) << nodeID
					<< std::setw(colWidths.at(2)) << std::string((char*) bName.data, bName.length)
					<< std::setw(colWidths.at(3)) << std::string((char*) dName.data, dName.length)
					<< std::setw(colWidths.at(4)) << (var.hasData() ?
						read(nsIndex, nodeID).toString() : std::string("N/A"))
					<< std::endl;
			}
			else if (ref->nodeId.nodeId.identifierType == UA_NODEIDTYPE_STRING)
			{
				UA_String nodeID = ref->nodeId.nodeId.identifier.string;
				std::string nID = std::string((char*) nodeID.data, nodeID.length);
				getValueNodeType(nsIndex, nID, var);
				//os << "TYPE: [" << getValueNodeType(nsIndex, nID) << ']' << std::endl;
				os << std::setw(colWidths.at(0)) << nsIndex << std::setw(11)
					<< std::setw(colWidths.at(1)) << nID
					<< std::setw(colWidths.at(2)) << std::string((char*) bName.data, bName.length)
					<< std::setw(colWidths.at(3)) << std::string((char*) dName.data, dName.length)
					<< std::setw(colWidths.at(4)) << (var.hasData() ?
						read(nsIndex, nID).toString() : std::string("N/A"))
					<< std::endl;
			}
			// TODO: distinguish further types
		}
	}
	UA_BrowseResponse_deleteMembers(&bResp);
}


} } // namespace IoT::OPC
