//
// Protocol.h
//
// Library: WebTunnel
// Package: WebTunnel
// Module:  Protocol
//
// Definition of the Protocol class.
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef WebTunnel_Protocol_INCLUDED
#define WebTunnel_Protocol_INCLUDED


#include "Poco/WebTunnel/WebTunnel.h"
#include <cstdlib>


namespace Poco {
namespace WebTunnel {


class WebTunnel_API Protocol
	/// Helper class for implementing the WebTunnel protocol.
	///
	/// The WebTunnel protocol uses a simple protocol wrapper on
	/// top of a WebSocket connection to encapsulate forwarded
	/// data. The following frames are used:
	///
	/// 1. Open Channel Request
	///
	/// Requests the peer to open a TCP connection to the
	/// specified remote port.
	///
	///     0        1        2        3
	///     +--------+--------+--------+--------+
	///     | 0x01   | 0x00   | Channel Number  |
	///     +--------+--------+--------+--------+
	///     | Port Number     |
	///     +-----------------+
	///
	/// 2. Open Channel Confirmation
	///
	/// If an Open Channel Request was successful, this response
	/// will be sent.
	///
	///     0        1        2        3
	///     +--------+--------+--------+--------+
	///     | 0x11   | 0x00   | Channel Number  |
	///     +--------+--------+--------+--------+
	///
	/// 3. Open Channel Fault
	///
	/// If an Open Channel Request was not successful, this response
	/// will be sent.
	///
	///     0        1        2        3
	///     +--------+--------+--------+--------+
	///     | 0x81   | 0x00   | Channel Number  |
	///     +--------+--------+--------+--------+
	///     + Error Code      |
	///     +-----------------+
	///
	/// 4. Close Channel Request
	///
	/// Requests closing the given channel and the associated
	/// connection to the remote socket.
	///
	///     0        1        2        3
	///     +--------+--------+--------+--------+
	///     | 0x02   | 0x00   | Channel Number  |
	///     +--------+--------+--------+--------+
	///
	/// 5. Data
	///
	/// Data to be forwarded to the peer through a channel.
	///
	///     0        1        2        3
	///     +--------+--------+--------+--------+
	///     | 0x00   | 0x00   | Channel Number  |
	///     +--------+--------+--------+--------+
	///     | Data                              |
	///     |                                   |
	///     +-----------------------------------+
	///
	/// 6. Properties Update
	///
	/// Updates to device properties.
	///
	///     0        1        2        3
	///     +--------+--------+--------+--------+
	///     | 0x40   | 0x00   | 0x00            |
	///     +--------+--------+--------+--------+
	///     | count  | <keyValuePair>*<count>   |
	///     |                                   |
	///     +-----------------------------------+
	///
	/// count is number of following key/value pairs (UInt8).
	/// <keyValuePair> is two strings in Poco::BinaryWriter format
	/// (7-bit encoded length followed by raw bytes; no terminating
	/// zero).
	///
	/// 7. General Error
	///
	///     0        1        2        3
	///     +--------+--------+--------+--------+
	///     | 0x80   | 0x00   | Channel Number  |
	///     +--------+--------+--------+--------+
	///     | Error Code      |
	///     +-----------------+
{
public:
	enum Opcodes
	{
		WT_OP_DATA            = 0x00,  /// Send payload data.
		WT_OP_OPEN_REQUEST    = 0x01,  /// Request to open a channel.
		WT_OP_OPEN_CONFIRM    = 0x11,  /// Confirms channel has been opened.
		WT_OP_OPEN_FAULT      = 0x81,  /// Error opening a channel.
		WT_OP_CLOSE           = 0x02,  /// Close a channel (uncomfirmed).
		WT_OP_PROP_UPDATE     = 0x40,  /// Properties update
		WT_OP_ERROR           = 0x80   /// General error notification, closes a channel.
	};

	enum ErrorCodes
	{
		WT_ERR_NONE           = 0x00,  /// No error (not used in protocol).
		WT_ERR_BAD_CHANNEL    = 0x01,  /// The given channel number is invalid.
		WT_ERR_NOT_FORWARDED  = 0x02,  /// Access to the given port has been denied (the port is not forwarded).
		WT_ERR_CONN_REFUSED   = 0x03,  /// Connection refused - no one listening on forwarded port.
		WT_ERR_TIMEOUT        = 0x04,  /// Connection timed out.
		WT_ERR_SOCKET         = 0x05,  /// General socket error.
		WT_ERR_PROTOCOL       = 0x06,  /// Protocol violation.
		WT_ERR_CHANNEL_IN_USE = 0x07   /// Channel is already in use.
	};

	enum
	{
		WT_FRAME_MAX_SIZE = 2048,
		WT_FRAME_HEADER_SIZE = 4
	};

	static std::size_t writeHeader(char* pBuffer, std::size_t bufferSize, Poco::UInt8 opcode, Poco::UInt8 flags, Poco::UInt16 channel, Poco::UInt16 portOrErrorCode = 0);
		/// Writes the protocol header to the given buffer, which must be of sufficient size
		/// (at least 4 or 6 bytes, depending on opcode).
		///
		/// Flags are currently unused and should be 0.
		///
		/// Returns the size of the header in bytes.

	static std::size_t readHeader(const char* pBuffer, std::size_t bufferSize, Poco::UInt8& opcode, Poco::UInt8& flags, Poco::UInt16& channel, Poco::UInt16* pPortOrErrorCode = 0);
		/// Reads the protocol header from the given buffer.
		///
		/// Returns the size of the header in bytes.
};


} } // namespace Poco::WebTunnel


#endif // WebTunnel_Protocol_INCLUDED
