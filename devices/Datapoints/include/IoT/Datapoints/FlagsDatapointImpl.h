//
// FlagsDatapointImpl.h
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  FlagsDatapointImpl
//
// Definition of the FlagsDatapointImpl class.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Datapoints_FlagsDatapointImpl_INCLUDED
#define IoT_Datapoints_FlagsDatapointImpl_INCLUDED


#include "IoT/Datapoints/Datapoints.h"
#include "IoT/Datapoints/Types.h"
#include "IoT/Datapoints/BasicDatapointImpl.h"
#include "IoT/Devices/FlagsDatapoint.h"
#include <map>


namespace IoT {
namespace Datapoints {


class IoTDatapoints_API FlagsDatapointImpl: public BasicDatapointImpl<IoT::Devices::FlagsDatapoint, FlagsDatapointImpl>
	/// A basic implementation of an FlagsDatapoint.
{
public:
	using Interface = IoT::Devices::FlagsDatapoint;
	using Params = FlagsDatapointParams;

	FlagsDatapointImpl(const std::string& id, const Params& params);
		/// Creates the ScalarDatapointImpl.

	~FlagsDatapointImpl();
		/// Destroys the ScalarDatapointImpl.

	FlagsType forceReset(const FlagsType& value = FlagsType());
		/// Force a reset, without performing an access check.

	void forceResetFlags(const std::vector<std::string>& flags = std::vector<std::string>());
		/// Force a reset, without performing an access check.

	// FlagsDatapoint
	FlagsType value() const;
	Poco::Optional<FlagsType> validValue() const;
	std::vector<std::string> flags() const;
	Poco::Optional<std::vector<std::string>> validFlags() const;
	FlagsType reset(FlagsType value = FlagsType());
	void resetFlags(const std::vector<std::string>& flags = std::vector<std::string>());
	FlagsType set(FlagsType flags);
	void setFlags(const std::vector<std::string>& flags);
	FlagsType unset(FlagsType flags);
	void unsetFlags(const std::vector<std::string>& flags);
	FlagsType toggle(FlagsType flags);
	void toggleFlags(const std::vector<std::string>& flags);
	std::vector<IoT::Devices::FlagValue> definedFlags() const;

	// Datapoint
	void invalidate();
	bool valid() const;

	FlagsDatapointImpl() = delete;

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

	void unsafeUpdate(const FlagsType& value);
	void unsafeSet(const FlagsType& value);
	void unsafeUnset(const FlagsType& value);
	void unsafeToggle(const FlagsType& value);
	Poco::UInt16 mapSymbolicName(const std::string& symbolicName) const;
	FlagsType mapSymbolicNames(const std::vector<std::string>& symbolicNames) const;
	std::vector<std::string> mapFlags(const FlagsType& value) const;

private:
	const std::string _id;
	const std::string _name;
	const int _access;
	const std::vector<IoT::Devices::FlagValue> _definedFlags;
	FlagsType _validMask;
	Poco::Timestamp _updated;
	FlagsType _value;
	bool _valid;
};


} } // namespace IoT::Datapoints


#endif // IoT_Datapoints_FlagsDatapointImpl_INCLUDED
