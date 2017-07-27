//
// Output.h
//
// $Id$
//
// Library: IoT/Dataflow/Runner
// Package: OutputNode
// Module:  OutputNode
//
// Definition of the Output class.
//
// Copyright (c) 2017, Applied Informatics Software Runnerering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Runner_Output_INCLUDED
#define IoT_Dataflow_Runner_Output_INCLUDED


#include "IoT/Dataflow/Runner/Runner.h"
#include "IoT/Dataflow/Runner/NodeFactoryService.h"
#include "IoT/Dataflow/Engine/Node.h"
#include "IoT/Dataflow/Engine/Inlet.h"
#include "Poco/Logger.h"


namespace IoT {
namespace Dataflow {
namespace Runner {


template <typename T>
class Output: public IoT::Dataflow::Engine::Node
	/// This class writes whatever it receives on its input
	/// to a Poco::Logger.
{
public:
	Output(const std::string& id, const AttributedObject& attrs):
		Node(id, attrs),
		_pInput(new IoT::Dataflow::Engine::Inlet<T>("input")),
		_format(attrs.getAttribute("format", std::string("%f"))),
		_logger(Poco::Logger::get(attrs.getAttribute("logger", std::string("dataflow.output"))))
	{
		addInlet(_pInput);
		
		_pInput->updated += Poco::delegate(this, &Output::update);
	}
	
	void update(const T& value)
	{
		_logger.information(_format, value);
	}
	
private:
	typename IoT::Dataflow::Engine::Inlet<T>::Ptr _pInput;
	std::string _format;
	Poco::Logger& _logger;
};


class IoTDataflowRunner_API OutputNodeFactoryService: public NodeFactoryService
	/// The NodeFactoryService for "io.macchina.dataflow.output" node type.
{
public:
	typedef Poco::AutoPtr<OutputNodeFactoryService> Ptr;

	OutputNodeFactoryService();
		/// Creates a OutputNodeFactoryService.

	~OutputNodeFactoryService();
		/// Destroys the OutputNodeFactoryService.
	
	// NodeFactoryService
	IoT::Dataflow::Engine::Node::Ptr createNode(const std::string& type, const std::string& id, const IoT::Dataflow::Engine::AttributedObject& attrs, IoT::Dataflow::Engine::Scheduler& scheduler);

	// Service
	const std::type_info& type() const;	
	bool isA(const std::type_info& otherType) const;
};


} } } // namespace IoT::Dataflow::Runner


#endif // IoT_Dataflow_Runner_Output_INCLUDED
