//
// BundleRepositoryTest.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "BundleRepositoryTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/OSP/BundleRepository.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/BundleFactory.h"
#include "Poco/OSP/BundleContextFactory.h"
#include "Poco/OSP/BundleLoader.h"
#include "Poco/OSP/BundleFilter.h"
#include "Poco/OSP/CodeCache.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/LanguageTag.h"
#include "Poco/OSP/Version.h"
#include "Poco/OSP/OSPException.h"
#include "Poco/OSP/SystemEvents.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/Logger.h"
#include "Poco/ConsoleChannel.h"
#include <sstream>


using Poco::OSP::BundleRepository;
using Poco::OSP::Bundle;
using Poco::OSP::BundleFactory;
using Poco::OSP::BundleContextFactory;
using Poco::OSP::BundleLoader;
using Poco::OSP::CodeCache;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::LanguageTag;
using Poco::OSP::Version;
using Poco::OSP::BundleEvent;
using Poco::Path;
using Poco::File;
using Poco::Logger;


class AcceptAllFilter: public Poco::OSP::BundleFilter
{
public:
	bool accept(Bundle::Ptr pBundle)
	{
		return true;
	}
};


class RejectAllFilter: public Poco::OSP::BundleFilter
{
public:
	bool accept(Bundle::Ptr pBundle)
	{
		return false;
	}
};


class AcceptOneFilter: public Poco::OSP::BundleFilter
{
public:
	bool accept(Bundle::Ptr pBundle)
	{
		return pBundle->symbolicName() == "com.appinf.osp.bundle5";
	}
};


BundleRepositoryTest::BundleRepositoryTest(const std::string& name): CppUnit::TestCase(name)
{
}


BundleRepositoryTest::~BundleRepositoryTest()
{
}


void BundleRepositoryTest::testLoad()
{
	CodeCache cc("codeCache");
	ServiceRegistry reg;
	LanguageTag lang("en", "US");
	BundleFactory::Ptr pBundleFactory(new BundleFactory(lang));
	Poco::OSP::SystemEvents systemEvents;
	BundleContextFactory::Ptr pBundleContextFactory(new BundleContextFactory(reg, systemEvents));
	BundleLoader loader(cc, pBundleFactory, pBundleContextFactory);
	BundleRepository repo(findBundleRepository(), loader);
	
	repo.loadBundles();
	
	Bundle::Ptr pBundle1(loader.findBundle("com.appinf.osp.bundle1"));
	Bundle::Ptr pBundle2(loader.findBundle("com.appinf.osp.bundle2"));
	Bundle::Ptr pBundle3(loader.findBundle("com.appinf.osp.bundle3"));
	Bundle::Ptr pBundle4(loader.findBundle("com.appinf.osp.bundle4"));
	Bundle::Ptr pBundle5(loader.findBundle("com.appinf.osp.bundle5"));
	Bundle::Ptr pBundle6(loader.findBundle("com.appinf.osp.bundle6"));
	Bundle::Ptr pBundle7(loader.findBundle("com.appinf.osp.bundle7"));
	Bundle::Ptr pBundle8(loader.findBundle("com.appinf.osp.bundle8"));
	Bundle::Ptr pBundle9(loader.findBundle("com.appinf.osp.bundle9"));

	assert (!pBundle1.isNull());
	assert (!pBundle2.isNull());
	assert (!pBundle3.isNull());
	assert (!pBundle4.isNull());
	assert (!pBundle5.isNull());
	assert (!pBundle6.isNull());
	assert (!pBundle7.isNull());
	assert (!pBundle8.isNull());
	assert (!pBundle9.isNull());
}


void BundleRepositoryTest::testInstall()
{
	// The following is a ZIP file containing the same
	// directory hierarchy as is used in BundleDirectoryTest.
	static const unsigned char TEST_BUNDLE_ZIP[] = 
	{
		0x50, 0x4b, 0x03, 0x04, 0x14, 0x00, 0x00, 0x00, 0x08, 0x00, 0x36, 0x46, 0x85, 0x36, 0x2a, 0x71,
		0x30, 0xee, 0x9d, 0x00, 0x00, 0x00, 0xec, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x4d, 0x45,
		0x54, 0x41, 0x2d, 0x49, 0x4e, 0x46, 0x2f, 0x6d, 0x61, 0x6e, 0x69, 0x66, 0x65, 0x73, 0x74, 0x2e,
		0x6d, 0x66, 0x6d, 0xcd, 0x3d, 0x0b, 0xc2, 0x30, 0x14, 0x85, 0xe1, 0x5d, 0xe8, 0x7f, 0xb8, 0xa3,
		0x82, 0x2d, 0xad, 0x8b, 0x90, 0x4d, 0x45, 0xd4, 0xc1, 0x0f, 0x08, 0x74, 0x4f, 0xd3, 0xdb, 0x7a,
		0x21, 0xb9, 0x09, 0x49, 0x44, 0xfa, 0xef, 0x05, 0x0b, 0xb5, 0x83, 0xeb, 0xe1, 0x39, 0xbc, 0x57,
		0xc5, 0xd4, 0x61, 0x4c, 0x79, 0x8d, 0x21, 0x92, 0x63, 0x01, 0x55, 0x51, 0x66, 0x8b, 0xfd, 0x8b,
		0x5b, 0x83, 0xf9, 0x4d, 0x59, 0x14, 0x70, 0x97, 0x0f, 0x90, 0xca, 0x7a, 0x83, 0x30, 0xee, 0x50,
		0x4d, 0x42, 0x0e, 0xb6, 0x71, 0x86, 0xf4, 0x28, 0xb5, 0xb3, 0x85, 0xf2, 0x9e, 0xb8, 0x2b, 0x5c,
		0xf4, 0x45, 0xf3, 0x35, 0x3f, 0x3c, 0x6f, 0xcc, 0x2a, 0x35, 0x72, 0xeb, 0x82, 0x80, 0x9d, 0xf7,
		0x86, 0xb0, 0x85, 0x0b, 0x77, 0x2e, 0x58, 0x95, 0x48, 0xc7, 0xc9, 0x1c, 0x9c, 0x1f, 0x02, 0xf5,
		0xcf, 0x24, 0x60, 0xa9, 0x57, 0xb0, 0x29, 0xcb, 0xed, 0xfa, 0xdf, 0x01, 0xa4, 0xeb, 0xd2, 0x5b,
		0x05, 0x84, 0x23, 0xf7, 0xc4, 0x88, 0x81, 0xb8, 0x87, 0x93, 0x6d, 0xce, 0xd9, 0xe2, 0x03, 0x50,
		0x4b, 0x03, 0x04, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf7, 0x45, 0x85, 0x36, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x4d, 0x45, 0x54,
		0x41, 0x2d, 0x49, 0x4e, 0x46, 0x2f, 0x50, 0x4b, 0x01, 0x02, 0x14, 0x00, 0x14, 0x00, 0x00, 0x00,
		0x08, 0x00, 0x36, 0x46, 0x85, 0x36, 0x2a, 0x71, 0x30, 0xee, 0x9d, 0x00, 0x00, 0x00, 0xec, 0x00,
		0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x21, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x4d, 0x45, 0x54, 0x41, 0x2d, 0x49, 0x4e, 0x46, 0x2f, 0x6d, 0x61, 0x6e,
		0x69, 0x66, 0x65, 0x73, 0x74, 0x2e, 0x6d, 0x66, 0x50, 0x4b, 0x01, 0x02, 0x14, 0x00, 0x0a, 0x00,
		0x00, 0x00, 0x00, 0x00, 0xf7, 0x45, 0x85, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
		0x00, 0x00, 0xcf, 0x00, 0x00, 0x00, 0x4d, 0x45, 0x54, 0x41, 0x2d, 0x49, 0x4e, 0x46, 0x2f, 0x50,
		0x4b, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x00, 0x79, 0x00, 0x00, 0x00, 0xf6,
		0x00, 0x00, 0x00, 0x00, 0x00
	};

	CodeCache cc("codeCache");
	ServiceRegistry reg;
	LanguageTag lang("en", "US");
	BundleFactory::Ptr pBundleFactory(new BundleFactory(lang));
	Poco::OSP::SystemEvents systemEvents;
	BundleContextFactory::Ptr pBundleContextFactory(new BundleContextFactory(reg, systemEvents));
	BundleLoader loader(cc, pBundleFactory, pBundleContextFactory);
	BundleRepository repo(std::string("installed-bundles") + Path::pathSeparator() + findBundleRepository(), loader);

	std::string bundleData(reinterpret_cast<const char*>(&TEST_BUNDLE_ZIP[0]), sizeof(TEST_BUNDLE_ZIP));
	std::istringstream istr(bundleData);
	
	Bundle::Ptr pBundle(repo.installBundle(istr));
	
	assert (!pBundle.isNull());
	assert (pBundle->state() == Bundle::BUNDLE_INSTALLED);
}


void BundleRepositoryTest::testBundleFilterAcceptAll()
{
	CodeCache cc("codeCache");
	ServiceRegistry reg;
	LanguageTag lang("en", "US");
	BundleFactory::Ptr pBundleFactory(new BundleFactory(lang));
	Poco::OSP::SystemEvents systemEvents;
	BundleContextFactory::Ptr pBundleContextFactory(new BundleContextFactory(reg, systemEvents));
	BundleLoader loader(cc, pBundleFactory, pBundleContextFactory);
	BundleRepository repo(findBundleRepository(), loader, new AcceptAllFilter);
	
	repo.loadBundles();
	
	Bundle::Ptr pBundle1(loader.findBundle("com.appinf.osp.bundle1"));
	Bundle::Ptr pBundle2(loader.findBundle("com.appinf.osp.bundle2"));
	Bundle::Ptr pBundle3(loader.findBundle("com.appinf.osp.bundle3"));
	Bundle::Ptr pBundle4(loader.findBundle("com.appinf.osp.bundle4"));
	Bundle::Ptr pBundle5(loader.findBundle("com.appinf.osp.bundle5"));
	Bundle::Ptr pBundle6(loader.findBundle("com.appinf.osp.bundle6"));
	Bundle::Ptr pBundle7(loader.findBundle("com.appinf.osp.bundle7"));
	Bundle::Ptr pBundle8(loader.findBundle("com.appinf.osp.bundle8"));
	Bundle::Ptr pBundle9(loader.findBundle("com.appinf.osp.bundle9"));

	assert (!pBundle1.isNull());
	assert (!pBundle2.isNull());
	assert (!pBundle3.isNull());
	assert (!pBundle4.isNull());
	assert (!pBundle5.isNull());
	assert (!pBundle6.isNull());
	assert (!pBundle7.isNull());
	assert (!pBundle8.isNull());
	assert (!pBundle9.isNull());
}


void BundleRepositoryTest::testBundleFilterRejectAll()
{
	CodeCache cc("codeCache");
	ServiceRegistry reg;
	LanguageTag lang("en", "US");
	BundleFactory::Ptr pBundleFactory(new BundleFactory(lang));
	Poco::OSP::SystemEvents systemEvents;
	BundleContextFactory::Ptr pBundleContextFactory(new BundleContextFactory(reg, systemEvents));
	BundleLoader loader(cc, pBundleFactory, pBundleContextFactory);
	BundleRepository repo(findBundleRepository(), loader, new RejectAllFilter);
	
	repo.loadBundles();
	
	Bundle::Ptr pBundle1(loader.findBundle("com.appinf.osp.bundle1"));
	Bundle::Ptr pBundle2(loader.findBundle("com.appinf.osp.bundle2"));
	Bundle::Ptr pBundle3(loader.findBundle("com.appinf.osp.bundle3"));
	Bundle::Ptr pBundle4(loader.findBundle("com.appinf.osp.bundle4"));
	Bundle::Ptr pBundle5(loader.findBundle("com.appinf.osp.bundle5"));
	Bundle::Ptr pBundle6(loader.findBundle("com.appinf.osp.bundle6"));
	Bundle::Ptr pBundle7(loader.findBundle("com.appinf.osp.bundle7"));
	Bundle::Ptr pBundle8(loader.findBundle("com.appinf.osp.bundle8"));
	Bundle::Ptr pBundle9(loader.findBundle("com.appinf.osp.bundle9"));

	assert (pBundle1.isNull());
	assert (pBundle2.isNull());
	assert (pBundle3.isNull());
	assert (pBundle4.isNull());
	assert (pBundle5.isNull());
	assert (pBundle6.isNull());
	assert (pBundle7.isNull());
	assert (pBundle8.isNull());
	assert (pBundle9.isNull());
}


void BundleRepositoryTest::testBundleFilterAcceptOne()
{
	CodeCache cc("codeCache");
	ServiceRegistry reg;
	LanguageTag lang("en", "US");
	BundleFactory::Ptr pBundleFactory(new BundleFactory(lang));
	Poco::OSP::SystemEvents systemEvents;
	BundleContextFactory::Ptr pBundleContextFactory(new BundleContextFactory(reg, systemEvents));
	BundleLoader loader(cc, pBundleFactory, pBundleContextFactory);
	BundleRepository repo(findBundleRepository(), loader, new AcceptOneFilter);
	
	repo.loadBundles();
	
	Bundle::Ptr pBundle1(loader.findBundle("com.appinf.osp.bundle1"));
	Bundle::Ptr pBundle2(loader.findBundle("com.appinf.osp.bundle2"));
	Bundle::Ptr pBundle3(loader.findBundle("com.appinf.osp.bundle3"));
	Bundle::Ptr pBundle4(loader.findBundle("com.appinf.osp.bundle4"));
	Bundle::Ptr pBundle5(loader.findBundle("com.appinf.osp.bundle5"));
	Bundle::Ptr pBundle6(loader.findBundle("com.appinf.osp.bundle6"));
	Bundle::Ptr pBundle7(loader.findBundle("com.appinf.osp.bundle7"));
	Bundle::Ptr pBundle8(loader.findBundle("com.appinf.osp.bundle8"));
	Bundle::Ptr pBundle9(loader.findBundle("com.appinf.osp.bundle9"));

	assert (pBundle1.isNull());
	assert (pBundle2.isNull());
	assert (pBundle3.isNull());
	assert (pBundle4.isNull());
	assert (!pBundle5.isNull());
	assert (pBundle6.isNull());
	assert (pBundle7.isNull());
	assert (pBundle8.isNull());
	assert (pBundle9.isNull());
}


void BundleRepositoryTest::setUp()
{
	Poco::AutoPtr<Poco::Channel> pChannel(new Poco::ConsoleChannel);
	Logger::root().setChannel(pChannel);
	Logger::root().setLevel(Poco::Message::PRIO_DEBUG);
	
	File dir("installed-bundles");
	try
	{
		dir.remove(true);
	}
	catch (...)
	{
	}
	dir.createDirectories();
}


void BundleRepositoryTest::tearDown()
{
	File dir("installed-bundles");
	try
	{
		dir.remove(true);
	}
	catch (...)
	{
	}
}


std::string BundleRepositoryTest::findBundleRepository()
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
		return p.toString();
	else
		throw Poco::FileNotFoundException("bundles");
}


CppUnit::Test* BundleRepositoryTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("BundleRepositoryTest");

	CppUnit_addTest(pSuite, BundleRepositoryTest, testLoad);
	CppUnit_addTest(pSuite, BundleRepositoryTest, testInstall);
	CppUnit_addTest(pSuite, BundleRepositoryTest, testBundleFilterAcceptAll);
	CppUnit_addTest(pSuite, BundleRepositoryTest, testBundleFilterRejectAll);
	CppUnit_addTest(pSuite, BundleRepositoryTest, testBundleFilterAcceptOne);

	return pSuite;
}
