//
// LogicalNodes.h
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


#ifndef IoT_Dataflow_Engine_LogicalNodes_INCLUDED
#define IoT_Dataflow_Engine_LogicalNodes_INCLUDED


#include "IoT/Dataflow/Engine/Node.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


template <typename T>
class Not: public Node
{
public:
	typedef Poco::AutoPtr<Not> Ptr;

	Not(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pInput(new Inlet<T>("input")),
		_pOutput(new Outlet<bool>("output", scheduler))
	{
		addInlet(_pInput);
		addOutlet(_pOutput);
		
		_pInput->updated += Poco::delegate(this, &Not::update);
	}
	
	void update(const T& value)
	{
		_pOutput->update(!value);	
	}
	
private:
	typename Inlet<T>::Ptr _pInput;
	typename Outlet<T>::Ptr _pOutput;
};


template <typename T>
class And: public Node
{
public:
	typedef Poco::AutoPtr<And> Ptr;

	And(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pFirst(new Inlet<T>("first")),
		_pSecond(new Inlet<T>("second")),
		_pResult(new Outlet<bool>("result", scheduler))
	{
		addInlet(_pFirst);
		addInlet(_pSecond);
		addOutlet(_pResult);
		
		_pFirst->updated += Poco::delegate(this, &And::update);
		_pSecond->updated += Poco::delegate(this, &And::update);
	}
	
	void update(const T&)
	{
		bool result = _pFirst->value() && _pSecond->value();
		_pResult->update(result);	
	}
	
private:
	typename Inlet<T>::Ptr _pFirst;
	typename Inlet<T>::Ptr _pSecond;
	typename Outlet<T>::Ptr _pResult;
};


template <typename T>
class Or: public Node
{
public:
	typedef Poco::AutoPtr<Or> Ptr;

	Or(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pFirst(new Inlet<T>("first")),
		_pSecond(new Inlet<T>("second")),
		_pResult(new Outlet<bool>("result", scheduler))
	{
		addInlet(_pFirst);
		addInlet(_pSecond);
		addOutlet(_pResult);
		
		_pFirst->updated += Poco::delegate(this, &Or::update);
		_pSecond->updated += Poco::delegate(this, &Or::update);
	}
	
	void update(const T&)
	{
		bool result = _pFirst->value() || _pSecond->value();
		_pResult->update(result);	
	}
	
private:
	typename Inlet<T>::Ptr _pFirst;
	typename Inlet<T>::Ptr _pSecond;
	typename Outlet<T>::Ptr _pResult;
};


template <typename T>
class Xor: public Node
{
public:
	typedef Poco::AutoPtr<Xor> Ptr;

	Xor(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pFirst(new Inlet<T>("first")),
		_pSecond(new Inlet<T>("second")),
		_pResult(new Outlet<bool>("result", scheduler))
	{
		addInlet(_pFirst);
		addInlet(_pSecond);
		addOutlet(_pResult);
		
		_pFirst->updated += Poco::delegate(this, &Xor::update);
		_pSecond->updated += Poco::delegate(this, &Xor::update);
	}
	
	void update(const T&)
	{
		bool result = _pFirst->value() ^ _pSecond->value();
		_pResult->update(result);	
	}
	
private:
	typename Inlet<T>::Ptr _pFirst;
	typename Inlet<T>::Ptr _pSecond;
	typename Outlet<T>::Ptr _pResult;
};


} } } // namespace IoT::Dataflow::Engine


#endif // IoT_Dataflow_Engine_LogicalNodes_INCLUDED
