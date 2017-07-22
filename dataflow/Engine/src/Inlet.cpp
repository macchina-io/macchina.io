//
// Inlet.cpp
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: Inlet
// Module:  Inlet
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Dataflow/Engine/Inlet.h"
#include "IoT/Dataflow/Engine/Outlet.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


AbstractInlet::AbstractInlet(const std::string& name):
	Port(name)
{
}


AbstractInlet::~AbstractInlet()
{
}


void AbstractInlet::connect(AbstractOutlet& outlet)
{
	outlet.connect(*this);
}


void AbstractInlet::disconnect(AbstractOutlet& outlet)
{
	outlet.disconnect(*this);
}


} } } // namespace IoT::Dataflow::Engine
