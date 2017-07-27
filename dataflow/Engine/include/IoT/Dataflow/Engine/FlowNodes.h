//
// FlowNodes.h
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: LogicalNodes
// Module:  LogicalNodes
//
// Definition of flow node class templates.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Engine_FlowNodes_INCLUDED
#define IoT_Dataflow_Engine_FlowNodes_INCLUDED


#include "Poco/Format.h"
#include "IoT/Dataflow/Engine/Node.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


template <typename T>
class Threshold: public Node
{
public:
	typedef Poco::AutoPtr<Threshold> Ptr;

	Threshold(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pInput(new Inlet<T>("input")),
		_pThreshold(new Inlet<T>("threshold", attrs.getAttribute<T>("threshold", 0))),
		_pOutput(new Outlet<bool>("output", scheduler))
	{
		addInlet(_pInput);
		addInlet(_pThreshold);
		addOutlet(_pOutput);
		
		_pInput->updated += Poco::delegate(this, &Threshold::update);
		_pThreshold->updated += Poco::delegate(this, &Threshold::update);
	}
	
	void update(const T& value)
	{
		bool output = _pInput->value() >= _pThreshold->value();
		_pOutput->update(output);
	}
	
private:
	typename Inlet<T>::Ptr _pInput;
	typename Inlet<T>::Ptr _pThreshold;
	Outlet<bool>::Ptr _pOutput;
};


template <typename T>
class Gate: public Node
{
public:
	typedef Poco::AutoPtr<Gate> Ptr;

	Gate(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pInput(new Inlet<T>("input")),
		_pOpen(new Inlet<bool>("open", attrs.getBoolAttribute("open", false))),
		_pOutput(new Outlet<T>("output", scheduler))
	{
		addInlet(_pInput);
		addInlet(_pOpen);
		addOutlet(_pOutput);
		
		_pInput->updated += Poco::delegate(this, &Gate::update);
		_pOpen->updated += Poco::delegate(this, &Gate::updateOpen);
	}
	
	void update(const T& value)
	{
		if (_pOpen->value())
		{
			_pOutput->update(_pInput->value());
		}
	}
	
	void updateOpen(const bool& value)
	{
		if (value)
		{
			_pOutput->update(_pInput->value());
		}
	}
	
private:
	typename Inlet<T>::Ptr _pInput;
	Inlet<bool>::Ptr _pOpen;
	typename Outlet<T>::Ptr _pOutput;
};


template <typename T>
class Splitter: public Node
{
public:
	typedef Poco::AutoPtr<Splitter> Ptr;

	Splitter(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pInput(new Inlet<T>("input"))
	{
		addInlet(_pInput);
		std::size_t numOutputs = attrs.getIntAttribute("numOutputs", 2);
		for (std::size_t i = 0; i < numOutputs; i++)
		{
			typename Outlet<T>::Ptr pOutlet = new Outlet<T>(Poco::format("outlet%z", i), scheduler);
			addOutlet(pOutlet);
			_outputs.push_back(pOutlet);
		}
		
		_pInput->updated += Poco::delegate(this, &Splitter::update);
	}
	
	void update(const T& value)
	{
		for (auto pOutput: _outputs)
		{
			pOutput->update(value);
		}
	}
	
private:
	typename Inlet<T>::Ptr _pInput;
	std::vector<typename Outlet<T>::Ptr> _outputs;
};


template <typename Tin, typename Tout>
class Cast: public Node
{
public:
	typedef Poco::AutoPtr<Cast> Ptr;

	Cast(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pInput(new Inlet<Tin>("input")),
		_pOutput(new Outlet<Tout>("output", scheduler))
	{
		addInlet(_pInput);
		addOutlet(_pOutput);
				
		_pInput->updated += Poco::delegate(this, &Cast::update);
	}
	
	void update(const Tin& value)
	{
		_pOutput->update(static_cast<Tout>(value));
	}
	
private:
	typename Inlet<Tin>::Ptr _pInput;
	typename Outlet<Tout>::Ptr _pOutput;
};


template <typename T>
class ChangeTrigger: public Node
{
public:
	typedef Poco::AutoPtr<ChangeTrigger> Ptr;

	ChangeTrigger(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pInput(new Inlet<T>("input")),
		_pOutput(new Outlet<void>("output", scheduler))
	{
		addInlet(_pInput);
		addOutlet(_pOutput);
				
		_pInput->updated += Poco::delegate(this, &ChangeTrigger::update);
	}
	
	void update(const T&)
	{
		_pOutput->update();
	}
	
private:
	typename Inlet<T>::Ptr _pInput;
	Outlet<void>::Ptr _pOutput;
};


} } } // namespace IoT::Dataflow::Engine


#endif // IoT_Dataflow_Engine_FlowNodes_INCLUDED
