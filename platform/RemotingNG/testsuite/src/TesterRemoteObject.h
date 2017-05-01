//
// TesterRemoteObject.h
//
// Package: Generated
// Module:  TesterRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//


#ifndef TesterRemoteObject_INCLUDED
#define TesterRemoteObject_INCLUDED


#include "ITester.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


class TesterRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public ITester
{
public:
	typedef Poco::AutoPtr<TesterRemoteObject> Ptr;

	TesterRemoteObject();
		/// Creates a TesterRemoteObject.

	virtual ~TesterRemoteObject();
		/// Destroys the TesterRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& TesterRemoteObject::remoting__typeId() const
{
	return ITester::remoting__typeId();
}




#endif // TesterRemoteObject_INCLUDED

