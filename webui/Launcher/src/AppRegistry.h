//
// AppRegistry.h
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef Launcher_AppRegistry_INCLUDED
#define Launcher_AppRegistry_INCLUDED


#include "Poco/OSP/Service.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/AutoPtr.h"
#include "Poco/Mutex.h"
#include <map>


namespace IoT {
namespace Web {
namespace Launcher {


class AppRegistry: public Poco::OSP::Service
{
public:
	typedef Poco::AutoPtr<AppRegistry> Ptr;
	
	struct App
	{
		std::string id;
		std::string path;
		std::string title;
		std::string tooltip;
		std::string icon;
		std::string permission;
		Poco::OSP::Bundle::Ptr pBundle;
	};
	typedef std::map<std::string, App> AppMap;
	typedef std::vector<App> AppVec;
	
	AppRegistry();
		/// Creates the AppRegistry.
			
	~AppRegistry();
		/// Destroys the AppRegistry.
	
	void add(const App& app);
		/// Adds an application to the registry.
	
	void remove(const std::string& bundle);
		/// Removes all applications defined in the bundle with
		/// the given symbolic name.
	
	void list(AppVec& apps);
		/// Returns a vector containing all registered applications.

	// Service
	const std::type_info& type() const;
	bool isA(const std::type_info& otherType) const;
	
	static std::string SERVICE_NAME;
	
private:
	AppRegistry(const AppRegistry&);
	AppRegistry& operator = (const AppRegistry&);
	
	Poco::FastMutex _mutex;
	AppMap _appMap;
};


} } } // namespace IoT::Web::Launcher


#endif // Launcher_AppRegistry_INCLUDED
