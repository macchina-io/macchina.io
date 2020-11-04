//
// BundleStreamFactoryTest.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "BundleStreamFactoryTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/BundleFactory.h"
#include "Poco/OSP/BundleContextFactory.h"
#include "Poco/OSP/BundleLoader.h"
#include "Poco/OSP/CodeCache.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/LanguageTag.h"
#include "Poco/OSP/BundleStreamFactory.h"
#include "Poco/OSP/SystemEvents.h"
#include "Poco/URIStreamOpener.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/Exception.h"


using Poco::OSP::Bundle;
using Poco::OSP::BundleFactory;
using Poco::OSP::BundleContextFactory;
using Poco::OSP::BundleLoader;
using Poco::OSP::CodeCache;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::LanguageTag;
using Poco::OSP::BundleStreamFactory;
using Poco::Path;
using Poco::File;


BundleStreamFactoryTest::BundleStreamFactoryTest(const std::string& name): CppUnit::TestCase(name)
{
}


BundleStreamFactoryTest::~BundleStreamFactoryTest()
{
}


void BundleStreamFactoryTest::testStreamFactory()
{
	CodeCache cc("codeCache");
	ServiceRegistry reg;
	LanguageTag lang("en", "US");

	BundleFactory::Ptr pBundleFactory(new BundleFactory(lang));
	Poco::OSP::SystemEvents systemEvents;
	BundleContextFactory::Ptr pBundleContextFactory(new BundleContextFactory(reg, systemEvents));
	BundleLoader loader(cc, pBundleFactory, pBundleContextFactory);

	loader.loadBundle(findBundle("com.appinf.osp.bundle2_1.0.0"));

	Poco::URIStreamOpener opener;
	opener.registerStreamFactory("bndl", new BundleStreamFactory(loader));

	std::unique_ptr<std::istream> pStream(opener.open("bndl://com.appinf.osp.bundle2/lang.txt"));
	assert (pStream.get() != 0);
	std::string s;
	*pStream >> s;
	assert (s == "en-US");

	try
	{
		std::unique_ptr<std::istream> pStream(opener.open("bndl://com.appinf.osp.bundle2/notfound.txt"));
		fail("resource not found - must throw");
	}
	catch (Poco::Exception&)
	{
	}

	try
	{
		std::unique_ptr<std::istream> pStream(opener.open("bndl://com.appinf.osp.bundle99/notfound.txt"));
		fail("bundle not found - must throw");
	}
	catch (Poco::Exception&)
	{
	}
}


void BundleStreamFactoryTest::setUp()
{
}


void BundleStreamFactoryTest::tearDown()
{
}


std::string BundleStreamFactoryTest::findBundle(const std::string& name)
{
	std::string bundles("bundles");
	std::string cwd(Path::current());
	Path cwdPath(cwd);
	Path p(cwdPath, bundles);
	bool found = false;
	while (!found && p.depth() > 0)
	{
		File f(p);
		if (f.exists())
			found = true;
		else
			p.popDirectory();
	}
	if (found)
		return Path(p, name).toString();
	else
		throw Poco::FileNotFoundException(name);
}


CppUnit::Test* BundleStreamFactoryTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("BundleStreamFactoryTest");

	CppUnit_addTest(pSuite, BundleStreamFactoryTest, testStreamFactory);

	return pSuite;
}
