//
// BundleActivator.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
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
#include "SandboxRequestHandler.h"


namespace IoT {
namespace Web {
namespace Playground {


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
		// We need to obtain the BundleLoader via the Application's OSPSubsystem.
		Poco::Util::Application& app = Poco::Util::Application::instance();
		Poco::OSP::OSPSubsystem& ospSubsystem = app.getSubsystem<Poco::OSP::OSPSubsystem>();
		Poco::OSP::BundleLoader& bundleLoader = ospSubsystem.bundleLoader();
		
		Poco::Path sandboxPath(pContext->persistentDirectory(), SandboxRequestHandler::SANDBOX_BUNDLE + ".bndl");
		Poco::File sandboxDir(sandboxPath.toString());
		if (!sandboxDir.exists())
		{
			pContext->logger().information("Creating sandbox bundle.");
			sandboxDir.createDirectories();
			Poco::Path metaInfPath(sandboxPath, "META-INF");
			Poco::File metaInfDir(metaInfPath.toString());
			metaInfDir.createDirectory();
			
			Poco::Path manifestPath(metaInfPath, "manifest.mf");
			Poco::SharedPtr<std::istream> pManifestIStream = pContext->thisBundle()->getResource("sandbox/manifest.mf");
			Poco::FileOutputStream manifestOStream(manifestPath.toString());
			Poco::StreamCopier::copyStream(*pManifestIStream, manifestOStream);

			Poco::Path extensionsPath(sandboxPath, "extensions.xml");
			Poco::SharedPtr<std::istream> pExtensionsIStream = pContext->thisBundle()->getResource("sandbox/extensions.xml");
			Poco::FileOutputStream extensionsOStream(extensionsPath.toString());
			Poco::StreamCopier::copyStream(*pExtensionsIStream, extensionsOStream);	

			Poco::Path scriptPath(sandboxPath, SandboxRequestHandler::SANDBOX_SCRIPT);
			Poco::SharedPtr<std::istream> pScriptIStream = pContext->thisBundle()->getResource("sandbox/sandbox.js");
			Poco::FileOutputStream scriptOStream(scriptPath.toString());
			Poco::StreamCopier::copyStream(*pScriptIStream, scriptOStream);	
		}
		pContext->logger().information("Loading sandbox bundle.");
		Poco::OSP::Bundle::Ptr pSandboxBundle = bundleLoader.loadBundle(sandboxPath.toString());
		pSandboxBundle->resolve();
	}
		
	void stop(Poco::OSP::BundleContext::Ptr pContext)
	{
	}
};


} } } // namespace IoT::Web::Playground


POCO_BEGIN_NAMED_MANIFEST(WebServer, Poco::OSP::Web::WebRequestHandlerFactory)
	POCO_EXPORT_CLASS(IoT::Web::Playground::SandboxRequestHandlerFactory)
POCO_END_MANIFEST


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::Web::Playground::BundleActivator)
POCO_END_MANIFEST
