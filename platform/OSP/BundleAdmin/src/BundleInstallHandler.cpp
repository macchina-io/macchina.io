//
// BundleInstallHandler.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "BundleInstallHandler.h"
#include "Poco/OSP/BundleInstallerService.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/PartHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/AutoPtr.h"
#include "Poco/NumberFormatter.h"
#include <vector>


using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;
using Poco::OSP::BundleInstallerService;
using Poco::OSP::ServiceRef;
using Poco::Net::HTMLForm;
using Poco::Net::PartHandler;
using Poco::Net::MessageHeader;
using Poco::NumberFormatter;
using Poco::AutoPtr;


class InstallPartHandler: public PartHandler
{
public:
	InstallPartHandler(HTMLForm& form, AutoPtr<BundleInstallerService> pInstaller):
		_pInstaller(pInstaller),
		_form(form)
	{
	}
	
	void handlePart(const MessageHeader& header, std::istream& stream)
	{
		std::string symbolicName;
		if (_form.has("symbolicName"))
			symbolicName = _form.get("symbolicName");

		if (header.has("Content-Disposition"))
		{
			if (symbolicName.empty())
			{
				_pBundle = _pInstaller->installBundle(stream);
			}
			else
			{
				_pBundle = _pInstaller->replaceBundle(symbolicName, stream);
			}
		}
	}
	
	bool installed() const
	{
		return !_pBundle.isNull();
	}
	
	Bundle::Ptr bundle() const
	{
		return _pBundle;
	}
		
private:
	AutoPtr<BundleInstallerService> _pInstaller;
	HTMLForm& _form;
	Bundle::Ptr _pBundle;
};


BundleInstallHandler::BundleInstallHandler(Poco::OSP::BundleContext::Ptr pContext):
	RequestHandler(pContext)
{
}


BundleInstallHandler::~BundleInstallHandler()
{
}

	
void BundleInstallHandler::run()
{
	ServiceRef::Ptr pInstallerRef = context()->registry().findByName(BundleInstallerService::SERVICE_NAME);
	AutoPtr<BundleInstallerService> pInstaller = pInstallerRef->castedInstance<BundleInstallerService>();

	HTMLForm form;
	InstallPartHandler partHandler(form, pInstaller);
	form.load(request(), request().stream(), partHandler);

	std::string title;
	std::string backLink;
	std::string backLinkTitle;
	std::string symbolicName = form.get("symbolicName", "");
	if (!symbolicName.empty())
	{
		Bundle::Ptr pBundle = context()->findBundle(symbolicName);
		title = text("upgradeBundle");
		title += ": ";
		title += symbolicName;
		backLink = bundlePath(symbolicName);
		backLinkTitle = text("bundle");
		backLinkTitle += ": ";
		backLinkTitle += pBundle->name();
	}
	else
	{
		title = text("installBundle");
		backLink = bundle()->properties().getString("web.path");
		backLinkTitle = text("installedBundles");
	}
		
	beginPage(title, backLink, backLinkTitle);
	if (partHandler.installed())
	{
		templat().clear();
		templat().setString("symbolicName", partHandler.bundle()->symbolicName());
		templat().setString("name", partHandler.bundle()->name());
		sendTemplate("html.installComplete");
		beginList();
		item(text("id"), NumberFormatter::format(partHandler.bundle()->id()));
		item(text("symbolicName"), partHandler.bundle()->symbolicName());
		item(text("version"), partHandler.bundle()->version().toString());
		item(text("path"), partHandler.bundle()->path());
		endList();
	}
	else if (symbolicName.empty())
	{
		sendTemplate("html.installForm");
	}
	else
	{
		templat().clear();
		templat().setString("symbolicName", symbolicName);
		sendTemplate("html.upgradeForm");
	}
	endPage();
}


std::string BundleInstallHandler::bundlePath(const std::string& symbolicName)
{
	templat().clear();
	templat().setString("symbolicName", symbolicName);
	return templat().expand(bundle()->properties().getString("html.bundlePath"));
}

