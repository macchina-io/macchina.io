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

	class NodeHandler: public Poco::XML::ContentHandler
	{
	public:
		typedef std::multimap<int, int> SourceTargetMap;

		struct Connector
		{
			std::string from;
			std::string outlet;
			std::string to;
			std::string inlet;
		};

		NodeHandler() = delete;

		NodeHandler(Poco::XML::AutoPtr<Poco::XML::Document> pDFDoc,
			Poco::XML::AutoPtr<Poco::XML::Element> pDataflow): _pDFDoc(pDFDoc), _pDataflow(pDataflow)
		{
		}

		~NodeHandler()
		{
		}

		void resolve()
		{
			std::string source, target;
			SourceTargetMap::const_iterator it = _sourceTargetMap.begin();
			SourceTargetMap::const_iterator end = _sourceTargetMap.end();
			for (; it != end; ++it)
			{
				source = getDFNodeName(it->first);
				target = getDFNodeName(it->second);
				if(source.empty() || target.empty())
				{
					throw Poco::NotFoundException("mxGraph names for pair (" +
						Poco::NumberFormatter::format(it->first) + ", " +
						Poco::NumberFormatter::format(it->second) + ": (" +
						source + ", " + target + ")");
				}
				Poco::XML::AutoPtr<Poco::XML::Element> pDFNode = _pDFDoc->createElement("connection");
				_pDataflow->appendChild(pDFNode);
				pDFNode->setAttribute("from", source);
				pDFNode->setAttribute("to", target);
				//TODO: inlet and outlet
			}
		}

		void add(int source, int target)
		{
			_sourceTargetMap.insert(SourceTargetMap::value_type(source, target));
		}

		void setDocumentLocator(const Poco::XML::Locator*) { }
		void startDocument() { }
		void endDocument() { }
		
		void startElement(const Poco::XML::XMLString& uri,
			const Poco::XML::XMLString& localName,
			const Poco::XML::XMLString& qname,
			const Poco::XML::Attributes& attributes)
		{
			/*where("startElement");
			std::cout << "uri:       " << uri << std::endl
					<< "localName: " << localName << std::endl
					<< "qname:     " << qname << std::endl;
			std::cout << "Attributes: " << std::endl;
			for (int i = 0; i < attributes.getLength(); ++i)
			{
				std::cout << attributes.getLocalName(i) << "=" << attributes.getValue(i) << std::endl;
			}*/
		}
		
		void endElement(const Poco::XML::XMLString&, const Poco::XML::XMLString&, const Poco::XML::XMLString&) { }
		void characters(const Poco::XML::XMLChar ch[], int, int) { }
		void ignorableWhitespace(const Poco::XML::XMLChar ch[], int, int) { }
		void processingInstruction(const Poco::XML::XMLString&, const Poco::XML::XMLString&) { }
		void startPrefixMapping(const Poco::XML::XMLString&, const Poco::XML::XMLString&) { }
		void endPrefixMapping(const Poco::XML::XMLString&) { }
		void skippedEntity(const Poco::XML::XMLString&) { }

	private:
		std::string getDFNodeName(int id)
		{
			Poco::XML::NodeIterator it(_pDFDoc, Poco::XML::NodeFilter::SHOW_ALL);
			Poco::XML::Node* pNode(it.nextNode());
			while (pNode)
			{
				Poco::XML::NamedNodeMap* pAttrs = pNode->attributes();
				if (pAttrs)
				{
					if (pNode->nodeName() == "object") // node
					{
						for (int i = 0; i < pAttrs->length(); ++i)
						{
							Poco::XML::Node* pAttr = pAttrs->item(i);
							if (pAttr)
							{
								if (pAttr->nodeName() == "mxId" &&
									Poco::NumberParser::parse(pAttr->nodeValue()) == id)
								{
									return pAttrs->getNamedItem("name")->nodeValue();
								}
							}
						}
					}
				}
				pNode = it.nextNode();
			}
			throw Poco::NotFoundException("mxGraph node name for id " + Poco::NumberFormatter::format(id));
		}

		std::vector<Connector> _connectors;
		SourceTargetMap _sourceTargetMap;
		Poco::XML::AutoPtr<Poco::XML::Document> _pDFDoc;
		Poco::XML::AutoPtr<Poco::XML::Element> _pDataflow;
	};

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
