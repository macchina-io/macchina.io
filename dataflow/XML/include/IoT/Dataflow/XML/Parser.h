//
// Parser.h
//
// $Id$
//
// Definition of the Parser class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Parser_INCLUDED
#define IoT_Dataflow_Parser_INCLUDED


#include "IoT/Dataflow/XML/XML.h"
#include "IoT/Dataflow/Engine/Dataflow.h"
#include "IoT/Dataflow/Engine/NodeFactory.h"


namespace IoT {
namespace Dataflow {
namespace XML {


class Parser
	/// This class parses a Dataflow from an XML representation.
	///
	/// The Dataflow XML consists of three elements:
	///   - dataflow: The document root element
	///   - node: Represents a Dataflow Node; attribute "type" specifies the
	///     type of node (see IoT::Dataflow::Engine::NodeFactory); attribute "id"
	///     contains the node name. Any other attributes are passed to the
	///     NodeFactory in an AttributedObject.
	///   - connection: Represents a connection between an outlet and an inlet.
	///     Attributes "from" and "to" specify the IDs (names) of the
	///     respective nodes, attributes "inlet" and "outlet" specify the names of the
	///     source node's outlet and the target node's inlet, respectively.
	///
	/// The order of node and connection elements does not matter, except that nodes
	/// must be defined before connections referring to them.
	///
	/// Example:
	///     <dataflow>
	///         <node type="core.arithmetic.add" id="1"/>
	///         <node type="core.computation.max" id="2"/>
	///         <connection from="1" outlet="output" to="2" inlet="first"/>
	///     </dataflow>
{
public:
	Parser(IoT::Dataflow::Engine::NodeFactory& nodeFactory);
		/// Creates the Parser, using the given NodeFactory.
		
	~Parser();
		/// Destroys the Parser.

	IoT::Dataflow::Engine::Dataflow::Ptr parse(std::istream& istr);
		/// Parses the Dataflow XML from the given input stream.
		///
		/// Returns the Dataflow object or throws an appropriate
		/// subclass of Poco::Exception if anything goes wrong.

private:
	Parser();
	Parser(const Parser&);
	Parser& operator = (const Parser&);

	IoT::Dataflow::Engine::NodeFactory& _nodeFactory;
};


} } } // namespace IoT::Parser::XML



#endif // IoT_Dataflow_Parser_INCLUDED
