//
// Counter.h
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_CAN_Counter_INCLUDED
#define IoT_CAN_Counter_INCLUDED


#include "IoT/CAN/CANDevices.h"
#include "IoT/Devices/Counter.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "Poco/Util/Timer.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace CAN {


class IoTCANDevices_API Counter: public IoT::Devices::DeviceImpl<IoT::Devices::Counter, Counter>
{
public:
	using Ptr = Poco::SharedPtr<Counter>;

	Counter(Poco::Util::Timer& timer, const std::string& signal);
		/// Creates a Counter.

	~Counter();
		/// Destroys the Counter.

	void update(Poco::Int32 value);
		/// Updates the counter value.

	void enable(bool enabled);
		/// Enables or disables the counter.

	// Counter
	Poco::Int32 count() const;
	Poco::Int32 reset();

	static const std::string NAME;
	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;

protected:
	Poco::Any getValueChangedDelta(const std::string&) const;
	void setValueChangedDelta(const std::string&, const Poco::Any& value);
	Poco::Any getValueChangedPeriod(const std::string&) const;
	void setValueChangedPeriod(const std::string&, const Poco::Any& value);
	Poco::Any getEnabled(const std::string&) const;
	void setEnabled(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getSignal(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;

protected:
	Poco::Util::Timer& _timer;
	bool _enabled;
	Poco::Int32 _value;
	double _valueChangedDelta;
	int _valueChangedPeriod;
	Poco::SharedPtr<IoT::Devices::EventModerationPolicy<Poco::Int32>> _pEventPolicy;
	Poco::Any _signal;
};


} } // namespace IoT::CAN


#endif // IoT_CAN_Counter_INCLUDED
