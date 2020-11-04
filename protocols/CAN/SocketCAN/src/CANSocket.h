//
// CANSocket.h
//
// Definition of the CANSocket class.
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_SocketCAN_CANSocket_INCLUDED
#define IoT_SocketCAN_CANSocket_INCLUDED


#include "Poco/Net/DatagramSocket.h"


namespace IoT {
namespace CAN {
namespace SocketCAN {


class CANSocket: public Poco::Net::DatagramSocket
	/// This class implements a SocketCAN socket.
{
public:
	CANSocket(const std::string& interfc);
		/// Creates the CANSocket using the given CAN interface (e.g., "can0").

	~CANSocket();
		/// Destroys the CANSocket.

protected:
	static int canSocket(const std::string& interfc);
};



} } } // namespace IoT::CAN::SocketCAN


#endif // IoT_SocketCAN_CANSocket_INCLUDED
