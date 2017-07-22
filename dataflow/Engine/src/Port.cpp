//
// Port.cpp
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: Port
// Module:  Port
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Dataflow/Engine/Port.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


Port::Port(const std::string& name):
	_name(name)
{
}


Port::~Port()
{
}


} } } // namespace IoT::Dataflow::Engine
