#ifndef DB_AUTHENTICATION_H1067808401_INCLUDE_GUARD_
#define DB_AUTHENTICATION_H1067808401_INCLUDE_GUARD_

#include <qcstring.h>

class Authenticator {
	public:
		virtual ~Authenticator() { }
		virtual const char* id() = 0;
		virtual bool need_cookie() = 0;
		virtual int generate( const char* pass, const char* cookie, char** result ) = 0;
		virtual QCString generateCookie() = 0;
};

class repeatedMD5Authenticator : public Authenticator {
	public:
	const char* id() { return "md5(md5(pass)*md5(cookie))"; }
	bool need_cookie() { return true; }
	int generate( const char*, const char*, char** );
	QCString generateCookie();
};



#endif /* DB_AUTHENTICATION_H1067808401_INCLUDE_GUARD_ */
