#include "database.h"
#include "options.h"

#include <iostream>
#include <cassert>


MYSQL* MySQLDatabase::connection_;

MySQLDatabase::MySQLDatabase()
{
	if ( !connection_ ) init();
}

void MySQLDatabase::init()
{
	assert( !connection_ );
	connection_ = new MYSQL;
	mysql_init( connection_ );
	if ( !mysql_real_connect( connection_,
		options->databaseHost().c_str(),
		options->databaseUser().c_str(),
		options->databasePassword().c_str(),
		options->databaseDb().c_str(),
		0, // port
		0, // socket
		0 ) // flags
			 ) {
		std::cerr << "MySQL error: "  << mysql_error( connection_ ) << std::endl;
		delete connection_;
		connection_ = 0;
	}
}

QCString MySQLDatabase::password( QString login )
{
	if ( !connection_ ) return QCString();
	std::string query = "select password from users where username = \'";
	query += login.utf8();
	query += "\'";
	std::cerr << "QUERY: \'" << query << "\'\n";
	if ( mysql_query( connection_, query.c_str() ) ) { 
		return QCString();
	}
	MYSQL_RES* mysqlres = mysql_store_result( connection_ );
	MYSQL_ROW row = mysql_fetch_row( mysqlres );
	QCString res;
	std::cerr << "PASSWORD: \'" << row[ 0 ] << "\'\n";
	if ( row ) res = QCString( row[ 0 ] );
	mysql_free_result( mysqlres );
	return res;
}

