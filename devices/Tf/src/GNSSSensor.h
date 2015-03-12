//
// GNSSSensor.h
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Tf_GNSSSensor_INCLUDED
#define IoT_Tf_GNSSSensor_INCLUDED


#include "IoT/Tf/Tf.h"
#include "IoT/Devices/GNSSSensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Tf/MasterConnection.h"
#include "BrickletImpl.h"
extern "C"
{
#include "bricklet_gps.h"
}

namespace IoT {
namespace Tf {


class IoTTf_API GNSSSensor: public BrickletImpl<IoT::Devices::GNSSSensor, GNSSSensor>
{
public:
	enum
	{
		DEVICE_IDENTIFIER = GPS_DEVICE_IDENTIFIER
	};
	
	GNSSSensor(MasterConnection::Ptr pMasterConn, const std::string& uid);
		/// Creates a GNSSSensorImpl.
		
	~GNSSSensor();
		/// Destroys the GNSSSensorImpl.
	
	// GNSSSensor
	bool positionAvailable() const;
	IoT::Devices::LatLon position() const;
	double course() const;
	double speed() const;
	double magneticVariation() const;
	double altitude() const;
	double hdop() const;

protected:
	Poco::Any getPositionChangedPeriod(const std::string&) const;
	void setPositionChangedPeriod(const std::string&, const Poco::Any& value);
	Poco::Any getPositionChangedDelta(const std::string&) const;
	void setPositionChangedDelta(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;

	static void onPositionChanged(Poco::UInt32 latitude, char ns, Poco::UInt32 longitude, char ew,
		Poco::UInt16 pdop, Poco::UInt16 hdop, Poco::UInt16 vdop, Poco::UInt16 epe, void* userData);
	
	static void onStatusChanged(Poco::UInt8 fix, Poco::UInt8 satsInView, Poco::UInt8 satsUsed, void* userData);
	
private:
	mutable GPS _gps;
	bool _positionAvailable;
};


} } // namespace IoT::Tf


#endif // IoT_Tf_GNSSSensor_INCLUDED
