//
// TimeService.h
//
// Definition of the TimeService class.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TimeService_INCLUDED
#define TimeService_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/BasicEvent.h"
#include "Poco/DateTime.h"
#include "Poco/Util/Timer.h"


namespace Services {


//@ remote
class TimeService
{
public:
	TimeService();
		/// Creates the TimeService.

	~TimeService();
		/// Destroys the TimeService.
		
	Poco::BasicEvent<const std::string> wakeUp;
	
	Poco::DateTime currentTime() const;
		/// Returns the current date and time.
		
	void wakeMeUp(const Poco::DateTime& time, const std::string& message);
		/// Schedules a wakeup call.
		///
		/// Fires the wakeUp event at the given time, passing
		/// the given message as argument.
		
private:
	Poco::Util::Timer _timer;
};


} // namespace Services


#endif // TimeService_INCLUDED
