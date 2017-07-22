//
// ComputationNodes.h
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: LogicalNodes
// Module:  LogicalNodes
//
// Definition of arithmetic node class templates.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Engine_ComputationNodes_INCLUDED
#define IoT_Dataflow_Engine_ComputationNodes_INCLUDED


#include "IoT/Dataflow/Engine/Node.h"
#include <deque>
#include <limits>
#include <cmath>


namespace IoT {
namespace Dataflow {
namespace Engine {


template <typename T>
class Constant: public Node
{
public:
	typedef Poco::AutoPtr<Constant> Ptr;
	
	Constant(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_scheduler(scheduler),
		_value(attrs.getAttribute<T>("value", 0)),
		_pOutput(new Outlet<T>("output", scheduler))
	{
		addOutlet(_pOutput);
		
		_scheduler.started += Poco::delegate(this, &Constant::update);
	}
	
	~Constant()
	{
		_scheduler.started -= Poco::delegate(this, &Constant::update);
	}
	
	void update()
	{
		_pOutput->update(_value);
	}
	
private:
	Scheduler& _scheduler;
	T _value;
	typename Outlet<T>::Ptr _pOutput;
};


template <typename Tin, typename Tout = Tin>
class Scale: public Node
{
public:
	typedef Poco::AutoPtr<Scale> Ptr;

	Scale(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pInput(new Inlet<Tin>("input")),
		_pScale(new Inlet<Tout>("scale", attrs.getAttribute<Tout>("scale", 0))),
		_pOffset(new Inlet<Tout>("offset", attrs.getAttribute<Tout>("offset", 0))),
		_pOutput(new Outlet<Tout>("output", scheduler))
	{
		addInlet(_pInput);
		addInlet(_pScale);
		addInlet(_pOffset);
		addOutlet(_pOutput);
		
		_pInput->updated += Poco::delegate(this, &Scale::update);
		_pScale->updated += Poco::delegate(this, &Scale::update2);
		_pOffset->updated += Poco::delegate(this, &Scale::update2);
	}
	
	void update(const Tin&)
	{
		Tout result = static_cast<Tout>(_pInput->value())*_pScale->value() + _pOffset->value();
		_pOutput->update(result);	
	}
	
	void update2(const Tout&)
	{
		Tout result = static_cast<Tout>(_pInput->value())*_pScale->value() + _pOffset->value();
		_pOutput->update(result);	
	}
	
private:
	typename Inlet<Tin>::Ptr _pInput;
	typename Inlet<Tout>::Ptr _pScale;
	typename Inlet<Tout>::Ptr _pOffset;
	typename Outlet<Tout>::Ptr _pOutput;
};


template <typename T>
class Max: public Node
{
public:
	typedef Poco::AutoPtr<Max> Ptr;

	Max(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pInput(new Inlet<T>("input")),
		_pOutput(new Outlet<T>("output", scheduler)),
		_max(std::numeric_limits<T>::lowest())
	{
		addInlet(_pInput);
		addOutlet(_pOutput);
		
		_pInput->updated += Poco::delegate(this, &Max::update);
	}
	
	void update(const T& value)
	{
		if (value > _max)
		{
			_max = value;
			_pOutput->update(value);
		}
	}

private:
	typename Inlet<T>::Ptr _pInput;
	typename Outlet<T>::Ptr _pOutput;
	T _max;
};


template <typename T>
class Min: public Node
{
public:
	typedef Poco::AutoPtr<Min> Ptr;

	Min(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pInput(new Inlet<T>("input")),
		_pOutput(new Outlet<T>("output", scheduler)),
		_min(std::numeric_limits<T>::max())
	{
		addInlet(_pInput);
		addOutlet(_pOutput);
		
		_pInput->updated += Poco::delegate(this, &Min::update);
	}
	
	void update(const T& value)
	{
		if (value < _min)
		{
			_min = value;
			_pOutput->update(value);
		}
	}

private:
	typename Inlet<T>::Ptr _pInput;
	typename Outlet<T>::Ptr _pOutput;
	T _min;
};


template <typename T>
class Avg: public Node
{
public:
	typedef Poco::AutoPtr<Avg> Ptr;

	Avg(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pInput(new Inlet<T>("input")),
		_pOutput(new Outlet<T>("output", scheduler)),
		_samples(attrs.getIntAttribute("samples", 32))
	{
		addInlet(_pInput);
		addOutlet(_pOutput);
		
		_pInput->updated += Poco::delegate(this, &Avg::update);
	}
	
	void update(const T& value)
	{
		_values.push_back(value);
		if (_values.size() > _samples)
		{
			_values.pop_front();
		}
		T avg = 0;
		for (auto v: _values)
		{
			avg += v;
		}
		avg /= _values.size();
		_pOutput->update(avg);
	}

private:
	typename Inlet<T>::Ptr _pInput;
	typename Outlet<T>::Ptr _pOutput;
	int _samples;
	std::deque<T> _values;
};


template <typename T>
class Count: public Node
{
public:
	typedef Poco::AutoPtr<Count> Ptr;
	
	Count(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pTrigger(new Inlet<void>("trigger")),
		_pReset(new Inlet<void>("reset")),
		_pCounter(new Outlet<T>("counter", scheduler)),
		_counter(0)
	{
		addInlet(_pTrigger);
		addInlet(_pReset);
		addOutlet(_pCounter);
		
		_pTrigger->updated += Poco::delegate(this, &Count::trigger);
		_pReset->updated += Poco::delegate(this, &Count::reset);
	}
	
	void trigger()
	{
		_counter++;
		_pCounter->update(_counter);
	}
	
	void reset()
	{
		_counter = 0;
		_pCounter->update(_counter);
	}

private:
	typename Inlet<void>::Ptr _pTrigger;
	Inlet<void>::Ptr _pReset;
	typename Outlet<T>::Ptr _pCounter;
	Poco::UInt32 _counter;
};


template <typename T>
class Abs: public Node
{
public:
	typedef Poco::AutoPtr<Abs> Ptr;

	Abs(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pInput(new Inlet<T>("input")),
		_pOutput(new Outlet<T>("output", scheduler))
	{
		addInlet(_pInput);
		addOutlet(_pOutput);
		
		_pInput->updated += Poco::delegate(this, &Abs::update);
	}
	
	void update(const T& value)
	{
		_pOutput->update(std::abs(value));
	}

private:
	typename Inlet<T>::Ptr _pInput;
	typename Outlet<T>::Ptr _pOutput;
};


template <typename T>
class Delta: public Node
{
public:
	typedef Poco::AutoPtr<Delta> Ptr;

	Delta(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pInput(new Inlet<T>("input")),
		_pOutput(new Outlet<T>("output", scheduler)),
		_last(),
		_haveLast(false)
	{
		addInlet(_pInput);
		addOutlet(_pOutput);
		
		_pInput->updated += Poco::delegate(this, &Delta::update);
	}
	
	void update(const T& value)
	{
		if (!_haveLast)
		{
			_last = value;
			_haveLast = true;
		}
		else
		{
			T delta = value - _last;
			_last = value;
			_pOutput->update(delta);
		}
	}

private:
	typename Inlet<T>::Ptr _pInput;
	typename Outlet<T>::Ptr _pOutput;
	T _last;
	bool _haveLast;
};


template <typename T>
class Accumulate: public Node
{
public:
	typedef Poco::AutoPtr<Accumulate> Ptr;

	Accumulate(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pInput(new Inlet<T>("input")),
		_pReset(new Inlet<void>("reset")),
		_pOutput(new Outlet<T>("output", scheduler)),
		_sum()
	{
		addInlet(_pInput);
		addInlet(_pReset);
		addOutlet(_pOutput);
		
		_pInput->updated += Poco::delegate(this, &Accumulate::update);
		_pReset->updated += Poco::delegate(this, &Accumulate::reset);
	}
	
	void update(const T& value)
	{
		_sum += value;
		_pOutput->update(_sum);
	}
	
	void reset()
	{
		_sum = 0;
	}

private:
	typename Inlet<T>::Ptr _pInput;
	Inlet<void>::Ptr _pReset;
	typename Outlet<T>::Ptr _pOutput;
	T _sum;
};


} } } // namespace IoT::Dataflow::Engine


#endif // IoT_Dataflow_Engine_ComputationNodes_INCLUDED
