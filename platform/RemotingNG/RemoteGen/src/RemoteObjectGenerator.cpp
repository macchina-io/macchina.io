//
// RemoteObjectGenerator.cpp
//
// $Id: //poco/1.7/RemotingNG/RemoteGen/src/RemoteObjectGenerator.cpp#4 $
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "RemoteObjectGenerator.h"
#include "InterfaceGenerator.h"
#include "EventDispatcherGenerator.h"
#include "GenUtility.h"
#include "Poco/CodeGeneration/Utility.h"
#include "Poco/CodeGeneration/CppGenerator.h"
#include "Poco/CppParser/Function.h"
#include "Poco/CppParser/Utility.h"
#include "Poco/Exception.h"
#include "Poco/Path.h"
#include "Poco/String.h"
#include "Poco/Util/LayeredConfiguration.h"
#include "Poco/Util/Application.h"


using Poco::CodeGeneration::Utility;


RemoteObjectGenerator::RemoteObjectGenerator(Poco::CodeGeneration::CppGenerator& cppGen): AbstractGenerator(cppGen)
{
}


RemoteObjectGenerator::~RemoteObjectGenerator()
{
}


std::string RemoteObjectGenerator::generateClassName(const Poco::CppParser::Struct* pStruct)
{
	poco_assert_dbg (pStruct);
	std::string newClassName(pStruct->name());
	newClassName.append("RemoteObject");
	return newClassName;
}


std::string RemoteObjectGenerator::generateQualifiedClassName(const std::string& ns, const Poco::CppParser::Struct* pStruct)
{
	if (ns.empty())
		return RemoteObjectGenerator::generateClassName(pStruct);

	return ns + "::" + RemoteObjectGenerator::generateClassName(pStruct);
}


void RemoteObjectGenerator::structStart(const Poco::CppParser::Struct* pStruct, const CodeGenerator::Properties& properties)
{
	AbstractGenerator::structStart(pStruct, properties);
	// add constructor/destructor
	Poco::CppParser::Function* pConstr = new Poco::CppParser::Function(_pStruct->name(), _pStruct);
	//const Identifiable::ObjectId& oid

	pConstr->addDocumentation(	" Creates a " + _pStruct->name() + ".");

	Poco::CppParser::Function* pDestr = new Poco::CppParser::Function(std::string("virtual ~")+_pStruct->name(), _pStruct);
	pDestr->addDocumentation(	" Destroys the " + _pStruct->name() + ".");

	Poco::CppParser::TypeDef* pTypeDef = new Poco::CppParser::TypeDef("typedef Poco::AutoPtr<" + generateClassName(pStruct) + "> Ptr", _pStruct);
	poco_check_ptr (pTypeDef); // just avoid unused variable warning

	// adds the member var
	_cppGen.addIncludeFile("Poco/SharedPtr.h");
	_cppGen.addIncludeFile("Poco/RemotingNG/RemoteObject.h");
	
	// add a method virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const
	Poco::CppParser::Function* pTypeId = new Poco::CppParser::Function("virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId", _pStruct);
	pTypeId->makeConst();
	pTypeId->makeInline();
}


void RemoteObjectGenerator::registerCallbacks(Poco::CodeGeneration::GeneratorEngine& e)
{
	// for all other methods we want the simple fwd implementation
	e.registerCallback(_pStruct->name(), &RemoteObjectGenerator::constructorCodeGen);
	e.registerCallback("~"+_pStruct->name(), &RemoteObjectGenerator::destructorCodeGen);
	e.registerCallback("remoting__typeId", &AbstractGenerator::typeIdCodeGen);
}


void RemoteObjectGenerator::methodStart(const Poco::CppParser::Function* pFuncOld, const CodeGenerator::Properties& properties)
{
}


std::vector<std::string> RemoteObjectGenerator::newBaseClasses(const Poco::CppParser::Struct* pStruct)
{
	std::vector<std::string> bases;
	bases.push_back("virtual Poco::RemotingNG::RemoteObject");
	bases.push_back(InterfaceGenerator::generateQualifiedClassName(nameSpace(), pStruct));
	return bases;
}


void RemoteObjectGenerator::constructorCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam)
{
	poco_check_ptr (addParam);
}


void RemoteObjectGenerator::destructorCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam)
{
	poco_check_ptr (addParam);
}

