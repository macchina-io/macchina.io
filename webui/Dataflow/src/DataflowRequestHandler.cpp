//
// DataflowRequestHandler.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "DataflowRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Util/PropertyFileConfiguration.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/Auth/AuthService.h"
#include "Poco/Zip/Compress.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DirectoryIterator.h"
#include "Poco/Format.h"
#include "Poco/AutoPtr.h"
#include "Poco/URI.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/DOM/NodeList.h"
#include "Poco/SAX/InputSource.h"
#include "Utility.h"
#include <sstream>
#include <fstream>
#include <map>
#include <iostream>

namespace IoT {
namespace Web {
namespace Dataflow {


const std::string DataflowRequestHandler::DATAFLOW_PROPERTIES("dataflow.properties");
Poco::FastMutex DataflowRequestHandler::_mutex;


DataflowRequestHandler::DataflowRequestHandler(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext),
	_graphDir(context()->persistentDirectory())
{
	Poco::Path p("graph/");
	_graphDir.append(p);
	p.makeDirectory();
	Poco::File f(_graphDir);
	if(!f.exists()) f.createDirectories();
}


void DataflowRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	Poco::OSP::Web::WebSession::Ptr pSession;
	{
		Poco::OSP::ServiceRef::Ptr pWebSessionManagerRef = context()->registry().findByName(Poco::OSP::Web::WebSessionManager::SERVICE_NAME);
		if (pWebSessionManagerRef)
		{
			Poco::OSP::Web::WebSessionManager::Ptr pWebSessionManager = pWebSessionManagerRef->castedInstance<Poco::OSP::Web::WebSessionManager>();
			pSession = pWebSessionManager->find(context()->thisBundle()->properties().getString("websession.id"), request);
		}
	}
	if (!Utility::isAuthenticated(pSession, response)) return;

	std::string username = pSession->getValue<std::string>("username");
	Poco::OSP::Auth::AuthService::Ptr pAuthService = Poco::OSP::ServiceFinder::findByName<Poco::OSP::Auth::AuthService>(context(), "osp.auth");

	if (!pAuthService->authorize(username, "bundleAdmin")) // FIXME: proper role auth
	{
		response.setContentLength(0);
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_FORBIDDEN);
		response.send();
		return;
	}

	Poco::Path p(Poco::URI(request.getURI()).getPath(), Poco::Path::PATH_UNIX);
	std::string action = p.getBaseName();
	std::string err;
	std::string file, xml;
	try
	{
		Poco::Net::HTMLForm form(request, request.stream());
		if (action == "list") // list files
		{
			FileList files = listFiles(_graphDir.toString());
			FileList::iterator it = files.begin();
			FileList::iterator end = files.end();
			std::string ret("{\"files\":[");
			if (it != end)
			{
				for (;;)
				{
					ret.append("{\"name\":").append(Utility::jsonize(it->_name)).
						append(",\"date\":").
						append(Utility::jsonize(Poco::DateTimeFormatter::format(it->_lastModified,
								Poco::DateTimeFormat::SORTABLE_FORMAT))).
						append(1, '}');
					if (++it == end) break;
					ret.append(1, ',');
				}
			}
			ret.append("]}");
			response.setContentType("application/json");
			response.setChunkedTransferEncoding(true);
			response.send() << ret;
			return;
		}
		else if (action == "open") // open file
		{
			std::string file(_graphDir.toString());
			std::string fname;
			if (!form.has("upfile"))
			{
				// check if file name is in the URI guery
				Poco::URI uri(request.getURI());
				typedef Poco::URI::QueryParameters QParams;
				QParams params = uri.getQueryParameters();
				QParams::const_iterator it = params.begin();
				QParams::const_iterator end = params.end();
				for (; it != end; ++it)
				{
					std::cout << it->first << ':' << it->second << std::endl;
					if (it->first == "upfile")
					{
						fname = it->second;
					}
				}
			}
			else
			{
				fname = form["upfile"];
				file.append(fname);
			}
			context()->logger().information("Open: " + file);
			Poco::FileInputStream fis(file);
			response.setContentType("text/html");
			response.setChunkedTransferEncoding(true);
			std::ostream& ros = response.send();
			ros << "<html>" << std::endl;
			ros << "<head>" << std::endl;
			ros << "</head>" << std::endl;
			ros << "<body>" << std::endl;
			ros << "<script type=\"text/javascript\">" << std::endl;

			std::ifstream f(file);
			std::string str((std::istreambuf_iterator<char>(f)),
				std::istreambuf_iterator<char>());
			Poco::URI::encode(str, "", xml);
			ros << "window.parent.openFile.setData(decodeURIComponent('" << xml << "'), '" << fname << "');";
			ros << "</script>" << std::endl;
			ros << "</body>" << std::endl;
			ros << "</html>" << std::endl;
			return;
		}
		else if (action == "save") // save file
		{
			if (form.has("filename") && form.has("xml"))
			{
				file = form["filename"];
				context()->logger().information("Save: " + file);
				Poco::URI::decode(form["xml"], xml, false);
				//context()->logger().debug("XML: " + xml);

				Poco::Path path = _graphDir;
				path.setFileName(file);

				saveDataflow(path, xml);

				Poco::FileOutputStream fos(path.toString(), std::ios_base::trunc);
				poco_assert (fos.good());
				fos << xml;
				response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
				response.send();
				return;
			}
			else
			{
				throw Poco::NotFoundException("Save requested but file name not found.");
			}
		}
	}
	catch (Poco::Exception& exc)
	{
		err = exc.displayText();
		context()->logger().error(err);
	}
	catch (std::exception& exc)
	{
		err = exc.what();
		context()->logger().error(err);
	}

	response.setContentType("application/json");
	response.setChunkedTransferEncoding(true);
	response.send() << "{\"error\":" << Utility::jsonize(err) << "}";
}


void DataflowRequestHandler::saveDataflow(const Poco::Path& path, const std::string& xml)
{
	std::istringstream istr(xml);
	Poco::XML::InputSource src(istr);
	try
	{
		Poco::XML::AutoPtr<Poco::XML::Document> pDFDoc = new Poco::XML::Document;
		Poco::XML::AutoPtr<Poco::XML::Element> pDataflow = pDFDoc->createElement("dataflow");
		pDFDoc->appendChild(pDataflow);

		Poco::XML::DOMParser parser;
		Poco::XML::AutoPtr<Poco::XML::Document> pMXDoc = parser.parse(&src);

		Poco::XML::NodeIterator it(pMXDoc, Poco::XML::NodeFilter::SHOW_ALL);
		Poco::XML::Node* pMXNode = it.nextNode();
		PortMap ports;
		NodeMap nodes;
		while (pMXNode)
		{
			Poco::XML::AutoPtr<Poco::XML::Element> pDFNode;
			Poco::XML::NamedNodeMap* pAttrs = pMXNode->attributes();
			if (pAttrs)
			{
				if (pMXNode->nodeName() == "object")
				{
					Poco::XML::Node* pAttr = pAttrs->getNamedItem("type");
					if (pAttr)
					{
						std::string type = pAttr->nodeValue();
						if (type == "node")
						{
							Poco::XML::Node* pName = pAttrs->getNamedItem("name");
							if (pName)
							{
								std::cout << "Found " << pAttr->nodeName() << ": " << pName->nodeValue() << std::endl;
								pDFNode = pDFDoc->createElement("node");
								pDFNode->setAttribute("id", pName->nodeValue());
								pAttr = pAttrs->getNamedItem("id");
								if (pAttr)
								{
									nodes[Poco::NumberParser::parse(pAttr->nodeValue())] = pName->nodeValue();
								}
								else
								{
									throw Poco::IllegalStateException("Node without id: " + pName->nodeValue());
								}
								pAttr = pAttrs->getNamedItem("nodeType");
								if (pAttr)
								{
									pDFNode->setAttribute("type", pAttr->nodeValue());
								}
								else
								{
									throw Poco::IllegalStateException("Node without dataflow type: " + pName->nodeValue());
								}
								// add any leftover attributes verbatim
								for (int i = 0; i < pAttrs->length(); ++i)
								{
									pAttr = pAttrs->item(i);
									if (pAttr && pAttr->nodeName() != "label"
											  && pAttr->nodeName() != "name"
											  && pAttr->nodeName() != "id"
											  && pAttr->nodeName() != "type"
											  && pAttr->nodeName() != "nodeType")
									{
										pDFNode->setAttribute(pAttr->nodeName(), pAttr->nodeValue());
									}
								}
								pDataflow->appendChild(pDFNode);
							}
							else
							{
								throw Poco::IllegalStateException("Node without a name detected.");
							}
						}
						else if(type == "inlet" || type == "outlet")
						{
							Port port;

							Poco::XML::Node* pA = pAttrs->getNamedItem("name");
							if (pA)
							{
								port._name = pA->nodeValue();
							}
							else
							{
								throw Poco::IllegalStateException("Port without a name detected.");
							}

							pA = pAttrs->getNamedItem("type");
							if (pA)
							{
								std::string portType = pA->nodeValue();
								if (portType == "inlet")
								{
									port._type = PORT_TYPE_INLET;
								}
								else if (portType == "outlet")
								{
									port._type = PORT_TYPE_OUTLET;
								}
								else
								{
									throw Poco::IllegalStateException("Port with unknown type (" +
										portType + ") detected.");
								}
							}
							else
							{
								throw Poco::IllegalStateException("Port without a type detected.");
							}

							pA = pAttrs->getNamedItem("id");
							if (pA)
							{
								port._id = Poco::NumberParser::parse(pA->nodeValue());
							}
							else
							{
								throw Poco::IllegalStateException("Port without an Id detected.");
							}

							Poco::XML::AutoPtr<Poco::XML::NodeList> pChildren = pMXNode->childNodes();
							if (pChildren)
							{
								for (int i = 0; i < pChildren->length(); ++i)
								{
									Poco::XML::Node* pChild = pChildren->item(i);
									if (pChild->nodeName() == "mxCell")
									{
										Poco::XML::NamedNodeMap* pAt = pChild->attributes();
										if (pAt)
										{
											pA = pAt->getNamedItem("parent");
											if (pA)
											{
												port._parentId = pA->nodeValue();
											}
											else
											{
												std::ostringstream os;
												os << "Port (id: " << port._id << ") without a parent Id detected.";
												throw Poco::IllegalStateException(os.str());
											}
										}
										else
										{
											std::ostringstream os;
											os << "Port (id: " << port._id << ") child without attributes detected.";
											throw Poco::IllegalStateException(os.str());
										}
										break;
									}
								}
							}
							else
							{
								throw Poco::IllegalStateException("Port without children detected.");
							}

							// optional datatype, defaults to empty string
							pA = pAttrs->getNamedItem("dataType");
							port._dataType = pA ? pA->nodeValue() : Poco::XML::XMLString("string");
							pA = pAttrs->getNamedItem("value");
							port._value = pA ? pA->nodeValue() : Poco::XML::XMLString();

							ports.insert(PortMap::value_type(port._id, port));
						}
						else if (type == "connection")
						{
							std::cout << "Found " << pAttr->nodeValue() << std::endl;
							Poco::XML::AutoPtr<Poco::XML::NodeList> pChildren = pMXNode->childNodes();
							if (pChildren)
							{
								for (int i = 0; i < pChildren->length(); ++i)
								{
									Poco::XML::Node* pChild = pChildren->item(i);
									if (pChild->nodeName() == "mxCell")
									{
										std::string id;
										Poco::XML::Node* pIdAttr = pAttrs->getNamedItem("id");
										if (pIdAttr)
										{
											id = pIdAttr->nodeValue();
										}
										Poco::XML::NamedNodeMap* pA = pChild->attributes();
										if (pA)
										{
											Poco::XML::Node* pSource = pA->getNamedItem("source");
											Poco::XML::Node* pTarget = pA->getNamedItem("target");
											if (!pSource || !pTarget)
											{
												context()->logger().warning("Connection without source or target detected, id: " + id);
											}
											else
											{
												// source/target are used as temporary values for from/to and
												// will be replaced with node/port later when ports are resolved,
												// where conection from/to are matched with ports parentIds
												pDFNode = pDFDoc->createElement("connection");
												pDFNode->setAttribute("from", pSource->nodeValue());
												pDFNode->setAttribute("outlet", "");
												pDFNode->setAttribute("to", pTarget->nodeValue());
												pDFNode->setAttribute("inlet", "");
												pDataflow->appendChild(pDFNode);
											}
										}
										else
										{
											throw Poco::IllegalStateException("Connection without attributes detected.");
										}
										break;
									}
								}
							}
							else
							{
								throw Poco::IllegalStateException("Connection object without children detected.");
							}
						}
						else
						{
							context()->logger().warning("Unknown object type: " + pAttr->nodeValue() + ", ignoring.");
						}
					}
				}
			}
			pMXNode = it.nextNode();
		}

		// additional pass - replace from/to with ports' parents names, and fill in ports names
		ConnectionFilter connectionFilter;
		Poco::XML::NodeIterator cIt(pDFDoc, Poco::XML::NodeFilter::SHOW_ALL, &connectionFilter);
		Poco::XML::Node* pCNode = cIt.nextNode();
		while (pCNode)
		{
			assignParentId(nodes, ports, pCNode, "from");
			assignParentId(nodes, ports, pCNode, "to");
			pCNode = cIt.nextNode();
		}

		Poco::FileOutputStream fos(Poco::replace(path.toString(), ".xml", ".dfl"), std::ios_base::trunc);
		poco_assert (fos.good());
		Poco::XML::DOMWriter writer;
		writer.writeNode(fos, pDFDoc);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}


void DataflowRequestHandler::assignParentId(const NodeMap& nodes, const PortMap& ports,
	Poco::XML::Node* pCNode, const std::string& name)
{
	Poco::XML::NamedNodeMap* pAttrs = pCNode->attributes();
	Poco::XML::Node* pAttr = pAttrs->getNamedItem(name);
	if (pAttr)
	{
		PortMap::const_iterator pmIt = ports.find(Poco::NumberParser::parse(pAttr->nodeValue()));
		if (pmIt != ports.end())
		{
			NodeMap::const_iterator nmIt = nodes.find(Poco::NumberParser::parse(pmIt->second._parentId));
			if (nmIt != nodes.end())
			{
				pAttr->setNodeValue(nmIt->second);
			}
			if (name == "from") pAttr = pAttrs->getNamedItem("outlet");
			else if (name == "to") pAttr = pAttrs->getNamedItem("inlet");
			pAttr->setNodeValue(pmIt->second._name);
		}
		else
		{
			throw Poco::IllegalStateException("Port " + pAttr->nodeValue() + " not found in ports map.");
		}
	}
	else
	{
		throw Poco::IllegalStateException("Connection object without '" + name + "' attribute detected.");
	}
}


std::string DataflowRequestHandler::lastFile(const std::string& dir)
{
	std::string file;
	Poco::DateTime last(1970, 1, 1);
	Poco::DirectoryIterator it(dir);
	Poco::DirectoryIterator end;
	while (it != end)
	{
		if (!it->isDirectory() && (it->getLastModified() > last.timestamp()))
		{
			file = Poco::Path(it->path()).getFileName();
			last = it->getLastModified();
		}
		++it;
	}
	return file;
}

DataflowRequestHandler::FileList DataflowRequestHandler::listFiles(const std::string& dir)
{
	FileList list;
	Poco::DirectoryIterator it(dir);
	Poco::DirectoryIterator end;
	while (it != end)
	{
		Poco::Path p(it->path());
		list.push_back({it->isDirectory(), it->canRead(), it->canWrite(),
			it->getLastModified(), p.getFileName()});
		++it;
	}
	return list;
}


void DataflowRequestHandler::handleExport(Poco::OSP::Bundle::Ptr pBundle, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
#if 0
	Poco::Net::HTMLForm form(request, request.stream());
	std::string name = form.get("name", "");
	std::string symbolicName = form.get("symbolicName", "");
	std::string version = form.get("version", "");
	std::string vendor = form.get("vendor", "");
	std::string copyright = form.get("copyright", "");
	
	if (name.empty() || symbolicName.empty() || version.empty() || 
	    symbolicName.find("..") != std::string::npos || 
	    version.find("..") != std::string::npos)
	{
		context()->logger().error(Poco::format(
			"Bundle export: bad form parameters submitted: name=\"%s\", symbolicName=\"%s\", version=\"%s\"", 
			name, symbolicName, version));
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
		response.setContentLength(0);
		response.send();
		return;
	}
	
	Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> pProps = new Poco::Util::PropertyFileConfiguration();
	pProps->setString("name", name);
	pProps->setString("symbolicName", symbolicName);
	pProps->setString("version", version);
	pProps->setString("vendor", vendor);
	pProps->setString("copyright", copyright);
	
	Poco::Path propsPath(pBundle->path());
	propsPath.makeDirectory();
	propsPath.setFileName(DATAFLOW_PROPERTIES);
	pProps->save(propsPath.toString());

	std::string bundleFileName(symbolicName);
	bundleFileName += "_";
	bundleFileName += version;
	bundleFileName += ".bndl";
	
	Poco::Path exportPath(context()->temporaryDirectory(), "export.bndl");
	Poco::File exportDir(exportPath.toString());
	if (exportDir.exists())
	{
		exportDir.remove(true);
	}
	
	exportDir.createDirectories();
	Poco::Path metaInfPath(exportPath, "META-INF");
	Poco::File metaInfDir(metaInfPath.toString());
	metaInfDir.createDirectories();
	
	Poco::Path manifestPath(metaInfPath, "manifest.mf");
	Poco::FileOutputStream manifestStream(manifestPath.toString());
	manifestStream 
		<< "Manifest-Version: 1.0\n"
		<< "Bundle-Name: " << name << "\n"
		<< "Bundle-SymbolicName: " << symbolicName << "\n"
		<< "Bundle-Version: " << version << "\n"
		<< "Bundle-Vendor: " << vendor << "\n"
		<< "Bundle-Copyright: " << copyright << "\n"
		<< "Bundle-RunLevel: 900\n"
		<< "Bundle-LazyStart: false\n";
	manifestStream.close();
/*
	Poco::Path extensionsPath(exportPath, "extensions.xml");
	Poco::FileOutputStream extensionsStream(extensionsPath.toString());
	extensionsStream
		<< "<extensions>\n"
		<< "\t<extension point=\"com.appinf.osp.js\" script=\"main.js\"/>\n"
		<< "</extensions>\n";
	extensionsStream.close();

	Poco::Path dataflowScriptPath(pBundle->path(), DATAFLOW_SCRIPT);
	Poco::FileInputStream dataflowScriptStream(dataflowScriptPath.toString());
	Poco::Path scriptPath(exportPath);
	scriptPath.makeDirectory();
	scriptPath.setFileName("main.js");
	Poco::FileOutputStream scriptStream(scriptPath.toString());
	Poco::StreamCopier::copyStream(dataflowScriptStream, scriptStream);
	scriptStream.close();
	dataflowScriptStream.close();
*/
	Poco::Path exportBndlPath(context()->temporaryDirectory(), bundleFileName);
	Poco::FileOutputStream exportBndlStream(exportBndlPath.toString());
	Poco::Zip::Compress compress(exportBndlStream, true);
	compress.addRecursive(exportPath.toString(), Poco::Zip::ZipCommon::CM_AUTO, Poco::Zip::ZipCommon::CL_MAXIMUM, true);
	compress.close();
	exportBndlStream.close();
	
	response.set("Content-Disposition", Poco::format("attachment; filename=%s", bundleFileName));
	response.sendFile(exportBndlPath.toString(), "application/octet-stream");
	
	try
	{
		exportDir.remove(true);
		Poco::File exportBndlFile(exportBndlPath.toString());
		exportBndlFile.remove();
	}
	catch (Poco::Exception& exc)
	{
		context()->logger().error(Poco::format("Error cleaning up after bundle export: %s", exc.displayText()));
	}
#endif
}


Poco::Net::HTTPRequestHandler* DataflowRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	return new DataflowRequestHandler(context());
}


} } } // namespace IoT::Web::Dataflow
