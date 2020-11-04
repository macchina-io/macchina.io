//
// ExtensionPointService.cpp
//
// Library: OSP
// Package: ExtensionPointService
// Module:  ExtensionPointService
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/ExtensionPointService.h"
#include "Poco/OSP/BundleEvents.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/SAX/InputSource.h"
#include "Poco/Delegate.h"
#include <memory>


using namespace std::string_literals;


using Poco::AutoPtr;
using Poco::XML::Document;
using Poco::XML::Element;
using Poco::XML::Node;
using Poco::XML::InputSource;
using Poco::Logger;
using Poco::FastMutex;


namespace Poco {
namespace OSP {


const std::string ExtensionPointService::SERVICE_NAME("osp.core.xp");
const std::string ExtensionPointService::EXTENSIONS_XML("extensions.xml");
const std::string ExtensionPointService::EXTENSIONS_ELEM("extensions");
const std::string ExtensionPointService::EXTENSION_ELEM("extension");
const std::string ExtensionPointService::POINT_ATTR("point");


ExtensionPointService::ExtensionPointService(BundleEvents& events):
	_events(events),
	_logger(Logger::get(SERVICE_NAME))
{
	_events.bundleStarted += Poco::Delegate<ExtensionPointService, BundleEvent>(this, &ExtensionPointService::onBundleStarted);
	_events.bundleStopped += Poco::Delegate<ExtensionPointService, BundleEvent>(this, &ExtensionPointService::onBundleStopped);
}


ExtensionPointService::~ExtensionPointService()
{
	try
	{
		_events.bundleStarted -= Poco::Delegate<ExtensionPointService, BundleEvent>(this, &ExtensionPointService::onBundleStarted);
		_events.bundleStopped -= Poco::Delegate<ExtensionPointService, BundleEvent>(this, &ExtensionPointService::onBundleStopped);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void ExtensionPointService::registerExtensionPoint(Bundle::ConstPtr pBundle, const std::string& id, ExtensionPoint::Ptr pExtensionPoint)
{
	FastMutex::ScopedLock lock(_mutex);

	if (_xpMap.find(id) == _xpMap.end())
	{
		_xpMap[id] = pExtensionPoint;
		_bundleMap.insert(BundleMap::value_type(pBundle, id));

		_logger.information("Extension point %s registered by bundle %s."s, id, pBundle->symbolicName());
	}
	else throw Poco::ExistsException("Extension point", id);
}


void ExtensionPointService::unregisterExtensionPoint(const std::string& id)
{
	FastMutex::ScopedLock lock(_mutex);

	XPMap::iterator it = _xpMap.find(id);
	if (it != _xpMap.end())
	{
		_xpMap.erase(it);

		_logger.information("Extension point %s unregistered."s, id);
	}
	else throw Poco::NotFoundException("Extension point", id);
}


void ExtensionPointService::onBundleStarted(const void* pSender, BundleEvent& event)
{
	handleExtensions(event.bundle(), &ExtensionPointService::handleExtension, DIR_FORWARD);
}


void ExtensionPointService::onBundleStopped(const void* pSender, BundleEvent& event)
{
	handleExtensions(event.bundle(), &ExtensionPointService::removeExtension, DIR_REVERSE);

	FastMutex::ScopedLock lock(_mutex);

	BundleMap::const_iterator it = _bundleMap.find(event.bundle());
	while (it != _bundleMap.end() && it->first == event.bundle())
	{
		XPMap::iterator itxp = _xpMap.find(it->second);
		if (itxp != _xpMap.end())
		{
			_logger.information("Extension point %s unregistered because the bundle that defined it (%s) was stopped."s,
				itxp->first,
				event.bundle()->symbolicName());

			_xpMap.erase(itxp);
		}
		++it;
	}
}


void ExtensionPointService::handleExtensions(Bundle::ConstPtr pBundle, GenericHandler handler, Direction dir)
{
	std::unique_ptr<std::istream> pStream(pBundle->getResource(EXTENSIONS_XML));
	if (pStream.get())
	{
		try
		{
			handleExtensions(pBundle, *pStream, handler, dir);
		}
		catch (Poco::Exception& exc)
		{
			_logger.error("Failed to handle %s for bundle %s: %s"s,
			    EXTENSIONS_XML,
				pBundle->symbolicName(),
				exc.displayText());
		}
	}
}


void ExtensionPointService::handleExtensions(Bundle::ConstPtr pBundle, std::istream& istr, GenericHandler handler, Direction dir)
{
	Poco::XML::DOMParser parser;
	parser.setFeature(Poco::XML::XMLReader::FEATURE_NAMESPACES, false);
	parser.setFeature(Poco::XML::DOMParser::FEATURE_FILTER_WHITESPACE, true);
	Poco::XML::InputSource source(istr);
	AutoPtr<Document> pDoc(parser.parse(&source));
	Node* pRoot = pDoc->firstChild();
	while (pRoot && pRoot->nodeName() != EXTENSIONS_ELEM)
	{
		pRoot = pRoot->nextSibling();
	}
	if (pRoot)
	{
		Node* pNode = (dir == DIR_FORWARD ? pRoot->firstChild() : pRoot->lastChild());
		while (pNode)
		{
			if (pNode->nodeType() == Node::ELEMENT_NODE)
			{
				if (pNode->nodeName() == EXTENSION_ELEM)
				{
					Element* pElem = static_cast<Element*>(pNode);
					const std::string& id = pElem->getAttribute(POINT_ATTR);
					if (!id.empty())
					{
						(this->*handler)(pBundle, id, pElem);
					}
					else
					{
						_logger.error("No point attribute found in extension element of bundle %s."s, pBundle->symbolicName());
					}
				}
				else
				{
					_logger.warning("Unsupported element '%s' found in %s of bundle %s."s,
						pNode->nodeName(),
						EXTENSIONS_XML,
						pBundle->symbolicName());
				}
			}

			pNode = (dir == DIR_FORWARD ? pNode->nextSibling() : pNode->previousSibling());
		}
	}
	else throw Poco::NotFoundException("No extensions element found");
}


void ExtensionPointService::handleExtension(Bundle::ConstPtr pBundle, const std::string& id, Poco::XML::Element* pExtensionElement)
{
	try
	{
		ExtensionPoint::Ptr pXP = findExtensionPoint(id);
		pXP->handleExtension(pBundle, pExtensionElement);
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("Error handling extension point %s in bundle %s: %s"s,
			id,
			pBundle->symbolicName(),
			exc.displayText());
	}
}


void ExtensionPointService::removeExtension(Bundle::ConstPtr pBundle, const std::string& id, Poco::XML::Element* pExtensionElement)
{
	try
	{
		ExtensionPoint::Ptr pXP = findExtensionPoint(id);
		pXP->removeExtension(pBundle, pExtensionElement);
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("Error removing extension point %s in bundle %s: %s"s,
			id,
			pBundle->symbolicName(),
			exc.displayText());
	}
}


ExtensionPoint::Ptr ExtensionPointService::findExtensionPoint(const std::string& id)
{
	FastMutex::ScopedLock lock(_mutex);

	XPMap::const_iterator it = _xpMap.find(id);
	if (it != _xpMap.end())
		return it->second;
	else
		throw Poco::NotFoundException("Extension point", id);
}


const std::type_info& ExtensionPointService::type() const
{
	return typeid(ExtensionPointService);
}


bool ExtensionPointService::isA(const std::type_info& otherType) const
{
	std::string name(typeid(ExtensionPointService).name());
	return name == otherType.name() || Service::isA(otherType);
}


} } // namespace Poco::OSP
