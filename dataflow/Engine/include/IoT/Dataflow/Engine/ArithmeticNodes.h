//
// ArithmeticNodes.h
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: ArithmeticNodes
// Module:  ArithmeticNodes
//
// Definition of arithmetic node class templates.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Engine_ArithmeticNodes_INCLUDED
#define IoT_Dataflow_Engine_ArithmeticNodes_INCLUDED


#include "IoT/Dataflow/Engine/Node.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


template <typename T>
class Add: public Node
	/// This node adds the values from its two inlets
	/// and provides the result via its outlet.
{
public:
	typedef Poco::AutoPtr<Add> Ptr;

	Add(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pFirst(new Inlet<T>("first")),
		_pSecond(new Inlet<T>("second")),
		_pResult(new Outlet<T>("result", scheduler))
	{
		addInlet(_pFirst);
		addInlet(_pSecond);
		addOutlet(_pResult);
		
		_pFirst->updated += Poco::delegate(this, &Add::update);
		_pSecond->updated += Poco::delegate(this, &Add::update);
	}
	
	void update(const T&)
	{
		T result = _pFirst->value() + _pSecond->value();
		_pResult->update(result);	
	}
	
private:
	typename Inlet<T>::Ptr _pFirst;
	typename Inlet<T>::Ptr _pSecond;
	typename Outlet<T>::Ptr _pResult;
};


template <typename T>
class Sub: public Node
	/// This node subtracts the value from its second
	/// inlet from the value from its first inlet
	/// and provides the result via its outlet.
{
public:
	typedef Poco::AutoPtr<Sub> Ptr;

	Sub(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pFirst(new Inlet<T>("first")),
		_pSecond(new Inlet<T>("second")),
		_pResult(new Outlet<T>("result", scheduler))
	{
		addInlet(_pFirst);
		addInlet(_pSecond);
		addOutlet(_pResult);
		
		_pFirst->updated += Poco::delegate(this, &Sub::update);
		_pSecond->updated += Poco::delegate(this, &Sub::update);
	}
	
	void update(const T&)
	{
		T result = _pFirst->value() - _pSecond->value();
		_pResult->update(result);	
	}
	
private:
	typename Inlet<T>::Ptr _pFirst;
	typename Inlet<T>::Ptr _pSecond;
	typename Outlet<T>::Ptr _pResult;
};


template <typename T>
class Mul: public Node
	/// This node multiplies the value from its first
	/// inlet with the value from its second inlet
	/// and provides the result via its outlet.
{
public:
	typedef Poco::AutoPtr<Mul> Ptr;

	Mul(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pFirst(new Inlet<T>("first")),
		_pSecond(new Inlet<T>("second")),
		_pResult(new Outlet<T>("result", scheduler))
	{
		addInlet(_pFirst);
		addInlet(_pSecond);
		addOutlet(_pResult);
		
		_pFirst->updated += Poco::delegate(this, &Mul::update);
		_pSecond->updated += Poco::delegate(this, &Mul::update);
	}
	
	void update(const T&)
	{
		T result = _pFirst->value() * _pSecond->value();
		_pResult->update(result);	
	}
	
private:
	typename Inlet<T>::Ptr _pFirst;
	typename Inlet<T>::Ptr _pSecond;
	typename Outlet<T>::Ptr _pResult;
};


template <typename T>
class Div: public Node
	/// This node divides the value from its first
	/// inlet with the value from its second inlet
	/// and provides the result via its outlet.
{
public:
	typedef Poco::AutoPtr<Div> Ptr;

	Div(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pFirst(new Inlet<T>("first")),
		_pSecond(new Inlet<T>("second")),
		_pResult(new Outlet<T>("result", scheduler))
	{
		addInlet(_pFirst);
		addInlet(_pSecond);
		addOutlet(_pResult);
		
		_pFirst->updated += Poco::delegate(this, &Div::update);
		_pSecond->updated += Poco::delegate(this, &Div::update);
	}
	
	void update(const T&)
	{
		T result = _pFirst->value() / _pSecond->value();
		_pResult->update(result);	
	}
	
private:
	typename Inlet<T>::Ptr _pFirst;
	typename Inlet<T>::Ptr _pSecond;
	typename Outlet<T>::Ptr _pResult;
};


template <typename T>
class Mod: public Node
	/// This node divides the value from its first
	/// inlet with the value from its second inlet
	/// and provides the remainder via its outlet.
{
public:
	typedef Poco::AutoPtr<Mod> Ptr;

	Mod(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pFirst(new Inlet<T>("first")),
		_pSecond(new Inlet<T>("second")),
		_pResult(new Outlet<T>("result", scheduler))
	{
		addInlet(_pFirst);
		addInlet(_pSecond);
		addOutlet(_pResult);
		
		_pFirst->updated += Poco::delegate(this, &Mod::update);
		_pSecond->updated += Poco::delegate(this, &Mod::update);
	}
	
	void update(const T&)
	{
		T result = static_cast<long>(_pFirst->value()) % static_cast<long>(_pSecond->value());
		_pResult->update(result);	
	}
	
private:
	typename Inlet<T>::Ptr _pFirst;
	typename Inlet<T>::Ptr _pSecond;
	typename Outlet<T>::Ptr _pResult;
};


} } } // namespace IoT::Dataflow::Engine


#endif // IoT_Dataflow_Engine_ArithmeticNodes_INCLUDED
