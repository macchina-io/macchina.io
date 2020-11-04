//
// BundleAdmin.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "BundleListHandler.h"
#include "BundleInfoHandler.h"
#include "BundleInstallHandler.h"
#include "RequestHandlerFactory.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::Web::WebRequestHandlerFactory;


using BundleListHandlerFactory = RequestHandlerFactory<BundleListHandler>;
using BundleInfoHandlerFactory = RequestHandlerFactory<BundleInfoHandler>;
using BundleInstallHandlerFactory = RequestHandlerFactory<BundleInstallHandler>;


POCO_BEGIN_NAMED_MANIFEST(WebServer, WebRequestHandlerFactory)
	POCO_EXPORT_CLASS(BundleListHandlerFactory)
	POCO_EXPORT_CLASS(BundleInfoHandlerFactory)
	POCO_EXPORT_CLASS(BundleInstallHandlerFactory)
POCO_END_MANIFEST
