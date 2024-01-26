//
// JSExtensionPoint.h
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/JS/JSExtensionPoint.h"
#include "Poco/OSP/BundleEvents.h"
#include "Poco/StreamCopier.h"
#include "Poco/NumberParser.h"
#include "Poco/StringTokenizer.h"
#include "Poco/Format.h"
#include "Poco/Delegate.h"
#include <memory>


using namespace std::string_literals;


namespace Poco {
namespace OSP {
namespace JS {


JSExtensionPoint::JSExtensionPoint(BundleContext::Ptr pContext):
	_pContext(pContext)
{
	_pContext->events().bundleStopped += Poco::delegate(this, &JSExtensionPoint::onBundleStopped);
}


JSExtensionPoint::~JSExtensionPoint()
{
	_pContext->events().bundleStopped -= Poco::delegate(this, &JSExtensionPoint::onBundleStopped);
}


void JSExtensionPoint::handleExtension(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem)
{
	std::string scriptPath = pExtensionElem->getAttribute("script"s);
	Poco::UInt64 memoryLimit = pBundle->properties().getUInt64("osp.js.memoryLimit"s, JSExecutor::getDefaultMemoryLimit());
	std::string strMemoryLimit = pExtensionElem->getAttribute("memoryLimit"s);
	if (!strMemoryLimit.empty())
	{
		memoryLimit = Poco::NumberParser::parseUnsigned64(strMemoryLimit);
	}

	Poco::StringTokenizer tok(pExtensionElem->getAttribute("searchPaths"s), ",;"s, Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
	std::vector<std::string> moduleSearchPaths(tok.begin(), tok.end());

	std::string script;
	std::unique_ptr<std::istream> pStream(pBundle->getResource(scriptPath));
	Poco::StreamCopier::copyToString(*pStream, script);
	_pContext->logger().information(Poco::format("Starting script %s from bundle %s."s, scriptPath, pBundle->symbolicName()));
	std::string scriptURI("bndl://");
	scriptURI += pBundle->symbolicName();
	if (scriptPath.empty() || scriptPath[0] != '/') scriptURI += "/";
	scriptURI += scriptPath;
	TimedJSExecutor::Ptr pExecutor = new TimedJSExecutor(_pContext->contextForBundle(pBundle), pBundle, script, Poco::URI(scriptURI), moduleSearchPaths, memoryLimit);
	{
		FastMutex::ScopedLock lock(_mutex);
		_executors.push_back(pExecutor);
	}
	pExecutor->run();
}


void JSExtensionPoint::onBundleStopped(const void* pSender, Poco::OSP::BundleEvent& ev)
{
	FastMutex::ScopedLock lock(_mutex);

	Poco::OSP::Bundle::ConstPtr pBundle = ev.bundle();
	for (std::vector<TimedJSExecutor::Ptr>::iterator it = _executors.begin(); it != _executors.end();)
	{
		if ((*it)->bundle() == pBundle)
		{
			_pContext->logger().information(Poco::format("Stopping script %s."s, (*it)->uri().toString()));
			(*it)->stop();
			it = _executors.erase(it);
		}
		else ++it;
	}
}


} } } // namespace Poco::OSP::JS
