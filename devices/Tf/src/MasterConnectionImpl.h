//
// MasterConnectionImpl.h
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Tf_MasterConnectionImpl_INCLUDED
#define IoT_Tf_MasterConnectionImpl_INCLUDED


#include "IoT/Tf/MasterConnection.h"
#include "ip_connection.h"


namespace IoT {
namespace Tf {


class IoTTf_API MasterConnectionImpl: public MasterConnection
{
public:
	using Ptr = Poco::AutoPtr<MasterConnection>;

	MasterConnectionImpl();
		/// Creates an unconnected MasterConnection.

	~MasterConnectionImpl();
		/// Destroys the MasterConnection.

	IPConnection* ipcon();
		/// Returns the underlying ip_connection.

	// MasterConnection
	void connect(const std::string& host, Poco::UInt16 port);
	void disconnect();
	bool connected() const;

protected:
	static void enumerate(
		const char *uid,
		const char *masterUID,
        char position,
        uint8_t hardwareVersion[3],
        uint8_t firmwareVersion[3],
        uint16_t type,
        uint8_t eventType,
        void *data);

private:
	IPConnection _ipcon;
};


//
// inlines
//
inline IPConnection* MasterConnectionImpl::ipcon()
{
	return &_ipcon;
}


} } // namespace IoT::Tf


#endif // IoT_Tf_MasterConnectionImpl_INCLUDED
