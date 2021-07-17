//
// SchedulerExtensionPoint.h
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_JS_Scheduler_SchedulerExtensionPoint_INCLUDED
#define OSP_JS_Scheduler_SchedulerExtensionPoint_INCLUDED


#include "Poco/OSP/ExtensionPoint.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/BundleEvent.h"
#include "Poco/OSP/JS/JSExecutor.h"
#include "Poco/Util/Timer.h"
#include "Poco/StringTokenizer.h"
#include "Poco/DateTime.h"
#include "Poco/Mutex.h"
#include <vector>


namespace Poco {
namespace OSP {
namespace JS {
namespace Scheduler {


class SchedulerExtensionPoint: public Poco::OSP::ExtensionPoint
	/// An extension point for starting JavaScript scripts contained
	/// in bundles.
	///
	/// The following extension point attributes are supported:
	///   - script: path (bundle resource) to the script to be executed
	///   - memoryLimit: size limit for JavaScript allocated memory (default 1 MB)
{
public:
	SchedulerExtensionPoint(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the JavaScript extension point.

	~SchedulerExtensionPoint();
		/// Destroys the JavaScript extension point.

	void scheduleTasks();
		/// Starts all tasks ready for execution.

	// Poco::OSP::ExtensionPoint
	void handleExtension(Poco::OSP::Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem);

protected:
	void onBundleStopped(const void* pSender, Poco::OSP::BundleEvent& ev);

private:
	struct Schedule
	{
		Schedule();

		std::string expression;
		Poco::UInt64 minutesMask;     /// bitmask for minutes (bits 0 .. 59)
		Poco::UInt32 hoursMask;       /// bitmask for hours (bits 0 .. 23)
		Poco::UInt32 daysOfMonthMask; /// bitmask for days of month (bits 1 .. 31)
		Poco::UInt16 monthsMask;      /// bitmask for months (bits 1 .. 12)
		Poco::UInt8  daysOfWeekMask;  /// bitmask for days of week (bits 0 .. 6)
		Poco::DateTime notBefore;     /// treated as local time
		Poco::DateTime notAfter;      /// treated as local time
	};

	struct Task
	{
		Task();

		Schedule schedule;
		Poco::OSP::JS::TimedJSExecutor::Ptr pExecutor;
		bool exportsStart;
	};

	void parseSchedule(Schedule& schedule, const std::string& expr);
	void parseSchedule(Schedule& schedule, std::string::const_iterator& it, const std::string::const_iterator& end);
	Poco::UInt64 parseScheduleItem(std::string::const_iterator& it, const std::string::const_iterator& end, int min, int max, const std::string& symbols);
	int parseIncrement(std::string::const_iterator& it, const std::string::const_iterator& end);
	int parseNumberOrSymbol(std::string::const_iterator& it, const std::string::const_iterator& end, const Poco::StringTokenizer& symbols);
	void scheduleNext();

	static const std::string YEARLY;
	static const std::string MONTHLY;
	static const std::string WEEKLY;
	static const std::string DAILY;
	static const std::string HOURLY;

	Poco::OSP::BundleContext::Ptr _pContext;
	std::vector<Task> _tasks;
	Poco::Util::Timer _schedulerTimer;
	Poco::FastMutex _mutex;
};


} } } } // namespace Poco::OSP::JS::Scheduler


#endif // OSP_JS_Scheduler_SchedulerExtensionPoint_INCLUDED
