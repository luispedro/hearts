#ifndef DB_DATABASE_H1067811020_INCLUDE_GUARD_
#define DB_DATABASE_H1067811020_INCLUDE_GUARD_

#include <qstring.h>
#include <mysql.h>

class Database
{
	public:
		virtual QCString password( QString login ) = 0;
};

class VeryStupidDatabase : public Database
{
	public:
		QCString password( QString )
		{
			return QCString( "fixed" );
		}
};


class MySQLDatabase : public Database
{
	public:
		MySQLDatabase();
		QCString password( QString login );

	private:
		static void init();
		static MYSQL* connection_;
};

#endif /* DB_DATABASE_H1067811020_INCLUDE_GUARD_ */
