#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <memory>
#include <qstring.h>

#include "database.h"

/** An API to validate a username/password combination */
class Validator {
	public:
		virtual ~Validator() { }
		virtual bool validate( QString username, QCString cookie, QCString result) = 0;
		virtual QCString cookie() const = 0;
		virtual const char* id() const = 0;
};

template <typename AuthClass, typename DatabaseClass>
class AuthenticationValidator : public Validator {
	public:
		AuthenticationValidator():authenticator_( new AuthClass ), resolver_( new DatabaseClass ) { }
		AuthenticationValidator( std::auto_ptr<Authenticator> auth ):authenticator_( auth ) { }
		QCString cookie() const { return authenticator_->generateCookie(); }

		const char* id() const { return authenticator_->id(); }
		
		bool validate( QString name, QCString cookie, QCString result );
	private:
		std::auto_ptr<Authenticator> authenticator_;
		std::auto_ptr<Database> resolver_;
};

#include "validator.hpp"

#endif // VALIDATOR_H

