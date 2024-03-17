//
// JWTValidator.h
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_JWT_JWTValidator_INCLUDED
#define OSP_JWT_JWTValidator_INCLUDED


#include "Poco/OSP/Web/TokenValidator.h"
#include "Poco/JWT/Signer.h"
#include "Poco/Logger.h"


namespace Poco {
namespace OSP {
namespace JWT {


class JWTValidator: public Poco::OSP::Web::TokenValidator
	/// A TokenValidator that validates JSON Web Tokens (JWTs).
{
public:
	using Ptr = Poco::AutoPtr<JWTValidator>;

	struct Config
	{
		std::set<std::string> algorithms;
		std::string hmacKey;
		std::string rsaPublicKey;
		std::string ecPublicKey;
		Poco::Timespan leeway;
		std::string issuer;
	};

	explicit JWTValidator(const Config& config);
		/// Creates the JWTValidator with the given configuration.

	~JWTValidator();
		/// Destroys the JWTValidator.

	// TokenValidator
	bool validateToken(const std::string& token, std::string& username, std::string& scope);

	static const std::string SERVICE_NAME;

protected:
	void configureSigner(const Config& config);

private:
	Poco::JWT::Signer _signer;
	Poco::Timespan _leeway;
	std::string _issuer;
	Poco::Logger& _logger;
};


} } } // namespace Poco::OSP::JWT


#endif // OSP_JWT_JWTValidator_INCLUDED
