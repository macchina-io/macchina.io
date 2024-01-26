//
// PDUWriterTest.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "PDUWriterTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "IoT/Modbus/PDUWriter.h"
#include "Poco/BinaryWriter.h"
#include "Poco/MemoryStream.h"


using namespace IoT::Modbus;


PDUWriterTest::PDUWriterTest(const std::string& name): 
	CppUnit::TestCase(name)
{
}


PDUWriterTest::~PDUWriterTest()
{
}


void PDUWriterTest::testGenericMessage()
{
	char buffer[MODBUS_MAX_PDU_SIZE];
	Poco::MemoryOutputStream ostr(buffer, sizeof(buffer));
	Poco::BinaryWriter binaryWriter(ostr, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);
	
	GenericMessage message;
	message.slaveOrUnitAddress = 0x01;
	message.functionCode = 0x02;
	message.data.push_back(0x10);
	message.data.push_back(0x11);
	
	PDUWriter pduWriter(binaryWriter);
	pduWriter.write(message);
	
	assert (ostr.charsWritten() == 4);
	assert (buffer[0] == 0x01);
	assert (buffer[1] == 0x02);
	assert (buffer[2] == 0x10);
	assert (buffer[3] == 0x11);
}


void PDUWriterTest::testReadCoilsRequest()
{
	unsigned char buffer[MODBUS_MAX_PDU_SIZE];
	Poco::MemoryOutputStream ostr((char*)buffer, sizeof(buffer));
	Poco::BinaryWriter binaryWriter(ostr, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);

	ReadCoilsRequest message;
	message.slaveOrUnitAddress = 0x02;
	message.startingAddress = 0xAAFF;
	message.nOfCoils = 8;

	PDUWriter pduWriter(binaryWriter);
	pduWriter.write(message);

	assert (ostr.charsWritten() == 6);
	assert (buffer[0] == 0x02);
	assert (buffer[1] == MODBUS_READ_COILS);
	assert (buffer[2] == 0xAA);
	assert (buffer[3] == 0xFF);
	assert (buffer[4] == 0x00);
	assert (buffer[5] == 0x08);
}


void PDUWriterTest::testReadDiscreteInputsRequest()
{
	unsigned char buffer[MODBUS_MAX_PDU_SIZE];
	Poco::MemoryOutputStream ostr((char*)buffer, sizeof(buffer));
	Poco::BinaryWriter binaryWriter(ostr, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);

	ReadDiscreteInputsRequest message;
	message.slaveOrUnitAddress = 0x02;
	message.startingAddress = 0xAAFF;
	message.nOfInputs = 8;

	PDUWriter pduWriter(binaryWriter);
	pduWriter.write(message);

	assert (ostr.charsWritten() == 6);
	assert (buffer[0] == 0x02);
	assert (buffer[1] == MODBUS_READ_DISCRETE_INPUTS);
	assert (buffer[2] == 0xAA);
	assert (buffer[3] == 0xFF);
	assert (buffer[4] == 0x00);
	assert (buffer[5] == 0x08);
}


void PDUWriterTest::testReadHoldingRegistersRequest()
{
	unsigned char buffer[MODBUS_MAX_PDU_SIZE];
	Poco::MemoryOutputStream ostr((char*)buffer, sizeof(buffer));
	Poco::BinaryWriter binaryWriter(ostr, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);

	ReadHoldingRegistersRequest message;
	message.slaveOrUnitAddress = 0x02;
	message.startingAddress = 0x55FF;
	message.nOfRegisters = 0x7D;

	PDUWriter pduWriter(binaryWriter);
	pduWriter.write(message);

	assert (ostr.charsWritten() == 6);
	assert (buffer[0] == 0x02);
	assert (buffer[1] == MODBUS_READ_HOLDING_REGISTERS);
	assert (buffer[2] == 0x55);
	assert (buffer[3] == 0xFF);
	assert (buffer[4] == 0x00);
	assert (buffer[5] == 0x7D);
}


void PDUWriterTest::testReadInputRegistersRequest()
{
	unsigned char buffer[MODBUS_MAX_PDU_SIZE];
	Poco::MemoryOutputStream ostr((char*)buffer, sizeof(buffer));
	Poco::BinaryWriter binaryWriter(ostr, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);

	ReadInputRegistersRequest message;
	message.slaveOrUnitAddress = 0x02;
	message.startingAddress = 0x55FF;
	message.nOfRegisters = 0x007D;

	PDUWriter pduWriter(binaryWriter);
	pduWriter.write(message);

	assert (ostr.charsWritten() == 6);
	assert (buffer[0] == 0x02);
	assert (buffer[1] == MODBUS_READ_INPUT_REGISTERS);
	assert (buffer[2] == 0x55);
	assert (buffer[3] == 0xFF);
	assert (buffer[4] == 0x00);
	assert (buffer[5] == 0x7D);
}


void PDUWriterTest::testWriteSingleCoilRequest()
{
	unsigned char buffer[MODBUS_MAX_PDU_SIZE];
	Poco::MemoryOutputStream ostr((char*)buffer, sizeof(buffer));
	Poco::BinaryWriter binaryWriter(ostr, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);

	WriteSingleCoilRequest message;
	message.slaveOrUnitAddress = 0x02;
	message.outputAddress = 0x55FF;
	message.value = true;

	PDUWriter pduWriter(binaryWriter);
	pduWriter.write(message);

	assert (ostr.charsWritten() == 6);
	assert (buffer[0] == 0x02);
	assert (buffer[1] == MODBUS_WRITE_SINGLE_COIL);
	assert (buffer[2] == 0x55);
	assert (buffer[3] == 0xFF);
	assert (buffer[4] == 0xFF);
	assert (buffer[5] == 0x00);
}


void PDUWriterTest::testWriteSingleRegisterRequest()
{
	unsigned char buffer[MODBUS_MAX_PDU_SIZE];
	Poco::MemoryOutputStream ostr((char*)buffer, sizeof(buffer));
	Poco::BinaryWriter binaryWriter(ostr, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);

	WriteSingleRegisterRequest message;
	message.slaveOrUnitAddress = 0x02;
	message.registerAddress = 0x55FF;
	message.value = 0xAA55;

	PDUWriter pduWriter(binaryWriter);
	pduWriter.write(message);

	assert (ostr.charsWritten() == 6);
	assert (buffer[0] == 0x02);
	assert (buffer[1] == MODBUS_WRITE_SINGLE_REGISTER);
	assert (buffer[2] == 0x55);
	assert (buffer[3] == 0xFF);
	assert (buffer[4] == 0xAA);
	assert (buffer[5] == 0x55);
}


void PDUWriterTest::testReadExceptionStatusRequest()
{
	unsigned char buffer[MODBUS_MAX_PDU_SIZE];
	Poco::MemoryOutputStream ostr((char*)buffer, sizeof(buffer));
	Poco::BinaryWriter binaryWriter(ostr, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);

	ReadExceptionStatusRequest message;
	message.slaveOrUnitAddress = 0x02;

	PDUWriter pduWriter(binaryWriter);
	pduWriter.write(message);

	assert (ostr.charsWritten() == 2);
	assert (buffer[0] == 0x02);
	assert (buffer[1] == MODBUS_READ_EXCEPTION_STATUS);
}


void PDUWriterTest::testWriteMultipleCoilsRequest()
{
	unsigned char buffer[MODBUS_MAX_PDU_SIZE];
	Poco::MemoryOutputStream ostr((char*)buffer, sizeof(buffer));
	Poco::BinaryWriter binaryWriter(ostr, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);

	WriteMultipleCoilsRequest message;
	message.slaveOrUnitAddress = 0x02;
	message.startingAddress = 0x55AA;
	message.values.push_back(true);
	message.values.push_back(false);
	message.values.push_back(true);
	message.values.push_back(false);
	message.values.push_back(true);
	message.values.push_back(false);
	message.values.push_back(true);
	message.values.push_back(false);

	PDUWriter pduWriter(binaryWriter);
	pduWriter.write(message);

	assert (ostr.charsWritten() == 8);
	assert (buffer[0] == 0x02);
	assert (buffer[1] == MODBUS_WRITE_MULTIPLE_COILS); //function code
	assert (buffer[2] == 0x55); //starting address high
	assert (buffer[3] == 0xAA); //starting address low
	assert (buffer[4] == 0x00); //quantity of outputs high
	assert (buffer[5] == 0x08); //quantity of outputs low
	assert (buffer[6] == 0x01); //byte count
	assert (buffer[7] == 0x55); //output value
}


void PDUWriterTest::testWriteMultipleRegistersRequest()
{
	unsigned char buffer[MODBUS_MAX_PDU_SIZE];
	Poco::MemoryOutputStream ostr((char*)buffer, sizeof(buffer));
	Poco::BinaryWriter binaryWriter(ostr, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);

	WriteMultipleRegistersRequest message;
	message.slaveOrUnitAddress = 0x02;
	message.startingAddress = 0x55AA;
	message.values.push_back(0x1001);
	message.values.push_back(0x2002);
	message.values.push_back(0x3003);
	message.values.push_back(0x4004);

	PDUWriter pduWriter(binaryWriter);
	pduWriter.write(message);

	assert (ostr.charsWritten() == 15);
	assert (buffer[0] == 0x02); //slave address
	assert (buffer[1] == MODBUS_WRITE_MULTIPLE_REGISTERS); //function code
	assert (buffer[2] == 0x55); //starting address high
	assert (buffer[3] == 0xAA); //starting address low
	assert (buffer[4] == 0x00); //quantity of registers high
	assert (buffer[5] == 0x04); //quantity of registers low
	assert (buffer[6] == 0x08); //byte count
	assert (buffer[7] == 0x10); //register1 value high
	assert (buffer[8] == 0x01); //register1 value low
	assert (buffer[9] == 0x20); //register2 value high
	assert (buffer[10] == 0x02);
	assert (buffer[11] == 0x30);
	assert (buffer[12] == 0x03);
	assert (buffer[13] == 0x40);
	assert (buffer[14] == 0x04);
}


void PDUWriterTest::testMaskWriteRegisterRequest()
{
	unsigned char buffer[MODBUS_MAX_PDU_SIZE];
	Poco::MemoryOutputStream ostr((char*)buffer, sizeof(buffer));
	Poco::BinaryWriter binaryWriter(ostr, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);

	MaskWriteRegisterRequest message;
	message.slaveOrUnitAddress = 0x02;
	message.referenceAddress = 0x55AA;
	message.andMask = 0x77BB;
	message.orMask = 0x88CC;

	PDUWriter pduWriter(binaryWriter);
	pduWriter.write(message);

	assert (ostr.charsWritten() == 8);
	assert (buffer[0] == 0x02); //slave address
	assert (buffer[1] == MODBUS_MASK_WRITE_REGISTER); //function code
	assert (buffer[2] == 0x55); //reference address high
	assert (buffer[3] == 0xAA); //reference address low
	assert (buffer[4] == 0x77); //and mask high
	assert (buffer[5] == 0xBB); //and mask low
	assert (buffer[6] == 0x88); //or mask high
	assert (buffer[7] == 0xCC); //or mask low
}


void PDUWriterTest::testReadWriteMultipleRegistersRequest()
{
	unsigned char buffer[MODBUS_MAX_PDU_SIZE]={0};
	Poco::MemoryOutputStream ostr((char*)buffer, sizeof(buffer));
	Poco::BinaryWriter binaryWriter(ostr, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);

	ReadWriteMultipleRegistersRequest message;
	message.slaveOrUnitAddress = 0x02;
	message.readStartingAddress = 0x55AA;
	message.readCount = 0x11;
	message.writeStartingAddress = 0x66BB;
	message.values.push_back(0x1001);
	message.values.push_back(0x2002);
	message.values.push_back(0x3003);
	message.values.push_back(0x4004);

	PDUWriter pduWriter(binaryWriter);
	pduWriter.write(message);

	assert (ostr.charsWritten() == 19);
	assert (buffer[0] == 0x02); //slave address
	assert (buffer[1] == MODBUS_READ_WRITE_MULTIPLE_REGISTERS); //function code
	assert (buffer[2] == 0x55); //read starting address high
	assert (buffer[3] == 0xAA); //read starting address low
	assert (buffer[4] == 0x00); //quantity to read high
	assert (buffer[5] == 0x11); //quantity to read low
	assert (buffer[6] == 0x66); //write starting address high
	assert (buffer[7] == 0xBB); //write starting address low
	assert (buffer[8] == 0x00); //quantity to write high
	assert (buffer[9] == 0x04); //quantity to write low
	assert (buffer[10] == 0x08); //write byte count
	assert (buffer[11] == 0x10); //register1 value high
	assert (buffer[12] == 0x01); //register1 value low
	assert (buffer[13] == 0x20); //register2 value high
	assert (buffer[14] == 0x02);
	assert (buffer[15] == 0x30);
	assert (buffer[16] == 0x03);
	assert (buffer[17] == 0x40);
	assert (buffer[18] == 0x04);
}


void PDUWriterTest::testReadFIFOQueueRequest()
{
	unsigned char buffer[MODBUS_MAX_PDU_SIZE];
	Poco::MemoryOutputStream ostr((char*)buffer, sizeof(buffer));
	Poco::BinaryWriter binaryWriter(ostr, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);

	ReadFIFOQueueRequest message;
	message.slaveOrUnitAddress = 0x02;
	message.fifoAddress = 0x55AA;

	PDUWriter pduWriter(binaryWriter);
	pduWriter.write(message);

	assert (ostr.charsWritten() == 4);
	assert (buffer[0] == 0x02); //slave address
	assert (buffer[1] == MODBUS_READ_FIFO_QUEUE); //function code
	assert (buffer[2] == 0x55); //read starting address high
	assert (buffer[3] == 0xAA); //read starting address low
}


void PDUWriterTest::setUp()
{
}


void PDUWriterTest::tearDown()
{
}


CppUnit::Test* PDUWriterTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("PDUWriterTest");

	CppUnit_addTest(pSuite, PDUWriterTest, testGenericMessage);
	CppUnit_addTest(pSuite, PDUWriterTest, testReadCoilsRequest);
	CppUnit_addTest(pSuite, PDUWriterTest, testReadDiscreteInputsRequest);
	CppUnit_addTest(pSuite, PDUWriterTest, testReadHoldingRegistersRequest);
	CppUnit_addTest(pSuite, PDUWriterTest, testReadInputRegistersRequest);
	CppUnit_addTest(pSuite, PDUWriterTest, testWriteSingleCoilRequest);
	CppUnit_addTest(pSuite, PDUWriterTest, testWriteSingleRegisterRequest);
	CppUnit_addTest(pSuite, PDUWriterTest, testReadExceptionStatusRequest);
	CppUnit_addTest(pSuite, PDUWriterTest, testWriteMultipleCoilsRequest);
	CppUnit_addTest(pSuite, PDUWriterTest, testWriteMultipleRegistersRequest);
	CppUnit_addTest(pSuite, PDUWriterTest, testMaskWriteRegisterRequest);
	CppUnit_addTest(pSuite, PDUWriterTest, testReadWriteMultipleRegistersRequest);
	CppUnit_addTest(pSuite, PDUWriterTest, testReadFIFOQueueRequest);

	return pSuite;
}
