//
// XMLDataflow.cpp
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Dataflow/Engine/Dataflow.h"
#include "IoT/Dataflow/Engine/CoreNodeFactory.h"
#include "IoT/Dataflow/XML/Parser.h"
#include <iostream>
#include <fstream>


using namespace IoT::Dataflow::Engine;


template <typename T>
class Sensor: public Node
{
public:
	typedef Poco::AutoPtr<Sensor> Ptr;
	
	Sensor(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_value(attrs.getAttribute<T>("value", 0)),
		_pOutput(new Outlet<T>("output", scheduler))
	{
		addOutlet(_pOutput);
	}
	
	~Sensor()
	{
	}
	
	void update(T value)
	{
		_value = value;
		_pOutput->update(_value);
	}
	
private:
	T _value;
	typename Outlet<T>::Ptr _pOutput;
};


template <typename T>
class Output: public Node
{
public:
	Output(const std::string& id):
		Node(id),
		_pInput(new Inlet<T>("input"))
	{
		addInlet(_pInput);
		
		_pInput->updated += Poco::delegate(this, &Output::update);
	}
	
	void update(const T& value)
	{
		std::cout << this->id() << ": " << value << std::endl;
	}
	
private:
	typename Inlet<T>::Ptr _pInput;
};


class SampleNodeFactory: public CoreNodeFactory
{
public:
	SampleNodeFactory()
	{
	}
	
	Node::Ptr createNode(const std::string& type, const std::string& id, const AttributedObject& attrs, Scheduler& scheduler)
	{
		if (type == "sample.sensor")
			return new Sensor<double>(id, attrs, scheduler);
		else if (type == "sample.output")
			return new Output<double>(id);
		else
			return CoreNodeFactory::createNode(type, id, attrs, scheduler);
	}
};


int main(int argc, char** argv)
{
	if (argc < 2)	
	{
		std::cerr << "No dataflow XML file specified" << std::endl;
		return 1;
	}
	
	try
	{
		SampleNodeFactory nodeFactory;
		std::ifstream istr(argv[1]);
		IoT::Dataflow::XML::Parser parser(nodeFactory);
		
		Dataflow::Ptr pDataflow = parser.parse(istr);
		
		Node::Ptr pNode = pDataflow->findNode("sensor");
		Sensor<double>::Ptr pSensor;
		if (pNode)
		{
			pSensor = pNode.cast<Sensor<double>>();
		}
			
		pDataflow->start();
		if (pSensor)
		{
			for (int speed = 0; speed < 100; speed++)
			{
				pSensor->update(speed);
				Poco::Thread::sleep(50);
			}
			for (int speed = 100; speed >= 0; speed--)
			{
				pSensor->update(speed);
				Poco::Thread::sleep(50);
			}
		}
		Poco::Thread::sleep(10000);
		pDataflow->stop();
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
	
	return 0;
}
