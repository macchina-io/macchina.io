//
// BundleDirectoryTest.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "BundleDirectoryTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/OSP/BundleDirectory.h"
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/Exception.h"
#include <fstream>
#include <memory>


using Poco::OSP::BundleDirectory;
using Poco::OSP::BundleStorage;
using Poco::File;
using Poco::Path;


BundleDirectoryTest::BundleDirectoryTest(const std::string& name): CppUnit::TestCase(name)
{
}


BundleDirectoryTest::~BundleDirectoryTest()
{
}


void BundleDirectoryTest::testResource()
{
	std::string s;
	BundleStorage::Ptr pBD(new BundleDirectory("testBundle"));

	std::unique_ptr<std::istream> istr1(pBD->getResource("META-INF/manifest.mf"));
	assert (istr1.get() != 0);
	std::getline(*istr1, s);
	assert (s == "Manifest-Version: 1.0");

	std::unique_ptr<std::istream> istr2(pBD->getResource("bundle.properties"));
	assert (istr2.get() != 0);
	std::getline(*istr2, s);
	assert (s == "foo: bar");

	std::istream* istr3(pBD->getResource("nonexistent"));
	assert (istr3 == 0);

	try
	{
		std::istream* istr3(pBD->getResource("/foo.bar"));
		fail("invalid resource path - must throw");
	}
	catch (Poco::Exception&)
	{
	}

	try
	{
		std::istream* istr3(pBD->getResource("foo/../../bar"));
		fail("invalid resource path - must throw");
	}
	catch (Poco::Exception&)
	{
	}

	try
	{
		std::istream* istr3(pBD->getResource("foo\\..\\bar"));
		fail("invalid resource path - must throw");
	}
	catch (Poco::Exception&)
	{
	}
}


void BundleDirectoryTest::testDirectory()
{
	BundleStorage::Ptr pBD(new BundleDirectory("testBundle"));
	std::vector<std::string> files;
	pBD->list("", files);
	assert (files.size() == 2);

	pBD->list("META-INF", files);
	assert (files.size() == 1);
	assert (files[0] == "manifest.mf");
}


void BundleDirectoryTest::setUp()
{
	File baseDir("testBundle");
	if (baseDir.exists())
	{
		baseDir.remove(true);
	}
	Path basePath("testBundle");
	basePath.makeDirectory();
	Path metaPath(basePath, std::string("META-INF"));
	metaPath.makeDirectory();
	File metaDir(metaPath);
	metaDir.createDirectories();
	std::string manif(metaPath.toString() + "manifest.mf");
	std::ofstream manifStr(manif.c_str(), std::ios::binary);
	manifStr << "Manifest-Version: 1.0\n";
	manifStr.close();
	std::string props(basePath.toString() + "bundle.properties");
	std::ofstream propsStr(props.c_str(), std::ios::binary);
	propsStr << "foo: bar\n" << std::endl;
	propsStr.close();
}


void BundleDirectoryTest::tearDown()
{
	File f("testBundle");
	if (f.exists())
	{
		f.remove(true);
	}
}


CppUnit::Test* BundleDirectoryTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("BundleDirectoryTest");

	CppUnit_addTest(pSuite, BundleDirectoryTest, testResource);
	CppUnit_addTest(pSuite, BundleDirectoryTest, testDirectory);

	return pSuite;
}
