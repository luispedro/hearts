#include "database.h"
#include "options.h"

#include <iostream>

MySQLDatabase::MySQLDatabase()
{
	mysql_init( &connection_ );
	if ( !mysql_real_connect( &connection_,
		options->databaseHost().c_str(),
		options->databaseUser().c_str(),
		options->databasePassword().c_str(),
		options->databaseDb().c_str(),
		0, // port
		0, // socket
		0 ) // flags
			 ) {
		std::cerr << "MySQL error: "  << mysql_error( &connection_ );
	}
}

QCString MySQLDatabase::password( QString login )
{
	std::string query = "select password from users where login = \'";
	query += login.utf8();
	query += "\'";
	if ( mysql_query( &connection_, query.c_str() ) ) { 
		return QCString();
	}
	MYSQL_RES* mysqlres = mysql_store_result( &connection_ );
	MYSQL_ROW row = mysql_fetch_row( mysqlres );
	QCString res;
	if ( row ) res = QCString( row[ 0 ] );
	mysql_free_result( mysqlres );
	return res;
}

