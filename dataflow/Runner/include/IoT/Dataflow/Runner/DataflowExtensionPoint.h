//
// DataflowExtensionPoint.h
//
// $Id$
//
// Library: IoT/Dataflow/Runner
// Package: DataflowExtensionPoint
// Module:  DataflowExtensionPoint
//
// Definition of the DataflowExtensionPoint class.
//
// Copyright (c) 2017, Applied Informatics Software Runnerering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Runner_DataflowExtensionPoint_INCLUDED
#define IoT_Dataflow_Runner_DataflowExtensionPoint_INCLUDED


#include "IoT/Dataflow/Runner/Runner.h"
#include "IoT/Dataflow/Engine/Dataflow.h"
#include "Poco/OSP/ExtensionPoint.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/BundleEvent.h"
#include "Poco/Mutex.h"
#include <vector>


namespace IoT {
namespace Dataflow {
namespace Runner {


class IoTDataflowRunner_API DataflowExtensionPoint: public Poco::OSP::ExtensionPoint
	/// An extension point for starting dataflows contained
	/// in bundles.
	///
	/// The following extension point attributes are supported:
	///   - source: path (bundle resource) to the dataflow XML to be loaded
{
public:
	typedef Poco::AutoPtr<DataflowExtensionPoint> Ptr;

	DataflowExtensionPoint(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the DataflowExtensionPoint using the given BundleContext.
	
	~DataflowExtensionPoint();
		/// Destroys the DataflowExtensionPoint.
	
	// Poco::OSP::ExtensionPoint
	void handleExtension(Poco::OSP::Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem);

protected:
	void onBundleStopped(const void* pSender, Poco::OSP::BundleEvent& ev);

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	std::vector<IoT::Dataflow::Engine::Dataflow::Ptr> _dataflows;
	Poco::FastMutex _mutex;
};


} } } // namespace IoT::Dataflow::Runner


#endif // IoT_Dataflow_Runner_DataflowExtensionPoint_INCLUDED
