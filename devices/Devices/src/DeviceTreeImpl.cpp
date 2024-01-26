//
// DeviceTreeImpl.cpp
//
// Library: IoT/Devices
// Package: Devices
// Module:  DeviceTree
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/DeviceTreeImpl.h"
#include "IoT/Devices/IComposite.h"
#include "IoT/Devices/IDevice.h"
#include "Poco/StringTokenizer.h"


using namespace std::string_literals;


namespace IoT {
namespace Devices {


DeviceTreeImpl::DeviceTreeImpl(const Poco::OSP::ServiceRegistry& registry):
	_registry(registry)
{
}


DeviceTreeImpl::~DeviceTreeImpl()
{
}


DeviceNode DeviceTreeImpl::deviceByPath(const std::string& path) const
{
	Poco::Optional<DeviceNode> optNode = findDeviceByPath(path);
	if (optNode.isSpecified())
		return optNode.value();
	else
		throw Poco::NotFoundException(path);
}


Poco::Optional<DeviceNode> DeviceTreeImpl::findDeviceByPath(const std::string& path) const
{
	if (path == "/" || path.empty())
	{
		return rootDevice();
	}
	else
	{
		Poco::StringTokenizer tok(path, "/"s, Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
		Poco::Optional<DeviceNode> optRoot = rootDevice();
		if (optRoot.isSpecified())
		{
			return findDevice(optRoot.value(), tok.begin(), tok.end());
		}
		else return optRoot;
	}
}


DeviceNode DeviceTreeImpl::deviceById(const std::string& id) const
{
	Poco::Optional<DeviceNode> optDevice = findDeviceById(id);
	if (optDevice.isSpecified())
		return optDevice.value();
	else
		throw Poco::NotFoundException(id);
}


Poco::Optional<DeviceNode> DeviceTreeImpl::findDeviceById(const std::string& id) const
{
	DeviceNode node;
	Poco::OSP::ServiceRef::Ptr pDeviceRef = _registry.findByName(id);
	if (pDeviceRef)
	{
		const std::string type = pDeviceRef->properties().get("io.macchina.device"s, ""s);
		const std::string name = pDeviceRef->properties().get("io.macchina.nodeName"s, ""s);
		node.composite = pDeviceRef->properties().get("io.macchina.composite"s, ""s);
		node.type = type;
		if (type == "io.macchina.composite")
		{
			IComposite::Ptr pComposite = pDeviceRef->castedInstance<IComposite>();
			node.id = pDeviceRef->name();
			if (name.empty())
			{
				node.name = pComposite->getPropertyString("name"s);
			}
			else
			{
				node.name = name;
			}
			node.fragments = pComposite->fragments();
			return node;
		}
		else if (!type.empty())
		{
			node.id = pDeviceRef->name();
			if (name.empty())
			{
				IDevice::Ptr pDevice = pDeviceRef->castedInstance<IDevice>();
				node.name = pDevice->getPropertyString("name"s);
			}
			else
			{
				node.name = name;
			}
			return node;
		}
		else throw Poco::InvalidAccessException("Service is not a device"s, id);
	}
	else return Poco::Optional<DeviceNode>();
}


Poco::Optional<DeviceNode> DeviceTreeImpl::rootDevice() const
{
	DeviceNode rootNode;
	Poco::OSP::ServiceRef::Ptr pRootRef = _registry.findByName("io.macchina.composite.root"s);
	if (pRootRef)
	{
		IComposite::Ptr pRoot = pRootRef->castedInstance<IComposite>();
		rootNode.id = pRootRef->name();
		rootNode.name = "/";
		rootNode.fragments = pRoot->fragments();
		return rootNode;
	}
	else return Poco::Optional<DeviceNode>();
}


Poco::Optional<DeviceNode> DeviceTreeImpl::findDevice(const DeviceNode& node, std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end) const
{
	if (begin == end)
	{
		return node;
	}
	else
	{
		const std::string& name = *begin;
		if (node.fragments.isSpecified())
		{
			const auto& fragments = node.fragments.value();
			for (const auto& fragment: fragments)
			{
				DeviceNode fragmentNode = deviceById(fragment);
				if (fragmentNode.name == name)
				{
					++begin;
					return findDevice(fragmentNode, begin, end);
				}
			}
		}
		return Poco::Optional<DeviceNode>();
	}
}


} } // namespace IoT::Devices
