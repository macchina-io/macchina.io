//
// StringDatapointImpl.h
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  StringDatapointImpl
//
// Definition of the StringDatapointImpl class.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Datapoints_StringDatapointImpl_INCLUDED
#define IoT_Datapoints_StringDatapointImpl_INCLUDED


#include "IoT/Datapoints/Datapoints.h"
#include "IoT/Datapoints/Types.h"
#include "IoT/Datapoints/BasicDatapointImpl.h"
#include "IoT/Devices/StringDatapoint.h"


namespace IoT {
namespace Datapoints {


class IoTDatapoints_API StringDatapointImpl: public BasicDatapointImpl<IoT::Devices::StringDatapoint, StringDatapointImpl>
	/// A basic implementation of a StringDatapoint.
{
public:
	using Interface = IoT::Devices::StringDatapoint;
	using Params = StringDatapointParams;

	StringDatapointImpl(const std::string& id, const Params& params);
		/// Creates the ScalarDatapointImpl.

	~StringDatapointImpl();
		/// Destroys the ScalarDatapointImpl.

	void forceUpdate(const std::string& value);
		/// Force an update, without performing an access check.

	// StringDatapoint
	std::string value() const;
	Poco::Optional<std::string> validValue() const;
	void update(const std::string& value);

	// Datapoint
	void invalidate();
	bool valid() const;

	StringDatapointImpl() = delete;

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
	void unsafeUpdate(const std::string& value);

private:
	const std::string _id;
	const std::string _name;
	const int _access;
	Poco::Timestamp _updated;
	std::string _value;
	bool _valid;
	mutable Poco::Mutex _mutex;
};


} } // namespace IoT::Datapoints


#endif // IoT_Datapoints_StringDatapointImpl_INCLUDED
