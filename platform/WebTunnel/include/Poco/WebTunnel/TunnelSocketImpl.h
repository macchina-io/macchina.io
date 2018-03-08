//
// TunnelSocketImpl.h
//
// Library: WebTunnel
// Package: WebTunnel
// Module:  TunnelSocketImpl
//
// Definition of the TunnelSocketImpl class.
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef WebTunnel_TunnelSocketImpl_INCLUDED
#define WebTunnel_TunnelSocketImpl_INCLUDED


#include "Poco/WebTunnel/WebTunnel.h"
#include "Poco/WebTunnel/PortReflector.h"
#include "Poco/Net/StreamSocketImpl.h"
#include "Poco/Exception.h"
#include "Poco/Buffer.h"
#include "Poco/Logger.h"


namespace Poco {
namespace WebTunnel {


class WebTunnel_API TunnelSocketImpl: public Poco::Net::StreamSocketImpl
{
public:
	TunnelSocketImpl(PortReflector& portReflector, PortReflector::TargetInfo::Ptr pTargetInfo, PortReflector::ChannelInfo::Ptr pChannelInfo);
		/// Creates a TunnelSocketImpl using the given PortReflector, TargetInfo and channel.

	int enqueueBytes(const char* buffer, int size);
		/// Copies the content of the given buffer into the internal circular buffer.

	void enqueueClose(Poco::UInt16 statusCode = Protocol::WT_ERR_NONE);
		/// Signals the socket should be closed.

	Poco::UInt16 statusCode() const;
		/// Returns the close status code.

	// StreamSocketImpl
	virtual int sendBytes(const void* buffer, int length, int flags);
	virtual int receiveBytes(void* buffer, int length, int flags);
	virtual Poco::Net::SocketImpl* acceptConnection(Poco::Net::SocketAddress& clientAddr);
	virtual void connect(const Poco::Net::SocketAddress& address);
	virtual void connect(const Poco::Net::SocketAddress& address, const Poco::Timespan& timeout);
	virtual void connectNB(const Poco::Net::SocketAddress& address);
	virtual void bind(const Poco::Net::SocketAddress& address, bool reuseAddress = false);
	virtual void bind6(const Poco::Net::SocketAddress& address, bool reuseAddress = false, bool ipV6Only = false);
	virtual void listen(int backlog = 64);
	virtual void close();
	virtual void shutdownReceive();
	virtual void shutdownSend();
	virtual void shutdown();
	virtual int sendTo(const void* buffer, int length, const Poco::Net::SocketAddress& address, int flags = 0);
	virtual int receiveFrom(void* buffer, int length, Poco::Net::SocketAddress& address, int flags = 0);
	virtual void sendUrgent(unsigned char data);
	virtual bool secure() const;
	virtual void setSendTimeout(const Poco::Timespan& timeout);
	virtual Poco::Timespan getSendTimeout();
	virtual void setReceiveTimeout(const Poco::Timespan& timeout);
	virtual Poco::Timespan getReceiveTimeout();

protected:
	virtual ~TunnelSocketImpl();

private:
	TunnelSocketImpl();

	enum
	{
		CONNECT_TIMEOUT = 60000,
		BUFFER_TIMEOUT  = 30000
	};

	template <class Elem>
	class CircularBuffer
	{
	public:
		CircularBuffer(std::size_t size):
			_buffer(size),
			_available(0),
			_reserved(0),
			_readIndex(0),
			_writeIndex(0),
			_canRead(false),
			_canWrite(false),
			_close(false)
		{
		}

		~CircularBuffer()
		{
		}

		int write(const Elem* data, int length, long timeout)
		{
			poco_assert (0 < length && length < _buffer.size());

			int result = 0;
			if (reserveWrite(length) || _canWrite.tryWait(timeout))
			{
				Poco::FastMutex::ScopedLock lock(_mutex);

				result = length;
				_available += length;
				int size = static_cast<int>(_buffer.size());
				while (length-- > 0)
				{
					_buffer[_writeIndex++] = *data++;
					if (_writeIndex == size) _writeIndex = 0;
				}
				_canRead.set();
			}
			else throw Poco::TimeoutException();
			return result;
		}

		int read(Elem* data, int length, long timeout)
		{
			int result = 0;
			if (_canRead.tryWait(timeout))
			{
				Poco::FastMutex::ScopedLock lock(_mutex);

				if (_available == 0) return 0; // closed
				if (length > _available) length = _available;
				result = length;
				_available -= length;
				int size = static_cast<int>(_buffer.size());
				while (length-- > 0)
				{
					*data++ = _buffer[_readIndex++];
					if (_readIndex == size) _readIndex = 0;
				}
				if (_buffer.size() - _available >= _reserved)
				{
					_canWrite.set();
				}
				if (_available == 0 && !_close)
				{
					_canRead.reset();
				}
			}
			else throw Poco::TimeoutException();
			return result;
		}

		void close()
		{
			_close = true;
			_canRead.set();
		}

		bool reserveWrite(std::size_t size)
		{
			Poco::FastMutex::ScopedLock lock(_mutex);

			_reserved = static_cast<int>(size);
			if (_buffer.size() - _available >= _reserved)
			{
				_canWrite.set();
				return true;
			}
			else
			{
				_canWrite.reset();
				return false;
			}
		}

	private:
		Poco::Buffer<Elem> _buffer;
		int _available;
		int _reserved;
		int _readIndex;
		int _writeIndex;
		Poco::Event _canRead;
		Poco::Event _canWrite;
		bool _close;
		Poco::FastMutex _mutex;
	};

	PortReflector& _portReflector;
	PortReflector::TargetInfo::Ptr _pTargetInfo;
	PortReflector::ChannelInfo::Ptr _pChannelInfo;
	Poco::Buffer<char> _writeBuffer;
	CircularBuffer<char> _readBuffer;
	Poco::UInt16 _statusCode;
	Poco::Timespan _sendTimeout;
	Poco::Timespan _receiveTimeout;
	Poco::Logger& _logger;
};


//
// inlines
//
inline Poco::UInt16 TunnelSocketImpl::statusCode() const
{
	return _statusCode;
}


} } // namespace Poco::WebTunnel


#endif // WebTunnel_TunnelSocketImpl_INCLUDED
