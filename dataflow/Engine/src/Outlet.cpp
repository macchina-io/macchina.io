//
// Outlet.cpp
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: Outlet
// Module:  Outlet
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Dataflow/Engine/Outlet.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


AbstractOutlet::AbstractOutlet(const std::string& name, Scheduler& scheduler):
	Port(name),
	_scheduler(scheduler)
{
}


AbstractOutlet::~AbstractOutlet()
{
}


} } } // namespace IoT::Dataflow::Engine
