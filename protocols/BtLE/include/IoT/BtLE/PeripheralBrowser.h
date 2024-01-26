//
// PeripheralBrowser.h
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  PeripheralBrowser
//
// Definition of the PeripheralBrowser class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_BtLE_PeripheralBrowser_INCLUDED
#define IoT_BtLE_PeripheralBrowser_INCLUDED


#include "IoT/BtLE/BtLE.h"
#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include <vector>


namespace IoT {
namespace BtLE {


enum AddressType
	/// Bt LE Address Types
{
	ADDRESS_TYPE_BR_EDR = 0,
	ADDRESS_TYPE_PUBLIC = 1,
	ADDRESS_TYPE_RANDOM = 2
};


enum AdvertisingDataType
	/// Bt LE Advertising Common Data Types
{
	AD_TYPE_FLAGS                              = 0x01,
	AD_TYPE_INCOMPLETTE_SERVICE_CLASS_LIST_16  = 0x02,
	AD_TYPE_COMPLETE_SERVICE_CLASS_LIST_16     = 0x03,
	AD_TYPE_INCOMPLETTE_SERVICE_CLASS_LIST_32  = 0x04,
	AD_TYPE_COMPLETE_SERVICE_CLASS_LIST_32     = 0x05,
	AD_TYPE_INCOMPLETTE_SERVICE_CLASS_LIST_128 = 0x06,
	AD_TYPE_COMPLETE_SERVICE_CLASS_LIST_128    = 0x07,
	AD_TYPE_SHORTENED_LOCAL_NAME               = 0x08,
	AD_TYPE_COMPLETE_LOCAL_NAME                = 0x09,
	AD_TYPE_TX_POWER_LEVEL                     = 0x0A,
	AD_TYPE_DEVICE_CLASS                       = 0x0D,
	AD_TYPE_SIMPLE_PAIRING_HASH_C192           = 0x0E,
	AD_TYPE_SIMPLE_PAIRING_RND_R192            = 0x0F,
	AD_TYPE_DEVICE_ID                          = 0x10,
	AD_TYPE_SECURITY_MGR_TK                    = 0x10,
	AD_TYPE_SECURITY_MGR_OOB                   = 0x11,
	AD_TYPE_CONN_INT_RANGE                     = 0x12,
	AD_TYPE_SERVICE_SOLICITATION_16            = 0x14,
	AD_TYPE_SERVICE_SOLICITATION_128           = 0x15,
	AD_TYPE_SERVICE_DATA_UUID16                = 0x16,
	AD_TYPE_PUBLIC_TARGET_ADDRESS              = 0x17,
	AD_TYPE_RANDOM_TARGET_ADDRESS              = 0x18,
	AD_TYPE_APPEARANCE                         = 0x19,
	AD_TYPE_ADVERTISING_INTERVAL               = 0x1A,
	AD_TYPE_LE_BLUETOOTH_DEVICE_ADDRESS        = 0x1B,
	AD_TYPE_LE_ROLE                            = 0x1C,
	AD_TYPE_SIMPLE_PAIRING_HASH_C256           = 0x1D,
	AD_TYPE_SIMPLE_PAIRING_RND_R256            = 0x1E,
	AD_TYPE_SERVICE_SOLICITATION_32            = 0x1F,
	AD_TYPE_SERVICE_DATA_UUID32                = 0x20,
	AD_TYPE_SERVICE_DATA_UUID128               = 0x21,
	AD_TYPE_LE_SECURE_CONN_CONFIRM             = 0x22,
	AD_TYPE_LE_SECURE_CONN_RANDOM              = 0x23,
	AD_TYPE_URI                                = 0x24,
	AD_TYPE_INDOOR_POSITIONING                 = 0x25,
	AD_TYPE_TRANSPORT_DISCOVERY                = 0x26,
	AD_TYPE_LE_SUPPORTED_FEATURES              = 0x27,
	AD_TYPE_CHANNEL_MAP_UPDATE_IND             = 0x28,
	AD_TYPE_PB_ADV                             = 0x29,
	AD_TYPE_MESH_MESSAGE                       = 0x2A,
	AD_TYPE_MESH_BEACON                        = 0x2B,
	AD_TYPE_BIGINFO                            = 0x2C,
	AD_TYPE_BROADCAST_CODE                     = 0x2D,
	AD_TYPE_RESOLVABLE_SET_ID                  = 0x2E,
	AD_TYPE_ADVERTISING_INTERVAL_LONG          = 0x2F,
	AD_TYPE_BROADCAST_NAME                     = 0x30,
	AD_TYPE_ENCRYPTED_AD_DATA                  = 0x31,
	AD_TYPE_PERIODIC_AD_RESP_TIMING            = 0x32,
	AD_TYPE_ELECTRONIC_SHELF_LABEL             = 0x34,
	AD_TYPE_3D_INFORMATION_DATA                = 0x3D,
	AD_TYPE_MANUFACTURER_SPECIFIC              = 0xFF
};


enum AdvertisingFlags
{
	AD_FLAG_LE_LIMITED_DISC_MODE = 0x01,
	AD_FLAG_LE_GENERAL_DISC_MODE = 0x02,
	AD_FLAG_BR_EDR_NOT_SUPPORTED = 0x04,
	AD_FLAG_LE_BR_EDR_CONTROLLER = 0x08,
	AD_FLAG_LE_BR_EDR_HOST       = 0x10
};


//@ serialize
struct AdvertisingData
{
	Poco::UInt8 type;       /// Type of advertising data (see AdvertisingDataType)
	std::vector<char> data; /// Raw data.
};


//@ serialize
struct PeripheralInfo
{
	std::string address;
		/// Bt address of the peripheral, e.g., "C4:BE:84:72:C5:06".

	AddressType addressType = ADDRESS_TYPE_PUBLIC;
		/// Type of address.

	std::string name;
		/// Peripheral name, extracted from advertising data 
		/// (AD_TYPE_COMPLETE_LOCAL_NAME or AD_TYPE_SHORTENED_LOCAL_NAME, whichever is first).

	short rssi = 0;
		/// RSSI (received signal strength indicator) in dB, e.g. -79.

	bool connectable = false;
		/// Indicates whether this devices accepts a connection (true) or not (false).

	std::vector<AdvertisingData> data;
		/// Advertising data, split into elements.
};


//@ remote
class IoTBtLE_API PeripheralBrowser
	/// This class provides browsing (scanning) for available Bt LE devices.
{
public:
	using Ptr = Poco::SharedPtr<PeripheralBrowser>;

	Poco::BasicEvent<void> browseStarted;
		/// Fired when browsing has been started.

	Poco::BasicEvent<const PeripheralInfo> peripheralFound;
		/// Fired when a peripheral has been found during browsing.

	Poco::BasicEvent<void> browseComplete;
		/// Fired when browsing has been completed.

	Poco::BasicEvent<const std::string> browseError;
		/// Fired when an error was encountered during browsing.

	//@ $activeScan = {optional}
	virtual void browse(bool activeScan = false) = 0;
		/// Scan for peripherals.
		///
		/// If activeScan is true, an active scan will be performed, 
		/// otherwise a passive scan. Full advertising data will only
		/// be provided in an active scan. Advertising data for a passive
		/// scan is limited to at most 31 bytes. For extended advertising data
		/// provided by an active scan, the maximum size is 1650 bytes.
		///
		/// Any peripherals found will be reported through the peripheralFound
		/// event. Scanning for peripherals will be done asynchronously, therefore
		/// this method returns immediately.
		///
		/// An active scan will stop automatically after some time, firing the
		/// browseComplete event. A passive scan will go on until canceled by
		/// calling cancelBrowse().
		///
		/// If a browse is already in progress, throws a Poco::IllegalStateException.

	virtual void cancelBrowse() = 0;
		/// Cancels an ongoing browse operation.

	virtual bool browseInProgress() = 0;
		/// Returns true if a browse (scan) is currently in progress, otherwise false.

	virtual ~PeripheralBrowser();
		/// Destroys the PeripheralBrowser.
};


} } // namespace IoT::BtLE


#endif // IoT_BtLE_PeripheralBrowser_INCLUDED
