//
// CheckVatClient.cpp
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#include "CheckVat/CheckVatServiceClientHelper.h"
#include "Poco/RemotingNG/SOAP/TransportFactory.h"
#include <iostream>


int main(int argc, char** argv)
{
	try
	{
		// register transport
		Poco::RemotingNG::SOAP::TransportFactory::registerFactory();
		
		// get proxy for CheckVatService web service
		CheckVat::ICheckVatService::Ptr pVatService = CheckVat::CheckVatServiceClientHelper::find("http://ec.europa.eu/taxation_customs/vies/services/checkVatService", "soap");

		std::string countryCode;
		std::string vatNumber;
		Poco::DateTime dateTime;
		bool valid;
		Poco::Nullable<std::string> name;
		Poco::Nullable<std::string> address;
		
		// invoke web service
		pVatService->checkVat("AT", "U62417138", countryCode, vatNumber, dateTime, valid, name, address);
		
		std::cout << "countryCode: " << countryCode << std::endl;
		std::cout << "vatNumber:   " << vatNumber << std::endl;
		std::cout << "valid:       " << (valid ? "true" : "false") << std::endl;
		if (!name.isNull()) 
			std::cout << "name:        " << name.value() << std::endl;
		if (!address.isNull())
			std::cout << "address:     " << address.value() << std::endl; 
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
		return 1;
	}
	return 0;
}
