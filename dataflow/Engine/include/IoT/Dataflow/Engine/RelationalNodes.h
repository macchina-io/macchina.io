//
// RelationalNodes.h
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: RelationalNodes
// Module:  RelationalNodes
//
// Definition of arithmetic node class templates.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Engine_RelationalNodes_INCLUDED
#define IoT_Dataflow_Engine_RelationalNodes_INCLUDED


#include "IoT/Dataflow/Engine/Node.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


template <typename T>
class GreaterThan: public Node
{
public:
	typedef Poco::AutoPtr<GreaterThan> Ptr;

	GreaterThan(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pFirst(new Inlet<T>("first")),
		_pSecond(new Inlet<T>("second")),
		_pResult(new Outlet<bool>("result", scheduler))
	{
		addInlet(_pFirst);
		addInlet(_pSecond);
		addOutlet(_pResult);
		
		_pFirst->updated += Poco::delegate(this, &GreaterThan::update);
		_pSecond->updated += Poco::delegate(this, &GreaterThan::update);
	}
	
	void update(const T&)
	{
		bool result = _pFirst->value() > _pSecond->value();
		_pResult->update(result);	
	}
	
private:
	typename Inlet<T>::Ptr _pFirst;
	typename Inlet<T>::Ptr _pSecond;
	Outlet<bool>::Ptr _pResult;
};


template <typename T>
class GreaterThanOrEqual: public Node
{
public:
	typedef Poco::AutoPtr<GreaterThanOrEqual> Ptr;

	GreaterThanOrEqual(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pFirst(new Inlet<T>("first")),
		_pSecond(new Inlet<T>("second")),
		_pResult(new Outlet<bool>("result", scheduler))
	{
		addInlet(_pFirst);
		addInlet(_pSecond);
		addOutlet(_pResult);
		
		_pFirst->updated += Poco::delegate(this, &GreaterThanOrEqual::update);
		_pSecond->updated += Poco::delegate(this, &GreaterThanOrEqual::update);
	}
	
	void update(const T&)
	{
		bool result = _pFirst->value() >= _pSecond->value();
		_pResult->update(result);	
	}
	
private:
	typename Inlet<T>::Ptr _pFirst;
	typename Inlet<T>::Ptr _pSecond;
	Outlet<bool>::Ptr _pResult;
};


template <typename T>
class LessThan: public Node
{
public:
	typedef Poco::AutoPtr<LessThan> Ptr;

	LessThan(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pFirst(new Inlet<T>("first")),
		_pSecond(new Inlet<T>("second")),
		_pResult(new Outlet<bool>("result", scheduler))
	{
		addInlet(_pFirst);
		addInlet(_pSecond);
		addOutlet(_pResult);
		
		_pFirst->updated += Poco::delegate(this, &LessThan::update);
		_pSecond->updated += Poco::delegate(this, &LessThan::update);
	}
	
	void update(const T&)
	{
		bool result = _pFirst->value() < _pSecond->value();
		_pResult->update(result);	
	}
	
private:
	typename Inlet<T>::Ptr _pFirst;
	typename Inlet<T>::Ptr _pSecond;
	Outlet<bool>::Ptr _pResult;
};


template <typename T>
class LessThanOrEqual: public Node
{
public:
	typedef Poco::AutoPtr<LessThanOrEqual> Ptr;

	LessThanOrEqual(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pFirst(new Inlet<T>("first")),
		_pSecond(new Inlet<T>("second")),
		_pResult(new Outlet<bool>("result", scheduler))
	{
		addInlet(_pFirst);
		addInlet(_pSecond);
		addOutlet(_pResult);
		
		_pFirst->updated += Poco::delegate(this, &LessThanOrEqual::update);
		_pSecond->updated += Poco::delegate(this, &LessThanOrEqual::update);
	}
	
	void update(const T&)
	{
		bool result = _pFirst->value() <= _pSecond->value();
		_pResult->update(result);	
	}
	
private:
	typename Inlet<T>::Ptr _pFirst;
	typename Inlet<T>::Ptr _pSecond;
	Outlet<bool>::Ptr _pResult;
};


template <typename T>
class Equal: public Node
{
public:
	typedef Poco::AutoPtr<Equal> Ptr;

	Equal(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pFirst(new Inlet<T>("first")),
		_pSecond(new Inlet<T>("second")),
		_pResult(new Outlet<bool>("result", scheduler))
	{
		addInlet(_pFirst);
		addInlet(_pSecond);
		addOutlet(_pResult);
		
		_pFirst->updated += Poco::delegate(this, &Equal::update);
		_pSecond->updated += Poco::delegate(this, &Equal::update);
	}
	
	void update(const T&)
	{
		bool result = _pFirst->value() == _pSecond->value();
		_pResult->update(result);	
	}
	
private:
	typename Inlet<T>::Ptr _pFirst;
	typename Inlet<T>::Ptr _pSecond;
	Outlet<bool>::Ptr _pResult;
};


template <typename T>
class NotEqual: public Node
{
public:
	typedef Poco::AutoPtr<NotEqual> Ptr;

	NotEqual(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pFirst(new Inlet<T>("first")),
		_pSecond(new Inlet<T>("second")),
		_pResult(new Outlet<bool>("result", scheduler))
	{
		addInlet(_pFirst);
		addInlet(_pSecond);
		addOutlet(_pResult);
		
		_pFirst->updated += Poco::delegate(this, &NotEqual::update);
		_pSecond->updated += Poco::delegate(this, &NotEqual::update);
	}
	
	void update(const T&)
	{
		bool result = _pFirst->value() != _pSecond->value();
		_pResult->update(result);	
	}
	
private:
	typename Inlet<T>::Ptr _pFirst;
	typename Inlet<T>::Ptr _pSecond;
	Outlet<bool>::Ptr _pResult;
};


} } } // namespace IoT::Dataflow::Engine


#endif // IoT_Dataflow_Engine_RelationalNodes_INCLUDED
