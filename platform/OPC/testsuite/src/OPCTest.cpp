//
// OPCTest.cpp
//
// $Id: //poco/1.4/OPC/testsuite/src/OPCTest.cpp#1 $
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "OPCTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/OPC/Types.h"
#include "Poco/OPC/Server.h"
#include "Poco/OPC/Client.h"
#include "Poco/Thread.h"
#include "Poco/UUID.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/Exception.h"
#include <iostream>


using namespace Poco;
using namespace Poco::OPC;
using namespace Poco::Dynamic;
using namespace open62541;


OPCTest::OPCTest(const std::string& name): CppUnit::TestCase("OPC")
{

}


OPCTest::~OPCTest()
{

}


void OPCTest::setUp()
{
}


void OPCTest::tearDown()
{
}


const UA_String& getUAString(const UA_String& uaStr)
{
	return uaStr;
}


void OPCTest::testString()
{
	String str = {};
	std::string stdStr = STDString(str);
	assert(stdStr.empty());

	const char* cstr = "abcXYZ123";
	str = open62541::UA_STRING_ALLOC(cstr);
	assert((((UA_String) STDString(str)).length) == strlen(cstr));
	assert(0 == strncmp(reinterpret_cast<const char*>(((UA_String) STDString(str)).data), cstr, str.length));
	stdStr = STDString(str);
	assert(stdStr == cstr);
	UA_free(str.data);
	str.data = 0;
	str.length = 0;

	stdStr = cstr;
	str = open62541::UA_STRING(const_cast<char*>(stdStr.c_str()));
	assert(str.length == stdStr.size());
	assert(0 == strncmp(reinterpret_cast<const char*>(str.data), stdStr.c_str(), stdStr.size()));
	str.data = 0;
	str.length = 0;

	UAString uaStr(stdStr);
	assert(str.data == 0);
	assert(str.length == 0);
	str = uaStr;
	assert(stdStr == cstr);
	assert(str.length && str.length == stdStr.size());
	assert(0 == strncmp(reinterpret_cast<const char*>(str.data), stdStr.c_str(), stdStr.size()));

	UAString uaStr2(uaStr);
	stdStr.clear();
	assert(stdStr.empty());
	stdStr = uaStr2;
	assert(stdStr == cstr);

	stdStr.clear();
	assert(stdStr.empty());
	stdStr = uaStr;
	assert(stdStr == cstr);

	stdStr = "abc123";
	UAString uaStr3(stdStr);
	assert(uaStr3.length() == stdStr.length());
	assert(std::memcmp(uaStr3.data(), stdStr.data(), stdStr.length()) == 0);
}


void OPCTest::testEmptyNodeID()
{
	NodeID nodeID;
	assert(nodeID.isNull());
	assert(!nodeID.isNumeric());
	assert(!nodeID.isString());
	assert(!nodeID.isByteString());
	assert(!nodeID.isGuid());

	try
	{
		Poco::UInt16 tmp = nodeID.getNSIndex();
		fail("calling getNSIndex() on a null nodeID must throw.");
		std::memset(&tmp, 0, sizeof(tmp)); // silence the compiler
	}
	catch(NullPointerException&){}

	try
	{
		NodeID::IDType tmp = nodeID.getIDType();
		fail("calling getIDType() on a null nodeID must throw.");
		std::memset(&tmp, 0, sizeof(tmp)); // silence the compiler
	}
	catch(NullPointerException&){}

	try
	{
		NodeID::Type tmp = nodeID.getType();
		fail("calling getType() on a null nodeID must throw.");
		std::memset(&tmp, 0, sizeof(tmp)); // silence the compiler
	}
	catch(NullPointerException&){}

	try
	{
		UInt32 tmp = nodeID.getNumeric();
		fail("calling getNumeric() on a null nodeID must throw.");
		std::memset(&tmp, 0, sizeof(tmp)); // silence the compiler
	}
	catch(NullPointerException&){}

	try
	{
		std::string str = nodeID.getString();
		fail("calling getString() on a null nodeID must throw.");
		str.clear(); // silence the compiler
	}
	catch(NullPointerException&){}

	try
	{
		NodeID::ByteStringType bstr = nodeID.getByteString();
		fail("calling getByteString() on a null nodeID must throw.");
		bstr.clear(); // silence the compiler
	}
	catch(NullPointerException&){}

	try
	{
		UUID uuid = nodeID.getGuid();
		fail("calling getGuid() on a null nodeID must throw.");
		assert(uuid.isNull()); // silence the compiler
	}
	catch(NullPointerException&){}
}
#if 0
struct UA_DataType {
#ifdef UA_ENABLE_TYPENAMES
    const char *typeName;
#endif
    UA_NodeId  typeId;           /* The nodeid of the type */
UA_UInt16  memSize;          /* Size of the struct in memory */
UA_UInt16  typeIndex;        /* Index of the type in the datatypetable */
UA_Byte    membersSize;      /* How many members does the type have? */
UA_Boolean builtin      : 1; /* The type is "builtin" and has dedicated de-
                                    and encoding functions */
UA_Boolean fixedSize    : 1; /* The type (and its members) contains no
                                    pointers */
UA_Boolean overlayable  : 1; /* The type has the identical memory layout in
                                    memory and on the binary stream. */
UA_UInt16  binaryEncodingId; /* NodeId of datatype when encoded as binary */
//UA_UInt16  xmlEncodingId;  /* NodeId of datatype when encoded as XML */
UA_DataTypeMember *members;
};
#endif
void printDataType(const open62541::UA_NodeId& nIDType)
{
	const open62541::UA_DataType* pDT = open62541::UA_findDataType(&nIDType);
	if(pDT)
	{
		std::cout << "name: " << pDT->typeName << std::endl;
		//std::cout << "ID: " << pDT->typeId << std::endl;
		std::cout << "memSize: " << pDT->memSize << std::endl;
		std::cout << "typeIndex: " << pDT->typeIndex << std::endl;
		std::cout << "membersSize: " << (int)pDT->membersSize << std::endl;
		std::cout << "builtin: " << pDT->builtin << std::endl;
		std::cout << "fixedSize: " << pDT->fixedSize << std::endl;
		std::cout << "overlayable: " << pDT->overlayable << std::endl;
		std::cout << "binaryEncodingId: " << pDT->binaryEncodingId << std::endl;
		std::cout << "members: " << pDT->members << std::endl;
	}
	else
	{
		std::cout << "Type NOT found" << std::endl;
	}
}

void OPCTest::testNumericNodeID()
{
	NodeID nodeID(1, 2);
	//printDataType(nodeID.getType());
	assert(nodeID.isNumeric());
	assert(!nodeID.isString());
	assert(!nodeID.isByteString());
	assert(!nodeID.isGuid());
	assert(!nodeID.isNull());
	assert(1 == nodeID.getNSIndex());
	assert(0 == nodeID.getIDType());
	NodeID::Type t = nodeID.getType();
	assert(1 == t.namespaceIndex);
	assert(open62541::UA_NODEIDTYPE_NUMERIC == t.identifierType);
	assert(2 == t.identifier.numeric);

	assert(2 == nodeID.getNumeric());

	try
	{
		std::string str = nodeID.getString();
		fail("calling getString() on a numeric nodeID must throw.");
		str.clear(); // silence the compiler
	}
	catch(InvalidAccessException&){}

	try
	{
		NodeID::ByteStringType bstr = nodeID.getByteString();
		fail("calling getByteString() on a numeric nodeID must throw.");
		bstr.clear(); // silence the compiler
	}
	catch(InvalidAccessException&){}

	try
	{
		UUID uuid = nodeID.getGuid();
		fail("calling getGuid() on a numeric nodeID must throw.");
		assert(uuid.isNull()); // silence the compiler
	}
	catch(InvalidAccessException&){}
}


void OPCTest::testStringNodeID()
{
	const char* cstr = "abc.123.xyz";
	NodeID nodeID(1, cstr);
	//open62541::UA_NodeId valueNodeId = open62541::UA_NODEID_STRING_ALLOC(1, "xyzthe.answer");
	//open62541::UA_NodeId valueNodeId = open62541::UA_NODEID_NUMERIC(1, 3);
	//printDataType(valueNodeId);
	open62541::UA_DataType dt;
	open62541::UA_new(&dt);
	assert(!nodeID.isNumeric());
	assert(nodeID.isString());
	assert(!nodeID.isByteString());
	assert(!nodeID.isGuid());
	assert(!nodeID.isNull());
	assert(1 == nodeID.getNSIndex());
	assert(open62541::UA_NODEIDTYPE_STRING == nodeID.getIDType());
	NodeID::Type t = nodeID.getType();
	assert(1 == t.namespaceIndex);
	assert(open62541::UA_NODEIDTYPE_STRING == t.identifierType);
	assert(t.identifier.string.length == strlen(cstr));
	assert(0 == strncmp(cstr, (const char*) t.identifier.string.data, strlen(cstr)));

	assert(nodeID.getString() == cstr);

	try
	{
		UInt32 tmp = nodeID.getNumeric();
		fail("calling getNumeric() on a string nodeID must throw.");
		std::memset(&tmp, 0, sizeof(tmp)); // silence the compiler
	}
	catch(InvalidAccessException&){}

	try
	{
		NodeID::ByteStringType bstr = nodeID.getByteString();
		fail("calling getByteString() on a string nodeID must throw.");
		bstr.clear(); // silence the compiler
	}
	catch(InvalidAccessException&){}

	try
	{
		UUID uuid = nodeID.getGuid();
		fail("calling getGuid() on a string nodeID must throw.");
		assert(uuid.isNull()); // silence the compiler
	}
	catch(InvalidAccessException&){}
}


void OPCTest::testByteStringNodeID()
{
	const char* cstr = "abc.123.xyz";
	NodeID::ByteStringType bstr(strlen(cstr));
	std::memcpy(&bstr[0], (const unsigned char*) cstr, strlen(cstr));
	NodeID nodeID(1, bstr);
	assert(!nodeID.isNumeric());
	assert(!nodeID.isString());
	assert(nodeID.isByteString());
	assert(!nodeID.isGuid());
	assert(!nodeID.isNull());
	assert(1 == nodeID.getNSIndex());
	assert(open62541::UA_NODEIDTYPE_BYTESTRING == nodeID.getIDType());
	NodeID::Type t = nodeID.getType();
	assert(1 == t.namespaceIndex);
	assert(open62541::UA_NODEIDTYPE_BYTESTRING == t.identifierType);
	assert(t.identifier.byteString.length == bstr.size());
	assert(0 == memcmp(&bstr[0], t.identifier.byteString.data, bstr.size()));

	assert(0 == memcmp(&bstr[0], &nodeID.getByteString()[0], bstr.size()));

	try
	{
		UInt32 tmp = nodeID.getNumeric();
		fail("calling getNumeric() on a string nodeID must throw.");
		std::memset(&tmp, 0, sizeof(tmp)); // silence the compiler
	}
	catch(InvalidAccessException&){}

	try
	{
		std::string str = nodeID.getString();
		fail("calling getString() on a byteString nodeID must throw.");
		str.clear(); // silence the compiler
	}
	catch(InvalidAccessException&){}

	try
	{
		UUID uuid = nodeID.getGuid();
		fail("calling getGuid() on a string nodeID must throw.");
		assert(uuid.isNull()); // silence the compiler
	}
	catch(InvalidAccessException&){}
}


void OPCTest::testGuidNodeID()
{
	UUID uuid("6ba7b810-9dad-11d1-80b4-00c04fd430c8");
	std::string uuidStr = uuid.toString();

	NodeID nodeID(1, uuid);
	assert(!nodeID.isNumeric());
	assert(!nodeID.isString());
	assert(!nodeID.isByteString());
	assert(nodeID.isGuid());
	assert(!nodeID.isNull());
	assert(1 == nodeID.getNSIndex());
	assert(open62541::UA_NODEIDTYPE_GUID == nodeID.getIDType());
	NodeID::Type t = nodeID.getType();
	assert(1 == t.namespaceIndex);
	assert(open62541::UA_NODEIDTYPE_GUID == t.identifierType);

	assert(nodeID.getGuid() == uuid);

	try
	{
		UInt32 tmp = nodeID.getNumeric();
		fail("calling getNumeric() on a Guid nodeID must throw.");
		std::memset(&tmp, 0, sizeof(tmp)); // silence the compiler
	}
	catch(InvalidAccessException&){}

	try
	{
		std::string str = nodeID.getString();
		fail("calling getString() on a Guid nodeID must throw.");
		str.clear(); // silence the compiler
	}
	catch(InvalidAccessException&){}

	try
	{
		NodeID::ByteStringType bstr = nodeID.getByteString();
		fail("calling getByteString() on a Guid nodeID must throw.");
		bstr.clear(); // silence the compiler
	}
	catch(InvalidAccessException&){}
}


void OPCTest::testDataTypeMember()
{
	DataTypeMember dtm;
	assert(0 == dtm.getIndex());
	assert(dtm.getName().empty());
	assert(0 == dtm.getPadding());
	assert(dtm.getNSZero());
	assert(!dtm.getIsArray());

	dtm.setIndex(1);
	dtm.setName("abc");
	dtm.setPadding(4);
	dtm.setNSZero(false);
	dtm.setIsArray(true);
	assert(1 == dtm.getIndex());
	assert(dtm.getName() == "abc");
	assert(4 == dtm.getPadding());
	assert(!dtm.getNSZero());
	assert(dtm.getIsArray());

	DataTypeMember::Type t;
	t.memberName = "xyz";
	t.memberTypeIndex = 2;
	t.padding = 8;
	t.namespaceZero = true;
	t.isArray = true;
	dtm.set(t);
	assert(2 == dtm.getIndex());
	assert(dtm.getName() == "xyz");
	assert(8 == dtm.getPadding());
	assert(dtm.getNSZero());
	assert(dtm.getIsArray());

	std::memset(&t, 0, sizeof(t));
	assert(0 == t.memberName);
	assert(t.memberTypeIndex == 0);
	assert(t.padding == 0);
	assert(t.namespaceZero == false);
	assert(t.isArray == false);
	t = dtm.get();
	assert(0 == strcmp(t.memberName, "xyz"));
	assert(t.memberTypeIndex == 2);
	assert(t.padding == 8);
	assert(t.namespaceZero == true);
	assert(t.isArray == true);

	std::memset(&t, 0, sizeof(t));
	assert(0 == t.memberName);
	assert(t.memberTypeIndex == 0);
	assert(t.padding == 0);
	assert(t.namespaceZero == false);
	assert(t.isArray == false);
	dtm.set(t);
	assert(0 == dtm.getIndex());
	assert(dtm.getName().empty());
	assert(0 == dtm.getPadding());
	assert(!dtm.getNSZero());
	assert(!dtm.getIsArray());
}


void OPCTest::testDateTime()
{
	OPC::DateTime dt;
	assert(0 == dt.nanosecond());
	Poco::DateTime pdt;
	dt = pdt;
	assert(dt.year() == pdt.year());
	assert(dt.month() == pdt.month());
	assert(dt.day() == pdt.day());
	assert(dt.minute() == pdt.minute());
	assert(dt.second() == pdt.second());
	assert(dt.millisecond() == pdt.millisecond());
	assert(dt.microsecond() == pdt.microsecond());
	assert(dt.nanosecond() == 0);

	UA_DateTimeStruct uaDT = UA_DateTime_toStruct(UA_DateTime_now());
	OPC::DateTime oDT(uaDT);
	assert(oDT.year() == uaDT.year);
	assert(oDT.month() == uaDT.month);
	assert(oDT.day() == uaDT.day);
	assert(oDT.minute() == uaDT.min);
	assert(oDT.second() == uaDT.sec);
	assert(oDT.millisecond() == uaDT.milliSec);
	assert(oDT.microsecond() == uaDT.microSec);
	assert(oDT.nanosecond() == uaDT.nanoSec);

	assert(Poco::OPC::DateTime::fromString(oDT.toString()) == oDT);

	OPC::DateTime sDT(oDT.toString());
	assert(sDT == oDT);

	std::string str = "05/26/2017 23:06:54.812.795.123";
	sDT = str;
	assert(sDT.toString() == str);
	assert(sDT.nanosecond() == 123);

	Var vDT = oDT;
	assert(vDT.convert<OPC::DateTime>() == oDT);
	assert(vDT.toString() == oDT.toString());
}


void OPCTest::testClient()
{
	try
	{
		Server server;

		int nsIndex = 1;
		Var id = "the.int.answer";
		std::string name = "the int answer";
		server.addVariableNode(nsIndex, id, 42, UA_TYPES_INT32, name, name, name);
		nsIndex = server.addNamespace("ns2");
		id = "the.double.answer";
		name = "the double answer";
		server.addVariableNode(nsIndex, id, 4.2, UA_TYPES_DOUBLE, name, name, name);

		id = 3;
		name = "the double answer by ID in ns2";
		server.addVariableNode(nsIndex, id, 2.4, UA_TYPES_DOUBLE, name, name, name);

		id = 4;
		name = "the string answer by ID in ns2";
		server.addVariableNode(nsIndex, id, std::string("abc123"), UA_TYPES_STRING, name, name, name);

		id = 5;
		name = "the DateTime answer by ID in ns2";
		Poco::Int64 ts = OPC::DateTime::now();
		server.addVariableNode(nsIndex, id, ts, UA_TYPES_DATETIME, name, name, name);

		Thread thread;
		thread.start(server);

		Thread::sleep(100);

		Client client("localhost");
		while(!client.isConnected()) Thread::sleep(10);

		nsIndex = 1;
		name = "the.int.answer";
		assert(42 == client.readInt32ByName(nsIndex, name));
		client.write(nsIndex, name, 24);
		assert(24 == client.readInt32ByName(nsIndex, name));

		nsIndex = 2;
		name = "the.double.answer";
		double dbl = client.readDoubleByName(nsIndex, name);
		assert(4.19 < dbl && dbl < 4.21);
		client.write(nsIndex, name, 2.4);
		dbl = client.readDoubleByName(nsIndex, name);
		assert(2.39 < dbl && dbl < 2.41);

		int nID = 3;
		dbl = client.readDoubleByID(nsIndex, nID);
		assert(2.3 < dbl && dbl < 2.5);
		client.write(nsIndex, nID, 4.2);
		dbl = client.readDoubleByID(nsIndex, nID);
		assert(4.19 < dbl && dbl < 4.21);

		nID = 4;
		assert(client.readStringByID(nsIndex, nID) == "abc123");
		client.write(nsIndex, nID, "321cba");
		assert(client.readStringByID(nsIndex, nID) == "321cba");

		nID = 5;
		assert(client.readTimestampByID(nsIndex, nID) == ts);
		try
		{
			client.write(nsIndex, nID, 1.2, true);
			fail("invalid DateTime type must fail");
		}
		catch(Poco::InvalidArgumentException&) { }

		ts = OPC::DateTime::now();
		client.write(nsIndex, nID, ts, true);
		assert(client.readTimestampByID(nsIndex, nID) == ts);

		client.writeCurrentDateTimeByID(nsIndex, nID);
		assert(client.readTimestampByID(nsIndex, nID) > ts);

		client.disconnect();
		while(client.isConnected()) Thread::sleep(10);

		server.stop();
		thread.join();
	}
	catch(Poco::Exception& ex)
	{
		fail(ex.displayText());
	}
}


CppUnit::Test* OPCTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("OPCTest");

	CppUnit_addTest(pSuite, OPCTest, testString);
	CppUnit_addTest(pSuite, OPCTest, testEmptyNodeID);
	CppUnit_addTest(pSuite, OPCTest, testNumericNodeID);
	CppUnit_addTest(pSuite, OPCTest, testStringNodeID);
	CppUnit_addTest(pSuite, OPCTest, testByteStringNodeID);
	CppUnit_addTest(pSuite, OPCTest, testGuidNodeID);
	CppUnit_addTest(pSuite, OPCTest, testDataTypeMember);
	CppUnit_addTest(pSuite, OPCTest, testDateTime);
	CppUnit_addTest(pSuite, OPCTest, testClient);

	return pSuite;
}
