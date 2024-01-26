//
// PDUReaderTest.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "PDUReaderTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "IoT/Modbus/PDUReader.h"
#include "Poco/BinaryReader.h"
#include "Poco/MemoryStream.h"


using namespace IoT::Modbus;


PDUReaderTest::PDUReaderTest(const std::string& name): 
	CppUnit::TestCase(name)
{
}


PDUReaderTest::~PDUReaderTest()
{
}


void PDUReaderTest::testGenericMessage()
{
	char buffer[] = {
		0x01,
		0x02,
		0x10,
		0x11
	};
	
	Poco::MemoryInputStream istr(buffer, sizeof(buffer));
	Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);
	
	PDUReader pduReader(binaryReader);

	GenericMessage message;
	pduReader.read(message);
	
	assert (message.slaveOrUnitAddress == 0x01);
	assert (message.functionCode == 0x02);
	assert (message.data.size() == 2);	
	assert (message.data[0] == 0x10);
	assert (message.data[1] == 0x11);	
}


void PDUReaderTest::testModbusExceptionMessage()
{
	char buffer[] = {
		0x01,
		0x02,
		0x10,
		0x11
	};

	Poco::MemoryInputStream istr(buffer, sizeof(buffer));
	Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);

	PDUReader pduReader(binaryReader);

	ModbusExceptionMessage message;
	pduReader.read(message);

	assert (message.slaveOrUnitAddress == 0x01);
	assert (message.functionCode == 0x02);
	assert (message.exceptionCode == 0x10);
}


void PDUReaderTest::testReadCoilsResponse()
{
	char buffer[] = {
		0x01, //Slave Address
		MODBUS_READ_COILS, //Function Code
		0x01, //number Of bytes
		0x55  //coil status 1010 0101
	};

	Poco::MemoryInputStream istr(buffer, sizeof(buffer));
	Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);

	PDUReader pduReader(binaryReader);

	ReadCoilsResponse message;
	pduReader.read(message);

	assert (message.slaveOrUnitAddress == 0x01);
	assert (message.functionCode == MODBUS_READ_COILS);
	assert (message.coilStatus.size() == 8);
	assert (message.coilStatus[0] == true);
	assert (message.coilStatus[1] == false);
	assert (message.coilStatus[2] == true);
	assert (message.coilStatus[3] == false);
	assert (message.coilStatus[4] == true);
	assert (message.coilStatus[5] == false);
	assert (message.coilStatus[6] == true);
	assert (message.coilStatus[7] == false);
}


void PDUReaderTest::testReadDiscreteInputsResponse()
{
	char buffer[] = {
		0x01, //Slave Address
		MODBUS_READ_DISCRETE_INPUTS, //Function Code
		0x01, //number Of bytes
		0x55  //input status 1010 0101
	};

	Poco::MemoryInputStream istr(buffer, sizeof(buffer));
	Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);

	PDUReader pduReader(binaryReader);

	ReadDiscreteInputsResponse message;
	pduReader.read(message);

	assert (message.slaveOrUnitAddress == 0x01);
	assert (message.functionCode == MODBUS_READ_DISCRETE_INPUTS);
	assert (message.inputStatus.size() == 8);
	assert (message.inputStatus[0] == true);
	assert (message.inputStatus[1] == false);
	assert (message.inputStatus[2] == true);
	assert (message.inputStatus[3] == false);
	assert (message.inputStatus[4] == true);
	assert (message.inputStatus[5] == false);
	assert (message.inputStatus[6] == true);
	assert (message.inputStatus[7] == false);
}


void PDUReaderTest::testReadHoldingRegistersResponse()
{
	unsigned char buffer[] = {
		0x01, //Slave Address
		MODBUS_READ_HOLDING_REGISTERS, //Function Code
		0x08, //byte count
		0x10, //Hi byte 1st register
		0x01, //Lo byte 1st register
		0x20,
		0x02,
		0x30,
		0x03,
		0x40,
		0x04
	};

	Poco::MemoryInputStream istr((char*)buffer, sizeof(buffer));
	Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);

	PDUReader pduReader(binaryReader);

	ReadHoldingRegistersResponse message;
	pduReader.read(message);

	assert (message.slaveOrUnitAddress == 0x01);
	assert (message.functionCode == MODBUS_READ_HOLDING_REGISTERS);
	assert (message.registerValues.size() == 4);
	assert (message.registerValues[0] == 0x1001);
	assert (message.registerValues[1] == 0x2002);
	assert (message.registerValues[2] == 0x3003);
	assert (message.registerValues[3] == 0x4004);
}


void PDUReaderTest::testReadInputRegistersResponse()
{
	unsigned char buffer[] = {
		0x01, //Slave Address
		MODBUS_READ_INPUT_REGISTERS, //Function Code
		0x08, //byte count
		0x10, //Hi byte 1st register
		0x01, //Lo byte 1st register
		0x20,
		0x02,
		0x30,
		0x03,
		0x40,
		0x04
	};

	Poco::MemoryInputStream istr((char*)buffer, sizeof(buffer));
	Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);

	PDUReader pduReader(binaryReader);

	ReadInputRegistersResponse message;
	pduReader.read(message);

	assert (message.slaveOrUnitAddress == 0x01);
	assert (message.functionCode == MODBUS_READ_INPUT_REGISTERS);
	assert (message.registerValues.size() == 4);
	assert (message.registerValues[0] == 0x1001);
	assert (message.registerValues[1] == 0x2002);
	assert (message.registerValues[2] == 0x3003);
	assert (message.registerValues[3] == 0x4004);
}


void PDUReaderTest::testWriteSingleCoilResponse()
{
	unsigned char buffer[] = {
		0x02, //Slave Address
		MODBUS_WRITE_SINGLE_COIL, //Function Code
		0xAA, //output address hi
		0x55, //output address lo
		0xFF, //output value hi
		0x00 //output value lo
	};

	Poco::MemoryInputStream istr((char*)buffer, sizeof(buffer));
	Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);

	PDUReader pduReader(binaryReader);

	WriteSingleCoilResponse message;
	pduReader.read(message);

	assert (message.slaveOrUnitAddress == 0x02);
	assert (message.functionCode == MODBUS_WRITE_SINGLE_COIL);
	assert (message.outputAddress == 0xAA55);
	assert (message.value == true);
}


void PDUReaderTest::testWriteSingleRegisterResponse()
{
	unsigned char buffer[] = {
		0x01, //Slave Address
		MODBUS_WRITE_SINGLE_REGISTER, //Function Code
		0xAA, //output address hi
		0x55, //output address lo
		0xBB, //output value hi
		0x66 //output value lo
	};

	Poco::MemoryInputStream istr((char*)buffer, sizeof(buffer));
	Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);

	PDUReader pduReader(binaryReader);

	WriteSingleRegisterResponse message;
	pduReader.read(message);

	assert (message.slaveOrUnitAddress == 0x01);
	assert (message.functionCode == MODBUS_WRITE_SINGLE_REGISTER);
	assert (message.registerAddress == 0xAA55);
	assert (message.value == 0xBB66);
}


void PDUReaderTest::testReadExceptionStatusResponse()
{
	unsigned char buffer[] = {
		0x01, //Slave Address
		MODBUS_READ_EXCEPTION_STATUS, //Function Code
		0xA5  //exception data
	};

	Poco::MemoryInputStream istr((char*)buffer, sizeof(buffer));
	Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);

	PDUReader pduReader(binaryReader);

	ReadExceptionStatusResponse message;
	pduReader.read(message);

	assert (message.slaveOrUnitAddress == 0x01);
	assert (message.functionCode == MODBUS_READ_EXCEPTION_STATUS);
	assert (message.data == 0xA5);
}


void PDUReaderTest::testWriteMultipleCoilsResponse()
{
	unsigned char buffer[] = {
		0x01, //Slave Address
		MODBUS_WRITE_MULTIPLE_COILS, //Function Code
		0xAA, //starting address hi
		0x55, //starting address lo
		0x07, //quantity of outputs hi
		0xB0 //quantity of outputs lo
	};

	Poco::MemoryInputStream istr((char*)buffer, sizeof(buffer));
	Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);

	PDUReader pduReader(binaryReader);

	WriteMultipleCoilsResponse message;
	pduReader.read(message);

	assert (message.slaveOrUnitAddress == 0x01);
	assert (message.functionCode == MODBUS_WRITE_MULTIPLE_COILS);
	assert (message.startingAddress == 0xAA55);
	assert (message.nOfCoils == 0x07B0);
}


void PDUReaderTest::testWriteMultipleRegistersResponse()
{
	unsigned char buffer[] = {
		0x01, //Slave Address
		MODBUS_WRITE_MULTIPLE_REGISTERS, //Function Code
		0xAA, //starting address hi
		0x55, //starting address lo
		0x07, //quantity of registers hi
		0xB0 //quantity of registers lo
	};

	Poco::MemoryInputStream istr((char*)buffer, sizeof(buffer));
	Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);

	PDUReader pduReader(binaryReader);

	WriteMultipleRegistersResponse message;
	pduReader.read(message);

	assert (message.slaveOrUnitAddress == 0x01);
	assert (message.functionCode == MODBUS_WRITE_MULTIPLE_REGISTERS);
	assert (message.startingAddress == 0xAA55);
	assert (message.nOfRegisters == 0x07B0);
}


void PDUReaderTest::testMaskWriteRegisterResponse()
{
	unsigned char buffer[] = {
		0x33, //Slave Address
		MODBUS_MASK_WRITE_REGISTER, //Function Code
		0xAA, //reference address hi
		0x55, //reference address lo
		0xBB, //and mask hi
		0x66, //and mask lo
		0xCC, //or mask hi
		0x77, //or mask lo
	};

	Poco::MemoryInputStream istr((char*)buffer, sizeof(buffer));
	Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);

	PDUReader pduReader(binaryReader);

	MaskWriteRegisterResponse message;
	pduReader.read(message);

	assert (message.slaveOrUnitAddress == 0x33);
	assert (message.functionCode == MODBUS_MASK_WRITE_REGISTER);
	assert (message.referenceAddress == 0xAA55);
	assert (message.andMask == 0xBB66);
	assert (message.orMask == 0xCC77);
}


void PDUReaderTest::testReadWriteMultipleRegistersResponse()
{
	unsigned char buffer[] = {
		0x01, //Slave Address
		MODBUS_READ_WRITE_MULTIPLE_REGISTERS, //Function Code
		0x04, //byte count
		0xAA, //Value Register1 Hi
		0x55, //Value Register1 Lo
		0xCC, //Value Register2 Hi
		0x77, //Value Register2 Lo
	};

	Poco::MemoryInputStream istr((char*)buffer, sizeof(buffer));
	Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);

	PDUReader pduReader(binaryReader);

	ReadWriteMultipleRegistersResponse message;
	pduReader.read(message);

	assert (message.slaveOrUnitAddress == 0x01);
	assert (message.functionCode == MODBUS_READ_WRITE_MULTIPLE_REGISTERS);
	assert (message.values[0] == 0xAA55);
	assert (message.values[1] == 0xCC77);
}


void PDUReaderTest::testReadFIFOQueueResponse()
{
	unsigned char buffer[] = {
		0x01, //Slave Address
		MODBUS_READ_FIFO_QUEUE, //Function Code
		0x00, //byte count hi
		0x04, //byte count lo
		0x00, //FIFO count hi
		0x02, //FIFO count lo
		0xAA, //FIFO Value Register Hi
		0x55, //FIFO Value Register Lo
		0xCC, //FIFO Value Register Hi
		0x77, //FIFO Value Register Lo
	};

	Poco::MemoryInputStream istr((char*)buffer, sizeof(buffer));
	Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);

	PDUReader pduReader(binaryReader);

	ReadFIFOQueueResponse message;
	pduReader.read(message);

	assert (message.slaveOrUnitAddress == 0x01);
	assert (message.functionCode == MODBUS_READ_FIFO_QUEUE);
	assert (message.values[0] == 0xAA55);
	assert (message.values[1] == 0xCC77);
}


void PDUReaderTest::setUp()
{
}


void PDUReaderTest::tearDown()
{
}


CppUnit::Test* PDUReaderTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("PDUReaderTest");

	CppUnit_addTest(pSuite, PDUReaderTest, testGenericMessage);
	CppUnit_addTest(pSuite, PDUReaderTest, testModbusExceptionMessage);
	CppUnit_addTest(pSuite, PDUReaderTest, testReadCoilsResponse);
	CppUnit_addTest(pSuite, PDUReaderTest, testReadDiscreteInputsResponse);
	CppUnit_addTest(pSuite, PDUReaderTest, testReadHoldingRegistersResponse);
	CppUnit_addTest(pSuite, PDUReaderTest, testReadInputRegistersResponse);
	CppUnit_addTest(pSuite, PDUReaderTest, testWriteSingleCoilResponse);
	CppUnit_addTest(pSuite, PDUReaderTest, testWriteSingleRegisterResponse);
	CppUnit_addTest(pSuite, PDUReaderTest, testReadExceptionStatusResponse);
	CppUnit_addTest(pSuite, PDUReaderTest, testWriteMultipleCoilsResponse);
	CppUnit_addTest(pSuite, PDUReaderTest, testWriteMultipleRegistersResponse);
	CppUnit_addTest(pSuite, PDUReaderTest, testMaskWriteRegisterResponse);
	CppUnit_addTest(pSuite, PDUReaderTest, testReadWriteMultipleRegistersResponse);
	CppUnit_addTest(pSuite, PDUReaderTest, testReadFIFOQueueResponse);

	return pSuite;
}
