//
// HighRateButton.h
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_XDK_HighRateButton_INCLUDED
#define IoT_XDK_HighRateButton_INCLUDED


#include "IoT/Devices/Trigger.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/BtLE/Peripheral.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace XDK {


class HighRateButton: public IoT::Devices::DeviceImpl<IoT::Devices::Trigger, HighRateButton>
{
public:
	using Ptr = Poco::SharedPtr<HighRateButton>;

	HighRateButton(BtLE::Peripheral::Ptr pPeripheral);
		/// Creates a HighRateButton.

	~HighRateButton();
		/// Destroys the HighRateButton.

	bool isConnected() const;
		/// Returns true if the sensor's peripheral is connected.

	void update(bool state);
		/// Updates the button state.

	// Trigger
	bool state() const;

	static const std::string NAME;
	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;

protected:
	void init();
	void enable(bool enabled);
	Poco::Any getConnected(const std::string&) const;
	Poco::Any getEnabled(const std::string&) const;
	void setEnabled(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getDeviceIdentifier(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	void onConnected();
	void onDisconnected();

protected:
	mutable BtLE::Peripheral::Ptr _pPeripheral;
	bool _enabled;
	bool _ready;
	bool _state;
	Poco::Any _deviceIdentifier;
};


} } // namespace IoT::XDK


#endif // IoT_XDK_HighRateButton_INCLUDED
