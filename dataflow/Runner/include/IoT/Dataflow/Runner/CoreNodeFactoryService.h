//
// CoreNodeFactoryService.h
//
// $Id$
//
// Library: IoT/Dataflow/Runner
// Package: CoreNodeFactoryService
// Module:  CoreNodeFactoryService
//
// Definition of the CoreNodeFactoryService class.
//
// Copyright (c) 2017, Applied Informatics Software Runnerering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Runner_CoreNodeFactoryService_INCLUDED
#define IoT_Dataflow_Runner_CoreNodeFactoryService_INCLUDED


#include "IoT/Dataflow/Runner/NodeFactoryService.h"
#include "IoT/Dataflow/Engine/CoreNodeFactory.h"


namespace IoT {
namespace Dataflow {
namespace Runner {


class IoTDataflowRunner_API CoreNodeFactoryService: public NodeFactoryService
	/// The NodeFactoryService for "core.*" node types.
{
public:
	typedef Poco::AutoPtr<CoreNodeFactoryService> Ptr;

	CoreNodeFactoryService();
		/// Creates a CoreNodeFactoryService.

	~CoreNodeFactoryService();
		/// Destroys the NodeFactoryService.
	
	// NodeFactoryService
	IoT::Dataflow::Engine::Node::Ptr createNode(const std::string& type, const std::string& id, const IoT::Dataflow::Engine::AttributedObject& attrs, IoT::Dataflow::Engine::Scheduler& scheduler);

	// Service
	const std::type_info& type() const;	
	bool isA(const std::type_info& otherType) const;
	
private:
	IoT::Dataflow::Engine::CoreNodeFactory _coreNodeFactory;
};


} } } // namespace IoT::Dataflow::Runner


#endif // IoT_Dataflow_Runner_CoreNodeFactoryService_INCLUDED
