//
// BlueZPeripheralBrowser.h
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  BlueZPeripheralBrowser
//
// Definition of the BlueZPeripheralBrowser class.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_BtLE_BlueZPeripheralBrowser_INCLUDED
#define IoT_BtLE_BlueZPeripheralBrowser_INCLUDED


#include "HelperClient.h"
#include "IoT/BtLE/PeripheralBrowser.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/Mutex.h"
#include "Poco/Logger.h"


namespace IoT {
namespace BtLE {
namespace BlueZ {


class BlueZPeripheralBrowser: public PeripheralBrowser, protected HelperClient
	/// An implementation of the PeripheralBrowser interface using the BlueZ Linux
	/// Bt stack via an external helper executable.
{
public:
	using Ptr = Poco::SharedPtr<BlueZPeripheralBrowser>;

	explicit BlueZPeripheralBrowser(const std::string& helperPath);
		/// Creates the BlueZPeripheralBrowser with the given helper path.

	~BlueZPeripheralBrowser();
		/// Destroys the BlueZPeripheralBrowser.

	// PeripheralBrowser
	void browse(bool activeScan);
	void cancelBrowse();
	bool browseInProgress();

protected:
	void processResponse(const std::string& response);
	static std::string formatAddress(const std::string& binaryAddress);
	static std::string extractName(const std::string& data);
	static std::vector<AdvertisingData> splitData(const std::string& data);

private:
	Poco::FastMutex _mutex;
	bool _activeScan = false;
	bool _scanning = false;
	bool _error = false;
	Poco::Logger& _logger;
};


} } } // namespace IoT::BtLE::BlueZ


#endif // IoT_BtLE_BlueZPeripheralBrowser_INCLUDED
