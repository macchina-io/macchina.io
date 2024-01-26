//
// EnumDatapointImpl.h
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  EnumDatapointImpl
//
// Definition of the EnumDatapointImpl class.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Datapoints_EnumDatapointImpl_INCLUDED
#define IoT_Datapoints_EnumDatapointImpl_INCLUDED


#include "IoT/Datapoints/Datapoints.h"
#include "IoT/Datapoints/Types.h"
#include "IoT/Datapoints/BasicDatapointImpl.h"
#include "IoT/Devices/EnumDatapoint.h"
#include <map>


namespace IoT {
namespace Datapoints {


class IoTDatapoints_API EnumDatapointImpl: public BasicDatapointImpl<IoT::Devices::EnumDatapoint, EnumDatapointImpl>
	/// A basic implementation of an EnumDatapoint.
{
public:
	using Interface = IoT::Devices::EnumDatapoint;
	using Params = EnumDatapointParams;

	EnumDatapointImpl(const std::string& id, const Params& params);
		/// Creates the ScalarDatapointImpl.

	~EnumDatapointImpl();
		/// Destroys the ScalarDatapointImpl.

	void forceUpdate(int value);
		/// Force an update, without performing an access check.

	void forceUpdateString(const std::string& symbolicName);
		/// Force an update, without performing an access check.

	// EnumDatapoint
	int value() const;
	Poco::Optional<int> validValue() const;
	std::string stringValue() const;
	Poco::Optional<std::string> validStringValue() const;
	void update(int value);
	void updateString(const std::string& symbolicName);
	std::vector<IoT::Devices::EnumValue> definedValues() const;

	// Datapoint
	void invalidate();
	bool valid() const;

	EnumDatapointImpl() = delete;

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
	void checkedUpdate(int value);
	void unsafeUpdate(int value);
	int mapSymbolicName(const std::string& symbolicName) const;
	const std::string& mapValue(int value) const;

private:
	const std::string _id;
	const std::string _name;
	const int _access;
	const std::vector<IoT::Devices::EnumValue> _definedValues;
	Poco::Timestamp _updated;
	int _value;
	bool _valid;
	mutable Poco::Mutex _mutex;
};


} } // namespace IoT::Datapoints


#endif // IoT_Datapoints_EnumDatapointImpl_INCLUDED
