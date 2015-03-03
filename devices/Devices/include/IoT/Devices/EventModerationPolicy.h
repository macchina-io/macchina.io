//
// EventModerationPolicy.h
//
// $Id: //poco/1.4/UPnP/GENA/include/Poco/UPnP/GENA/EventModerationPolicy.h#1 $
//
// Library: IoT/Devices
// Package: Devices
// Module:  Utilities
//
// Definition of the EventModerationPolicy class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_EventModerationPolicy_INCLUDED
#define IoT_Devices_EventModerationPolicy_INCLUDED


#include "IoT/Devices/Devices.h"
#include "Poco/Util/Timer.h"
#include "Poco/Util/TimerTaskAdapter.h"
#include "Poco/BasicEvent.h"
#include "Poco/Clock.h"
#include "Poco/Mutex.h"


namespace IoT {
namespace Devices {


template <typename T>
class EventModerationPolicy
	/// An EventModerationPolicy controls the frequency of events
	/// sent when an evented sensor or state variable changes. Any class or
	/// class template that fulfills the following criteria can be 
	/// used as EventModerationPolicy:
	///    * The class must provide a public member function
	///      named valueChanged that takes as only argument
	///      the new value of the state variable (passed
	///      by const reference).
	///    * valueChanged() must check whether the criteria
	///      for firing an event are fulfilled, and in if this is 
	///      the case, fire the event.
	///    * Typically, the Poco::BasicEvent instance will be
	///      passed to the policy object through the constructor.
{
public:
	virtual void valueChanged(const T& newValue) = 0;
		
	virtual ~EventModerationPolicy()
	{
	}
};


template <typename T>
class NoModerationPolicy: public EventModerationPolicy<T>
	/// This event moderation policy does no moderation and
	/// fires an event whenever the event variable's value changes
	/// (the valueChanged() member function is called).
	///
	/// This moderation policy can be used with any event value type
	/// (numeric and string).
{
public:
	typedef Poco::BasicEvent<const T> Event;

	NoModerationPolicy(Event& event):
		_pEvent(&event)
	{
	}
	
	void valueChanged(const T& newValue)
	{
		(*_pEvent)(this, newValue);
	}
	
private:
	NoModerationPolicy();
	
	Event* _pEvent;
};


template <typename T>
class MinimumDeltaModerationPolicy: public EventModerationPolicy<T>
	/// This event moderation policy will fire an event whenever the
	/// value of an event variable changes more than the given
	/// minimum delta since the last time an event was sent.
	///
	/// This moderation policy can only be used with numeric (int, float, etc.)
	/// event value types.
{
public:
	typedef Poco::BasicEvent<const T> Event;
	
	MinimumDeltaModerationPolicy(Event& event, T initialValue, T minimumDelta):
		_pEvent(&event),
		_value(initialValue),
		_minimumDelta(minimumDelta)
	{
	}
	
	MinimumDeltaModerationPolicy(const MinimumDeltaModerationPolicy& other):
		_pEvent(other._pEvent),
		_value(other._value),
		_minimumDelta(other._minimumDelta)
	{
	}
	
	MinimumDeltaModerationPolicy& operator = (const MinimumDeltaModerationPolicy& other)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		if (&other != this)
		{
			_pEvent       = other._pEvent;
			_value        = other._value;
			_minimumDelta = other._minimumDelta;
		}
		return *this;
	}
	
	void setMinimumDelta(T value)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		_minimumDelta = value;
	}
	
	T getMinimumDelta() const
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		return _minimumDelta;
	}
	
	void valueChanged(const T& value)
	{
		double minimumDelta;
		{
			Poco::FastMutex::ScopedLock lock(_mutex);
			minimumDelta = _minimumDelta;
		}
		
		T diff = value - _value;
		if (diff < 0) diff = -diff;
		if (diff >= minimumDelta)
		{
			_value = value;
			(*_pEvent)(this, _value);
		}
	}
	
private:
	Event* _pEvent;
	T _value;
	T _minimumDelta;
	mutable Poco::FastMutex _mutex;
};


template <typename T>
class MaximumRateModerationPolicy: public EventModerationPolicy<T>
	/// This event moderation policy will fire an event at most every n milliseconds.
	/// An external Poco::Util::Timer instance must be supplied.
{
public:
	typedef Poco::BasicEvent<const T> Event;

	MaximumRateModerationPolicy(Event& event, const T& initialValue, long maximumRateMS, Poco::Util::Timer& timer):
		_pEvent(&event),
		_value(initialValue),
		_maximumRate(maximumRateMS),
		_lastEvent(0),
		_pTimer(&timer)
	{
	}
	
	MaximumRateModerationPolicy(const MaximumRateModerationPolicy& other):
		_pEvent(other._pEvent),
		_value(other._value),
		_maximumRate(other._maximumRate),
		_lastEvent(0),
		_pTimer(other._pTimer)
	{
	}
	
	MaximumRateModerationPolicy& operator = (const MaximumRateModerationPolicy& other)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		if (&other != this)
		{
			_pEvent      = other._pEvent;
			_value       = other._value;
			_maximumRate = other._maximumRate;
			_pTimer      = other._pTimer;
		}
		return *this;
	}

	void valueChanged(const T& newValue)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		if (newValue != _value)
		{
			_value = newValue;
			if (_lastEvent.elapsed()/1000 >= _maximumRate)
			{
				if (_pTimerTask)
				{
					_pTimerTask->cancel();
					_pTimerTask = 0;
				}
				(*_pEvent)(this, _value);
				_lastEvent.update();
			}
			else if (!_pTimerTask)
			{
				_pTimerTask = new Poco::Util::TimerTaskAdapter<MaximumRateModerationPolicy>(*this, &MaximumRateModerationPolicy::onTimer);
				_pTimer->schedule(_pTimerTask, _lastEvent + _maximumRate*Poco::Clock::resolution()/1000);
			}
		}
	}
	
	long getMaximumRate() const
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		return _maximumRate;
	}
	
	void setMaximumRate(long milliseconds)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		_maximumRate = milliseconds;
	}
	
protected:
	void onTimer(Poco::Util::TimerTask&)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);
		
		(*_pEvent)(this, _value);
		_lastEvent.update();
		_pTimerTask = 0;
	}
	
private:
	MaximumRateModerationPolicy();
	
	Event* _pEvent;
	T _value;
	long _maximumRate;
	Poco::Clock _lastEvent;
	Poco::Util::Timer* _pTimer;
	Poco::Util::TimerTask::Ptr _pTimerTask;
	mutable Poco::FastMutex _mutex;
};


} } // namespace namespace IoT::Devices


#endif // IoT_Devices_EventModerationPolicy_INCLUDED
