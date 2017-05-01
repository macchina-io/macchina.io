//
// RemoteObjectGenerator.h
//
// $Id: //poco/1.7/RemotingNG/RemoteGen/src/RemoteObjectGenerator.h#2 $
//
// Definition of the RemoteObjectGenerator class.
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef RemoteGen_RemoteObjectGenerator_INCLUDED
#define RemoteGen_RemoteObjectGenerator_INCLUDED


#include "AbstractGenerator.h"
#include "Poco/CodeGeneration/GeneratorEngine.h"
#include <map>


class RemoteObjectGenerator: public AbstractGenerator
	/// RemoteObjectGenerator generates a wrapper extending RemoteObject for a given class definition. C++ specific. 
{
public:
	RemoteObjectGenerator(Poco::CodeGeneration::CppGenerator& cppGen);
		/// Creates the RemoteObjectGenerator.

	~RemoteObjectGenerator();
		/// Destroys the RemoteObjectGenerator.

	static std::string generateClassName(const Poco::CppParser::Struct* pStruct);
		/// Generates for a given class, its interface class name.

	static std::string generateQualifiedClassName(const std::string& ns, const Poco::CppParser::Struct* pStruct);
		/// Generates for a given class, its interface class name.

	void structStart(const Poco::CppParser::Struct* pStruct, const CodeGenerator::Properties& properties);
		/// Must not write the namespace

	void methodStart(const Poco::CppParser::Function* pFunc, const CodeGenerator::Properties& properties);
		/// Writes the method header. Properties contains the properties found in the functions docuementation and in the class documentation.

	void registerCallbacks(Poco::CodeGeneration::GeneratorEngine& e);

	std::string newClassName(const Poco::CppParser::Struct* pStruct);
		/// generates the new class name based on the old one

	std::vector<std::string> newBaseClasses(const Poco::CppParser::Struct* pStruct);

private:	
	static void constructorCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam);
		/// Code generator for constructor

	static void destructorCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam);
		/// Code generator for destructor
};


//
// inlines
//
inline std::string RemoteObjectGenerator::newClassName(const Poco::CppParser::Struct* pStruct)
{
	return RemoteObjectGenerator::generateClassName(pStruct);
}


#endif // RemoteGen_RemoteObjectGenerator_INCLUDED
