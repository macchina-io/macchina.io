//
// VectorDatapointImpl.h
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  VectorDatapointImpl
//
// Definition of the VectorDatapointImpl class.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Datapoints_VectorDatapointImpl_INCLUDED
#define IoT_Datapoints_VectorDatapointImpl_INCLUDED


#include "IoT/Datapoints/Datapoints.h"
#include "IoT/Datapoints/Types.h"
#include "IoT/Datapoints/BasicDatapointImpl.h"
#include "IoT/Devices/VectorDatapoint.h"


namespace IoT {
namespace Datapoints {


class IoTDatapoints_API VectorDatapointImpl: public BasicDatapointImpl<IoT::Devices::VectorDatapoint, VectorDatapointImpl>
	/// A basic implementation of a VectorDatapoint.
{
public:
	using Interface = IoT::Devices::VectorDatapoint;
	using Params = VectorDatapointParams;

	VectorDatapointImpl(const std::string& id, const Params& params);
		/// Creates the ScalarDatapointImpl.

	~VectorDatapointImpl();
		/// Destroys the ScalarDatapointImpl.

	void forceUpdate(const Vector& value);
		/// Force an update, without performing an access check.

	// VectorDatapoint
	Vector value() const;
	Poco::Optional<Vector> validValue() const;
	void update(const Vector& value);

	// Datapoint
	void invalidate();
	bool valid() const;

	VectorDatapointImpl() = delete;

	static const std::string SYMBOLIC_NAME;
	static const std::string TYPE;

protected:
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getDeviceIdentifier(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	Poco::Any getUpdated(const std::string&) const;
	Poco::Any getAccess(const std::string&) const;
	void unsafeUpdate(const Vector& value);

private:
	const std::string _id;
	const std::string _name;
	const int _access;
	Poco::Timestamp _updated;
	Vector _value;
	bool _valid;
	mutable Poco::Mutex _mutex;
};


} } // namespace IoT::Datapoints


#endif // IoT_Datapoints_VectorDatapointImpl_INCLUDED
