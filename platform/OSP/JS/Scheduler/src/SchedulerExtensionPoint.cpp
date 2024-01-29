//
// SchedulerExtensionPoint.cpp
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "SchedulerExtensionPoint.h"
#include "Poco/OSP/BundleEvents.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/StreamCopier.h"
#include "Poco/DateTime.h"
#include "Poco/LocalDateTime.h"
#include "Poco/NumberParser.h"
#include "Poco/DateTimeParser.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Format.h"
#include "Poco/Delegate.h"
#include "Poco/Event.h"
#include "Poco/String.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/MD5Engine.h"
#include "v8.h"
#include <memory>


using Poco::JS::Core::Wrapper;
using namespace std::string_literals;


namespace Poco {
namespace OSP {
namespace JS {
namespace Scheduler {


bool notBefore(const Poco::DateTime& refDate, const Poco::LocalDateTime& curDate)
{
	if (curDate.year() > refDate.year()) return true;
	if (curDate.year() == refDate.year())
	{
		if (curDate.month() > refDate.month()) return true;
		if (curDate.month() == refDate.month())
		{
			if (curDate.day() > refDate.day()) return true;
			if (curDate.day() == refDate.day())
			{
				if (curDate.hour() > refDate.hour()) return true;
				if (curDate.hour() == refDate.hour())
				{
					if (curDate.minute() >= refDate.minute()) return true;
				}
			}
		}
	}
	return false;
}


bool notAfter(const Poco::DateTime& refDate, const Poco::LocalDateTime& curDate)
{
	if (curDate.year() < refDate.year()) return true;
	if (curDate.year() == refDate.year())
	{
		if (curDate.month() < refDate.month()) return true;
		if (curDate.month() == refDate.month())
		{
			if (curDate.day() < refDate.day()) return true;
			if (curDate.day() == refDate.day())
			{
				if (curDate.hour() < refDate.hour()) return true;
				if (curDate.hour() == refDate.hour())
				{
					if (curDate.minute() < refDate.minute()) return true;
				}
			}
		}
	}
	return false;
}


class SchedulerTask: public Poco::Util::TimerTask
{
public:
	SchedulerTask(SchedulerExtensionPoint& scheduler):
		_scheduler(scheduler)
	{
	}

	void run()
	{
		_scheduler.scheduleTasks();
	}

private:
	SchedulerExtensionPoint& _scheduler;
};


class CallExportedFunctionTask: public Poco::Util::TimerTask
{
public:
	typedef Poco::AutoPtr<CallExportedFunctionTask> Ptr;

	CallExportedFunctionTask(Poco::OSP::JS::TimedJSExecutor::Ptr pExecutor, const std::string& function):
		_pExecutor(pExecutor),
		_function(function)
	{
	}

	void run()
	{
		try
		{
			v8::Isolate* pIsolate = _pExecutor->isolate();
			v8::Locker locker(pIsolate);
			v8::Isolate::Scope isoScope(pIsolate);
			v8::HandleScope handleScope(pIsolate);

			v8::Persistent<v8::Context>& persistentContext = _pExecutor->scriptContext();
			if (!persistentContext.IsEmpty()) // ran at least once
			{
				v8::Local<v8::Context> context(v8::Local<v8::Context>::New(pIsolate, persistentContext));
				v8::Context::Scope contextScope(context);

				v8::Local<v8::Object> global = context->Global();

				v8::MaybeLocal<v8::Value> maybeModuleValue = global->Get(context, Wrapper::toV8Internalized(pIsolate, "module"s));
				v8::Local<v8::Value> moduleValue;
				if (maybeModuleValue.ToLocal(&moduleValue) && moduleValue->IsObject())
				{
					v8::Local<v8::Object> module = moduleValue.As<v8::Object>();
					v8::MaybeLocal<v8::Value> maybeExportsValue = module->Get(context, Wrapper::toV8Internalized(pIsolate, "exports"s));
					v8::Local<v8::Value> exportsValue;
					if (maybeExportsValue.ToLocal(&exportsValue) && exportsValue->IsObject())
					{
						v8::Local<v8::Object> exports = exportsValue.As<v8::Object>();
						v8::MaybeLocal<v8::Value> maybeStartValue = exports->Get(context, Wrapper::toV8String(pIsolate, _function));
						v8::Local<v8::Value> startValue;
						if (maybeStartValue.ToLocal(&startValue) && startValue->IsFunction())
						{
							v8::Local<v8::Function> start = startValue.As<v8::Function>();
							v8::Handle<v8::Value> arg;
							_pExecutor->callInContext(pIsolate, context, start, exportsValue, 0, &arg);
						}
					}
				}
			}
		}
		catch (Poco::Exception&)
		{
		}
		_done.set();
	}

	void wait()
	{
		_done.wait();
	}

	bool tryWait(long milliseconds)
	{
		return _done.tryWait(milliseconds);
	}

private:
	Poco::OSP::JS::TimedJSExecutor::Ptr _pExecutor;
	std::string _function;
	Poco::Event _done;
};


SchedulerExtensionPoint::Schedule::Schedule():
	minutesMask(0),
	hoursMask(0),
	daysOfMonthMask(0),
	monthsMask(0),
	daysOfWeekMask(0)
{
}


SchedulerExtensionPoint::Task::Task():
	exportsStart(false)
{
}


const std::string SchedulerExtensionPoint::YEARLY("0 0 1 1 *");
const std::string SchedulerExtensionPoint::MONTHLY("0 0 1 * *");
const std::string SchedulerExtensionPoint::WEEKLY("0 0 * * 0");
const std::string SchedulerExtensionPoint::DAILY("0 0 * * *");
const std::string SchedulerExtensionPoint::HOURLY("0 * * * *");


SchedulerExtensionPoint::SchedulerExtensionPoint(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext)
{
	_pContext->events().bundleStopped += Poco::delegate(this, &SchedulerExtensionPoint::onBundleStopped);
	scheduleNext();
}


SchedulerExtensionPoint::~SchedulerExtensionPoint()
{
	_pContext->events().bundleStopped -= Poco::delegate(this, &SchedulerExtensionPoint::onBundleStopped);
	_schedulerTimer.cancel(true);
}


void SchedulerExtensionPoint::scheduleTasks()
{
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		Poco::LocalDateTime now;
		for (std::vector<Task>::iterator it = _tasks.begin(); it != _tasks.end(); ++it)
		{
			if (notBefore(it->schedule.notBefore, now) && notAfter(it->schedule.notAfter, now))
			{
				if ((it->schedule.minutesMask & (1ULL << now.minute())) &&
					(it->schedule.hoursMask & (1 << now.hour())) &&
					(it->schedule.daysOfMonthMask & (1 << now.day())) &&
					(it->schedule.monthsMask & (1 << now.month())) &&
					(it->schedule.daysOfWeekMask & (1 << now.dayOfWeek())))
				{
					CallExportedFunctionTask::Ptr pStartTask = new CallExportedFunctionTask(it->pExecutor, "start");
					it->pExecutor->schedule(pStartTask);
				}
			}
		}
	}
	scheduleNext();
}


void SchedulerExtensionPoint::handleExtension(Poco::OSP::Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem)
{
	std::string schedule = pExtensionElem->getAttribute("schedule"s);
	std::string notBefore = pExtensionElem->getAttribute("notBefore"s);
	std::string notAfter = pExtensionElem->getAttribute("notAfter"s);
	std::string scriptPath = pExtensionElem->getAttribute("script"s);
	std::string runtimeLimit = pExtensionElem->getAttribute("runtimeLimit"s);
	Poco::UInt64 memoryLimit = pBundle->properties().getUInt64("osp.js.memoryLimit"s, JSExecutor::getDefaultMemoryLimit());
	std::string strMemoryLimit = pExtensionElem->getAttribute("memoryLimit"s);
	if (!strMemoryLimit.empty())
	{
		memoryLimit = Poco::NumberParser::parseUnsigned64(strMemoryLimit);
	}

	Poco::StringTokenizer tok(pExtensionElem->getAttribute("modulePath"s), ",;"s, Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
	std::vector<std::string> moduleSearchPaths(tok.begin(), tok.end());

	std::string script;
	std::unique_ptr<std::istream> pStream(pBundle->getResource(scriptPath));
	if (!pStream)
	{
		_pContext->logger().error("Script not found: %s"s, scriptPath);
		return;
	}
	Poco::StreamCopier::copyToString(*pStream, script);
	_pContext->logger().information("Starting script %s from bundle %s."s, scriptPath, pBundle->symbolicName());
	std::string scriptURI("bndl://");
	scriptURI += pBundle->symbolicName();
	if (scriptPath.empty() || scriptPath[0] != '/') scriptURI += "/";
	scriptURI += scriptPath;

	if (schedule.empty()) schedule = "@start";

	Task task;
	task.pExecutor = new Poco::OSP::JS::TimedJSExecutor(_pContext->contextForBundle(pBundle), pBundle, script, Poco::URI(scriptURI), moduleSearchPaths, memoryLimit);
	task.schedule.expression = schedule;
	parseSchedule(task.schedule, schedule);

	if (!notBefore.empty())
	{
		int tzd;
		task.schedule.notBefore = Poco::DateTimeParser::parse(Poco::DateTimeFormat::ISO8601_FORMAT, notBefore, tzd);
	}
	else
	{
		task.schedule.notBefore = Poco::DateTime(2000, 1, 1);
	}

	if (!notAfter.empty())
	{
		int tzd;
		task.schedule.notAfter = Poco::DateTimeParser::parse(Poco::DateTimeFormat::ISO8601_FORMAT, notAfter, tzd);
	}
	else
	{
		task.schedule.notAfter = Poco::DateTime(2200, 1, 1);
	}

	{
		Poco::FastMutex::ScopedLock lock(_mutex);
		_tasks.push_back(task);
	}

	if (task.schedule.expression == "@start")
	{
		task.pExecutor->run();

		CallExportedFunctionTask::Ptr pStartTask = new CallExportedFunctionTask(task.pExecutor, "start"s);
		task.pExecutor->schedule(pStartTask);
		pStartTask->wait();
	}
	else if (task.schedule.expression == "@once")
	{
		Poco::MD5Engine md5;
		md5.update(scriptPath);

		std::string onceFileName = ".once_";
		onceFileName += Poco::DigestEngine::digestToHex(md5.digest());

		Poco::OSP::BundleContext::Ptr pBundleContext = _pContext->contextForBundle(pBundle);
		Poco::Path oncePath = pBundleContext->persistentDirectory();
		oncePath.makeDirectory();
		oncePath.setFileName(onceFileName);
		Poco::File onceFile(oncePath.toString());
		if (!onceFile.exists())
		{
			Poco::FileOutputStream ostr(onceFile.path());
			ostr << scriptPath << "\n";
			ostr.close();

			task.pExecutor->run();

			CallExportedFunctionTask::Ptr pStartTask = new CallExportedFunctionTask(task.pExecutor, "start"s);
			task.pExecutor->schedule(pStartTask);
		}
	}
	else
	{
		task.pExecutor->run();
	}
}


void SchedulerExtensionPoint::onBundleStopped(const void* pSender, Poco::OSP::BundleEvent& ev)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	Poco::OSP::Bundle::ConstPtr pBundle = ev.bundle();
	for (std::vector<Task>::iterator it = _tasks.begin(); it != _tasks.end();)
	{
		if (it->pExecutor->bundle() == pBundle)
		{
			_pContext->logger().information("Stopping script %s."s, it->pExecutor->uri().toString());
			it->pExecutor->terminate();
			CallExportedFunctionTask::Ptr pStopTask = new CallExportedFunctionTask(it->pExecutor, "stop"s);
			it->pExecutor->schedule(pStopTask);
			pStopTask->wait();
			it->pExecutor->stop();
			it = _tasks.erase(it);
		}
		else ++it;
	}
}


void SchedulerExtensionPoint::parseSchedule(Schedule& schedule, const std::string& expr)
{
	if (expr == "@yearly")
	{
		std::string::const_iterator it = YEARLY.begin();
		std::string::const_iterator end = YEARLY.end();
		parseSchedule(schedule, it, end);
	}
	else if (expr == "@monthly")
	{
		std::string::const_iterator it = MONTHLY.begin();
		std::string::const_iterator end = MONTHLY.end();
		parseSchedule(schedule, it, end);
	}
	else if (expr == "@weekly")
	{
		std::string::const_iterator it = WEEKLY.begin();
		std::string::const_iterator end = WEEKLY.end();
		parseSchedule(schedule, it, end);
	}
	else if (expr == "@daily")
	{
		std::string::const_iterator it = DAILY.begin();
		std::string::const_iterator end = DAILY.end();
		parseSchedule(schedule, it, end);
	}
	else if (expr == "@hourly")
	{
		std::string::const_iterator it = HOURLY.begin();
		std::string::const_iterator end = HOURLY.end();
		parseSchedule(schedule, it, end);
	}
	else if (expr != "@start" && expr != "@once")
	{
		std::string::const_iterator it = expr.begin();
		std::string::const_iterator end = expr.end();
		parseSchedule(schedule, it, end);
	}
}


void SchedulerExtensionPoint::parseSchedule(Schedule& schedule, std::string::const_iterator& it, const std::string::const_iterator& end)
{
	schedule.minutesMask = parseScheduleItem(it, end, 0, 59, ""s);
	schedule.hoursMask = static_cast<Poco::UInt32>(parseScheduleItem(it, end, 0, 23, ""s));
	schedule.daysOfMonthMask = static_cast<Poco::UInt32>(parseScheduleItem(it, end, 1, 31, ""s));
	schedule.monthsMask = static_cast<Poco::UInt16>(parseScheduleItem(it, end, 1, 12, "#,JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC"s));
	schedule.daysOfWeekMask = static_cast<Poco::UInt8>(parseScheduleItem(it, end, 0, 7, "SUN,MON,TUE,WED,THU,FRI,SAT"s));
	if (schedule.daysOfWeekMask & 0x80) // special case - 7 = SUN
	{
		schedule.daysOfWeekMask |= 0x01;
	}
}


Poco::UInt64 SchedulerExtensionPoint::parseScheduleItem(std::string::const_iterator& it, const std::string::const_iterator& end, int min, int max, const std::string& symbols)
{
	Poco::UInt64 mask = 0;
	while (it != end && Poco::Ascii::isSpace(*it)) ++it;

	Poco::StringTokenizer tok(symbols, ","s, 0);

	if (it == end || *it == '*')
	{
		if (it != end) ++it;
		int incr = parseIncrement(it, end);
		for (int i = min; i <= max; i += incr)
		{
			mask |= (1ULL << i);
		}
	}
	else
	{
		while (it != end && Poco::Ascii::isAlphaNumeric(*it))
		{
			int num = parseNumberOrSymbol(it, end, tok);
			if (num < min || num > max) throw Poco::InvalidArgumentException("argument out of range");
			if (it != end && *it == '-')
			{
				++it;
				int to = parseNumberOrSymbol(it, end, tok);
				if (min == 0 && max == 7 && to == 0) to = 7; // special case: make MON-SUN work
				if (to < num || to > max) throw Poco::InvalidArgumentException("argument out of range");
				int incr = parseIncrement(it, end);
				for (int i = num; i <= to; i += incr)
				{
					mask |= (1ULL << i);
				}
			}
			else
			{
				mask += (1ULL << num);
			}
			if (it != end && *it == ',')
			{
				++it;
			}
		}
	}
	return mask;
}


int SchedulerExtensionPoint::parseIncrement(std::string::const_iterator& it, const std::string::const_iterator& end)
{
	int incr = 1;
	if (it != end && *it == '/')
	{
		++it;
		if (it != end && Poco::Ascii::isDigit(*it))
		{
			incr = *it++ - '0';
			while (it != end && Poco::Ascii::isDigit(*it))
			{
				incr = 10*incr + *it++ - '0';
			}
		}
		else throw Poco::SyntaxException("invalid schedule: expecting increment (integer) after '/'");
	}
	if (incr == 0) throw Poco::InvalidArgumentException("increment cannot be 0");
	return incr;
}


int SchedulerExtensionPoint::parseNumberOrSymbol(std::string::const_iterator& it, const std::string::const_iterator& end, const Poco::StringTokenizer& symbols)
{
	int num = 0;
	if (it != end && Poco::Ascii::isDigit(*it))
	{
		num = *it++ - '0';
		while (it != end && Poco::Ascii::isDigit(*it))
		{
			num = 10*num + *it++ - '0';
		}
	}
	else if (it != end)
	{
		std::string tok;
		tok += *it++;
		while (it != end && Poco::Ascii::isAlpha(*it))
		{
			tok += Poco::Ascii::toUpper(*it++);
		}
		num = static_cast<int>(symbols.find(tok));
	}
	return num;
}


void SchedulerExtensionPoint::scheduleNext()
{
	Poco::Clock clock;
	Poco::DateTime now;
	long secondsToStart = 60 - now.second();
	clock += secondsToStart*Poco::Clock::resolution();
	_schedulerTimer.schedule(new SchedulerTask(*this), clock);
}


} } } } // namespace Poco::OSP::JS::Scheduler
