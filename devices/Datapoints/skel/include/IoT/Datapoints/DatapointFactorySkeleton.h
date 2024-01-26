//
// DatapointFactorySkeleton.h
//
// Library: IoT/Datapoints
// Package: Generated
// Module:  DatapointFactorySkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Datapoints_DatapointFactorySkeleton_INCLUDED
#define IoT_Datapoints_DatapointFactorySkeleton_INCLUDED


#include "IoT/Datapoints/DatapointFactoryRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Datapoints {


class DatapointFactorySkeleton: public Poco::RemotingNG::Skeleton
	/// A factory for the dynamic creation of Datapoints.
{
public:
	DatapointFactorySkeleton();
		/// Creates a DatapointFactorySkeleton.

	virtual ~DatapointFactorySkeleton();
		/// Destroys a DatapointFactorySkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& DatapointFactorySkeleton::remoting__typeId() const
{
	return IDatapointFactory::remoting__typeId();
}


} // namespace Datapoints
} // namespace IoT


#endif // IoT_Datapoints_DatapointFactorySkeleton_INCLUDED

