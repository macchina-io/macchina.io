//
// ExtensionPoint.h
//
// Library: OSP
// Package: ExtensionPointService
// Module:  ExtensionPoint
//
// Definition of the ExtensionPoint class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_ExtensionPoint_INCLUDED
#define OSP_ExtensionPoint_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/DOM/Element.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"


namespace Poco {
namespace OSP {


class OSP_API ExtensionPoint: public Poco::RefCountedObject
	/// An extension point allows a bundle to provide
	/// "hooks" that other bundles can hook into to
	/// extend a bundle's functionality.
	///
	/// A bundle registers one or more instances of
	/// subclasses of ExtensionPoint with the ExtensionPointService.
	/// The ExtensionPointService then looks for an
	/// "extensions.xml" file in every bundle that is started
	/// and calls the handleExtension() member function
	/// for every extension element targetted at
	/// the extension point.
	///
	/// When a bundle defining an extension is stopped,
	/// the ExtensionPoint's removeExtension() member function
	/// is invoked.
{
public:
	using Ptr = Poco::AutoPtr<ExtensionPoint>;
	using ConstPtr = const Ptr;

	virtual void handleExtension(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem) = 0;
		/// Handles the "extension" element in a bundle's
		/// "extensions.xml" configuration file.
		/// Must be overridden by subclasses.
		///
		/// The ExtensionPoint facility entirely leaves it
		/// to the ExtensionPoint subclass to define
		/// the content (child elements and attributes) of the
		/// extension element.
		/// The only required attribute on the "extension" element
		/// is the "point" attribute identifying the extension
		/// point (and thus the ExtensionPoint object handling
		/// the "extension" element.

	virtual void removeExtension(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem);
		/// Removes an extension from the extension point.
		///
		/// Usually this includes reverting actions, performed
		/// in handleExtension().
		///
		/// To keep compatibility with existing extension points,
		/// this member function is not pure virtual.

protected:
	ExtensionPoint();
		/// Creates the ExtensionPoint.

	~ExtensionPoint();
		/// Destroys the ExtensionPoint.
};


} } // namespace Poco::OSP


#endif // OSP_ExtensionPoint_INCLUDED
