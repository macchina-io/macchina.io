//
// Types.h
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  Utility
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Datapoints/Utility.h"
#include "IoT/Datapoints/Types.h"


using namespace std::string_literals;


namespace IoT {
namespace Datapoints {


std::string Utility::accessString(int access)
{
	switch (access)
	{
	case ACCESS_NONE:
		return ""s;
	case ACCESS_READ:
		return "ro"s;
	case ACCESS_WRITE:
		return "wo"s;
	case ACCESS_ALL:
		return "rw"s;
	default:
		return "?"s;
	}
}


} } // namespace IoT::Datapoints
