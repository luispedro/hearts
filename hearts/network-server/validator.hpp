#include <kdebug.h>

template <typename AuthClass, typename DatabaseClass>
bool AuthenticationValidator<AuthClass,DatabaseClass>::validate( QString name, QCString cookie, QCString result ) {
	kdDebug() << "AuthenticationValidator<AuthClass,DatabaseClass>::validate( " << name 
		<< ", " << cookie << ", " << result << " )" << endl;
	QCString password = resolver_->password( name );
	if ( password.isNull() ) {
		std::cerr << "Error resolving password. Denying access.\n";
		return false;
	}
	char* should;
	authenticator_->generate( password, cookie, &should);
	bool res = ( result == should );
	std::free( should );
	return res;
}

