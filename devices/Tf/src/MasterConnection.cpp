//
// MasterConnection.cpp
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Tf/MasterConnection.h"
#include "MasterConnectionImpl.h"


namespace IoT {
namespace Tf {


MasterConnection::MasterConnection()
{
}

	
MasterConnection::~MasterConnection()
{
}


MasterConnection::Ptr MasterConnection::create()
{
	return new MasterConnectionImpl;
}


} } // namespace IoT::Tf
