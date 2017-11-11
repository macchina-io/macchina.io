//
// MasterConnection.cpp
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
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
