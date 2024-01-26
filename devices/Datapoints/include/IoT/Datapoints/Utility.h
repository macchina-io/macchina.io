//
// Types.h
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  Utility
//
// Definition of Utility class.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Datapoints_Utility_INCLUDED
#define IoT_Datapoints_Utility_INCLUDED


#include "IoT/Datapoints/Datapoints.h"


namespace IoT {
namespace Datapoints {


class IoTDatapoints_API Utility
{
public:
	static std::string accessString(int access);
		/// Returns a string representation of access mode ("ro", "rw", "wo");
};


} } // namespace IoT::Datapoints


#endif // IoT_Datapoints_Utility_INCLUDED
