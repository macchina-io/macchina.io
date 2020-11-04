//
// TimeService.cpp
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "TimeService.h"
#include "Poco/Util/TimerTask.h"


namespace Services {


class WakeUpTask: public Poco::Util::TimerTask
{
public:
	WakeUpTask(TimeService& owner, const std::string& message):
		_owner(owner),
		_message(message)
	{
	}
	
	void run()
	{
		_owner.wakeUp(this, _message);
	}
	
private:
	TimeService& _owner;
	std::string _message;
};


TimeService::TimeService()
{
}


TimeService::~TimeService()
{
}


Poco::DateTime TimeService::currentTime() const
{
	Poco::DateTime now;
	return now;
}


void TimeService::wakeMeUp(const Poco::DateTime& time, const std::string& message)
{
	_timer.schedule(new WakeUpTask(*this, message), time.timestamp());
}


} // namespace Services
