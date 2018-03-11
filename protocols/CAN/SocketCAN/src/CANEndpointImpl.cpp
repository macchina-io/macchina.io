//
// CANEndpointImpl.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "CANEndpointImpl.h"
#ifdef MACCHINA_HAVE_SOCKETCAN
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <errno.h>
#endif // MACCHINA_HAVE_SOCKETCAN
#include <cstring>


#ifdef CANFD_MTU
#define MACCHINA_HAVE_CANFD 1
#endif


namespace IoT {
namespace CAN {
namespace SocketCAN {


bool operator == (const Filter& f1, const Filter& f2)
{
	return f1.id == f2.id && f1.mask == f2.mask;
}


CANEndpointImpl::CANEndpointImpl(const std::string& interfc):
	_interfc(interfc),
	_socket(interfc),
	_filterMode(CAN_FILTER_MODE_OR),
	_enableEvents(0),
	_enableFD(0),
	_logger(Poco::Logger::get("IoT.CAN.SocketCAN.CANEndpointImpl"))
{
}


CANEndpointImpl::~CANEndpointImpl()
{
	Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);

	if (_enableEvents)
	{
		_enableEvents = 0;
		lock.unlock();
		_thread.join();
	}
}


void CANEndpointImpl::run()
{
	_logger.debug("Starting receive loop...");

	Poco::Timespan timeout(CAN_POLL_TIMEOUT);
	while (eventsEnabled())
	{
		try
		{
#ifdef MACCHINA_HAVE_SOCKETCAN
			if (_socket.poll(timeout, Poco::Net::Socket::SELECT_READ))
			{
#ifdef MACCHINA_HAVE_CANFD
				struct canfd_frame scFrame;
				int n = _socket.receiveBytes(&scFrame, sizeof(scFrame));
				if (n == CAN_MTU)
				{
					_logger.dump("CAN frame received", scFrame.data, scFrame.len);
					CANFrame::Flags flags(0);
					if (scFrame.can_id & CAN_EFF_FLAG) flags |= CANFrame::CAN_FLAG_IDE;
					if (scFrame.can_id & CAN_RTR_FLAG) flags |= CANFrame::CAN_FLAG_RTR;
					CANFrame::ID id = scFrame.can_id & CAN_EFF_MASK;

					CANFrame frame(id, flags, scFrame.len, reinterpret_cast<char*>(&scFrame.data[0]));
					frameReceived(this, frame);
				}
				else if (n == CANFD_MTU)
				{
					_logger.dump("CAN-FD frame received", scFrame.data, scFrame.len);
					CANFDFrame::Flags flags(0);
					if (scFrame.can_id & CAN_EFF_FLAG) flags |= CANFrame::CAN_FLAG_IDE;
					if (scFrame.can_id & CAN_RTR_FLAG) flags |= CANFrame::CAN_FLAG_RTR;
					CANFDFrame::ID id = scFrame.can_id & CAN_EFF_MASK;

					CANFDFrame frame(id, flags, scFrame.len, reinterpret_cast<char*>(&scFrame.data[0]));
					fdFrameReceived(this, frame);
				}
				else
				{
					_logger.notice("Invalid CAN frame received.");
				}
#else
				struct can_frame scFrame;
				int n = _socket.receiveBytes(&scFrame, sizeof(scFrame));
				if (n == CAN_MTU)
				{
					CANFrame::Flags flags(0);
					if (scFrame.can_id & CAN_EFF_FLAG) flags |= CANFrame::CAN_FLAG_IDE;
					if (scFrame.can_id & CAN_RTR_FLAG) flags |= CANFrame::CAN_FLAG_RTR;
					CANFrame::ID id = scFrame.can_id & CAN_EFF_MASK;

					CANFrame frame(id, flags, scFrame.can_dlc, reinterpret_cast<char*>(&scFrame.data[0]));
					frameReceived(this, frame);
				}
				else
				{
					_logger.notice("Invalid CAN frame received.");
				}
#endif // MACCHINA_HAVE_CANFD
			}
#endif // MACCHINA_HAVE_SOCKETCAN
		}
		catch (Poco::Exception& exc)
		{
			_logger.log(exc);
		}
	}
	_logger.debug("Receive loop exiting.");
}


std::string CANEndpointImpl::device() const
{
	return _interfc;
}


void CANEndpointImpl::setFilter(const std::vector<Filter>& filter)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_filter = filter;
	applyFilter();
}


std::vector<Filter> CANEndpointImpl::getFilter() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _filter;
}


bool CANEndpointImpl::addFilter(const Filter& filter)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	for (std::vector<Filter>::iterator it = _filter.begin(); it != _filter.end(); ++it)
	{
		if (filter == *it) return false;
	}
	_filter.push_back(filter);
	applyFilter();
	return true;
}


bool CANEndpointImpl::removeFilter(const Filter& filter)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	for (std::vector<Filter>::iterator it = _filter.begin(); it != _filter.end(); ++it)
	{
		if (filter == *it)
		{
			_filter.erase(it);
			applyFilter();
			return true;
		}
	}
	return false;
}


void CANEndpointImpl::setFilterMode(FilterMode mode)
{
#ifdef MACCHINA_HAVE_SOCKETCAN
	if (mode == CAN_FILTER_MODE_AND)
	{
		_socket.setOption(SOL_CAN_RAW, CAN_RAW_JOIN_FILTERS, 1);
	}
	else
	{
		_socket.setOption(SOL_CAN_RAW, CAN_RAW_JOIN_FILTERS, 0);
	}
#endif
	_filterMode = mode;
}


FilterMode CANEndpointImpl::getFilterMode() const
{
	return _filterMode;
}


void CANEndpointImpl::sendCANFrame(const CANFrame& frame)
{
	if (_logger.debug())
	{
		_logger.dump("Sending CAN frame", frame.payload().data(), frame.dlc());
	}
#ifdef MACCHINA_HAVE_SOCKETCAN
	struct can_frame scFrame;
	scFrame.can_id = frame.id();
	if (frame.flags() & CANFrame::CAN_FLAG_IDE) scFrame.can_id |= CAN_EFF_FLAG;
	if (frame.flags() & CANFrame::CAN_FLAG_RTR) scFrame.can_id |= CAN_RTR_FLAG;
	scFrame.can_dlc = frame.dlc();
	std::memcpy(scFrame.data, frame.payload().data(), frame.dlc());
	_socket.sendBytes(&scFrame, sizeof(scFrame));
#endif
}


void CANEndpointImpl::sendCANFDFrame(const CANFDFrame& frame)
{
#ifdef MACCHINA_HAVE_CANFD
	if (_logger.debug())
	{
		_logger.dump("Sending CAN-FD frame", frame.payload().data(), frame.length());
	}
#ifdef MACCHINA_HAVE_SOCKETCAN
	struct canfd_frame scFrame;
	scFrame.can_id = frame.id();
	if (frame.flags() & CANFrame::CAN_FLAG_IDE) scFrame.can_id |= CAN_EFF_FLAG;
	if (frame.flags() & CANFrame::CAN_FLAG_RTR) scFrame.can_id |= CAN_RTR_FLAG;
	scFrame.len = frame.length();
	std::memcpy(scFrame.data, frame.payload().data(), frame.length());
	_socket.sendBytes(&scFrame, sizeof(scFrame));
#endif
#else
	throw Poco::NotImplementedException("CAN-FD frames not supported by platform's SocketCAN");
#endif
}


void CANEndpointImpl::sendFrame(const CANFDFrame& frame, FrameType type)
{
	if (_logger.debug())
	{
		_logger.dump("Sending frame", frame.payload().data(), frame.length());
	}
#ifdef MACCHINA_HAVE_SOCKETCAN
#ifdef MACCHINA_HAVE_CANFD
	int mtu;
	switch (type)
	{
	case CAN_FRAME_AUTO:
		mtu = frame.length() <= 8 ? CAN_MTU : CANFD_MTU;
		break;
	case CAN_FRAME_CAN:
		if (frame.length() > 8) throw Poco::InvalidArgumentException("Frame too big for standard CAN frame");
		mtu = CAN_MTU;
		break;
	case CAN_FRAME_CANFD:
		mtu = CANFD_MTU;
		break;
	default:
		throw Poco::InvalidArgumentException("type");
	}

	struct canfd_frame scFrame;
	scFrame.can_id = frame.id();
	if (frame.flags() & CANFrame::CAN_FLAG_IDE) scFrame.can_id |= CAN_EFF_FLAG;
	if (frame.flags() & CANFrame::CAN_FLAG_RTR) scFrame.can_id |= CAN_RTR_FLAG;
	scFrame.len = frame.length();
	std::memcpy(scFrame.data, frame.payload().data(), frame.length());
	_socket.sendBytes(&scFrame, mtu);
#else
	switch (type)
	{
	case CAN_FRAME_AUTO:
		if (frame.length() > 8) throw Poco::InvalidArgumentException("Frame too big for standard CAN frame and CAN-FD frames are not supported by platform's SocketCAN");
		break;
	case CAN_FRAME_CAN:
		if (frame.length() > 8) throw Poco::InvalidArgumentException("Frame too big for standard CAN frame");
		break;
	case CAN_FRAME_CANFD:
		throw Poco::NotImplementedException("CAN-FD frames not supported by platform's SocketCAN");
		break;
	default:
		throw Poco::InvalidArgumentException("type");
	}
	struct can_frame scFrame;
	scFrame.can_id = frame.id();
	if (frame.flags() & CANFrame::CAN_FLAG_IDE) scFrame.can_id |= CAN_EFF_FLAG;
	if (frame.flags() & CANFrame::CAN_FLAG_RTR) scFrame.can_id |= CAN_RTR_FLAG;
	scFrame.can_dlc = frame.length();
	std::memcpy(scFrame.data, frame.payload().data(), frame.dlc());
	_socket.sendBytes(&scFrame, sizeof(scFrame));
#endif // MACCHINA_HAVE_CANFD
#endif // MACCHINA_HAVE_SOCKETCAN
}


void CANEndpointImpl::enableEvents(bool enable)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (enable)
	{
		if (++_enableEvents == 1)
		{
			_thread.start(*this);
		}
	}
	else if (_enableEvents > 0)
	{
		if (--_enableEvents == 0)
		{
			_thread.join();
		}
	}
}


bool CANEndpointImpl::eventsEnabled() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _enableEvents > 0;
}


void CANEndpointImpl::enableFD(bool enable)
{
#ifdef CANFD_MTU
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (enable)
	{
		if (++_enableFD == 1)
  		{
			_socket.setOption(SOL_CAN_RAW, CAN_RAW_FD_FRAMES, 1);
		}
	}
	else if (_enableFD > 0)
	{
		if (--_enableFD == 0)
		{
			_socket.setOption(SOL_CAN_RAW, CAN_RAW_FD_FRAMES, 0);
		}
	}
#else
	if (enable) throw Poco::NotImplementedException("CAN-FD not supported by platform's SocketCAN");
#endif
}


bool CANEndpointImpl::fdEnabled() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _enableFD > 0;
}


bool CANEndpointImpl::fdSupported() const
{
#ifdef MACCHINA_HAVE_CANFD
	return true;
#else
	return false;
#endif
}


void CANEndpointImpl::applyFilter()
{
#ifdef MACCHINA_HAVE_SOCKETCAN
	std::vector<struct can_filter> fvec;
	fvec.resize(_filter.size());
	for (std::size_t i = 0; i < _filter.size(); i++)
	{
		fvec[i].can_id = _filter[i].id;
		fvec[i].can_mask = _filter[i].mask;
		if (_filter[i].invert) fvec[i].can_id |= CAN_INV_FILTER;
	}

	if (setsockopt(_socket.impl()->sockfd(), SOL_CAN_RAW, CAN_RAW_FILTER, &fvec[0], sizeof(struct can_filter)*fvec.size()) == -1)
		throw Poco::IOException("Failed to set CAN frame filter", errno);
#endif
}


} } } // namespace IoT::CAN::SocketCAN
