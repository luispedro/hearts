#ifndef DB_DATABASE_H1067811020_INCLUDE_GUARD_
#define DB_DATABASE_H1067811020_INCLUDE_GUARD_

#include <qstring.h>

class Database {
	public:
		virtual QCString password( QString name ) = 0;
};

class VeryStupidDatabase : public Database {
	public:
		QCString password( QString ) { return QCString( "fixed" ); }
};



#endif /* DB_DATABASE_H1067811020_INCLUDE_GUARD_ */
