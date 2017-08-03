//
// SimpleDataflow.cpp
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Dataflow/Engine/Dataflow.h"
#include "IoT/Dataflow/Engine/FlowNodes.h"
#include "IoT/Dataflow/Engine/ArithmeticNodes.h"
#include "IoT/Dataflow/Engine/ComputationNodes.h"
#include "IoT/Dataflow/Engine/LogicalNodes.h"
#include "IoT/Dataflow/Engine/RelationalNodes.h"
#include "IoT/Dataflow/Engine/TimingNodes.h"
#include <iostream>


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


int main(int argc, char** argv)
{
	Dataflow flow;
	AttributedObject attrs;
	
	try
	{
		Sensor<double>::Ptr pSpeedSensor = new Sensor<double>("speedSensor", attrs, flow.scheduler());
	
		Node::Ptr pSpeedOutput = new Output<double>("speedOutput");
		pSpeedOutput->inlet("input")->connect(*pSpeedSensor->outlet("output"));
		
		Node::Ptr pThreshOutput = new Output<bool>("threshOut");
		attrs.setAttribute("threshold", 50);
		Node::Ptr pThreshold = new Threshold<double>("thresh", attrs, flow.scheduler());
		pThreshOutput->inlet("input")->connect(*pThreshold->outlet("output"));
		pThreshold->inlet("input")->connect(*pSpeedSensor->outlet("output"));
		
		Node::Ptr pAvgOutput = new Output<double>("avgOut");
		attrs.clearAttributes();
		Node::Ptr pAvg = new Avg<double>("avg", attrs, flow.scheduler());
		pAvgOutput->inlet("input")->connect(*pAvg->outlet("output"));
		pAvg->inlet("input")->connect(*pSpeedSensor->outlet("output"));

		flow.start();
		for (int speed = 0; speed < 100; speed++)
		{
			pSpeedSensor->update(speed);
			Poco::Thread::sleep(50);
		}
		for (int speed = 100; speed >= 0; speed--)
		{
			pSpeedSensor->update(speed);
			Poco::Thread::sleep(50);
		}
		Poco::Thread::sleep(1000);
		flow.stop();
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}

	return 0;
}
