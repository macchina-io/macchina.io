//
// Bundle.cpp
//
// $Id: //poco/1.6/OSP/src/Bundle.cpp#1 $
//
// Library: OSP
// Package: Bundle
// Module:  Bundle
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/BundleLoader.h"
#include "Poco/OSP/OSPException.h"
#include "Poco/Util/PropertyFileConfiguration.h"
#include "Poco/Path.h"
#include <memory>


using Poco::Util::LayeredConfiguration;
using Poco::Util::PropertyFileConfiguration;
using Poco::Path;


namespace Poco {
namespace OSP {


namespace
{
	class StateChange
	{
	public:
		StateChange(Bundle::State& state, Bundle::State newState):
			_state(state),
			_oldState(state)
		{
			_state = newState;
		}
		
		~StateChange()
		{
			_state = _oldState;
		}
		
		void set(Bundle::State state)
		{
			_state = state;
		}
		
		void commit(Bundle::State state)
		{
			_state = _oldState = state;
		}

		void commit()
		{
			_oldState = _state;
		}
		
	private:
		Bundle::State& _state;
		Bundle::State  _oldState;
	};
}


const std::string Bundle::MANIFEST_FILE("META-INF/manifest.mf");
const std::string Bundle::PROPERTIES_FILE("bundle.properties");
const std::string Bundle::BUNDLE_INSTALLED_STRING("installed");
const std::string Bundle::BUNDLE_UNINSTALLED_STRING("uninstalled");
const std::string Bundle::BUNDLE_RESOLVED_STRING("resolved");
const std::string Bundle::BUNDLE_STARTING_STRING("starting");
const std::string Bundle::BUNDLE_ACTIVE_STRING("active");
const std::string Bundle::BUNDLE_STOPPING_STRING("stopping");
const std::string Bundle::BUNDLE_INVALID_STRING("INVALID");


Bundle::Bundle(int id, BundleLoader& loader, BundleStorage::Ptr pStorage, const LanguageTag& language):
	_id(id),
	_state(BUNDLE_INSTALLED),
	_loader(loader),
	_pStorage(pStorage),
	_language(language),
	_pProperties(new BundleProperties),
	_pActivator(0)
{
	poco_check_ptr (_pStorage);
	
	loadManifest();
	loadProperties();
	
	_name      = _pProperties->expand(_pManifest->name());
	_vendor    = _pProperties->expand(_pManifest->vendor());
	_copyright = _pProperties->expand(_pManifest->copyright());
}


Bundle::~Bundle()
{
}


const std::string& Bundle::stateString() const
{
	switch (_state)
	{
	case BUNDLE_INSTALLED:
		return BUNDLE_INSTALLED_STRING;
	case BUNDLE_UNINSTALLED:
		return BUNDLE_UNINSTALLED_STRING;
	case BUNDLE_RESOLVED:
		return BUNDLE_RESOLVED_STRING;
	case BUNDLE_STARTING:
		return BUNDLE_STARTING_STRING;
	case BUNDLE_ACTIVE:
		return BUNDLE_ACTIVE_STRING;
	case BUNDLE_STOPPING:
		return BUNDLE_STOPPING_STRING;
	default:
		poco_bugcheck();
		return BUNDLE_INVALID_STRING;
	}
}


std::istream* Bundle::getResource(const std::string& name) const
{
	std::istream* pStream = _pStorage->getResource(name);
	if (!pStream)
	{
		Poco::FastMutex::ScopedLock lock(_extensionBundlesMutex);

		std::set<Bundle::Ptr>::const_iterator it = _extensionBundles.begin();
		std::set<Bundle::Ptr>::const_iterator end = _extensionBundles.end();
		while (!pStream && it != end)
		{
			pStream = (*it)->getResource(name);
			++it; 
		}
	}
	return pStream;
}


std::istream* Bundle::getLocalizedResource(const std::string& name) const
{
	return getLocalizedResource(name, _language);
}


std::istream* Bundle::getLocalizedResource(const std::string& name, const LanguageTag& language) const
{
	Path localPath(false);
	localPath.pushDirectory(language.primaryTag());
	localPath.pushDirectory(language.subTags());
	Path resPath(localPath, name);
	std::istream* pStream = getResource(resPath.toString(Path::PATH_UNIX)); 
	while (!pStream && localPath.depth() > 0)
	{
		localPath.popDirectory();
		resPath = Path(localPath, name);
		pStream = getResource(resPath.toString(Path::PATH_UNIX));
	}
	return pStream;
}


inline BundleEvents& Bundle::events()
{
	return _loader.events();
}


void Bundle::resolve()
{
	if (_state != BUNDLE_INSTALLED) throw BundleStateException("resolve() requires INSTALLED state");
	
	BundleEvent resolvingEvent(this, BundleEvent::EV_BUNDLE_RESOLVING);
	events().bundleResolving(this, resolvingEvent);
	_loader.resolveBundle(this);
	_state = BUNDLE_RESOLVED;
	BundleEvent resolvedEvent(this, BundleEvent::EV_BUNDLE_RESOLVED);
	events().bundleResolved(this, resolvedEvent);
}


void Bundle::start()
{
	if (_state != BUNDLE_RESOLVED) throw BundleStateException("start() requires RESOLVED state");
	
	StateChange stateChange(_state, BUNDLE_STARTING);
	BundleEvent startingEvent(this, BundleEvent::EV_BUNDLE_STARTING);
	events().bundleStarting(this, startingEvent);
	_loader.startBundle(this);
	stateChange.commit(BUNDLE_ACTIVE);
	BundleEvent startedEvent(this, BundleEvent::EV_BUNDLE_STARTED);
	events().bundleStarted(this, startedEvent);
}


void Bundle::stop()
{
	if (_state != BUNDLE_ACTIVE) throw BundleStateException("stop() requires ACTIVE state");
	
	StateChange stateChange(_state, BUNDLE_STOPPING);
	BundleEvent stoppingEvent(this, BundleEvent::EV_BUNDLE_STOPPING);
	events().bundleStopping(this, stoppingEvent);
	_loader.stopBundle(this);
	stateChange.commit(BUNDLE_RESOLVED);
	BundleEvent stoppedEvent(this, BundleEvent::EV_BUNDLE_STOPPED);
	events().bundleStopped(this, stoppedEvent);
}


void Bundle::uninstall()
{
	if (_state != BUNDLE_INSTALLED && _state != BUNDLE_RESOLVED) throw BundleStateException("uninstall() requires INSTALLED or RESOLVED state");
	
	BundleEvent uninstallingEvent(this, BundleEvent::EV_BUNDLE_UNINSTALLING);
	events().bundleUninstalling(this, uninstallingEvent);
	_loader.uninstallBundle(this);
	_state = BUNDLE_UNINSTALLED;
	BundleEvent uninstalledEvent(this, BundleEvent::EV_BUNDLE_UNINSTALLED);
	events().bundleUninstalled(this, uninstalledEvent);
}


bool Bundle::isExtensionBundle() const
{
	return !_pManifest->extendedBundle().empty();
}

		
Bundle::Ptr Bundle::extendedBundle() const
{
	Bundle::Ptr pExtendedBundle;
	const std::string& bundleId = _pManifest->extendedBundle();
	if (!bundleId.empty())
	{
		pExtendedBundle = _loader.findBundle(bundleId);
	}
	return pExtendedBundle;
}


void Bundle::loadManifest()
{
	std::auto_ptr<std::istream> pStream(_pStorage->getResource(MANIFEST_FILE));
	if (pStream.get())
		_pManifest = new BundleManifest(*pStream);
	else
		throw BundleLoadException("No manifest found", _pStorage->path());
}


void Bundle::loadProperties()
{
	Path localPath(false);
	localPath.pushDirectory(_language.primaryTag());
	localPath.pushDirectory(_language.subTags());
	while (localPath.depth() > 0)
	{
		Path resPath(localPath, PROPERTIES_FILE);
		addProperties(resPath.toString(Path::PATH_UNIX));
		localPath.popDirectory();
	}
	addProperties(PROPERTIES_FILE);
}


void Bundle::addProperties(const std::string& path)
{
	std::auto_ptr<std::istream> pStream(getResource(path));
	if (pStream.get())
	{
		PropertyFileConfiguration* pConfig = new PropertyFileConfiguration(*pStream);
		_pProperties->addProperties(pConfig, false);
	}
}


void Bundle::setActivator(BundleActivator* pActivator)
{
	_pActivator = pActivator;
}


void Bundle::addExtensionBundle(Bundle* pExtensionBundle)
{
	if (isResolved())
	{
		{
			Poco::FastMutex::ScopedLock lock(_extensionBundlesMutex);
		
			_extensionBundles.insert(Bundle::Ptr(pExtensionBundle, true));
		}
		_pProperties->addProperties(pExtensionBundle->_pProperties, -static_cast<int>(_extensionBundles.size()), true);
	}
	else throw BundleStateException("addExtensionBundle() requires at least RESOLVED state");
}

	
void Bundle::removeExtensionBundle(Bundle* pExtensionBundle)
{
	Poco::FastMutex::ScopedLock lock(_extensionBundlesMutex);

	_extensionBundles.erase(Bundle::Ptr(pExtensionBundle, true));
	_pProperties->removeProperties(pExtensionBundle->_pProperties);
}


} } // namespace Poco::OSP
