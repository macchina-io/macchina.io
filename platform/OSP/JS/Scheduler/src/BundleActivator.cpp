//
// BundleActivator.cpp
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/ExtensionPointService.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/ClassLibrary.h"
#include "SchedulerExtensionPoint.h"


using namespace std::string_literals;


namespace Poco {
namespace OSP {
namespace JS {
namespace Scheduler {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}

	~BundleActivator()
	{
	}

	void start(Poco::OSP::BundleContext::Ptr pContext)
	{
		_pContext = pContext;

		_pPrefs = Poco::OSP::ServiceFinder::find<Poco::OSP::PreferencesService>(_pContext);
		_pXPS = Poco::OSP::ServiceFinder::find<Poco::OSP::ExtensionPointService>(_pContext);

		Poco::OSP::ExtensionPoint::Ptr pXP = new SchedulerExtensionPoint(pContext);
		_pXPS->registerExtensionPoint(pContext->thisBundle(), "com.appinf.osp.js.schedule"s, pXP);
	}

	void stop(Poco::OSP::BundleContext::Ptr pContext)
	{
		_pXPS->unregisterExtensionPoint("com.appinf.osp.js.schedule"s);
		_pXPS = 0;
		_pPrefs = 0;
		_pContext = 0;
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::ExtensionPointService::Ptr _pXPS;
	Poco::OSP::PreferencesService::Ptr _pPrefs;
};


} } } } // namespace Poco::OSP::JS::Scheduler


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(Poco::OSP::JS::Scheduler::BundleActivator)
POCO_END_MANIFEST
