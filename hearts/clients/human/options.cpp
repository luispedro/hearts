#include "options.h"

#include "general/helper.h"

#include <cassert>
#include <kconfig.h>
#include <kglobal.h>

QString Options::playerName( player_id::type who )
{
	KConfig * c = KGlobal::config();
	const char* defaults[] = { "Calvin", "Hobbes", "LP Lapin", "Brigitte" };
	KConfigGroupSaver s( c, QString::fromLatin1( "player-names" ) );
	using namespace player_id;
	switch ( who ) {
#define CASE(x) case x: { QString tmp = c->readEntry(#x); \
						if (tmp.isNull()) { \
								c->writeEntry(#x,QString::fromLatin1(defaults[x]));\
								tmp = QString::fromLatin1(defaults[x]);\
						}\
					return tmp; }

		CASE( self )
		CASE( right )
		CASE( front )
		CASE( left )
#undef CASE
		default:
		massert( 0 );
	}
}

void Options::savePlayerName( player_id::type who, const QString& name )
{
	KConfig * kc = KGlobal::config();
	KConfigGroupSaver s( kc, QString::fromLatin1( "player-names" ) );
	if ( !name )
		LOG_PLACE() << " !name.\n";
	LOG_PLACE() << " saving " << who << " = " << ( const char* ) name << ".\n";
	switch ( who ) {
#define CASE(x) case player_id::x: kc->writeEntry(#x,name); break
		CASE( self );
		CASE( right );
		CASE( front );
		CASE( left );
	}
	LOG_PLACE_NL();
}


Options::Account::Account( const char* group )
{
	assert( group );
}

QString Options::Account::login() const
{
	KConfig* kc = KGlobal::config();
	KConfigGroupSaver s( kc, QString::fromLatin1( "network" ) );
	
	return kc->readEntry( "login", QString::null );
}

void Options::Account::saveLogin( const QString& name )
{
	KConfig* kc = KGlobal::config();
	KConfigGroupSaver s( kc, QString::fromLatin1( "network" ) );
	
	kc->writeEntry( "login", name );
}

QCString Options::Account::password() const
{
	KConfig* kc = KGlobal::config();
	KConfigGroupSaver s( kc, QString::fromLatin1( "network" ) );
	
	QString res = kc->readEntry( "password", QString::null );
	if ( res.isNull() ) return QCString();
	return res.utf8();
}

void Options::Account::savePassword( const QCString& pwd )
{
	KConfig* kc = KGlobal::config();
	KConfigGroupSaver s( kc, QString::fromLatin1( "network" ) );
	
	kc->writeEntry( "password", QString::fromUtf8( pwd ) );
}

const char* Options::Account::host() const
{
	return "hearts.luispedro.org";
}

short Options::Account::port() const
{
	return 1443;
}

Options::Account& Options::getNetwork() {
	static Options::Account account( "hearts.luispedro.org" );
	return account;
}

