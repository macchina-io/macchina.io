//
// RemoteGen.cpp
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/StringTokenizer.h"
#include "Poco/Path.h"
#include "Poco/String.h"
#include "Poco/File.h"
#include "Poco/Process.h"
#include "Poco/Environment.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"
#include "Poco/NullStream.h"
#include "Poco/Delegate.h"
#include "Poco/Format.h"
#include "Poco/XML/XMLWriter.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/Util/OptionException.h"
#include "Poco/CppParser/Parser.h"
#include "Poco/CppParser/NameSpace.h"
#include "Poco/CppParser/BuiltIn.h"
#include "Poco/CppParser/Struct.h"
#include "Poco/CppParser/Utility.h"
#include "Poco/CppParser/Utility.h"
#include "Poco/CodeGeneration/Utility.h"
#include "Poco/CodeGeneration/GeneratorEngine.h"
#include "Poco/CodeGeneration/MethodPropertyFilter.h"
#include "InterfaceGenerator.h"
#include "RemoteObjectGenerator.h"
#include "ProxyGenerator.h"
#include "BundleActivatorGenerator.h"
#include "ProxyFactoryGenerator.h"
#include "SkeletonGenerator.h"
#include "ClientHelperGenerator.h"
#include "ServerHelperGenerator.h"
#include "SerializerGenerator.h"
#include "DeserializerGenerator.h"
#include "XSDGenerator.h"
#include "WSDLGenerator.h"
#include "ExtensionsGenerator.h"
#include "EventDispatcherGenerator.h"
#include "EventSubscriberGenerator.h"
#if defined(POCO_REQUIRE_LICENSE)
#include "Poco/Licensing/License.h"
#endif
#include <set>
#include <fstream>
#include <iostream>


using Poco::StringTokenizer;
using Poco::Path;
using Poco::File;
using Poco::Process;
using Poco::ProcessHandle;
using Poco::Environment;
using Poco::NumberFormatter;
using Poco::Exception;
using Poco::format;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionCallback;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::CppParser::NameSpace;
using Poco::CppParser::Function;
using Poco::CppParser::Struct;
using Poco::CppParser::Symbol;
using Poco::CodeGeneration::GeneratorEngine;
using Poco::CodeGeneration::MethodPropertyFilter;


class RemoteGenApp: public Application
{
public:
	RemoteGenApp():
	  _helpRequested(false),
	  _enableOSP(false),
	  _bundlePath("bundle"),
	  _enableTimestamps(true)
	{
		Poco::CppParser::NameSpace* pNS = new Poco::CppParser::NameSpace("Poco", Poco::CppParser::NameSpace::root());
		new Poco::CppParser::BuiltIn("Int8", pNS);
		new Poco::CppParser::BuiltIn("UInt8", pNS);
		new Poco::CppParser::BuiltIn("Int16", pNS);
		new Poco::CppParser::BuiltIn("UInt16", pNS);
		new Poco::CppParser::BuiltIn("Int32", pNS);
		new Poco::CppParser::BuiltIn("UInt32", pNS);
		new Poco::CppParser::BuiltIn("Int64", pNS);
		new Poco::CppParser::BuiltIn("UInt64", pNS);
		new Poco::CppParser::BuiltIn("IntPtr", pNS);
		new Poco::CppParser::BuiltIn("UIntPtr", pNS);
	}

	~RemoteGenApp()
	{
	}

protected:
	void initialize(Application& self)
	{
		Application::initialize(self);
		AbstractGenerator::EError += Poco::Delegate<RemoteGenApp, const std::string>(this, &RemoteGenApp::onError);
	}

	void uninitialize()
	{
		AbstractGenerator::EError -= Poco::Delegate<RemoteGenApp, const std::string>(this, &RemoteGenApp::onError);
		Application::uninitialize();
	}

	void reinitialize(Application& self)
	{
		Application::reinitialize(self);
	}

	void defineOptions(OptionSet& options)
	{
		Application::defineOptions(options);

		options.addOption(
			Option("help", "h", "Display help information on command line arguments.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<RemoteGenApp>(this, &RemoteGenApp::handleHelp)));

		options.addOption(
			Option("define", "D",
				"Define a configuration property. A configuration property "
				"defined with this option can be referenced in the configuration "
				"file, using the following syntax: ${<name>}.")
				.required(false)
				.repeatable(true)
				.argument("<name>=<value>")
				.callback(OptionCallback<RemoteGenApp>(this, &RemoteGenApp::handleDefine)));

		options.addOption(
			Option("config", "c",
				"Load configuration from the given file specified by <file>. "
				"This option is supported for backwards compatibility only.")
				.required(false)
				.repeatable(false)
				.argument("<file>")
				.callback(OptionCallback<RemoteGenApp>(this, &RemoteGenApp::handleConfig)));

		options.addOption(
			Option("mode", "m",
				"Override generation mode specified in configuration file. "
				"Valid values for <mode> are \"client\", \"server\", \"both\" or \"interface\".")
				.required(false)
				.repeatable(false)
				.argument("<mode>")
				.callback(OptionCallback<RemoteGenApp>(this, &RemoteGenApp::handleMode)));

		options.addOption(
			Option("compiler", "C",
				"Specify the compiler to use. Compilers are defined in the configuration file. "
				"If not specified, the first compiler defined in the configuration file will be used.")
				.required(false)
				.repeatable(false)
				.argument("<id>")
				.callback(OptionCallback<RemoteGenApp>(this, &RemoteGenApp::handleCompiler)));

		options.addOption(
			Option("osp", "o", "Create services for Applied Informatics Open Service Platform.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<RemoteGenApp>(this, &RemoteGenApp::handleOSP)));
	}

	void handleConfig(const std::string& name, const std::string& value)
	{
		loadConfiguration(value);
	}

	void handleCompiler(const std::string& name, const std::string& value)
	{
		_compiler = value;
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

	void handleMode(const std::string& name, const std::string& value)
	{
		_mode = Poco::toLower(value);
		if (_mode != BOTH && _mode != SERVER && _mode != CLIENT && _mode != INTERFACE)
		{
			throw Poco::InvalidArgumentException("invalid option value for mode: only use client|server|both|interface");
			_mode.clear();
		}
	}

	void handleHelp(const std::string& name, const std::string& value)
	{
		_helpRequested = true;
		displayHelp();
		stopOptionsProcessing();
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("[<option> ...] <file> ...");
		helpFormatter.setHeader(
			"\n"
			"The Applied Informatics Remoting NG Code Generator.\n"
			"Copyright (c) 2006-2020 by Applied Informatics Software Engineering GmbH.\n"
			"All rights reserved.\n\n"
			"This program parses C++ header files annotated with "
			"Remoting attributes and generates C++ code for "
			"making C++ objects available remotely over a network.\n\n"
			"The following command line options are supported:"
		);
		helpFormatter.setFooter(
			"For more information, please see the Remoting NG "
			"documentation at <http://docs.appinf.com>."
		);
		helpFormatter.setIndent(8);
		helpFormatter.format(std::cout);
	}

	void handleOSP(const std::string& name, const std::string& value)
	{
		_enableOSP = true;
	}

	void generateAll()
	{
		std::string compilerKey = "RemoteGen.compiler[";
		if (_compiler.empty())
		{
			compilerKey += "0";
		}
		else
		{
			compilerKey += "@id=";
			compilerKey += _compiler;
		}
		compilerKey += "]";
		std::string compiler = config().getString(compilerKey + ".exec", "");
		std::string opts = config().getString(compilerKey + ".options", "");
		std::string path = config().getString(compilerKey + ".path", "");
		std::string includes = config().getString("RemoteGen.files.include");
		std::string excludes = config().getString("RemoteGen.files.exclude", "");
		_enableOSP = _enableOSP || config().getBool("RemoteGen.output.osp.enable", false);
		_bundlePath = config().getString("RemoteGen.output.bundle", _bundlePath);
		_bundleActivator = config().getString("RemoteGen.output.osp.bundleActivator", "");
		_enableTimestamps = config().getBool("RemoteGen.output.timestamps", true);

		if (compiler.empty()) throw Poco::NotFoundException("No compiler definition found in configuration file", _compiler);

		if (config().hasProperty("RemoteGen.output.namespace"))
			checkNameSpaceExists(config().getString("RemoteGen.output.namespace"));

		StringTokenizer incTokenizer(includes, ",;\n", StringTokenizer::TOK_IGNORE_EMPTY | StringTokenizer::TOK_TRIM);
		std::vector<std::string> inc;
		for (StringTokenizer::Iterator it = incTokenizer.begin(); it != incTokenizer.end(); ++it)
		{
			inc.push_back(Poco::Path::expand(*it));
		}
		StringTokenizer excTokenizer(excludes, ",;\n", StringTokenizer::TOK_IGNORE_EMPTY | StringTokenizer::TOK_TRIM);
		std::vector<std::string> exc;
		for (StringTokenizer::Iterator it = excTokenizer.begin(); it != excTokenizer.end(); ++it)
		{
			exc.push_back(Poco::Path::expand(*it));
		}

		Poco::CppParser::Utility::parseDir(inc, exc, _gst, compiler, opts, path);

		// now generate the code
		NameSpace::SymbolTable::const_iterator itS = _gst.begin();
		NameSpace::SymbolTable::const_iterator itSEnd = _gst.end();
		for (; itS != itSEnd; ++itS)
		{
			if (itS->second->kind() == Symbol::SYM_NAMESPACE)
			{
				generateSymbolTable(static_cast<const Poco::CppParser::NameSpace*>(itS->second));
			}
			else if (itS->second->kind() == Symbol::SYM_STRUCT)
			{
				// Note that Codegeneration will change the content of _gst, thus copy all structs to a seperate vector
				_structsToProcess.push_back(static_cast<const Poco::CppParser::Struct*>(itS->second));
			}
		}

		// now check that the Poco::RemotingNG namespace is known
		std::string helpMsg(
			"The configuration file element \"RemoteGen.files.include\" must contain the header files RemoteObject.h, Proxy.h and Skeleton.h. "
			"Check the configuration file for the headers and verify their paths.");
		Poco::CppParser::Symbol* pS = Poco::CppParser::NameSpace::root()->lookup("Poco::RemotingNG");
		if (!pS) throw Poco::NotFoundException("namespace Poco::RemotingNG", helpMsg);
		pS = Poco::CppParser::NameSpace::root()->lookup("Poco::RemotingNG::RemoteObject");
		if (!pS) throw Poco::NotFoundException("class Poco::RemotingNG::RemoteObject", helpMsg);
		pS = Poco::CppParser::NameSpace::root()->lookup("Poco::RemotingNG::Proxy");
		if (!pS) throw Poco::NotFoundException("class Poco::RemotingNG::Proxy", helpMsg);
		pS = Poco::CppParser::NameSpace::root()->lookup("Poco::RemotingNG::Skeleton");
		if (!pS) throw Poco::NotFoundException("class Poco::RemotingNG::Skeleton", helpMsg);

		std::vector<const Poco::CppParser::Struct*>::const_iterator itV = _structsToProcess.begin();
		std::vector<const Poco::CppParser::Struct*>::const_iterator itVEnd = _structsToProcess.end();
		for (; itV != itVEnd; ++itV)
		{
			handleStruct(*itV);
		}
		_structsToProcess.clear();

		itV = _schemaGen.begin();
		itVEnd = _schemaGen.end();
		for (; itV != itVEnd; ++itV)
		{
			const Poco::CppParser::Struct* pStruct = *itV;
			const std::string& outFile = pStruct->getFile();
			Poco::Path incPath(outFile);

			while (incPath.depth() > 0 &&
				Poco::toLower(incPath.directory(incPath.depth()-1)).find("include") == std::string::npos &&
				Poco::toLower(incPath.directory(incPath.depth()-1)).find("src") == std::string::npos)
				incPath.popDirectory();
			if (incPath.depth() > 0)
			{
				incPath.popDirectory();
			}
			else
				incPath = outFile;

			incPath.setFileName("");

			std::string schemaPath = config().getString("RemoteGen.output.schema", "");
			if (!schemaPath.empty())
			{
				Poco::File schemaDir(schemaPath);
				schemaDir.createDirectories();
			}
			else schemaPath = Poco::Path::current();

			std::string cfgPath("RemoteGen.schema.");
			cfgPath.append(pStruct->name());
			// targetNS must be set at the class
			Poco::CodeGeneration::CodeGenerator::Properties structProps;
			Poco::CodeGeneration::GeneratorEngine::parseProperties(pStruct, structProps);
			std::string targetNS;
			Poco::CodeGeneration::GeneratorEngine::getStringProperty(structProps, Poco::CodeGeneration::Utility::NAMESPACE, targetNS);
			if (targetNS.empty())
				throw CodeGenerationException("A SOAP/WSDL web service requires an XML namespace. Add a @namespace attribute to class " + pStruct->fullName() + ".");

			generateWSDL(pStruct, schemaPath, targetNS);
		}
		// now generate bundle
		if (_enableOSP && !_bundleServices.empty())
		{
			const std::string& outFile = _bundleServices[0].pStruct->getFile();
			Poco::Path incPath(outFile);
			const std::string extension = incPath.getExtension();
			incPath.setFileName("");

			Poco::Path srcPath(incPath);

			while (srcPath.depth() > 0 && Poco::toLower(srcPath.directory(srcPath.depth()-1)).find(INCLUDE) == std::string::npos)
				srcPath.popDirectory();
			if (srcPath.depth() > 0)
			{
				srcPath.popDirectory(); // pop INCLUDE
				srcPath.pushDirectory(SRC);
			}
			else
				srcPath = incPath;

			std::string incFileDir = config().getString("RemoteGen.output.include", incPath.toString());
			std::string srcFileDir = config().getString("RemoteGen.output.src", srcPath.toString());
			incPath = Poco::Path(incFileDir);
			srcPath = Poco::Path(srcFileDir);
			std::string defaultNameSpace = config().getString("RemoteGen.output.namespace", _bundleServices[0].pStruct->nameSpace()->fullName());
			std::string libraryName = config().getString("RemoteGen.output.library", config().getString("RemoteGen.output.libraryname", ""));
			std::string copyright = config().getString("RemoteGen.output.copyright", "");
			bool usePocoIncludeStyle = config().getBool("RemoteGen.output.pocostyleincludes", true);
			generateBundleActivator(incPath, srcPath, defaultNameSpace, libraryName, usePocoIncludeStyle, copyright);
		}
		_schemaGen.clear();
	}

	void generateSymbolTable(const Poco::CppParser::NameSpace* st)
	{
		// now generate the code
		NameSpace::Iterator it = st->begin();
		NameSpace::Iterator itEnd = st->end();
		for (; it != itEnd; ++it)
		{
			if (it->second->kind() == Symbol::SYM_NAMESPACE)
			{
				generateSymbolTable(static_cast<const Poco::CppParser::NameSpace*>(it->second));
			}
			else if (it->second->kind() == Symbol::SYM_STRUCT)
			{
				// Note that Codegeneration will change the content of _gst, thus copy all structs to a seperate vector
				_structsToProcess.push_back(static_cast<const Poco::CppParser::Struct*>(it->second));
			}
		}
	}

	void checkNameSpaceExists(const std::string& ns)
	{
		Poco::StringTokenizer aStr(ns, "::", Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
		Poco::StringTokenizer::Iterator it = aStr.begin();
		Poco::CppParser::NameSpace* pRoot = Poco::CppParser::NameSpace::root();

		while (it != aStr.end())
		{
			Poco::CppParser::NameSpace::SymbolTable nameSpaces;
			pRoot->nameSpaces(nameSpaces);
			Poco::CppParser::NameSpace::Iterator itNS = nameSpaces.find(*it);
			if (itNS == nameSpaces.end())
			{
				Poco::CppParser::NameSpace* pNS = new Poco::CppParser::NameSpace(*it, pRoot);
				nameSpaces.clear();
				pRoot->nameSpaces(nameSpaces);
				itNS = nameSpaces.find(*it);
				poco_assert (itNS != nameSpaces.end() && itNS->second == pNS);
			}
			pRoot = const_cast<Poco::CppParser::NameSpace*>(static_cast <const Poco::CppParser::NameSpace*> (itNS->second));
			++it;
		}
	}

	void handleStruct(const Poco::CppParser::Struct* pStruct)
	{
		const std::string& outFile = pStruct->getFile();
		Poco::Path incPath(outFile);
		const std::string extension = incPath.getExtension();
		incPath.setFileName("");

		Poco::Path srcPath(incPath);

		while (srcPath.depth() > 0 && Poco::toLower(srcPath.directory(srcPath.depth()-1)).find(INCLUDE) == std::string::npos)
			srcPath.popDirectory();
		if (srcPath.depth() > 0)
		{
			srcPath.popDirectory(); // pop INCLUDE
			srcPath.pushDirectory(SRC);
		}
		else
			srcPath = incPath;

		std::string incFileDir = config().getString("RemoteGen.output.include", incPath.toString());
		std::string srcFileDir = config().getString("RemoteGen.output.src", srcPath.toString());
		incPath = Poco::Path(incFileDir);
		srcPath = Poco::Path(srcFileDir);
		Poco::File aFile(incPath);
		aFile.createDirectories();
		aFile = Poco::File(srcPath);
		aFile.createDirectories();

		std::string defaultNameSpace = config().getString("RemoteGen.output.namespace", pStruct->nameSpace()->fullName());
		std::string libraryName = config().getString("RemoteGen.output.library", config().getString("RemoteGen.output.libraryname", ""));
		std::string copyright = config().getString("RemoteGen.output.copyright", "");
		std::string mode = config().getString("RemoteGen.output.mode", BOTH);

		bool genBundle = !_bundleActivator.empty();

		if (!_mode.empty())
			mode = _mode;
		Poco::trimInPlace(mode);
		Poco::toLowerInPlace(mode);
		bool genClient = true;
		bool genServer = true;
		if (mode == CLIENT || mode == INTERFACE)
			genServer = false;
		if (mode == SERVER || mode == INTERFACE)
			genClient = false;
		if (mode == INTERFACE)
			genBundle = false;
		bool usePocoIncludeStyle = config().getBool("RemoteGen.output.pocostyleincludes", true);
		if (extension == H_EXT)
		{
			if (Poco::CodeGeneration::Utility::hasAnyRemoteProperty(pStruct))
			{
				generateInterface(pStruct, incPath, srcPath, defaultNameSpace, libraryName, usePocoIncludeStyle, copyright, _enableOSP);

				if (genBundle)
				{
					BundleActivatorGenerator::BundleService bs(pStruct, genClient, genServer);
					this->_bundleServices.push_back(bs);
				}

				if (genClient)
				{
					generateProxy(pStruct, incPath, srcPath, defaultNameSpace, libraryName, usePocoIncludeStyle, copyright);
					generateProxyFactory(pStruct, incPath, srcPath, defaultNameSpace, libraryName, usePocoIncludeStyle, copyright);
					generateClientHelper(pStruct, incPath, srcPath, defaultNameSpace, libraryName, usePocoIncludeStyle, copyright);
					bool hasEvents = GenUtility::hasEvents(pStruct);
					if (hasEvents)
					{
						std::string helpMsg(
							"The configuration file element \"RemoteGen.files.include\" must contain the header file EventSubscriber.h if events are being used in a remote interface. "
							"Check the configuration file for the header and verify its path.");
						Poco::CppParser::Symbol* pS = Poco::CppParser::NameSpace::root()->lookup("Poco::RemotingNG::EventSubscriber");
						if (!pS) throw Poco::NotFoundException("Poco::RemotingNG::EventSubscriber", helpMsg);
						generateEventSubscriber(pStruct, incPath, srcPath, defaultNameSpace, libraryName, usePocoIncludeStyle, copyright);
					}
				}

				if (genServer)
				{
					bool hasEvents = generateRemoteObject(pStruct, incPath, srcPath, defaultNameSpace, libraryName, usePocoIncludeStyle, copyright);
					if (hasEvents)
					{
						std::string helpMsg(
							"The configuration file element \"RemoteGen.files.include\" must contain the header file EventDispatcher.h if events are being used in a remote interface. "
							"Check the configuration file for the header and verify its path.");
						Poco::CppParser::Symbol* pS = Poco::CppParser::NameSpace::root()->lookup("Poco::RemotingNG::EventDispatcher");
						if (!pS) throw Poco::NotFoundException("Poco::RemotingNG::EventDispatcher", helpMsg);
						generateEventDispatcher(pStruct, incPath, srcPath, defaultNameSpace, libraryName, usePocoIncludeStyle, copyright);
					}
					generateSkeleton(pStruct, incPath, srcPath, defaultNameSpace, libraryName, usePocoIncludeStyle, copyright);
					generateServerHelper(pStruct, incPath, srcPath, defaultNameSpace, libraryName, usePocoIncludeStyle, copyright);
				}

				std::string cfgPath("RemoteGen.schema.");
				cfgPath.append(pStruct->name());
				if (config().hasProperty(cfgPath))
				{
					std::string endPoints;
					endPoints = config().getString(cfgPath+".serviceLocation");

					Poco::StringTokenizer aTok(endPoints, ",; \n", Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
					Poco::StringTokenizer::Iterator it = aTok.begin();
					Poco::StringTokenizer::Iterator itEnd = aTok.end();
					if (it == itEnd)
						throw CodeGenerationException("At least one service location is required for class " + pStruct->name() + ".");
					//we can only generate schemas after we have seen all complex types, delay it until all data was processed!
					_schemaGen.push_back(pStruct);
				}
			}

			if (genClient || genServer)
			{
				Poco::CodeGeneration::CodeGenerator::Properties props;
				Poco::CodeGeneration::GeneratorEngine::parseProperties(pStruct, props);
				bool doSerialize = false;
				Poco::CodeGeneration::GeneratorEngine::getBoolProperty(props, Poco::CodeGeneration::Utility::SERIALIZE, doSerialize);
				if (doSerialize)
				{
					generateSerializer(pStruct, incPath, usePocoIncludeStyle, copyright);
					generateDeserializer(pStruct, incPath, usePocoIncludeStyle, copyright);
				}
			}
		}
	}

	void generateInterface(const Poco::CppParser::Struct* pStruct, const Poco::Path& incPath, const Poco::Path& srcPath, const std::string& defaultNameSpace, const std::string& libraryName, bool usePocoIncludeStyle, const std::string& copyright, bool enableOSP)
	{
		std::ofstream hOut;
		std::ofstream cppOut;
		openFiles(incPath, srcPath, InterfaceGenerator::generateClassName(pStruct), hOut, cppOut);
		Poco::CodeGeneration::CppGenerator cppGen(defaultNameSpace, libraryName, usePocoIncludeStyle, copyright, hOut, cppOut);
		cppGen.enableTimestamps(_enableTimestamps);
		InterfaceGenerator* pI = new InterfaceGenerator(cppGen, enableOSP);
		Poco::CodeGeneration::MethodPropertyFilter mi(pI, Poco::CodeGeneration::Utility::REMOTE);

		GeneratorEngine e;
		e.generate(pStruct, mi);

		hOut.close();
		cppOut.close();
	}

	void generateBundleActivator(const Poco::Path& incPath, const Poco::Path& srcPath, const std::string& defaultNameSpace, const std::string& libraryName, bool usePocoIncludeStyle, const std::string& copyright)
	{
		Poco::Path implPath(srcPath);
		implPath.makeDirectory();
		implPath.setBaseName(_bundleActivator + "Impl");
		implPath.setExtension(CPP_EXT);
		std::ofstream hOut;
		std::ofstream cppOut;
		std::ofstream implOut;
		std::ostream* pImplOut(0);
		openFiles(incPath, srcPath, _bundleActivator, hOut, cppOut);
		Poco::File impl(implPath);
		if (!impl.exists())
		{
			implOut.open(implPath.toString().c_str());
			pImplOut = &implOut;
			Poco::CodeGeneration::Utility::writeStdHeader(implOut, implPath.getFileName(), libraryName, libraryName, implPath.getBaseName(), copyright);
		}
		if (!_bundleServices.empty() && _bundleServices[0].clientCode)
		{
			if (_bundlePath.empty())
			{
				if (incPath.toString() == srcPath.toString())
					_bundlePath = srcPath.toString();
				else
					_bundlePath = srcPath.parent().toString();
			}

			Poco::Path bundle(_bundlePath);
			bundle.makeDirectory();
			bundle.setFileName("extensions.xml");
			Poco::File fBundle(bundle);
			if (!fBundle.exists())
			{
				Poco::File bP(_bundlePath);
				bP.createDirectories();
				std::ofstream out(bundle.toString().c_str());
				ExtensionsGenerator gen(out);
				gen.generate(_bundleServices);
			}
		}

		Poco::CodeGeneration::CppGenerator cppGen(defaultNameSpace, libraryName, usePocoIncludeStyle, copyright, hOut, cppOut);
		cppGen.enableTimestamps(_enableTimestamps);
		BundleActivatorGenerator* pB = new BundleActivatorGenerator(cppGen, pImplOut, _bundleActivator, _bundleServices);
		Poco::CodeGeneration::MethodPropertyFilter mi(pB, Poco::CodeGeneration::Utility::REMOTE);

		GeneratorEngine e;
		e.generate(_bundleServices[0].pStruct, mi);

		hOut.close();
		cppOut.close();
		if (pImplOut)
		{
			implOut.close();
		}
	}

	bool generateRemoteObject(const Poco::CppParser::Struct* pStruct, const Poco::Path& incPath, const Poco::Path& srcPath, const std::string& defaultNameSpace, const std::string& libraryName, bool usePocoIncludeStyle, const std::string& copyright)
	{
		std::ofstream hOut;
		std::ofstream cppOut;
		openFiles(incPath, srcPath, RemoteObjectGenerator::generateClassName(pStruct), hOut, cppOut);
		Poco::CodeGeneration::CppGenerator cppGen(defaultNameSpace, libraryName, usePocoIncludeStyle, copyright, hOut, cppOut);
		cppGen.enableTimestamps(_enableTimestamps);
		RemoteObjectGenerator* pGen = new RemoteObjectGenerator(cppGen);
		Poco::CodeGeneration::MethodPropertyFilter mi(pGen, Poco::CodeGeneration::Utility::REMOTE);

		GeneratorEngine e;
		e.generate(pStruct, mi);

		hOut.close();
		cppOut.close();
		return pGen->eventsFound();
	}

	void generateEventDispatcher(const Poco::CppParser::Struct* pStruct, const Poco::Path& incPath, const Poco::Path& srcPath, const std::string& defaultNameSpace, const std::string& libraryName, bool usePocoIncludeStyle, const std::string& copyright)
	{
		std::ofstream hOut;
		std::ofstream cppOut;
		openFiles(incPath, srcPath, EventDispatcherGenerator::generateClassName(pStruct), hOut, cppOut);
		Poco::CodeGeneration::CppGenerator cppGen(defaultNameSpace, libraryName, usePocoIncludeStyle, copyright, hOut, cppOut);
		cppGen.enableTimestamps(_enableTimestamps);
		EventDispatcherGenerator* pGen = new EventDispatcherGenerator(cppGen);
		Poco::CodeGeneration::MethodPropertyFilter mi(pGen, Poco::CodeGeneration::Utility::REMOTE);

		GeneratorEngine e;
		e.generate(pStruct, mi);

		hOut.close();
		cppOut.close();
	}

	void generateEventSubscriber(const Poco::CppParser::Struct* pStruct, const Poco::Path& incPath, const Poco::Path& srcPath, const std::string& defaultNameSpace, const std::string& libraryName, bool usePocoIncludeStyle, const std::string& copyright)
	{
		std::ofstream hOut;
		std::ofstream cppOut;
		openFiles(incPath, srcPath, EventSubscriberGenerator::generateClassName(pStruct), hOut, cppOut);
		Poco::CodeGeneration::CppGenerator cppGen(defaultNameSpace, libraryName, usePocoIncludeStyle, copyright, hOut, cppOut);
		cppGen.enableTimestamps(_enableTimestamps);
		EventSubscriberGenerator* pGen = new EventSubscriberGenerator(cppGen);
		Poco::CodeGeneration::MethodPropertyFilter mi(pGen, Poco::CodeGeneration::Utility::REMOTE);

		GeneratorEngine e;
		e.generate(pStruct, mi);

		hOut.close();
		cppOut.close();
	}

	void generateProxy(const Poco::CppParser::Struct* pStruct, const Poco::Path& incPath, const Poco::Path& srcPath, const std::string& defaultNameSpace, const std::string& libraryName, bool usePocoIncludeStyle, const std::string& copyright)
	{
		std::ofstream hOut;
		std::ofstream cppOut;
		openFiles(incPath, srcPath, ProxyGenerator::generateClassName(pStruct), hOut, cppOut);
		Poco::CodeGeneration::CppGenerator cppGen(defaultNameSpace, libraryName, usePocoIncludeStyle, copyright, hOut, cppOut);
		cppGen.enableTimestamps(_enableTimestamps);
		ProxyGenerator* pGen = new ProxyGenerator(cppGen);
		Poco::CodeGeneration::MethodPropertyFilter mi(pGen, Poco::CodeGeneration::Utility::REMOTE);

		GeneratorEngine e;
		e.generate(pStruct, mi);

		hOut.close();
		cppOut.close();
	}

	void generateProxyFactory(const Poco::CppParser::Struct* pStruct, const Poco::Path& incPath, const Poco::Path& srcPath, const std::string& defaultNameSpace, const std::string& libraryName, bool usePocoIncludeStyle, const std::string& copyright)
	{
		std::ofstream hOut;
		std::ofstream cppOut;
		openFiles(incPath, srcPath, ProxyFactoryGenerator::generateClassName(pStruct), hOut, cppOut);
		Poco::CodeGeneration::CppGenerator cppGen(defaultNameSpace, libraryName, usePocoIncludeStyle, copyright, hOut, cppOut);
		cppGen.enableTimestamps(_enableTimestamps);
		ProxyFactoryGenerator* pGen = new ProxyFactoryGenerator(cppGen);
		Poco::CodeGeneration::MethodPropertyFilter mi(pGen, Poco::CodeGeneration::Utility::REMOTE);

		GeneratorEngine e;
		e.generate(pStruct, mi);

		hOut.close();
		cppOut.close();
	}

	void generateSkeleton(const Poco::CppParser::Struct* pStruct, const Poco::Path& incPath, const Poco::Path& srcPath, const std::string& defaultNameSpace, const std::string& libraryName, bool usePocoIncludeStyle, const std::string& copyright)
	{
		std::ofstream hOut;
		std::ofstream cppOut;
		openFiles(incPath, srcPath, SkeletonGenerator::generateClassName(pStruct), hOut, cppOut);
		Poco::CodeGeneration::CppGenerator cppGen(defaultNameSpace, libraryName, usePocoIncludeStyle, copyright, hOut, cppOut);
		cppGen.enableTimestamps(_enableTimestamps);
		SkeletonGenerator* pGen = new SkeletonGenerator(cppGen);
		Poco::CodeGeneration::MethodPropertyFilter mi(pGen, Poco::CodeGeneration::Utility::REMOTE);

		GeneratorEngine e;
		e.generate(pStruct, mi);

		hOut.close();
		cppOut.close();
	}

	void generateClientHelper(const Poco::CppParser::Struct* pStruct, const Poco::Path& incPath, const Poco::Path& srcPath, const std::string& defaultNameSpace, const std::string& libraryName, bool usePocoIncludeStyle, const std::string& copyright)
	{
		std::ofstream hOut;
		std::ofstream cppOut;
		openFiles(incPath, srcPath, ClientHelperGenerator::generateClassName(pStruct), hOut, cppOut);
		Poco::CodeGeneration::CppGenerator cppGen(defaultNameSpace, libraryName, usePocoIncludeStyle, copyright, hOut, cppOut);
		cppGen.enableTimestamps(_enableTimestamps);
		ClientHelperGenerator* pGen = new ClientHelperGenerator(cppGen);
		Poco::CodeGeneration::MethodPropertyFilter mi(pGen, Poco::CodeGeneration::Utility::REMOTE);

		GeneratorEngine e;
		e.generate(pStruct, mi);

		hOut.close();
		cppOut.close();
	}

	void generateServerHelper(const Poco::CppParser::Struct* pStruct, const Poco::Path& incPath, const Poco::Path& srcPath, const std::string& defaultNameSpace, const std::string& libraryName, bool usePocoIncludeStyle, const std::string& copyright)
	{
		std::ofstream hOut;
		std::ofstream cppOut;
		openFiles(incPath, srcPath, ServerHelperGenerator::generateClassName(pStruct), hOut, cppOut);
		Poco::CodeGeneration::CppGenerator cppGen(defaultNameSpace, libraryName, usePocoIncludeStyle, copyright, hOut, cppOut);
		cppGen.enableTimestamps(_enableTimestamps);
		ServerHelperGenerator* pGen = new ServerHelperGenerator(cppGen);
		Poco::CodeGeneration::MethodPropertyFilter mi(pGen, Poco::CodeGeneration::Utility::REMOTE);

		GeneratorEngine e;
		e.generate(pStruct, mi);

		hOut.close();
		cppOut.close();
	}

	void generateSerializer(const Poco::CppParser::Struct* pStruct, const Poco::Path& incPath, bool usePocoIncludeStyle, const std::string& copyright)
	{
		std::ofstream hOut;
		Poco::NullOutputStream cppOut;
		openTemplateFiles(incPath, SerializerGenerator::generateClassName(pStruct), hOut);
		Poco::CodeGeneration::CppGenerator cppGen("Poco::RemotingNG", "RemotingNG", usePocoIncludeStyle, copyright, hOut, cppOut);
		cppGen.enableTimestamps(_enableTimestamps);
		SerializerGenerator gen(cppGen);

		GeneratorEngine e;
		e.generate(pStruct, gen);

		hOut.close();
	}

	void generateDeserializer(const Poco::CppParser::Struct* pStruct, const Poco::Path& incPath, bool usePocoIncludeStyle, const std::string& copyright)
	{
		std::ofstream hOut;
		Poco::NullOutputStream cppOut;
		openTemplateFiles(incPath, DeserializerGenerator::generateClassName(pStruct), hOut);
		Poco::CodeGeneration::CppGenerator cppGen("Poco::RemotingNG", "RemotingNG", usePocoIncludeStyle, copyright, hOut, cppOut);
		cppGen.enableTimestamps(_enableTimestamps);
		DeserializerGenerator gen(cppGen);

		GeneratorEngine e;
		e.generate(pStruct, gen);

		hOut.close();
	}

	void generateSchema(const Poco::CppParser::Struct* pStruct, const Poco::Path& aPath, const std::string& targetNamespace)
	{
		Poco::NullOutputStream hOut;
		Poco::NullOutputStream cppOut;
		Poco::Path xsdPath(aPath);
		xsdPath.setFileName(XSDGenerator::generateFileName(pStruct));

		std::ofstream xsdOut(xsdPath.toString().c_str());
		if (!xsdOut)
			throw Poco::FileException("Failed to create file " + xsdPath.toString());

		Poco::XML::XMLWriter aWriter(xsdOut, Poco::XML::XMLWriter::PRETTY_PRINT);
		Poco::CodeGeneration::CppGenerator cppGen("Poco::RemotingNG", "RemotingNG", true, "", hOut, cppOut);
		cppGen.enableTimestamps(_enableTimestamps);
		XSDGenerator gen(cppGen, targetNamespace, aWriter, false);

		GeneratorEngine e;
		e.generate(pStruct, gen);

		xsdOut.close();
	}

	void generateWSDL(const Poco::CppParser::Struct* pStruct, const Poco::Path& aPath, const std::string& targetNamespace)
	{
		Poco::NullOutputStream hOut;
		Poco::NullOutputStream cppOut;
		Poco::Path wsdlPath(aPath);
		wsdlPath.makeDirectory();
		wsdlPath.setFileName(WSDLGenerator::generateFileName(pStruct));

		std::ofstream wsdlOut(wsdlPath.toString().c_str(), std::ios::binary);
		if (!wsdlOut)
			throw Poco::FileException("Failed to create file " + wsdlPath.toString());

		Poco::XML::XMLWriter aWriter(wsdlOut, Poco::XML::XMLWriter::PRETTY_PRINT);
		Poco::CodeGeneration::CppGenerator cppGen("Poco::RemotingNG", "RemotingNG", true, "", hOut, cppOut);
		cppGen.enableTimestamps(_enableTimestamps);
		WSDLGenerator gen(cppGen, targetNamespace, aWriter);

		GeneratorEngine e;
		e.generate(pStruct, gen);

		wsdlOut.close();
	}

	void openFiles(const Poco::Path& incPath, const Poco::Path& srcPath, const std::string& baseName, std::ofstream& hOut, std::ofstream& cppOut)
	{
		Poco::Path hPath(incPath);
		hPath.makeDirectory();
		hPath.setBaseName(baseName);
		hPath.setExtension(H_EXT);
		hOut.open(hPath.toString().c_str());

		if (hOut)
		{
			Poco::Path cppPath(srcPath);
			cppPath.makeDirectory();
			cppPath.setBaseName(baseName);
			cppPath.setExtension(CPP_EXT);
			cppOut.open(cppPath.toString().c_str());
			if (!cppOut)
			{
				hOut.close();
				Poco::CppParser::Utility::removeFile(hPath.toString());
				throw Poco::FileException("Failed to create file " + cppPath.toString() + ". Please make sure the file is writable.");
			}
		}
		else
			throw Poco::FileException("Failed to create file " + hPath.toString() + ". Please make sure the file is writable.");
	}

	void openTemplateFiles(const Poco::Path& path, const std::string& baseName, std::ofstream& hOut)
	{
		Poco::Path hPath(path);
		hPath.makeDirectory();
		hPath.setBaseName(baseName);
		hPath.setExtension(H_EXT);
		hOut.open(hPath.toString().c_str());

		if (!hOut)
			throw Poco::FileException("Failed to create file " + hPath.toString());
	}

	void onError(const void*, const std::string& errMsg)
	{
		_errMsgs.push_back(errMsg);
	}

	int main(const std::vector<std::string>& args)
	{
		if (!_helpRequested)
		{
			try
			{
				#if defined(POCO_REQUIRE_LICENSE)
				poco_verify_license(RemoteGen);
				#endif

				for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it)
				{
					loadConfiguration(*it);
				}

				if (config().hasProperty("RemoteGen"))
				{
					generateAll();
				}
				else
				{
					std::cerr << "Error: no configuration found.\n" << std::endl;
					displayHelp();
				}
			}
			catch (Exception& exc)
			{
				_errMsgs.push_back(exc.displayText());
			}
			std::vector<std::string>::const_iterator it = _errMsgs.begin();
			std::vector<std::string>::const_iterator itEnd = _errMsgs.end();
			for (; it != itEnd; ++it)
			{
				std::cerr << *it << std::endl;
			}
		}
		return _errMsgs.empty() ? Application::EXIT_OK : Application::EXIT_SOFTWARE;
	}

private:
	bool _helpRequested;
	bool _enableOSP;
	std::string _compiler;
	std::string _bundleActivator;
	std::string _bundlePath;
	Poco::CppParser::NameSpace::SymbolTable _gst;
	std::vector<std::string> _errMsgs;
	std::vector<const Poco::CppParser::Struct*> _schemaGen;
	std::vector<const Poco::CppParser::Struct*> _structsToProcess;
	std::vector<BundleActivatorGenerator::BundleService> _bundleServices;
	std::string  _mode;
	bool _enableTimestamps;
	static const std::string H_EXT;
	static const std::string CPP_EXT;
	static const std::string INCLUDE;
	static const std::string SRC;
	static const std::string BOTH;
	static const std::string CLIENT;
	static const std::string SERVER;
	static const std::string INTERFACE;
};


const std::string RemoteGenApp::H_EXT("h");
const std::string RemoteGenApp::CPP_EXT("cpp");
const std::string RemoteGenApp::INCLUDE("include");
const std::string RemoteGenApp::SRC("src");
const std::string RemoteGenApp::BOTH("both");
const std::string RemoteGenApp::CLIENT("client");
const std::string RemoteGenApp::SERVER("server");
const std::string RemoteGenApp::INTERFACE("interface");


int main(int argc, char** argv)
{
	RemoteGenApp app;
	try
	{
		app.init(argc, argv);
	}
	catch (Poco::Exception& exc)
	{
		app.logger().log(exc);
		return Application::EXIT_CONFIG;
	}
	return app.run();
}
