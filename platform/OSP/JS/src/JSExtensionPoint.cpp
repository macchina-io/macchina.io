//
// JSExtensionPoint.h
//
// $Id: //poco/1.4/OSP/JS/src/JSExtensionPoint.cpp#1 $
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "JSExtensionPoint.h"
#include "Poco/StreamCopier.h"
#include "Poco/NumberParser.h"
#include "Poco/Format.h"
#include <memory>


namespace Poco {
namespace OSP {
namespace JS {


JSExtensionPoint::JSExtensionPoint(BundleContext::Ptr pContext):
	_pContext(pContext)
{
}


void JSExtensionPoint::handleExtension(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem)
{
	std::string scriptPath = pExtensionElem->getAttribute("script");
	Poco::UInt64 memoryLimit = 1024*1024;
	std::string strMemoryLimit = pExtensionElem->getAttribute("memoryLimit");
	if (!strMemoryLimit.empty())
	{
		memoryLimit = Poco::NumberParser::parseUnsigned64(strMemoryLimit);
	}
	std::string script;
	std::auto_ptr<std::istream> pStream(pBundle->getResource(scriptPath));
	Poco::StreamCopier::copyToString(*pStream, script);
	_pContext->logger().information(Poco::format("Starting script %s from bundle %s", scriptPath, pBundle->symbolicName()));
	std::string scriptURI("bndl://");
	scriptURI += pBundle->symbolicName();
	if (scriptPath.empty() || scriptPath[0] != '/') scriptURI += "/";
	scriptURI += scriptPath;
	TimedJSExecutor::Ptr pExecutor = new TimedJSExecutor(_pContext, pBundle, script, Poco::URI(scriptURI), memoryLimit);
	_executors.push_back(pExecutor);
	pExecutor->run();
}


} } } // namespace Poco::OSP::JS
