//
// BundleInfoHandler.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "BundleInfoHandler.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/NumberFormatter.h"
#include <vector>


using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;
using Poco::OSP::BundleManifest;
using Poco::NumberFormatter;


BundleInfoHandler::BundleInfoHandler(Poco::OSP::BundleContext::Ptr pContext):
	RequestHandler(pContext)
{
}


BundleInfoHandler::~BundleInfoHandler()
{
}

	
void BundleInfoHandler::run()
{
	std::string symbolicName = form().get("symbolicName");
	
	Bundle::Ptr pBundle = context()->findBundle(symbolicName);
	if (pBundle)
	{
		if (form().has("action"))
		{
			if (performAction(pBundle, form().get("action")))
				return;
		}

		std::string title(text("bundle"));
		title += ": ";
		title += pBundle->name();
		beginPage(title, bundle()->properties().getString("web.path"), text("installedBundles"));
		beginList();
		item(text("id"), NumberFormatter::format(pBundle->id()));
		item(text("symbolicName"), pBundle->symbolicName());
		item(text("version"), pBundle->version().toString());
		item(text("vendor"), pBundle->vendor());
		item(text("copyright"), pBundle->copyright());
		item(text("state"), pBundle->stateString());
		item(text("runlevel"), pBundle->runLevel());
		item(text("path"), pBundle->path());
		endList();
		actions(pBundle);
		dependencies(pBundle);
		modules(pBundle);
		provided(pBundle);
		endPage();
	}
	else
	{
		beginPage("Unknown bundle.");
		endPage();
	}
}


void BundleInfoHandler::dependencies(Poco::OSP::Bundle::Ptr pBundle)
{
	const BundleManifest::Dependencies& deps = pBundle->requiredBundles();

	if (deps.empty()) return;

	heading(text("dependencies"));

	beginTable();
	beginRow(true);
	headerCell(text("bundle"));
	headerCell(text("version"));
	endRow();
	
	bool even = true;
	for (BundleManifest::Dependencies::const_iterator it = deps.begin(); it != deps.end(); ++it)
	{
		beginRow(even);
		beginCell();
		linkBundle(it->symbolicName);
		endCell();
		cell(it->versions.toString());
		endRow();
		even = !even;
	}
	endTable();
}


void BundleInfoHandler::modules(Poco::OSP::Bundle::Ptr pBundle)
{
	const BundleManifest::Dependencies& deps = pBundle->requiredModules();

	if (deps.empty()) return;

	heading(text("modules"));

	beginTable();
	beginRow(true);
	headerCell(text("module"));
	headerCell(text("version"));
	endRow();

	bool even = true;
	for (BundleManifest::Dependencies::const_iterator it = deps.begin(); it != deps.end(); ++it)
	{
		beginRow(even);
		cell(it->symbolicName);
		cell(it->versions.toString());
		endRow();
		even = !even;
	}
	endTable();
}


void BundleInfoHandler::provided(Poco::OSP::Bundle::Ptr pBundle)
{
	const Bundle::Modules& mods = pBundle->providedModules();

	if (mods.empty()) return;

	heading(text("provided"));

	beginTable();
	beginRow(true);
	headerCell(text("module"));
	headerCell(text("version"));
	endRow();

	bool even = true;
	for (Bundle::Modules::const_iterator it = mods.begin(); it != mods.end(); ++it)
	{
		beginRow(even);
		cell(it->symbolicName);
		cell(it->version.toString());
		endRow();
		even = !even;
	}
	endTable();
}


void BundleInfoHandler::actions(Poco::OSP::Bundle::Ptr pBundle)
{
	bool resolve   = false;
	bool start     = false;
	bool stop      = false;
	bool uninstall = false;
	bool upgrade   = false;
	if (pBundle->state() == Bundle::BUNDLE_INSTALLED)
	{
		resolve   = true;
		uninstall = true;
		upgrade   = true;
	}
	else if (pBundle->state() == Bundle::BUNDLE_RESOLVED)
	{
		start     = true;
		uninstall = true;
		upgrade   = true;
	}
	else if (pBundle->state() == Bundle::BUNDLE_ACTIVE)
	{
		stop = pBundle != context()->thisBundle();
	}
	beginActionBar();
	if (resolve) action(pBundle, "resolve", text("resolveBundle"));
	if (start) action(pBundle, "start", text("startBundle"));
	if (stop) action(pBundle, "stop", text("stopBundle"));
	if (upgrade) action(pBundle, "${html.installPath}", "upgrade", text("upgradeBundle"));
	if (uninstall) action(pBundle, "uninstall", text("uninstallBundle"));
	endActionBar();
}


bool BundleInfoHandler::performAction(Poco::OSP::Bundle::Ptr pBundle, const std::string& action)
{
	if (action == "resolve")
	{
		pBundle->resolve();
	}
	else if (action == "uninstall")
	{
		confirmUninstall(pBundle);
		return true;
	}
	else if (action == "confirmedUninstall")
	{
		pBundle->uninstall();
	}
	else if (action == "start")
	{
		pBundle->start();
	}
	else if (action == "stop")
	{
		BundleVec deps;
		dependingBundles(pBundle, deps);
		if (deps.empty())
		{
			pBundle->stop();
		}
		else
		{
			confirmStop(pBundle, deps);
			return true;
		}
	}
	else if (action == "confirmedStop")
	{
		pBundle->stop();
	}
	return false;
}


void BundleInfoHandler::confirmUninstall(Poco::OSP::Bundle::Ptr pBundle)
{
	beginPage(text("confirmUninstall"));
	beginPara();
	templat().setString("name", pBundle->name());
	templat().setString("symbolicName", pBundle->symbolicName());
	write(text("uninstallSure"));
	endPara();
	beginActionBar();
	action(pBundle, "confirmedUninstall", text("uninstallBundle"));
	action(pBundle, "cancel", text("cancel"));
	endActionBar();
	endPage();
}


void BundleInfoHandler::confirmStop(Poco::OSP::Bundle::Ptr pBundle, const BundleVec& dependingBundles)
{
	beginPage(text("confirmStop"));
	beginPara();
	templat().setString("name", pBundle->name());
	templat().setString("symbolicName", pBundle->symbolicName());
	write(text("stopSure"));
	endPara();

	beginTable();
	beginRow(true);
	headerCell(text("bundle"));
	headerCell(text("version"));
	endRow();
	
	bool even = true;
	for (BundleVec::const_iterator it = dependingBundles.begin(); it != dependingBundles.end(); ++it)
	{
		beginRow(even);
		beginCell();
		linkBundle((*it)->symbolicName());
		endCell();
		cell((*it)->version().toString());
		endRow();
		even = !even;
	}
	endTable();

	beginActionBar();
	action(pBundle, "confirmedStop", text("stopBundle"));
	action(pBundle, "cancel", text("cancel"));
	endActionBar();
	endPage();
}


void BundleInfoHandler::dependingBundles(Poco::OSP::Bundle::Ptr pBundle, BundleVec& dependingBundles)
{
	BundleVec bundles;
	context()->listBundles(bundles);
	for (BundleVec::const_iterator it = bundles.begin(); it != bundles.end(); ++it)
	{
		if ((*it)->isStarted())
		{
			const BundleManifest::Dependencies& deps = (*it)->requiredBundles();
			for (BundleManifest::Dependencies::const_iterator itDep = deps.begin(); itDep != deps.end(); ++itDep)
			{
				if (itDep->symbolicName == pBundle->symbolicName())
				{
					dependingBundles.push_back(*it);
					break;
				}
			}
		}
	}
}
