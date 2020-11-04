//
// SignalDecoder.h
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_CAN_SignalDecoder_INCLUDED
#define IoT_CAN_SignalDecoder_INCLUDED


#include "IoT/CAN/CANDevices.h"
#include "IoT/CAN/Sensor.h"
#include "IoT/CAN/Counter.h"
#include "IoT/CAN/BooleanSensor.h"
#include "IoT/CAN/CANFDFrame.h"
#include "Poco/AutoPtr.h"
#include <limits>


namespace IoT {
namespace CAN {


class IoTCANDevices_API SignalDecoder: public Poco::RefCountedObject
	/// Base class for all CAN signal decoders.
{
public:
	using Ptr = Poco::AutoPtr<SignalDecoder>;

	SignalDecoder();
		/// Creates a SignalDecoder.

	virtual ~SignalDecoder();
		/// Destroys the SignalDecoder.

	virtual void decode(const CANFDFrame& frame) = 0;
		/// Decodes the given frame and updates the connected
		/// device according to the content.
};


template <typename Bits, typename IntType>
class SensorDecoder: public SignalDecoder
	/// CAN message decoder for scaled values
	/// with slope and intercept.
{
public:
	SensorDecoder(Sensor::Ptr pSensor, std::size_t offset, std::size_t length, double slope, double intercept, IntType min = std::numeric_limits<IntType>::min(), IntType max = std::numeric_limits<IntType>::max()):
		_pSensor(pSensor),
		_offset(offset),
		_length(length),
		_slope(slope),
		_intercept(intercept),
		_min(min),
		_max(max)
	{
	}

	~SensorDecoder()
	{
	}

	// SignalDecoder
	void decode(const CANFDFrame& frame)
	{
		Bits bits(&frame.payload()[0], _offset, _length);
		IntType value;
		read(bits, value);
		if (value >= _min && value <= _max)
		{
			double scaled = _slope*value + _intercept;
			_pSensor->update(scaled);
		}
	}

	static void read(Bits& bits, Poco::Int32& value)
	{
		value = bits.readSigned();
	}

	static void read(Bits& bits, Poco::UInt32 value)
	{
		value = bits.readUnsigned();
	}

private:
	Sensor::Ptr _pSensor;
	std::size_t _offset;
	std::size_t _length;
	double _slope;
	double _intercept;
	IntType _min;
	IntType _max;
};


template <typename Bits, typename FloatType>
class SensorFloatDecoder: public SignalDecoder
	/// CAN message decoder for float and double.
{
public:
	SensorFloatDecoder(Sensor::Ptr pSensor, std::size_t offset, std::size_t length):
		_pSensor(pSensor),
		_offset(offset),
		_length(length)
	{
		poco_assert (length == sizeof(FloatType));
	}

	~SensorFloatDecoder()
	{
	}

	void decode(const CANFDFrame& frame)
	{
		Bits bits(&frame.payload()[0], _offset, _length);
		FloatType value = bits.template readFloat<FloatType>();
		_pSensor->update(value);
	}

private:
	Sensor::Ptr _pSensor;
	std::size_t _offset;
	std::size_t _length;
};


template <typename Bits, typename IntType>
class CounterDecoder: public SignalDecoder
	/// CAN message decoder for raw integer values.
{
public:
	CounterDecoder(Counter::Ptr pCounter, std::size_t offset, std::size_t length, IntType min = std::numeric_limits<IntType>::min(), IntType max = std::numeric_limits<IntType>::max()):
		_pCounter(pCounter),
		_offset(offset),
		_length(length),
		_min(min),
		_max(max)
	{
	}

	// SignalDecoder
	void decode(const CANFDFrame& frame)
	{
		Bits bits(&frame.payload()[0], _offset, _length);
		IntType value;
		read(bits, value);
		if (value >= _min && value <= _max)
		{
			_pCounter->update(value);
		}
	}

	static void read(Bits& bits, Poco::Int32& value)
	{
		value = bits.readSigned();
	}

	static void read(Bits& bits, Poco::UInt32 value)
	{
		value = bits.readUnsigned();
	}

private:
	Counter::Ptr _pCounter;
	std::size_t _offset;
	std::size_t _length;
	IntType _min;
	IntType _max;
};


class BooleanSensorDecoder: public SignalDecoder
{
public:
	BooleanSensorDecoder(BooleanSensor::Ptr pSensor, std::size_t offset);

	// SignalDecoder
	void decode(const CANFDFrame& frame);

private:
	BooleanSensor::Ptr _pSensor;
	std::size_t _offset;
};


template <typename Bits>
class MultiplexDecoder: public SignalDecoder
	/// CAN message decoder for multiplexed signals.
{
public:
	typedef std::multimap<Poco::UInt32, SignalDecoder::Ptr> Decoders;

	MultiplexDecoder(std::size_t offset, std::size_t length):
		_offset(offset),
		_length(length)
	{
	}

	void addDecoder(Poco::UInt32 multiplexID, SignalDecoder::Ptr pDecoder)
		/// Adds a SignalDecoder for the given multiplexID.
		///
		/// Multiple SignalDecoders can be registered for each ID.
	{
		_decoders.insert(Decoders::value_type(multiplexID, pDecoder));
	}

	// SignalDecoder
	void decode(const CANFDFrame& frame)
	{
		Bits bits(&frame.payload()[0], _offset, _length);
		Poco::UInt32 muxID = bits.readUnsigned();
		Decoders::iterator it = _decoders.find(muxID);
		while (it != _decoders.end() && it->first == muxID)
		{
			it->second->decode(frame);
			++it;
		}
	}

private:
	std::size_t _offset;
	std::size_t _length;
	Decoders _decoders;
};


} } // namespace IoT::CAN


#endif // IoT_CAN_SignalDecoder_INCLUDED
