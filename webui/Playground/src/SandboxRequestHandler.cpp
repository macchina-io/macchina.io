//
// SandboxRequestHandler.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "SandboxRequestHandler.h"
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
#include "Utility.h"


namespace IoT {
namespace Web {
namespace Playground {


const std::string SandboxRequestHandler::SANDBOX_BUNDLE("io.macchina.webui.playground.sandbox");
const std::string SandboxRequestHandler::SANDBOX_SCRIPT("sandbox.js");
const std::string SandboxRequestHandler::SANDBOX_PROPERTIES("sandbox.properties");
Poco::FastMutex SandboxRequestHandler::_mutex;


SandboxRequestHandler::SandboxRequestHandler(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext)
{
}


void SandboxRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
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

	Poco::Path p(request.getURI(), Poco::Path::PATH_UNIX);
	p.makeFile();
	std::string action = p.getBaseName();

	if (!(pAuthService->authorize(username, "bundleAdmin") && (action == "export" || action == "download" || request.get("X-XSRF-TOKEN", "") == pSession->csrfToken())))
	{
		response.setContentLength(0);
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_FORBIDDEN);
		response.send();
		return;
	}

	context()->logger().debug("Performing action: " + action);

	std::string bundleState;
	std::string error;
	Poco::OSP::Bundle::Ptr pBundle = context()->findBundle(SANDBOX_BUNDLE);
	if (pBundle)
	{
		try
		{
			if (action == "run")
			{
				pBundle->start();
			}
			else if (action == "stop")
			{
				pBundle->stop();
			}
			else if (action == "restart")
			{
				if (pBundle->state() == Poco::OSP::Bundle::BUNDLE_ACTIVE)
				{
					pBundle->stop();
				}
				pBundle->start();
			}
			else if (action == "load")
			{
				handleLoad(pBundle, request, response);
				return;
			}
			else if (action == "save")
			{
				Poco::Path scriptPath(pBundle->path());
				scriptPath.makeDirectory();
				scriptPath.setFileName(SANDBOX_SCRIPT);
				Poco::FileOutputStream ostr(scriptPath.toString());
				Poco::StreamCopier::copyStream(request.stream(), ostr);
			}
			else if (action == "info")
			{
				handleInfo(pBundle, request, response);
				return;
			}
			else if (action == "export")
			{
				handleExport(pBundle, request, response);
				return;
			}
			else if (action == "download")
			{
				handleDownload(pBundle, request, response);
				return;
			}
			else if (action == "state")
			{
				// Nothing to do
			}
			else
			{
				context()->logger().error("Invalid action: " + action);
			}
		}
		catch (Poco::Exception& exc)
		{
			error = exc.displayText();
			context()->logger().log(exc);
		}
		bundleState = pBundle->stateString();
	}
	else
	{
		error = "The sandbox bundle is not available.";
	}

	response.setContentType("application/json");
	response.setChunkedTransferEncoding(true);
	response.send()
		<< "{"
		<<   "\"bundleState\":" << Utility::jsonize(bundleState) << ","
		<<   "\"error\":" << Utility::jsonize(error)
		<< "}";
}


void SandboxRequestHandler::handleInfo(Poco::OSP::Bundle::Ptr pBundle, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	std::string name;
	std::string symbolicName;
	std::string version("1.0.0");
	std::string vendor;
	std::string copyright(Poco::format("(c) %04d", Poco::DateTime().year()));
	Poco::Path propsPath(pBundle->path());
	propsPath.makeDirectory();
	propsPath.setFileName(SANDBOX_PROPERTIES);
	Poco::File propsFile(propsPath.toString());
	if (propsFile.exists())
	{
		Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> pProps = new Poco::Util::PropertyFileConfiguration(propsPath.toString());
		name = pProps->getString("name", name);
		symbolicName = pProps->getString("symbolicName", symbolicName);
		version = pProps->getString("version", version);
		vendor = pProps->getString("vendor", vendor);
		copyright = pProps->getString("copyright", copyright);
	}
	response.set("Cache-Control", "no-cache");
	response.setContentType("application/json");
	if (request.getMethod() != Poco::Net::HTTPRequest::HTTP_HEAD)
	{
		response.setChunkedTransferEncoding(true);
		response.send()
			<< "{"
			<<   "\"bundleState\":" << Utility::jsonize(pBundle->stateString()) << ","
			<<   "\"bundleInfo\":"
			<<     "{"
			<<       "\"name\":" << Utility::jsonize(name) << ","
			<<       "\"symbolicName\":" << Utility::jsonize(symbolicName) << ","
			<<       "\"version\":" << Utility::jsonize(version) << ","
			<<       "\"vendor\":" << Utility::jsonize(vendor) << ","
			<<       "\"copyright\":" << Utility::jsonize(copyright)
			<<     "},"
			<<   "\"error\":\"\""
			<< "}";
	}
	else
	{
		response.send();
	}
}


void SandboxRequestHandler::handleExport(Poco::OSP::Bundle::Ptr pBundle, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
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
	propsPath.setFileName(SANDBOX_PROPERTIES);
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

	Poco::Path extensionsPath(exportPath, "extensions.xml");
	Poco::FileOutputStream extensionsStream(extensionsPath.toString());
	extensionsStream
		<< "<extensions>\n"
		<< "\t<extension point=\"com.appinf.osp.js\" script=\"main.js\"/>\n"
		<< "</extensions>\n";
	extensionsStream.close();

	Poco::Path sandboxScriptPath(pBundle->path(), SANDBOX_SCRIPT);
	Poco::FileInputStream sandboxScriptStream(sandboxScriptPath.toString());
	Poco::Path scriptPath(exportPath);
	scriptPath.makeDirectory();
	scriptPath.setFileName("main.js");
	Poco::FileOutputStream scriptStream(scriptPath.toString());
	Poco::StreamCopier::copyStream(sandboxScriptStream, scriptStream);
	scriptStream.close();
	sandboxScriptStream.close();

	Poco::Path exportBndlPath(context()->temporaryDirectory(), bundleFileName);
	Poco::FileOutputStream exportBndlStream(exportBndlPath.toString());
	Poco::Zip::Compress compress(exportBndlStream, true);
	compress.addRecursive(exportPath.toString(), Poco::Zip::ZipCommon::CM_AUTO, Poco::Zip::ZipCommon::CL_MAXIMUM, true);
	compress.close();
	exportBndlStream.close();

	response.set("Content-Disposition", Poco::format("attachment; filename=%s", bundleFileName));
	response.set("Cache-Control", "no-cache, no-store");
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
}


void SandboxRequestHandler::handleLoad(Poco::OSP::Bundle::Ptr pBundle, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	handleDownload(pBundle, request, response, false);
}


void SandboxRequestHandler::handleDownload(Poco::OSP::Bundle::Ptr pBundle, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, bool withContentDisposition)
{
	Poco::Path scriptPath(pBundle->path());
	scriptPath.makeDirectory();
	scriptPath.setFileName(SANDBOX_SCRIPT);

	response.set("Cache-Control", "no-cache, no-store");
	if (withContentDisposition)
	{
		response.set("Content-Disposition", "attachment; filename=sandbox.js");
	}
	if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET)
	{
		response.sendFile(scriptPath.toString(), "text/javascript");
	}
	else if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_HEAD)
	{
		Poco::File f(scriptPath.toString());
		Poco::Timestamp dateTime = f.getLastModified();
		Poco::File::FileSize length = f.getSize();
		response.set("Last-Modified", Poco::DateTimeFormatter::format(dateTime, Poco::DateTimeFormat::HTTP_FORMAT));
		response.setContentLength64(length);
		response.setContentType("text/javascript");
		response.send();
	}
}


Poco::Net::HTTPRequestHandler* SandboxRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	return new SandboxRequestHandler(context());
}


} } } // namespace IoT::Web::Playground
