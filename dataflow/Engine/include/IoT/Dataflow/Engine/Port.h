//
// Port.h
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: Port
// Module:  Port
//
// Definition of the Port class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Engine_Port_INCLUDED
#define IoT_Dataflow_Engine_Port_INCLUDED


#include "IoT/Dataflow/Engine/Engine.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include <ostream>


namespace IoT {
namespace Dataflow {
namespace Engine {


class IoTDataflowEngine_API Port: public Poco::RefCountedObject
	/// Port is the base class for inlets and outlets.
{
public:
	typedef Poco::AutoPtr<Port> Ptr;

	Port(const std::string& name);
		/// Creates a Port with a given name.
	
	~Port();
		/// Destroys the Port.

	const std::string& name() const;
		/// Returns the name of the port.
		
	virtual void print(std::ostream& ostr) = 0;
		/// Writes the current value of the port to the given output stream.
	
	virtual const std::type_info& type() const = 0;
		/// Returns the type information for the port.

private:
	Port();
	Port(const Port&);
	Port& operator = (const Port&);

	std::string _name;
};


//
// inlines
//


inline const std::string& Port::name() const
{
	return _name;
}


} } } // namespace IoT::Dataflow::Engine


#endif // IoT_Dataflow_Engine_Port_INCLUDED
