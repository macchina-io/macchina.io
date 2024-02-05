//
// BooleanDatapointImpl.h
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  BooleanDatapointImpl
//
// Definition of the BooleanDatapointImpl class.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Datapoints_BooleanDatapointImpl_INCLUDED
#define IoT_Datapoints_BooleanDatapointImpl_INCLUDED


#include "IoT/Datapoints/Datapoints.h"
#include "IoT/Datapoints/Types.h"
#include "IoT/Datapoints/BasicDatapointImpl.h"
#include "IoT/Devices/BooleanDatapoint.h"


namespace IoT {
namespace Datapoints {


class IoTDatapoints_API BooleanDatapointImpl: public BasicDatapointImpl<IoT::Devices::BooleanDatapoint, BooleanDatapointImpl>
	/// A basic implementation of a BooleanDatapoint.
{
public:
	using Interface = IoT::Devices::BooleanDatapoint;
	using Params = BooleanDatapointParams;

	BooleanDatapointImpl(const std::string& id, const Params& params);
		/// Creates the ScalarDatapointImpl.

	~BooleanDatapointImpl();
		/// Destroys the ScalarDatapointImpl.

	bool forceUpdate(bool value);
		/// Force an update, without performing an access check.

	// BooleanDatapoint
	bool value() const;
	Poco::Optional<bool> validValue() const;
	bool update(bool value);
	bool invert();

	// Datapoint
	void invalidate();
	bool valid() const;

	BooleanDatapointImpl() = delete;

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
	bool unsafeUpdate(bool value);

private:
	const std::string _id;
	const std::string _name;
	const int _access;
	Poco::Timestamp _updated;
	bool _value;
	bool _valid;
};


} } // namespace IoT::Datapoints


#endif // IoT_Datapoints_BooleanDatapointImpl_INCLUDED
