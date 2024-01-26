//
// HelperClient.h
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  Helper
//
// Definition of the HelperClient class.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_BtLE_HelperClient_INCLUDED
#define IoT_BtLE_HelperClient_INCLUDED


#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/Runnable.h"
#include "Poco/Thread.h"
#include "Poco/Mutex.h"
#include "Poco/Process.h"
#include "Poco/PipeStream.h"
#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/Logger.h"
#include <map>


namespace IoT {
namespace BtLE {
namespace BlueZ {


class HelperClient: public Poco::Runnable
	/// API to the BlueZ helper executable.
	///
	/// Using an external helper executable is necessary due to GPL licensing
	/// of relevant parts of the BlueZ library used in the client part.
	/// A future implementation of this class may use the D-Bus API of BlueZ.
{
public:
	HelperClient(const std::string helperPath);
		/// Creates the HelperClient using the given helper path and peripheral address.

	~HelperClient();
		/// Destroys the HelperClient.

	static std::string decodeValue(const std::string& value);
	static Poco::UInt16 decodeWord(const std::string& value);
	static Poco::UInt32 decodeWord32(const std::string& value);

protected:
	using KeyValuePair = std::pair<std::string, std::string>;

	class ParsedResponse: public Poco::Notification
	{
	public:
		using Ptr = Poco::AutoPtr<ParsedResponse>;
		using KeyValueVec = std::vector<KeyValuePair>;
		using const_iterator = KeyValueVec::const_iterator;

		std::string type() const
		{
			using namespace std::string_literals;
			return decodeValue(get("rsp"s));
		}

		const std::string& get(const std::string& key) const
		{
			const_iterator it = find(key);
			if (it != end())
				return it->second;
			else
				throw Poco::NotFoundException(key);
		}

		const std::string& get(const std::string& key, const std::string& deflt) const
		{
			const_iterator it = find(key);
			if (it != end())
				return it->second;
			else
				return deflt;
		}

		void add(const KeyValuePair& param)
		{
			_params.push_back(param);
		}

		const_iterator begin() const
		{
			return _params.begin();
		}

		const_iterator end() const
		{
			return _params.end();
		}

		const_iterator find(const std::string& key) const
		{
			for (std::vector<KeyValuePair>::const_iterator it = _params.begin(); it != _params.end(); ++it)
			{
				if (it->first == key)
					return it;
			}
			return _params.end();
		}

	private:
		std::vector<KeyValuePair> _params;
	};

	void startHelper();
	void stopHelper();
	bool helperRunning();
	void run();
	void sendCommand(const std::string& command);
	virtual void processResponse(const std::string& response) = 0;
	void parseResponse(const std::string& response, ParsedResponse& parsedResponse);
	ParsedResponse::Ptr waitResponse(long timeout);
	ParsedResponse::Ptr expectResponse(const std::string& type, long timeout);
	void enqueueResponse(ParsedResponse::Ptr pResponse);

	struct HelperInfo: public Poco::RefCountedObject
	{
		using Ptr = Poco::AutoPtr<HelperInfo>;

		HelperInfo(const Poco::ProcessHandle& ph, const Poco::Pipe& inputPipe, const Poco::Pipe& outputPipe):
			processHandle(ph),
			inputStream(outputPipe),
			outputStream(inputPipe)
		{
		}

		Poco::ProcessHandle    processHandle;
		Poco::PipeInputStream  inputStream;
		Poco::PipeOutputStream outputStream;
	};

	enum
	{
		DEFAULT_TIMEOUT = 30000,
		DISCONNECT_TIMEOUT = 2000
	};

private:
	std::string _helperPath;
	Poco::Thread _helperThread;
	HelperInfo::Ptr _pHelperInfo;
	Poco::NotificationQueue _responseQueue;
	Poco::Logger& _logger;
};


} } } // namespace IoT::BtLE::BlueZ


#endif // IoT_BtLE_HelperClient_INCLUDED
