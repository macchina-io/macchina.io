//
// Outlet.h
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: Outlet
// Module:  Outlet
//
// Definition of the Outlet class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Engine_Outlet_INCLUDED
#define IoT_Dataflow_Engine_Outlet_INCLUDED


#include "IoT/Dataflow/Engine/Engine.h"
#include "IoT/Dataflow/Engine/Port.h"
#include "IoT/Dataflow/Engine/FastEvent.h"
#include "IoT/Dataflow/Engine/Inlet.h"
#include "IoT/Dataflow/Engine/Scheduler.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


template <typename T, typename O>
class ValuePropagationTask: public SchedulerTask
{
public:
	ValuePropagationTask(const T& value, O* pOutlet):
		_value(value),
		_pOutlet(pOutlet)
	{
	}
	
	void run()
	{
		_pOutlet->propagate(_value);
	}
	
private:
	T _value;
	O* _pOutlet;
};


template <typename O>
class VoidPropagationTask: public SchedulerTask
{
public:
	VoidPropagationTask(O* pOutlet):
		_pOutlet(pOutlet)
	{
	}
	
	void run()
	{
		_pOutlet->propagate();
	}
	
private:
	O* _pOutlet;
};


class IoTDataflowEngine_API AbstractOutlet: public Port
	/// AbstractOutlet is the common base class for all Outlet 
	/// template specializations.
{
public:
	typedef Poco::AutoPtr<AbstractOutlet> Ptr;
	
	AbstractOutlet(const std::string& name, Scheduler& scheduler);
		/// Creates the AbstractOutlet with the given name and Scheduler.
		
	~AbstractOutlet();
		/// Destroys the AbstractOutlet.
	
	virtual void connect(AbstractInlet& inlet) = 0;
		/// Connects the outlet to the given inlet.
	
	virtual void disconnect(AbstractInlet& inlet) = 0;
		/// Disconnects the outlet from the given inlet.
		
protected:
	Scheduler& scheduler()
	{
		return _scheduler;
	}
	
private:
	Scheduler& _scheduler;
};


template <typename T>
class Outlet: public AbstractOutlet
	/// An Outlet is used to drain data from a processing node.
{
public:
	typedef Poco::AutoPtr<Outlet> Ptr;

	Outlet(const std::string& name, Scheduler& scheduler):
		AbstractOutlet(name, scheduler)
		/// Creates an Outlet with the given name and Scheduler.
	{
	}
	
	~Outlet()
		/// Destroys the Outlet.
	{
	}
	
	void update(const T& value)
		/// Updates the value of the outlet and notifies all connected inlets if
		/// the value has changed.
	{
		if (value != _value)
		{
			_value = value;
			scheduler().scheduleImmediately(new ValuePropagationTask<T, Outlet>(value, this));
		}
	}
	
	void set(const T& value)
		/// Updates the value of the outlet and notifies all connected inlets,
		/// even if the value has not changed.
	{
		_value = value;
		scheduler().scheduleImmediately(new ValuePropagationTask<T, Outlet>(value, this));
	}
	
	const T& value() const
		/// Returns the value of the outlet.
	{
		return _value;
	}
	
	void propagate(const T& value)
	{
		_updated(this, value);
	}
	
	// AbstractOutlet	
	void connect(AbstractInlet& inlet)
	{
		Inlet<T>* pTypedInlet = dynamic_cast<Inlet<T>*>(&inlet);
		if (pTypedInlet)
		{
			_updated += Poco::delegate(pTypedInlet, &Inlet<T>::update);
			pTypedInlet->reset(_value);
		}
		else throw Poco::InvalidArgumentException("Invalid inlet type", inlet.type().name());
	}

	void disconnect(AbstractInlet& inlet)
	{
		Inlet<T>* pTypedInlet = dynamic_cast<Inlet<T>*>(&inlet);
		if (pTypedInlet)
		{
			_updated -= Poco::delegate(pTypedInlet, &Inlet<T>::update);
		}
		else throw Poco::InvalidArgumentException("Invalid inlet type", inlet.type().name());
	}

	// Port
	void print(std::ostream& ostr)
	{
		ostr << _value;
	}

	const std::type_info& type() const
	{
		return typeid(T);
	}
	
private:
	FastEvent<const T> _updated;
	T _value;
};


template <>
class Outlet<void>: public AbstractOutlet
{
public:
	typedef Poco::AutoPtr<Outlet> Ptr;

	Outlet(const std::string& name, Scheduler& scheduler):
		AbstractOutlet(name, scheduler)
	{
	}
	
	~Outlet()
	{
	}
	
	void update()
	{
		scheduler().scheduleImmediately(new VoidPropagationTask<Outlet>(this));
	}
		
	// AbstractOutlet
	void propagate()
	{
		_updated(this);
	}
	
	void connect(AbstractInlet& inlet)
	{
		Inlet<void>* pTypedInlet = dynamic_cast<Inlet<void>*>(&inlet);
		if (pTypedInlet)
		{
			_updated += Poco::delegate(pTypedInlet, &Inlet<void>::update);
		}
		else throw Poco::InvalidArgumentException("Invalid inlet type", inlet.type().name());
	}

	void disconnect(AbstractInlet& inlet)
	{
		Inlet<void>* pTypedInlet = dynamic_cast<Inlet<void>*>(&inlet);
		if (pTypedInlet)
		{
			_updated -= Poco::delegate(pTypedInlet, &Inlet<void>::update);
		}
		else throw Poco::InvalidArgumentException("Invalid inlet type", inlet.type().name());
	}

	// Port
	void print(std::ostream& ostr)
	{
	}

	const std::type_info& type() const
	{
		return typeid(void);
	}
	
private:
	FastEvent<void> _updated;
};


} } } // namespace IoT::Dataflow::Engine


#endif // IoT_Dataflow_Engine_Outlet_INCLUDED
