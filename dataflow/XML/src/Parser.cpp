//
// Parser.cpp
//
// $Id$
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Dataflow/XML/Parser.h"
#include "IoT/Dataflow/Engine/AttributedObject.h"
#include "Poco/SAX/SAXParser.h"
#include "Poco/SAX/DefaultHandler.h"
#include "Poco/SAX/Attributes.h"
#include "Poco/SAX/InputSource.h"


namespace IoT {
namespace Dataflow {
namespace XML {


class DataflowHandler: public Poco::XML::DefaultHandler
{
public:
	DataflowHandler(IoT::Dataflow::Engine::Dataflow::Ptr pDataflow, IoT::Dataflow::Engine::NodeFactory& nodeFactory):
		_pDataflow(pDataflow),
		_nodeFactory(nodeFactory)
	{
	}
	
	// ContentHandler
	void startElement(const Poco::XML::XMLString& uri, const Poco::XML::XMLString& localName, const Poco::XML::XMLString& qname, const Poco::XML::Attributes& attributes)
	{
		if (qname == "node")
		{
			IoT::Dataflow::Engine::AttributedObject attrs;
			for (int i = 0; i < attributes.getLength(); ++i)
			{
				attrs.setAttribute(attributes.getQName(i), attributes.getValue(i));
			}
			IoT::Dataflow::Engine::Node::Ptr pNode = _nodeFactory.createNode(attrs.getAttribute("type"), attrs.getAttribute("id"), attrs, _pDataflow->scheduler());
			_pDataflow->addNode(pNode);
		}
		else if (qname == "connection")
		{
			_pDataflow->connect(attributes.getValue("from"), attributes.getValue("outlet"), attributes.getValue("to"), attributes.getValue("inlet"));
		}
	}
	
private:
	IoT::Dataflow::Engine::Dataflow::Ptr _pDataflow;
	IoT::Dataflow::Engine::NodeFactory& _nodeFactory;
};


Parser::Parser(IoT::Dataflow::Engine::NodeFactory& nodeFactory):
	_nodeFactory(nodeFactory)
{
}

	
Parser::~Parser()
{
}


IoT::Dataflow::Engine::Dataflow::Ptr Parser::parse(std::istream& istr)
{
	IoT::Dataflow::Engine::Dataflow::Ptr pDataflow = new IoT::Dataflow::Engine::Dataflow;
	DataflowHandler handler(pDataflow, _nodeFactory);

	Poco::XML::SAXParser parser;
	parser.setFeature(Poco::XML::XMLReader::FEATURE_NAMESPACES, false);
	parser.setContentHandler(&handler);
	
	Poco::XML::InputSource src(istr);
	parser.parse(&src);
	
	return pDataflow;
}


} } } // namespace IoT::Parser::XML
