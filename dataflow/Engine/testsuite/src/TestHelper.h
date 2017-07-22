//
// TestHelper.h
//
// $Id$
//
// Definition of the TestHelper functions.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TestHelper_INCLUDED
#define TestHelper_INCLUDED

#include "IoT/Dataflow/Engine/Node.h"
#include "IoT/Dataflow/Engine/Inlet.h"
#include "IoT/Dataflow/Engine/Outlet.h"
#include "Poco/Util/Timer.h"

using namespace IoT::Dataflow::Engine;


inline void Sleep(int milliseconds=10)
{
	Poco::Thread::sleep(milliseconds);
}

template <typename T>
Outlet<T>* defaultTest(Node* pNode, T first, T second)
{
	try
	{
		Outlet<T> outletFirst("first");
		outletFirst.set(first);
		Outlet<T> outletSecond("second");
		outletSecond.set(second);

		// set second first because of devision by zero e.g. with Div
		pNode->inlet("second")->connect(outletSecond);
		outletSecond.set(second);
		pNode->inlet("first")->connect(outletFirst);
		outletFirst.set(first);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}

	return (Outlet<T>*)(void*)pNode->outlet("result");
}

template <typename T>
Outlet<bool>* defaultTestBool(Node* pNode, T first, T second)
{
	try
	{
		return (Outlet<bool>*)defaultTest(pNode,first,second);

	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}

	return (Outlet<bool>*)(void*)pNode->outlet("result");
}


#endif // TestHelper_INCLUDED
