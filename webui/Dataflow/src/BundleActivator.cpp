//
// BundleActivator.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/BundleLoader.h"
#include "Poco/OSP/OSPSubsystem.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/Util/Application.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Exception.h"
#include "Poco/ClassLibrary.h"
#include "Poco/SharedPtr.h"
#include "DataflowRequestHandler.h"


namespace IoT {
namespace Web {
namespace Dataflow {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}
	
	~BundleActivator()
	{
	}
	
	void start(Poco::OSP::BundleContext::Ptr pContext)
	{	
#if 0	
		// We need to obtain the BundleLoader via the Application's OSPSubsystem.
		Poco::Util::Application& app = Poco::Util::Application::instance();
		Poco::OSP::OSPSubsystem& ospSubsystem = app.getSubsystem<Poco::OSP::OSPSubsystem>();
		Poco::OSP::BundleLoader& bundleLoader = ospSubsystem.bundleLoader();
		
		Poco::Path dataflowPath(pContext->persistentDirectory(), DataflowRequestHandler::DATAFLOW_BUNDLE + ".bndl");
		Poco::File dataflowDir(dataflowPath.toString());
		if (!dataflowDir.exists())
		{
			pContext->logger().information("Creating dataflow bundle.");
			pContext->logger().information("Creating " + dataflowPath.toString());
			dataflowDir.createDirectories();
			pContext->logger().information("Created " + dataflowPath.toString());
			Poco::Path metaInfPath(dataflowPath, "META-INF");
			Poco::File metaInfDir(metaInfPath.toString());
			pContext->logger().information("Creating " + metaInfPath.toString());
			metaInfDir.createDirectory();
			pContext->logger().information("Created " + metaInfPath.toString());
			
			Poco::Path manifestPath(metaInfPath, "manifest.mf");
			pContext->logger().information("Copying " + manifestPath.toString());
			Poco::SharedPtr<std::istream> pManifestIStream = pContext->thisBundle()->getResource("dataflow/manifest.mf");
			if(!pManifestIStream) pContext->logger().error("dataflow/manifest.mf is null");
			Poco::FileOutputStream manifestOStream(manifestPath.toString());
			Poco::StreamCopier::copyStream(*pManifestIStream, manifestOStream);
			pContext->logger().information("Copied " + manifestPath.toString());
/*
			Poco::Path extensionsPath(dataflowPath, "extensions.xml");
			pContext->logger().information("Copying " + extensionsPath.toString());
			Poco::SharedPtr<std::istream> pExtensionsIStream = pContext->thisBundle()->getResource("dataflow/extensions.xml");
			if(!pExtensionsIStream) pContext->logger().error("dataflow/extensions.xml is null");
			Poco::FileOutputStream extensionsOStream(extensionsPath.toString());
			Poco::StreamCopier::copyStream(*pExtensionsIStream, extensionsOStream);
			pContext->logger().information("Copied " + extensionsPath.toString());

			Poco::Path scriptPath(dataflowPath, DataflowRequestHandler::DATAFLOW_SCRIPT);
			pContext->logger().information("Copying " + scriptPath.toString());
			Poco::SharedPtr<std::istream> pScriptIStream = pContext->thisBundle()->getResource("dataflow/dataflow.js");
			if(!pScriptIStream) pContext->logger().error("dataflow/dataflow.js is null");
			Poco::FileOutputStream scriptOStream(scriptPath.toString());
			Poco::StreamCopier::copyStream(*pScriptIStream, scriptOStream);
			pContext->logger().information("Copied " + scriptPath.toString());
*/
		}
		pContext->logger().information("Loading dataflow bundle.");
		Poco::OSP::Bundle::Ptr pDataflowBundle = bundleLoader.loadBundle(dataflowPath.toString());
		pDataflowBundle->resolve();
#endif
	}
		
	void stop(Poco::OSP::BundleContext::Ptr pContext)
	{
	}
};


} } } // namespace IoT::Web::Dataflow


POCO_BEGIN_NAMED_MANIFEST(WebServer, Poco::OSP::Web::WebRequestHandlerFactory)
	POCO_EXPORT_CLASS(IoT::Web::Dataflow::DataflowRequestHandlerFactory)
POCO_END_MANIFEST


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::Web::Dataflow::BundleActivator)
POCO_END_MANIFEST
