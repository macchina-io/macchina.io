//
// StubGenerator.cpp
//
// $Id: //poco/1.7/RemotingNG/RemoteGen/src/StubGenerator.cpp#4 $
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "StubGenerator.h"
#include "RemoteObjectGenerator.h"
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


StubGenerator::StubGenerator(Poco::CodeGeneration::CppGenerator& cppGen): AbstractGenerator(cppGen), _hasEvents(false)
{
}


StubGenerator::~StubGenerator()
{
}


std::string StubGenerator::generateClassName(const Poco::CppParser::Struct* pStruct)
{
	poco_assert_dbg (pStruct);
	std::string newClassName(pStruct->name());
	newClassName.append("Stub");
	return newClassName;
}


std::string StubGenerator::generateQualifiedClassName(const std::string& ns, const Poco::CppParser::Struct* pStruct)
{
	if (ns.empty())
		return StubGenerator::generateClassName(pStruct);

	return ns + "::" + StubGenerator::generateClassName(pStruct);
}


void StubGenerator::structStart(const Poco::CppParser::Struct* pStruct, const CodeGenerator::Properties& properties)
{
	AbstractGenerator::structStart(pStruct, properties);
	_codeInjectors.clear();
	// add constructor/destructor
	Poco::CppParser::Function* pConstr = new Poco::CppParser::Function(_pStruct->name(), _pStruct);
	//const Identifiable::ObjectId& oid
	Poco::CppParser::Parameter* pParam1 = new Poco::CppParser::Parameter("const Poco::RemotingNG::Identifiable::ObjectId& oid", pConstr);
	Poco::CppParser::Parameter* pParam2 = new Poco::CppParser::Parameter("Poco::SharedPtr<" + pStruct->fullName() + "> pServiceObject", pConstr);
	pConstr->addParameter(pParam1);
	pConstr->addParameter(pParam2);

	pConstr->addDocumentation(	" Creates a " + _pStruct->name() + ".");

	Poco::CppParser::Function* pDestr = new Poco::CppParser::Function(std::string("virtual ~")+_pStruct->name(), _pStruct);
	pDestr->addDocumentation(	" Destroys the " + _pStruct->name() + ".");

	Poco::CppParser::TypeDef* pTypeDef = new Poco::CppParser::TypeDef("typedef Poco::AutoPtr<" + generateClassName(pStruct) + "> Ptr", _pStruct);
	poco_check_ptr (pTypeDef); // just avoid unused variable warning

	// adds the member var
	_cppGen.addIncludeFile("Poco/SharedPtr.h");
	Poco::CppParser::Variable* pVar = new Poco::CppParser::Variable("Poco::SharedPtr<" + pStruct->fullName() + "> _pServiceObject", _pStruct);
	pVar->setAccess(Poco::CppParser::Symbol::ACC_PRIVATE);
	// add a method virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const
	Poco::CppParser::Function* pTypeId = new Poco::CppParser::Function("virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId", _pStruct);
	pTypeId->makeConst();
	pTypeId->makeInline();

	if (GenUtility::hasEvents(pStruct))
	{
		Poco::CppParser::Function* pEvents = new Poco::CppParser::Function("virtual std::string remoting__enableEvents", _pStruct);
		Poco::CppParser::Parameter* pParam = new Poco::CppParser::Parameter("Poco::RemotingNG::Listener::Ptr pListener", 0);
		pEvents->addParameter(pParam);
		pParam = new Poco::CppParser::Parameter("bool enable = true", 0);
		pEvents->addParameter(pParam);

		Poco::CppParser::Function* pHasEvents = new Poco::CppParser::Function("virtual bool remoting__hasEvents", _pStruct);
		pHasEvents->makeConst();

		Poco::CppParser::Function* pRemoteEvents = new Poco::CppParser::Function("virtual void remoting__enableRemoteEvents", _pStruct);
		pParam = new Poco::CppParser::Parameter("const std::string& protocol", 0);
		pRemoteEvents->addParameter(pParam);

		std::string inc = Utility::createInclude(_pStruct, _cppGen.usePocoIncludeStyle());
		Poco::replaceInPlace(inc, "Stub", "EventDispatcher");
		_cppGen.addSrcIncludeFile(inc);
	}

	handleParentFunctions(_pStructIn);
	checkForParentEventMembers(pStruct);
	checkForEventMembers(pStruct);
}


void StubGenerator::registerCallbacks(Poco::CodeGeneration::GeneratorEngine& e)
{
	// for all other methods we want the simple fwd implementation
	e.registerDefaultCallback(&StubGenerator::fwdCodeGen);
	e.registerCallback(_pStruct->name(), &StubGenerator::constructorCodeGen);
	e.registerCallback("~"+_pStruct->name(), &StubGenerator::destructorCodeGen);
	e.registerCallback("remoting__typeId", &AbstractGenerator::typeIdCodeGen);
	if (eventsFound())
	{
		e.registerCallback("remoting__enableEvents", &StubGenerator::enableEventsCodeGen);
		e.registerCallback("remoting__hasEvents", &StubGenerator::hasEventsCodeGen);
		e.registerCallback("remoting__enableRemoteEvents", &StubGenerator::enableRemoteEventsCodeGen);
	}

	std::vector<std::string>::const_iterator itE = _events.begin();
	for (; itE != _events.end(); ++itE)
	{
		e.registerCallback(StubGenerator::generateEventFunctionName(*itE), &StubGenerator::eventCodeGen);
	}
	
	// now register others
	std::map<std::string, Poco::CodeGeneration::GeneratorEngine::MethodGenerator>::const_iterator it = _codeInjectors.begin();
	std::map<std::string, Poco::CodeGeneration::GeneratorEngine::MethodGenerator>::const_iterator itEnd = _codeInjectors.end();

	for (; it != itEnd; ++it)
	{
		e.registerCallback(it->first, it->second);
	}
	_codeInjectors.clear();
}


void StubGenerator::methodStart(const Poco::CppParser::Function* pFuncOld, const CodeGenerator::Properties& properties)
{
	if (_functions.find(pFuncOld->name()) != _functions.end())
		return;
	_functions.insert(pFuncOld->name());
	Poco::CppParser::Function* pFunc = methodClone(pFuncOld, properties);
	pFunc->makeInline(); // impl is just one single line
	Poco::CodeGeneration::CodeGenerator::Properties::const_iterator itSync = properties.find(Poco::CodeGeneration::Utility::SYNCHRONIZED);
	if (itSync != properties.end() && (itSync->second == Utility::VAL_TRUE || itSync->second.empty() || itSync->second == "all" || itSync->second == "remote"))
	{
		_codeInjectors.insert(std::make_pair(pFunc->name(), &StubGenerator::syncFwdCodeGen));
	}
	else
	{
		_codeInjectors.insert(std::make_pair(pFunc->name(), &StubGenerator::fwdCodeGen));
	}
}


std::vector<std::string> StubGenerator::newBaseClasses(const Poco::CppParser::Struct* pStruct)
{
	std::vector<std::string> bases;
	bases.push_back(RemoteObjectGenerator::generateQualifiedClassName(nameSpace(), pStruct));
	return bases;
}


void StubGenerator::fwdCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam)
{
	// we only write one line
	// either _pServiceObject->method (params) or return _pServiceObject->method (params)
	std::string codeLine;
	if (pFunc->getReturnParameter() != Poco::CodeGeneration::Utility::TYPE_VOID)
	{
		codeLine.append(Poco::CodeGeneration::Utility::RETURN+" ");
	}
	codeLine.append("_pServiceObject->");
	codeLine.append(pFunc->name());
	codeLine.append("(");
	Poco::CppParser::Function::Iterator it = pFunc->begin();
	Poco::CppParser::Function::Iterator itEnd = pFunc->end();

	for (; it != itEnd; ++it)
	{
		Poco::CppParser::Parameter* pParam = *it;
		Poco::CppParser::Function::Iterator itBeforeEnd = pFunc->end();
		--itBeforeEnd;
		codeLine.append(pParam->name());
		if (it != itBeforeEnd)
			codeLine.append(", ");
	}
	codeLine.append(");");
	gen.writeMethodImplementation(codeLine);
}


void StubGenerator::syncFwdCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam)
{
	gen.writeMethodImplementation("Poco::FastMutex::ScopedLock lock(remoting__mutex());");
	StubGenerator::fwdCodeGen(pFunc, pStruct, gen, addParam);
}


void StubGenerator::checkForEventMembers(const Poco::CppParser::Struct* pStruct)
{
	Poco::CppParser::NameSpace::SymbolTable tbl;
	pStruct->variables(tbl);
	Poco::CppParser::NameSpace::SymbolTable::const_iterator it = tbl.begin();
	Poco::CppParser::NameSpace::SymbolTable::const_iterator itEnd = tbl.end();
	for (; it != itEnd; ++it)
	{
		Poco::CppParser::Variable* pVar = static_cast<Poco::CppParser::Variable*>(it->second);
		const std::string& varType = pVar->declType();
		if (pVar->getAccess() == Poco::CppParser::Variable::ACC_PUBLIC && !(pVar->flags() & Poco::CppParser::Variable::VAR_STATIC))
		{
			if (varType.find("Poco::BasicEvent") == 0 || varType.find("Poco::FIFOEvent") == 0)
			{
				_hasEvents = true;
				_events.push_back(pVar->name());
				_cppGen.addSrcIncludeFile("Poco/RemotingNG/ORB.h");
				_cppGen.addSrcIncludeFile("Poco/Delegate.h");
				// generate a serializer method for that member too
				// call methodStart(const Poco::CppParser::Function* pFuncOld, const CodeGenerator::Properties& methodProperties)
				// convert the basicevent to a private function
				std::string funcDecl("void ");
				std::string fctName = generateEventFunctionName(pVar->name());
				funcDecl.append(fctName);
				std::vector<std::string> templTypes = GenUtility::getResolvedInnerTemplateTypes(pStruct, varType);
				if (templTypes.size() != 1)
					throw Poco::InvalidArgumentException("Illegal remote event param: " + pVar->fullName());
				std::string paramDecl = templTypes[0];
				if (paramDecl != "void")
				{
					paramDecl.append("& data");
				}
				Poco::CppParser::Function* pFunc = new Poco::CppParser::Function(funcDecl, _pStruct);
				pFunc->setAccess(Poco::CppParser::Symbol::ACC_PROTECTED);
				if (paramDecl != "void")
				{
					Poco::CppParser::Parameter* pParam = new Poco::CppParser::Parameter(paramDecl, 0);
					pFunc->addParameter(pParam);
				}		
			}
		}	
	}
}


void StubGenerator::checkForParentEventMembers(const Poco::CppParser::Struct* pStruct)
{
	checkForParentEventMembersImpl(pStruct);

	Poco::CppParser::Struct::BaseIterator itB = pStruct->baseBegin();
	Poco::CppParser::Struct::BaseIterator itBEnd = pStruct->baseEnd();
	for (; itB != itBEnd; ++itB)
	{
		const Poco::CppParser::Struct* pParent = itB->pClass;
		if (pParent && Utility::hasAnyRemoteProperty(pParent))
		{
			checkForParentEventMembers(pParent);
		}
	}
}


void StubGenerator::checkForParentEventMembersImpl(const Poco::CppParser::Struct* pStruct)
{
	Poco::CppParser::NameSpace::SymbolTable tbl;
	pStruct->variables(tbl);
	Poco::CppParser::NameSpace::SymbolTable::const_iterator it = tbl.begin();
	Poco::CppParser::NameSpace::SymbolTable::const_iterator itEnd = tbl.end();
	for (; it != itEnd; ++it)
	{
		Poco::CppParser::Variable* pVar = static_cast<Poco::CppParser::Variable*>(it->second);
		const std::string& varType = pVar->declType();
		if (pVar->getAccess() == Poco::CppParser::Variable::ACC_PUBLIC && !(pVar->flags() & Poco::CppParser::Variable::VAR_STATIC))
		{
			if (varType.find("Poco::BasicEvent") == 0 || varType.find("Poco::FIFOEvent") == 0)
			{
				_hasEvents = true;	
				_cppGen.addSrcIncludeFile("Poco/RemotingNG/ORB.h");
			}
		}	
	}
}


std::string StubGenerator::generateEventFunctionName(const std::string& eventVarname)
{
	return "event__" + Poco::trim(eventVarname);
}


void StubGenerator::constructorCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam)
{
	poco_check_ptr (addParam);

	AbstractGenerator* pAGen = reinterpret_cast<AbstractGenerator*>(addParam);
	StubGenerator* pProxy = dynamic_cast<StubGenerator*>(pAGen);
	poco_check_ptr (pProxy);
	
	gen.writeMethodImplementation("remoting__init(oid);");

	const Poco::CppParser::Struct* pDataType = pProxy->_pStructIn; // returns the data type for which pStruct was generated
	const std::vector<std::string>& events = pProxy->_events;
	std::vector<std::string>::const_iterator it = events.begin();
	for (; it != events.end(); ++it)
	{
		std::string line("_pServiceObject->");
		line.append(*it);
		line.append(" += ");
		line.append("Poco::delegate(this, &");
		line.append(StubGenerator::generateClassName(pDataType));
		line.append("::");
		line.append(StubGenerator::generateEventFunctionName(*it));
		line.append(");");
		gen.writeMethodImplementation(line);
	}
}


void StubGenerator::destructorCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam)
{
	poco_check_ptr (addParam);

	AbstractGenerator* pAGen = reinterpret_cast<AbstractGenerator*>(addParam);
	StubGenerator* pProxy = dynamic_cast<StubGenerator*>(pAGen);
	poco_check_ptr (pProxy);

	gen.writeMethodImplementation("try");
	gen.writeMethodImplementation("{");
	const Poco::CppParser::Struct* pDataType = pProxy->_pStructIn; // returns the data type for which pStruct was generated
	const std::vector<std::string>& events = pProxy->_events;
	std::vector<std::string>::const_iterator it = events.begin();
	for (; it != events.end(); ++it)
	{
		std::string line("\t_pServiceObject->");
		line.append(*it);
		line.append(" -= ");
		line.append("Poco::delegate(this, &");
		line.append(StubGenerator::generateClassName(pDataType));
		line.append("::");
		line.append(StubGenerator::generateEventFunctionName(*it));
		line.append(");");
		gen.writeMethodImplementation(line);
	}
	gen.writeMethodImplementation("}");
	gen.writeMethodImplementation("catch (...)");
	gen.writeMethodImplementation("{");
	gen.writeMethodImplementation("\tpoco_unexpected();");
	gen.writeMethodImplementation("}");
}


void StubGenerator::eventCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam)
{
	poco_check_ptr (addParam);

	AbstractGenerator* pAGen = reinterpret_cast<AbstractGenerator*>(addParam);
	StubGenerator* pProxy = dynamic_cast<StubGenerator*>(pAGen);
	poco_check_ptr (pProxy);

	const std::vector<std::string>& events = pProxy->_events;

	std::vector<std::string>::const_iterator it = events.begin();
	for (; it != events.end(); ++it)
	{
		std::string name = StubGenerator::generateEventFunctionName(*it);
		if (name == pFunc->name())
		{
			// jep, we found the value
			if (pFunc->countParameters() == 0) // void event
				gen.writeMethodImplementation(*it + "(this);");
			else
				gen.writeMethodImplementation(*it + "(this, data);");
			return;
		}
	}
}


void StubGenerator::hasEventsCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam)
{
	gen.writeMethodImplementation("return true;");
}


void StubGenerator::enableEventsCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam)
{
	gen.writeMethodImplementation("return std::string();");
}


void StubGenerator::enableRemoteEventsCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam)
{
	poco_assert (addParam);
	AbstractGenerator* pAGen = reinterpret_cast<AbstractGenerator*>(addParam);
	StubGenerator* pGen = dynamic_cast<StubGenerator*>(pAGen);
	poco_check_ptr (pGen);
	const Poco::CppParser::Struct* pStructIn = pGen->_pStructIn;

	gen.writeMethodImplementation("Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new " + EventDispatcherGenerator::generateClassName(pStructIn) + "(this, protocol);");
	gen.writeMethodImplementation("Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);");
}
