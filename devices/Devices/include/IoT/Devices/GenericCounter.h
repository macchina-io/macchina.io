//
// GenericCounter.h
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_GenericCounter_INCLUDED
#define IoT_Devices_GenericCounter_INCLUDED


#include "IoT/Devices/Counter.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "Poco/Util/Timer.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class IoTDevices_API GenericCounter: public IoT::Devices::DeviceImpl<IoT::Devices::Counter, GenericCounter>
{
public:
	typedef Poco::SharedPtr<GenericCounter> Ptr;

	GenericCounter(const std::string& name, const std::string& symbolicName, Poco::Util::Timer& timer);
		/// Creates a Counter.

	~GenericCounter();
		/// Destroys the Counter.

	void update(Poco::Int32 value);
		/// Updates the counter value.

	void enable(bool enabled);
		/// Enables or disables the counter.

	// Counter
	Poco::Int32 count() const;
	Poco::Int32 reset();

	static const std::string TYPE;

protected:
	Poco::Any getValueChangedDelta(const std::string&) const;
	void setValueChangedDelta(const std::string&, const Poco::Any& value);
	Poco::Any getValueChangedPeriod(const std::string&) const;
	void setValueChangedPeriod(const std::string&, const Poco::Any& value);
	Poco::Any getEnabled(const std::string&) const;
	void setEnabled(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;

protected:
	std::string _name;
	std::string _symbolicName;
	Poco::Util::Timer& _timer;
	bool _enabled;
	Poco::Int32 _value;
	double _valueChangedDelta;
	int _valueChangedPeriod;
	Poco::SharedPtr<IoT::Devices::EventModerationPolicy<Poco::Int32> > _pEventPolicy;
};


} } // namespace IoT::Devices


#endif // IoT_Devices_GenericCounter_INCLUDED
