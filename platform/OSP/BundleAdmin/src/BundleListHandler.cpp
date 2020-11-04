//
// BundleListHandler.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "BundleListHandler.h"
#include "Poco/NumberFormatter.h"
#include <vector>


using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;
using Poco::NumberFormatter;


BundleListHandler::BundleListHandler(Poco::OSP::BundleContext::Ptr pContext):
	RequestHandler(pContext)
{
}


BundleListHandler::~BundleListHandler()
{
}

	
void BundleListHandler::run()
{
	beginPage(text("installedBundles"));
	beginTable();
	beginRow(true);
	headerCell(text("id"));
	headerCell(text("bundleName"));
	headerCell(text("version"));
	headerCell(text("symbolicName"));
	headerCell(text("vendor"));
	headerCell(text("state"));
	endRow();
	
	std::vector<Bundle::Ptr> bundles;
	context()->listBundles(bundles);
	bool even = true;
	for (std::vector<Bundle::Ptr>::const_iterator it = bundles.begin(); it != bundles.end(); ++it)
	{
		beginRow(even);
		cell(NumberFormatter::format((*it)->id()));
		beginCell();
		linkBundle(*it, (*it)->name());
		endCell();
		cell((*it)->version().toString());
		cell((*it)->symbolicName());
		cell((*it)->vendor());
		cell((*it)->stateString());
		endRow();
		even = !even;
	}
	endTable();
	beginActionBar();
	action("${html.installPath}", "install", text("installBundle"));
	endActionBar();
	endPage();
}
