//
// BundleCreator.cpp
//
// The BundleCreator utility creates a bundle from a bundle specification file.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/XMLConfiguration.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/OSP/OSPSubsystem.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/BundleManifest.h"
#include "Poco/OSP/VersionRange.h"
#include "Poco/OSP/Version.h"
#include "Poco/Zip/Compress.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Environment.h"
#include "Poco/StringTokenizer.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/Glob.h"
#include "Poco/DirectoryIterator.h"
#include "Poco/FileStream.h"
#include "Poco/Thread.h"
#include "Poco/Random.h"
#include "ManifestInfo.h"
#include <iostream>
#include <cctype>
#include <set>


using Poco::Util::Application;
using Poco::Util::XMLConfiguration;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;
using Poco::OSP::OSPSubsystem;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::BundleManifest;
using Poco::OSP::VersionRange;
using Poco::OSP::Version;
using Poco::Zip::Compress;
using Poco::File;
using Poco::Path;
using Poco::DirectoryIterator;
using Poco::FileOutputStream;
using Poco::FileInputStream;


class FileLock
{
public:
	FileLock(const std::string& path):
		_file(path + ".lock")
	{
		acquire();
	}

	~FileLock()
	{
		try
		{
			release();
		}
		catch (...)
		{
		}
	}

protected:
	void acquire()
	{
		Poco::Random rnd;
		rnd.seed();
		int attempts = 0;
		bool haveLock = createFile();
		while (!haveLock)
		{
			if (++attempts > 100) throw Poco::FileException("Cannot acquire lock for bundle directory", _file.path());

			Poco::Thread::sleep(500 + rnd.next(2000));
			haveLock = createFile();
		}
	}

	void release()
	{
		_file.remove();
	}

	bool createFile()
	{
		try
		{
			return _file.createFile();
		}
		catch (Poco::Exception&)
		{
			return false;
		}
	}

private:
	FileLock();
	FileLock(const FileLock&);
	FileLock& operator = (const FileLock&);

	File _file;
};


class BundleCreatorApplication: public Application
{
public:
	BundleCreatorApplication():
		_osName(Poco::Environment::osName()),
		_osArch(Poco::Environment::osArchitecture()),
		_showHelp(false),
		_outputDir(Path::current()),
		_keep(false),
		_noDeflate(false),
		_noFile(false),
		_defaultVersion("1.0.0")
	{
		makeValidFileName(_osName);
		makeValidFileName(_osArch);
	}

protected:
	void initialize(Application& self)
	{
		loadConfiguration(); // load default configuration files, if present
		Application::initialize(self);
	}

	void defineOptions(OptionSet& options)
	{
		Application::defineOptions(options);

		options.addOption(
			Option("help", "h", "Display help information on command line arguments.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<BundleCreatorApplication>(this, &BundleCreatorApplication::handleHelp)));

		options.addOption(
			Option("output-dir", "o", "Specify the directory where the bundle is saved.")
				.required(false)
				.repeatable(false)
				.argument("<file>")
				.callback(OptionCallback<BundleCreatorApplication>(this, &BundleCreatorApplication::handleOutput)));

		options.addOption(
			Option("keep-bundle-dir", "k", "Keep intermediary bundle directory.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<BundleCreatorApplication>(this, &BundleCreatorApplication::handleKeep)));

		options.addOption(
			Option("bundle-dir-only", "d", "Create bundle directory only, no bundle (.bndl) file (implies --keep-bundle-dir).")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<BundleCreatorApplication>(this, &BundleCreatorApplication::handleBundleDir)));

		options.addOption(
			Option("osname", "n", "Specify default target operating system name (e.g., Linux).")
				.required(false)
				.repeatable(false)
				.argument("<osname>")
				.callback(OptionCallback<BundleCreatorApplication>(this, &BundleCreatorApplication::handleOSName)));

		options.addOption(
			Option("osarch", "a", "Specify default target operating system architecture (e.g., armv5tejl).")
				.required(false)
				.repeatable(false)
				.argument("<osarch>")
				.callback(OptionCallback<BundleCreatorApplication>(this, &BundleCreatorApplication::handleOSArch)));

		options.addOption(
			Option("no-deflate", "N", "Do not compress (deflate) files in bundle file. If a comma-separated list of extensions "
				"is specified, only files with these extensions are stored uncompressed.")
				.required(false)
				.repeatable(false)
				.argument("<extensions>", false)
				.callback(OptionCallback<BundleCreatorApplication>(this, &BundleCreatorApplication::handleNoDeflate)));

		options.addOption(
			Option("version", "v", "Specify default bundle version, e.g. \"1.0.0\", to be used "
				"if the bundle specification file does not have one.")
				.required(false)
				.repeatable(false)
				.argument("<version>")
				.callback(OptionCallback<BundleCreatorApplication>(this, &BundleCreatorApplication::handleVersion)));

		options.addOption(
			Option("define", "D",
				"Define a configuration property. A configuration property "
				"defined with this option can be referenced in the bundle specification "
				"file, using the following syntax: ${<name>}.")
				.required(false)
				.repeatable(true)
				.argument("<name>=<value>")
				.callback(OptionCallback<BundleCreatorApplication>(this, &BundleCreatorApplication::handleDefine)));
	}

	void handleHelp(const std::string& name, const std::string& value)
	{
		_showHelp = true;
		stopOptionsProcessing();
	}

	void handleOutput(const std::string& name, const std::string& value)
	{
		_outputDir = value;
	}

	void handleKeep(const std::string& name, const std::string& value)
	{
		_keep = true;
	}

	void handleBundleDir(const std::string& name, const std::string& value)
	{
		_keep = true;
		_noFile = true;
	}

	void handleOSName(const std::string& name, const std::string& value)
	{
		_osName = value;
		makeValidFileName(_osName);
	}

	void handleOSArch(const std::string& name, const std::string& value)
	{
		_osArch = value;
		makeValidFileName(_osArch);
	}

	void handleNoDeflate(const std::string& name, const std::string& value)
	{
		if (value.empty())
		{
			_noDeflate = true;
		}
		else
		{
			Poco::StringTokenizer tok(value, ",;", Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
			_storeExtensions.insert(tok.begin(), tok.end());
		}
	}

	void handleVersion(const std::string& name, const std::string& value)
	{
		_defaultVersion = value;
	}

	void handleDefine(const std::string& name, const std::string& value)
	{
		defineProperty(value);
	}

	void defineProperty(const std::string& def)
	{
		std::string name;
		std::string value;
		std::string::size_type pos = def.find('=');
		if (pos != std::string::npos)
		{
			name.assign(def, 0, pos);
			value.assign(def, pos + 1, def.length() - pos);
		}
		else name = def;
		config().setString(name, value);
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("[<option> ...] <file> ...");
		helpFormatter.setHeader(
			"\n"
			"The Applied Informatics OSP Bundle Creator Utility.\n"
			"Copyright (c) 2007-2020 by Applied Informatics Software Engineering GmbH.\n"
			"All rights reserved.\n\n"
			"This program builds bundle files for use with the "
			"Open Service Platform. What goes into a bundle "
			"is specified in a bundle specification file, passed "
			"as command line argument.\n\n"
			"The following command line options are supported:"
		);
		helpFormatter.setFooter(
			"For more information, please see the Open Service Platform "
			"documentation at <http://docs.appinf.com>."
		);
		helpFormatter.setIndent(8);
		helpFormatter.format(std::cout);
	}

	int main(const std::vector<std::string>& args)
	{
		if (_showHelp || args.empty())
		{
			displayHelp();
		}
		else
		{
			config().setString("osName", _osName);
			config().setString("osArch", _osArch);
			if (!config().hasProperty("bin"))
			{
				if (_osArch == "AMD64")
				{
					config().setString("bin", "bin64");
					config().setString("64", "64");
				}
				else
				{
					config().setString("bin", "bin");
					config().setString("64", "");
				}
			}

			for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it)
			{
				_ptrCfg = new XMLConfiguration(*it);
				handleConfig();
			}
		}
		return Application::EXIT_OK;
	}

private:
	void handleConfig()
	{
		File outputDir(_outputDir);
		outputDir.createDirectories();

		Path outputPath(_outputDir);
		outputPath.makeDirectory();
		ManifestInfo mi(loadManifest());
		std::string bndlName(mi.symbolicName() + "_" + mi.version().toString());
		Path bndlPath(outputPath, bndlName);

		File bndlDir(bndlPath);
		FileLock lock(bndlDir.path());
		if (bndlDir.exists())
		{
			safeRemove(bndlDir);
			bndlDir.remove(true);
		}
		bndlDir.createDirectories();
		try
		{
			handleBin(bndlPath);
			handleMeta(bndlPath, mi);
			handleOther(bndlPath);
			if (!_noFile)
			{
				Path bndlFilePath(bndlPath);
				bndlFilePath.setFileName(bndlFilePath.getFileName() + ".bndl");
				FileOutputStream out(bndlFilePath.toString());
				Compress compr(out, true);
				if (!_storeExtensions.empty())
				{
					compr.setStoreExtensions(_storeExtensions);
				}
				compr.addRecursive(bndlPath, _noDeflate ? Poco::Zip::ZipCommon::CM_STORE : Poco::Zip::ZipCommon::CM_AUTO, Poco::Zip::ZipCommon::CL_MAXIMUM, true);
				compr.close();
				out.close();
				if (!_keep)
				{
					safeRemove(bndlDir);
					bndlDir.remove(true);
				}
			}
		}
		catch (...)
		{
			if (!_keep)
			{
				safeRemove(bndlDir);
				bndlDir.remove(true);
			}
			throw;
		}
	}

	ManifestInfo loadManifest()
	{
		static const std::string PREFIX("manifest.");
		std::string name = getString(PREFIX + "name");
		std::string symbolicName = getString(PREFIX + "symbolicName");
		std::string vendor = getString(PREFIX + "vendor");
		std::string copyright = getString(PREFIX + "copyright", "");
		std::string activatorClass = getString(PREFIX + "activator.class", "");
		std::string activatorLibrary = getString(PREFIX + "activator.library", "");
		bool lazyStart = getBool(PREFIX + "lazyStart", false);
		bool sealed = getBool(PREFIX + "sealed", false);
		bool preventUninstall = getBool(PREFIX + "preventUninstall", false);
		std::string runLevel = getString(PREFIX + "runLevel", BundleManifest::DEFAULT_RUNLEVEL);
		std::string extendsBundle = getString(PREFIX + "extends", "");
		std::string versionStr(getString(PREFIX + "version", ""));
		if (versionStr.empty() || versionStr == "default" || versionStr == "auto")
		{
			versionStr = _defaultVersion;
		}
		Poco::OSP::Version version(versionStr);
		ManifestInfo::Dependencies requiredBundles;
		Poco::UInt32 idx = 0;
		std::string symName;
		std::string versionRange;
		do
		{
			std::string path(PREFIX+"dependency[");
			path.append(Poco::NumberFormatter::format(idx++));
			path.append("].");
			symName = path + "symbolicName";
			versionRange = path + "version";
			symName = getString(symName, "");
			versionRange = getString(versionRange, "");
			Poco::trimInPlace(symName);
			Poco::trimInPlace(versionRange);
			if (!symName.empty())
			{
				ManifestInfo::Dependency dep;
				dep.symbolicName = symName;
				if (!versionRange.empty())
				{
					dep.versions = versionRange;
				}
				requiredBundles.push_back(dep);
			}
		}
		while (!symName.empty());

		ManifestInfo::Dependencies requiredModules;
		idx = 0;
		do
		{
			std::string path(PREFIX+"module-dependency[");
			path.append(Poco::NumberFormatter::format(idx++));
			path.append("].");
			symName = path + "symbolicName";
			versionRange = path + "version";
			symName = getString(symName, "");
			versionRange = getString(versionRange, "");
			Poco::trimInPlace(symName);
			Poco::trimInPlace(versionRange);
			if (!symName.empty())
			{
				ManifestInfo::Dependency dep;
				dep.symbolicName = symName;
				if (!versionRange.empty())
				{
					dep.versions = versionRange;
				}
				requiredModules.push_back(dep);
			}
		}
		while (!symName.empty());

		ManifestInfo::ProvidedModules providedModules;
		idx = 0;
		do
		{
			std::string path(PREFIX+"module[");
			path.append(Poco::NumberFormatter::format(idx++));
			path.append("].");
			symName = path + "symbolicName";
			versionRange = path + "version";
			symName = getString(symName, "");
			versionRange = getString(versionRange, "");
			Poco::trimInPlace(symName);
			Poco::trimInPlace(versionRange);
			if (!symName.empty())
			{
				ManifestInfo::ProvidedModule mod;
				mod.symbolicName = symName;
				if (!versionRange.empty())
				{
					mod.version = versionRange;
				}
				providedModules.push_back(mod);
			}
		}
		while (!symName.empty());

		return ManifestInfo(name, symbolicName, version, vendor, copyright, activatorClass, activatorLibrary, requiredBundles, requiredModules, providedModules, lazyStart, sealed, preventUninstall, runLevel, extendsBundle);
	}

	void saveManifest(const ManifestInfo& info, std::ostream& out)
	{
		//Manifest-Version: 1.0
		//Bundle-Name: OSP Sample Bundle 9
		//Bundle-SymbolicName: com.appinf.osp.bundle9
		//Bundle-Version: 0.9.1
		//Bundle-Vendor: Applied Informatics
		//Bundle-Copyright: (c) 2007, Applied Informatics Software Engineering GmbH
		//Bundle-Activator: MyBundleActivator;library=TestBundle
		//Bundle-RunLevel: 200
		out << BundleManifest::MANIFEST_VERSION << ": " << BundleManifest::VERSION << std::endl;
		out << BundleManifest::BUNDLE_NAME << ": " << info.name() << std::endl;
		out << BundleManifest::BUNDLE_SYMBOLICNAME << ": " << info.symbolicName() << std::endl;
		out << BundleManifest::BUNDLE_VERSION << ": " << info.version().toString() << std::endl;
		out << BundleManifest::BUNDLE_VENDOR << ": " << info.vendor() << std::endl;
		if (!info.copyright().empty())
			out << BundleManifest::BUNDLE_COPYRIGHT << ": " << info.copyright() << std::endl;
		if (!info.activatorClass().empty() && !info.activatorLibrary().empty())
			out << BundleManifest::BUNDLE_ACTIVATOR << ": " << info.activatorClass() << ";library=" << info.activatorLibrary() << std::endl;
		if (!info.runLevel().empty())
			out << BundleManifest::BUNDLE_RUNLEVEL << ": " << info.runLevel() << std::endl;
		if (!info.extendsBundle().empty())
			out << BundleManifest::EXTENDS_BUNDLE << ": " << info.extendsBundle() << std::endl;
		out << BundleManifest::BUNDLE_LAZYSTART << ": " << (info.lazyStart()?"true":"false") << std::endl;
		if (info.sealed())
			out << BundleManifest::BUNDLE_SEALED << ": true" << std::endl;
		if (info.preventUninstall())
			out << BundleManifest::BUNDLE_PREVENTUNINSTALL << ": true" << std::endl;

		const ManifestInfo::Dependencies& deps = info.requiredBundles();
		//Require-Bundle: com.appinf.osp.bundle1;bundle-version=[1.0,2.0), com.appinf.osp.bundle2
		if (!deps.empty())
		{
			out << BundleManifest::REQUIRE_BUNDLE << ": ";
			std::string empty(BundleManifest::REQUIRE_BUNDLE.size()+2, ' ');
			ManifestInfo::Dependencies::const_iterator it = deps.begin();
			ManifestInfo::Dependencies::const_iterator itEnd = deps.end();
			for (; it != itEnd; ++it)
			{
				if (it != deps.begin())
				{
					out << ", \\" << std::endl << empty;
				}
				out << it->symbolicName;
				if (!it->versions.empty())
					out << ";bundle-version=" << it->versions;
			}
			out << std::endl;
		}

		const ManifestInfo::Dependencies& moduleDeps = info.requiredModules();
		//Require-Module: com.appinf.osp.module1;module-version=[1.0,2.0), com.appinf.osp.module2
		if (!moduleDeps.empty())
		{
			out << BundleManifest::REQUIRE_MODULE << ": ";
			std::string empty(BundleManifest::REQUIRE_MODULE.size()+2, ' ');
			ManifestInfo::Dependencies::const_iterator it = moduleDeps.begin();
			ManifestInfo::Dependencies::const_iterator itEnd = moduleDeps.end();
			for (; it != itEnd; ++it)
			{
				if (it != moduleDeps.begin())
				{
					out << ", \\" << std::endl << empty;
				}
				out << it->symbolicName;
				if (!it->versions.empty())
					out << ";module-version=" << it->versions;
			}
			out << std::endl;
		}

		const ManifestInfo::ProvidedModules& modules = info.providedModules();
		//Provide-Module: com.appinf.osp.module1;module-version=1.0.0
		if (!modules.empty())
		{
			out << BundleManifest::PROVIDE_MODULE << ": ";
			std::string empty(BundleManifest::PROVIDE_MODULE.size()+2, ' ');
			ManifestInfo::ProvidedModules::const_iterator it = modules.begin();
			ManifestInfo::ProvidedModules::const_iterator itEnd = modules.end();
			for (; it != itEnd; ++it)
			{
				if (it != modules.begin())
				{
					out << ", \\" << std::endl << empty;
				}
				out << it->symbolicName << ";module-version=" << it->version;
			}
			out << std::endl;
		}
	}

	void handleBin(const Path& root)
	{
		Path binDir(root, "bin");
		binDir.makeDirectory();
		File binFile(binDir);

		// now check for the code entries
		//<code [platform="Windows_NT/ia32"] globExpression />
		Poco::UInt32 idx = 0;
		std::string expr;
		std::string versionRange;

		std::string path("code[");
		path.append(Poco::NumberFormatter::format(idx++));
		path.append("]");
		while (_ptrCfg->hasProperty(path))
		{
			expr = getString(path, "");
			path.append("[@platform]");
			std::string platform = getString(path, "");
			if (platform.empty() || platform.find("/") == std::string::npos)
			{
				platform = _osName + "/" + _osArch;
			}
			Path platformDir(binDir, Path(platform, Path::PATH_UNIX));
			File platformFile(platformDir);
			platformFile.createDirectories();
			// now copy files as indicated in the expr
			std::set<std::string> files;
			Poco::StringTokenizer incTokenizer(expr, ",;\n", Poco::StringTokenizer::TOK_IGNORE_EMPTY | Poco::StringTokenizer::TOK_TRIM);
			std::vector<std::string> inc;
			for (Poco::StringTokenizer::Iterator it = incTokenizer.begin(); it != incTokenizer.end(); ++it)
			{
				Poco::Glob::glob(*it, files, Poco::Glob::GLOB_DOT_SPECIAL);
			}

			std::set<std::string>::const_iterator itF = files.begin();
			std::set<std::string>::const_iterator itFEnd = files.end();

			for (; itF != itFEnd; ++itF)
			{
				File aFile(*itF);
				if (aFile.exists())
				{
					copyFile(aFile, platformDir.toString());
				}
			}
			if (files.empty() && incTokenizer.count() > 0)
			{
				std::cerr << Poco::format("Warning: Non-empty <code> element, but no files found for expression '%s'.", Poco::cat(std::string("; "), incTokenizer.begin(), incTokenizer.end())) << std::endl;
			}

			path = "code[";
			path.append(Poco::NumberFormatter::format(idx++));
			path.append("]");
		}
	}

	void handleMeta(const Path& root, const ManifestInfo& mi)
	{
		Path metaDir(root, "META-INF");
		metaDir.makeDirectory();
		File metaFile(metaDir);
		metaFile.createDirectories();
		Path manifest(metaDir, "manifest.mf");
		FileOutputStream out(manifest.toString());
		saveManifest(mi, out);
		out.close();
		// verify
		FileInputStream in(manifest.toString());
		BundleManifest::Ptr pManifest = new BundleManifest(in);
	}

	void handleOther(const Path& root)
	{
		if (_ptrCfg->hasProperty("files"))
		{
			std::string globs = getString("files");
			std::set<std::string> files;
			Poco::StringTokenizer incTokenizer(globs, ",;\r", Poco::StringTokenizer::TOK_IGNORE_EMPTY | Poco::StringTokenizer::TOK_TRIM);
			std::vector<std::string> inc;
			for (Poco::StringTokenizer::Iterator it = incTokenizer.begin(); it != incTokenizer.end(); ++it)
			{
				Poco::Glob::glob(*it, files, Poco::Glob::GLOB_DOT_SPECIAL);
			}

			for (std::set<std::string>::iterator itFiles = files.begin(); itFiles != files.end(); ++itFiles)
			{
				File aFile(*itFiles);
				copyFile(aFile, root.toString());
			}

			if (files.empty() && incTokenizer.count() > 0)
			{
				std::cerr << Poco::format("Warning: Non-empty <files> element, but no files found for expression '%s'.", Poco::cat(std::string("; "), incTokenizer.begin(), incTokenizer.end())) << std::endl;
			}
		}
	}

	void makeValidFileName(std::string& name)
	{
		for (std::string::iterator it = name.begin(); it != name.end(); ++it)
		{
			if (!(std::isalnum(*it) || *it == '-')) *it = '_';
		}
	}

	void safeRemove(const File& p)
	{
		std::vector<File> entries;
		p.list(entries);
		std::vector<File>::iterator it = entries.begin();
		std::vector<File>::iterator itEnd = entries.end();
		for (; it != itEnd; ++it)
		{
			it->setWriteable(true);
			if (it->isDirectory())
			{
				safeRemove(*it);
			}
			it->remove(true);
		}
	}

	void copyFile(const File& file, const std::string& destPath) const
	{
		if (file.isHidden()) return;
		Path src(file.path());
		Path dest(destPath);
		File destFile(destPath);
		if ((destFile.exists() && destFile.isDirectory()) || dest.isDirectory())
		{
			dest.makeDirectory();
			dest.setFileName(src.getFileName());
		}
		if (file.isDirectory())
			copyDirectory(file, dest.toString());
		else
			file.copyTo(destPath);
	}

	void copyDirectory(const File& file, const std::string& destPath) const
	{
		File target(destPath);
		target.createDirectories();

		Path src(file.path());
		src.makeFile();
		DirectoryIterator it(src);
		DirectoryIterator end;
		for (; it != end; ++it)
		{
			copyFile(*it, destPath);
		}
	}

	std::string getString(const std::string& prop)
	{
		return config().expand(_ptrCfg->getString(prop));
	}

	std::string getString(const std::string& prop, const std::string& deflt)
	{
		return config().expand(_ptrCfg->getString(prop, deflt));
	}

	bool getBool(const std::string& prop, bool deflt)
	{
		return _ptrCfg->getBool(prop, deflt);
	}

private:
	std::string _osName;
	std::string _osArch;
	bool _showHelp;
	std::string _outputDir;
	bool _keep;
	bool _noDeflate;
	bool _noFile;
	Poco::AutoPtr<XMLConfiguration> _ptrCfg;
	std::set<std::string> _storeExtensions;
	std::string _defaultVersion;
};


POCO_APP_MAIN(BundleCreatorApplication)
