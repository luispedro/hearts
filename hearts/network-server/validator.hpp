
template <typename AuthClass, typename DatabaseClass>
bool AuthenticationValidator<AuthClass,DatabaseClass>::validate( QString name, QCString cookie, QCString result ) {
	QCString password = resolver_->password( name );
	char* should;
	authenticator_->generate( password, cookie, &should);
	bool res = result == should;
	std::free( should );
	return res;
}

