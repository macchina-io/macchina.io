//
// JWTValidator.cpp
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "JWTValidator.h"
#include "Poco/JWT/Token.h"
#include <sstream>


using namespace std::string_literals;


namespace Poco {
namespace OSP {
namespace JWT {


const std::string JWTValidator::SERVICE_NAME("osp.jwt.validator");


JWTValidator::JWTValidator(const Config& config):
	_leeway(config.leeway),
	_issuer(config.issuer),
	_logger(Poco::Logger::get("JWTValidator"s))
{
	configureSigner(config);
}


JWTValidator::~JWTValidator()
{
}


bool JWTValidator::validateToken(const std::string& jwt, std::string& username, std::string& scope)
{
	try
	{
		Poco::JWT::Token token;
		if (_signer.tryVerify(jwt, token))
		{
			if (_issuer.empty() || token.getIssuer() == _issuer)
			{
				Poco::Timestamp bitEarlier;
				bitEarlier -= _leeway;
				if (token.getExpiration() >= bitEarlier)
				{
					Poco::Timestamp bitLater;
					bitLater += _leeway;
					if (token.getNotBefore() <= bitLater)
					{
						username = token.getSubject();
						scope = token.payload().optValue("scope"s, ""s);
						return true;
					}
				}
			}
		}
	}
	catch (Poco::Exception& exc)
	{
		_logger.log(exc);
	}
	return false;
}


void JWTValidator::configureSigner(const Config& config)
{
	_signer.setAlgorithms(config.algorithms);
	if (!config.hmacKey.empty())
	{
		_signer.setHMACKey(config.hmacKey);
	}
	if (!config.rsaPublicKey.empty())
	{
		std::istringstream publicKeyStream(config.rsaPublicKey);
		Poco::SharedPtr<Poco::Crypto::RSAKey> pKey = new Poco::Crypto::RSAKey(&publicKeyStream);
		_signer.setRSAKey(pKey);
	}
	if (!config.ecPublicKey.empty())
	{
		std::istringstream publicKeyStream(config.rsaPublicKey);
		Poco::SharedPtr<Poco::Crypto::ECKey> pKey = new Poco::Crypto::ECKey(&publicKeyStream);
		_signer.setECKey(pKey);
	}
}


} } } // namespace Poco::OSP::JWT
