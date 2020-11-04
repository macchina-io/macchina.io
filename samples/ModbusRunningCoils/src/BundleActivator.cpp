//
// BundleActivator.cpp
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/Util/Timer.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/Format.h"
#include "Poco/ClassLibrary.h"
#include "IoT/Modbus/IModbusMaster.h"


namespace ModbusRunningCoils {


class RunningCoilsTask: public Poco::Util::TimerTask
{
public:
	RunningCoilsTask(IoT::Modbus::IModbusMaster::Ptr pModbusMaster, Poco::UInt8 slaveId, int nOfCoils, int baseAddress):
		_pModbusMaster(pModbusMaster),
		_slaveId(slaveId),
		_nOfCoils(nOfCoils),
		_baseAddress(baseAddress)
	{
	}

	void run()
	{
		int lastCoil = _currentCoil - 1;
		if (lastCoil < 0) lastCoil = _nOfCoils - 1;

		_pModbusMaster->writeSingleCoil(_slaveId, static_cast<Poco::UInt16>(_baseAddress + lastCoil), false);
		_pModbusMaster->writeSingleCoil(_slaveId, static_cast<Poco::UInt16>(_baseAddress + _currentCoil), true);

		_currentCoil++;
		if (_currentCoil >= _nOfCoils) _currentCoil = 0;
	}

private:
	IoT::Modbus::IModbusMaster::Ptr _pModbusMaster;
	Poco::UInt8 _slaveId;
	int _nOfCoils;
	int _currentCoil = 0;
	int _baseAddress;
};


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	void start(Poco::OSP::BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = Poco::OSP::ServiceFinder::find<Poco::OSP::PreferencesService>(pContext);

		std::string modbusMasterName = _pPrefs->configuration()->getString("modbusRunningCoils.modbusMaster", "io.macchina.modbus.rtu#adam");
		Poco::UInt8 slaveId = static_cast<Poco::UInt8>(_pPrefs->configuration()->getUInt("modbusRunningCoils.modbusSlave", 1));
		int nOfCoils = _pPrefs->configuration()->getInt("modbusRunningCoils.nOfCoils", 8);
		int baseAddress = _pPrefs->configuration()->getInt("modbusRunningCoils.baseAddress", 16);
		long interval = _pPrefs->configuration()->getInt("modbusRunningCoils.interval", 500);

		_pModbusMasterRef = pContext->registry().findByName(modbusMasterName);
		if (_pModbusMasterRef)
		{
			_pModbusMaster = _pModbusMasterRef->castedInstance<IoT::Modbus::IModbusMaster>();
			_timer.scheduleAtFixedRate(new RunningCoilsTask(_pModbusMaster, slaveId, nOfCoils, baseAddress), interval, interval);
		}
		else
		{
			_pContext->logger().warning("No ModbusMaster found.");
		}
	}

	void stop(Poco::OSP::BundleContext::Ptr pContext)
	{
		_timer.cancel(true);
		_pModbusMaster.reset();
		_pModbusMaster.reset();
		_pPrefs.reset();
		_pContext.reset();
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::PreferencesService::Ptr _pPrefs;
	Poco::OSP::ServiceRef::Ptr _pModbusMasterRef;
	IoT::Modbus::IModbusMaster::Ptr _pModbusMaster;
	Poco::Util::Timer _timer;
};


} // namespace ModbusRunningCoils


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(ModbusRunningCoils::BundleActivator)
POCO_END_MANIFEST
