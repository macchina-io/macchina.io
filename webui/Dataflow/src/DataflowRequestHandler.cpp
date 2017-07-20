//
// DataflowRequestHandler.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "DataflowRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Util/PropertyFileConfiguration.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/Auth/AuthService.h"
#include "Poco/Zip/Compress.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Format.h"
#include "Poco/AutoPtr.h"
#include "Poco/URI.h"
#include "Utility.h"
#include <iostream>

namespace IoT {
namespace Web {
namespace Dataflow {


const std::string DataflowRequestHandler::DATAFLOW_PROPERTIES("dataflow.properties");
Poco::FastMutex DataflowRequestHandler::_mutex;


DataflowRequestHandler::DataflowRequestHandler(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext)
{
}


void DataflowRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	Poco::OSP::Web::WebSession::Ptr pSession;
	{
		Poco::OSP::ServiceRef::Ptr pWebSessionManagerRef = context()->registry().findByName(Poco::OSP::Web::WebSessionManager::SERVICE_NAME);
		if (pWebSessionManagerRef)
		{
			Poco::OSP::Web::WebSessionManager::Ptr pWebSessionManager = pWebSessionManagerRef->castedInstance<Poco::OSP::Web::WebSessionManager>();
			pSession = pWebSessionManager->find(context()->thisBundle()->properties().getString("websession.id"), request);
		}
	}
	if (!Utility::isAuthenticated(pSession, response)) return;

	std::string username = pSession->getValue<std::string>("username");
	Poco::OSP::Auth::AuthService::Ptr pAuthService = Poco::OSP::ServiceFinder::findByName<Poco::OSP::Auth::AuthService>(context(), "osp.auth");

	if (!pAuthService->authorize(username, "bundleAdmin")) // FIXME: proper role auth
	{
		response.setContentLength(0);
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_FORBIDDEN);
		response.send();
		return;
	}

	Poco::Path p(request.getURI(), Poco::Path::PATH_UNIX);
	std::string action = p.getBaseName();
	std::string error;
	std::string file, xml;
	try
	{
		Poco::Net::HTMLForm form(request, request.stream());
		if (action == "open")
		{
			//context()->logger().information("Open: " + form["filename"]);
			/*Poco::Net::NameValueCollection::ConstIterator it = form.begin();
			Poco::Net::NameValueCollection::ConstIterator end = form.end();
			for (; it != end; ++it)
			{
				std::cout << it->first << ": " << it->second << std::endl;
			}*/
		}
		else if (action == "save")
		{
			if (form.has("filename") && form.has("xml"))
			{
				file = form["filename"];
				context()->logger().information("Save: " + file);
				Poco::URI::decode(form["xml"], xml, false);
				context()->logger().debug("XML: " + xml);
				Poco::Path path = context()->persistentDirectory();
				path.setFileName(file);
				Poco::FileOutputStream fos(path.toString(), std::ios_base::trunc);
				poco_assert (fos.good());
				fos << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\"?>" << std::endl;
				fos << xml;
			}
		}
	}
	catch (Poco::Exception& exc)
	{
		error = exc.displayText();
		context()->logger().log(exc);
	}
	
	response.setContentType("application/json");
	response.setChunkedTransferEncoding(true);
	response.send() << "{\"error\":" << Utility::jsonize(error) << "}";
}


void DataflowRequestHandler::handleExport(Poco::OSP::Bundle::Ptr pBundle, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
#if 0
	Poco::Net::HTMLForm form(request, request.stream());
	std::string name = form.get("name", "");
	std::string symbolicName = form.get("symbolicName", "");
	std::string version = form.get("version", "");
	std::string vendor = form.get("vendor", "");
	std::string copyright = form.get("copyright", "");
	
	if (name.empty() || symbolicName.empty() || version.empty() || 
	    symbolicName.find("..") != std::string::npos || 
	    version.find("..") != std::string::npos)
	{
		context()->logger().error(Poco::format(
			"Bundle export: bad form parameters submitted: name=\"%s\", symbolicName=\"%s\", version=\"%s\"", 
			name, symbolicName, version));
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
		response.setContentLength(0);
		response.send();
		return;
	}
	
	Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> pProps = new Poco::Util::PropertyFileConfiguration();
	pProps->setString("name", name);
	pProps->setString("symbolicName", symbolicName);
	pProps->setString("version", version);
	pProps->setString("vendor", vendor);
	pProps->setString("copyright", copyright);
	
	Poco::Path propsPath(pBundle->path());
	propsPath.makeDirectory();
	propsPath.setFileName(DATAFLOW_PROPERTIES);
	pProps->save(propsPath.toString());

	std::string bundleFileName(symbolicName);
	bundleFileName += "_";
	bundleFileName += version;
	bundleFileName += ".bndl";
	
	Poco::Path exportPath(context()->temporaryDirectory(), "export.bndl");
	Poco::File exportDir(exportPath.toString());
	if (exportDir.exists())
	{
		exportDir.remove(true);
	}
	
	exportDir.createDirectories();
	Poco::Path metaInfPath(exportPath, "META-INF");
	Poco::File metaInfDir(metaInfPath.toString());
	metaInfDir.createDirectories();
	
	Poco::Path manifestPath(metaInfPath, "manifest.mf");
	Poco::FileOutputStream manifestStream(manifestPath.toString());
	manifestStream 
		<< "Manifest-Version: 1.0\n"
		<< "Bundle-Name: " << name << "\n"
		<< "Bundle-SymbolicName: " << symbolicName << "\n"
		<< "Bundle-Version: " << version << "\n"
		<< "Bundle-Vendor: " << vendor << "\n"
		<< "Bundle-Copyright: " << copyright << "\n"
		<< "Bundle-RunLevel: 900\n"
		<< "Bundle-LazyStart: false\n";
	manifestStream.close();
/*
	Poco::Path extensionsPath(exportPath, "extensions.xml");
	Poco::FileOutputStream extensionsStream(extensionsPath.toString());
	extensionsStream
		<< "<extensions>\n"
		<< "\t<extension point=\"com.appinf.osp.js\" script=\"main.js\"/>\n"
		<< "</extensions>\n";
	extensionsStream.close();

	Poco::Path dataflowScriptPath(pBundle->path(), DATAFLOW_SCRIPT);
	Poco::FileInputStream dataflowScriptStream(dataflowScriptPath.toString());
	Poco::Path scriptPath(exportPath);
	scriptPath.makeDirectory();
	scriptPath.setFileName("main.js");
	Poco::FileOutputStream scriptStream(scriptPath.toString());
	Poco::StreamCopier::copyStream(dataflowScriptStream, scriptStream);
	scriptStream.close();
	dataflowScriptStream.close();
*/
	Poco::Path exportBndlPath(context()->temporaryDirectory(), bundleFileName);
	Poco::FileOutputStream exportBndlStream(exportBndlPath.toString());
	Poco::Zip::Compress compress(exportBndlStream, true);
	compress.addRecursive(exportPath.toString(), Poco::Zip::ZipCommon::CM_AUTO, Poco::Zip::ZipCommon::CL_MAXIMUM, true);
	compress.close();
	exportBndlStream.close();
	
	response.set("Content-Disposition", Poco::format("attachment; filename=%s", bundleFileName));
	response.sendFile(exportBndlPath.toString(), "application/octet-stream");
	
	try
	{
		exportDir.remove(true);
		Poco::File exportBndlFile(exportBndlPath.toString());
		exportBndlFile.remove();
	}
	catch (Poco::Exception& exc)
	{
		context()->logger().error(Poco::format("Error cleaning up after bundle export: %s", exc.displayText()));
	}
#endif
}


Poco::Net::HTTPRequestHandler* DataflowRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	return new DataflowRequestHandler(context());
}


} } } // namespace IoT::Web::Dataflow
