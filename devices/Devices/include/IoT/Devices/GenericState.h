//
// GenericState.h
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_GenericState_INCLUDED
#define IoT_Devices_GenericState_INCLUDED


#include "IoT/Devices/State.h"
#include "IoT/Devices/DeviceImpl.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class IoTDevices_API GenericState: public IoT::Devices::DeviceImpl<IoT::Devices::State, GenericState>
{
public:
	typedef Poco::SharedPtr<GenericState> Ptr;
	typedef std::map<StateType, std::string> StateStringMap;

	GenericState(const std::string& name, const std::string& symbolicName, const StateStringMap& stateStringMap);
		/// Creates a Counter.

	~GenericState();
		/// Destroys the Counter.

	void update(StateType value);
		/// Updates the counter value.

	// State
	StateType state() const;

	static const std::string TYPE;

protected:
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;

protected:
	std::string _name;
	std::string _symbolicName;
	StateStringMap _stateStringMap;
	StateType _state;
};


} } // namespace IoT::Devices


#endif // IoT_Devices_GenericState_INCLUDED
