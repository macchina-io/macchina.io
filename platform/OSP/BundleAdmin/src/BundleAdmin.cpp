//
// BundleAdmin.cpp
//
// $Id: //poco/1.6/OSP/BundleAdmin/src/BundleAdmin.cpp#1 $
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "BundleListHandler.h"
#include "BundleInfoHandler.h"
#include "BundleInstallHandler.h"
#include "RequestHandlerFactory.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::Web::WebRequestHandlerFactory;


typedef RequestHandlerFactory<BundleListHandler> BundleListHandlerFactory;
typedef RequestHandlerFactory<BundleInfoHandler> BundleInfoHandlerFactory;
typedef RequestHandlerFactory<BundleInstallHandler> BundleInstallHandlerFactory;


POCO_BEGIN_NAMED_MANIFEST(WebServer, WebRequestHandlerFactory)
	POCO_EXPORT_CLASS(BundleListHandlerFactory)
	POCO_EXPORT_CLASS(BundleInfoHandlerFactory)
	POCO_EXPORT_CLASS(BundleInstallHandlerFactory)
POCO_END_MANIFEST
