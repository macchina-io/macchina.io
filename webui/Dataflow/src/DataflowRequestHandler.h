//
// DataflowRequestHandler.h
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef Dataflow_DataflowRequestHandler_INCLUDED
#define Dataflow_DataflowRequestHandler_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/DateTime.h"
#include "Poco/NumberParser.h"
#include "Poco/NumberFormatter.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/NodeIterator.h"
#include "Poco/DOM/NodeFilter.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/NamedNodeMap.h"
#include "Poco/SAX/ContentHandler.h"
#include "Poco/Mutex.h"
#include "Poco/Exception.h"


namespace IoT {
namespace Web {
namespace Dataflow {


class DataflowRequestHandler: public Poco::Net::HTTPRequestHandler
{
public:
	DataflowRequestHandler(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the DataflowRequestHandler using the given bundle context.

	// Poco::Net::HTTPRequestHandler
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

	static const std::string DATAFLOW_PROPERTIES;

protected:
	struct FileInfo
	{
		bool _isDirectory;
		bool _canRead;
		bool _canWrite;
		Poco::DateTime _lastModified;
		std::string _name;
	};

	typedef std::vector<FileInfo> FileList;

	void handleExport(Poco::OSP::Bundle::Ptr pBundle, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

private:
	void saveDataflow(const Poco::Path& path, const std::string& xml);
	FileList listFiles(const std::string& dir);
	std::string lastFile(const std::string& dir);

	Poco::OSP::BundleContext::Ptr context() const
	{
		return _pContext;
	}

	typedef std::multimap<int, int> SourceTargetMap;

	enum PortType
	{
		PORT_TYPE_INLET,
		PORT_TYPE_OUTLET
	};

	struct Port
	{
		PortType _type;
		std::string _name;
		int _id;
		std::string _parentId;
		std::string _dataType;
		std::string _value;
	};

	typedef std::map<int, Port> PortMap;
	typedef std::map<int, std::string> NodeMap;

	class ConnectionFilter: public Poco::XML::NodeFilter
	{
		short acceptNode(Poco::XML::Node* node)
		{
			if (node->nodeName() == "connection")
				return Poco::XML::NodeFilter::FILTER_ACCEPT;
			else
				return Poco::XML::NodeFilter::FILTER_REJECT;
		}
	};

	class DFNodeFilter: public Poco::XML::NodeFilter
	{
		short acceptNode(Poco::XML::Node* node)
		{
			if (node->nodeName() == "node")
				return Poco::XML::NodeFilter::FILTER_ACCEPT;
			else
				return Poco::XML::NodeFilter::FILTER_REJECT;
		}
	};

	void assignParentId(const NodeMap& nodes, const PortMap& ports, Poco::XML::Node* pCNode, const std::string& name);
	void assignNodeProperties(const NodeMap& nodes, const PortMap& ports, Poco::XML::Node* pDNode);
	std::string getNodeId(const NodeMap& nodes, const std::string& mxId);
		/// Translates mxGraph node Id (integer) to the dataflow one (string)

	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::Path _graphDir;
	static Poco::FastMutex _mutex;
};


class DataflowRequestHandlerFactory: public Poco::OSP::Web::WebRequestHandlerFactory
{
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
};


} } } // namespace IoT::Web::Dataflow


#endif // Dataflow_DataflowRequestHandler_INCLUDED
