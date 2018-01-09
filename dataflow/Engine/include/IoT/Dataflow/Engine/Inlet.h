//
// Inlet.h
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: Inlet
// Module:  Inlet
//
// Definition of the Inlet class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Engine_Inlet_INCLUDED
#define IoT_Dataflow_Engine_Inlet_INCLUDED


#include "IoT/Dataflow/Engine/Engine.h"
#include "IoT/Dataflow/Engine/Port.h"
#include "IoT/Dataflow/Engine/FastEvent.h"
#include <typeinfo>


namespace IoT {
namespace Dataflow {
namespace Engine {


class AbstractOutlet;


class IoTDataflowEngine_API AbstractInlet: public Port
	/// AbstractInlet is the common base class for all Inlet 
	/// template specializations.
{
public:
	typedef Poco::AutoPtr<AbstractInlet> Ptr;
	
	AbstractInlet(const std::string& name);
		/// Creates the AbstractInlet with the given name.
		
	~AbstractInlet();
		/// Destroys the AbstractInlet.

	void connect(AbstractOutlet& outlet);
		/// Connects the inlet to the given outlet.

	void disconnect(AbstractOutlet& outlet);
		/// Disconnects the inlet from the given outlet.
};


template <typename T>
class Inlet: public AbstractInlet
	/// An Inlet is used to pump data into a processing node.
{
public:
	typedef Poco::AutoPtr<Inlet> Ptr;

	FastEvent<const T> updated;
	
	Inlet(const std::string& name):
		AbstractInlet(name),
		_value()
		/// Creates the Inlet using the given name and Scheduler.
	{
	}

	Inlet(const std::string& name, const T& deflt):
		AbstractInlet(name),
		_value(deflt)
		/// Creates the Inlet using the given name
		/// and default value.
	{
	}
	
	const T& value() const
		/// Returns the value of the Inlet.
	{
		return _value;
	}
	
	void update(const T& value)
		/// Updates the value of the Inlet.
	{
		_value = value;
		updated(this, value);
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

protected:
	void reset(const T& value)
		/// Updates the value of the Inlet without triggering the updated event.
		/// This is used after connecting the inlet to an outlet, to match the
		/// value of the inlet to that of the connected outlet without
		/// triggering the processing chain.
	{
		_value = value;
	}
	
private:
	T _value;
	
	template <typename> friend class Outlet;
};


template <>
class Inlet<void>: public AbstractInlet
{
public:
	typedef Poco::AutoPtr<Inlet> Ptr;

	FastEvent<void> updated;
	
	Inlet(const std::string& name):
		AbstractInlet(name)
	{
	}

	void update()
		/// Updates the value of the Inlet.
	{
		updated(this);
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
	template <typename> friend class Outlet;
};


} } } // namespace IoT::Dataflow::Engine


#endif // IoT_Dataflow_Engine_Inlet_INCLUDED
