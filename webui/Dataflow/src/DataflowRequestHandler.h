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
#include "Poco/Mutex.h"


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
	FileList listFiles(const std::string& dir);
	std::string lastFile(const std::string& dir);

	Poco::OSP::BundleContext::Ptr context() const
	{
		return _pContext;
	}

private:

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
