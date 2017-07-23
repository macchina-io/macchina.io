//
// DataflowExtensionPoint.cpp
//
// $Id$
//
// Library: IoT/Dataflow/Runner
// Package: DataflowExtensionPoint
// Module:  DataflowExtensionPoint
//
// Copyright (c) 2017, Applied Informatics Software Runnerering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Dataflow/Runner/DataflowExtensionPoint.h"
#include "IoT/Dataflow/Runner/NodeFactory.h"
#include "IoT/Dataflow/XML/Parser.h"
#include "Poco/OSP/BundleEvents.h"


namespace IoT {
namespace Dataflow {
namespace Runner {


DataflowExtensionPoint::DataflowExtensionPoint(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext)
{
	_pContext->events().bundleStopped += Poco::delegate(this, &DataflowExtensionPoint::onBundleStopped);
}


DataflowExtensionPoint::~DataflowExtensionPoint()
{
	_pContext->events().bundleStopped -= Poco::delegate(this, &DataflowExtensionPoint::onBundleStopped);
}


void DataflowExtensionPoint::handleExtension(Poco::OSP::Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem)
{
	std::string sourcePath = pExtensionElem->getAttribute("source");
	
#if __cplusplus < 201103L
	std::auto_ptr<std::istream> pStream(pBundle->getResource(sourcePath));
#else
	std::unique_ptr<std::istream> pStream(pBundle->getResource(sourcePath));
#endif

	NodeFactory nodeFactory(_pContext);
	IoT::Dataflow::XML::Parser parser(nodeFactory);
	IoT::Dataflow::Engine::Dataflow::Ptr pDataflow = parser.parse(*pStream);

	std::string dataflowURI("bndl://");
	dataflowURI += pBundle->symbolicName();
	if (dataflowURI.empty() || dataflowURI[0] != '/') dataflowURI += "/";
	dataflowURI += sourcePath;

	pDataflow->setAttribute("uri", dataflowURI);
	pDataflow->setAttribute("bundle", pBundle->symbolicName());

	{
		Poco::FastMutex::ScopedLock lock(_mutex);
		_dataflows.push_back(pDataflow);
	}
	
	_pContext->logger().information("Starting dataflow %s.", dataflowURI);
	pDataflow->start();
}


void DataflowExtensionPoint::onBundleStopped(const void* pSender, Poco::OSP::BundleEvent& ev)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	Poco::OSP::Bundle::ConstPtr pBundle = ev.bundle();
	for (auto it = _dataflows.begin(); it != _dataflows.end();)
	{
		if ((*it)->getAttribute("bundle") == pBundle->symbolicName())
		{
			_pContext->logger().information("Stopping dataflow %s.", (*it)->getAttribute("uri"));
			(*it)->stop();
			it = _dataflows.erase(it);
		}
		else ++it;
	}
}


} } } // namespace IoT::Dataflow::Runner
