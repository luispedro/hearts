#include <qptrlist.h>
#include <qobjectlist.h>
#include <qobject.h>
#include <errno.h>
#include <unistd.h>

#include "server.h"

#include <general/helper.h>

#include <sys/types.h>
#include <sys/socket.h>


#include "network/constants.h"

#define HACK_PORT 9348

#include "player.h"
#include "table.h"

#define FOR_ALL( Type, Name,  Code ) \
{\
	QObjectList* objects = queryList( #Type ); \
		for ( QObject* cur = objects->first(); cur; cur = objects->next() ) \
		{ \
			Type* Name = static_cast<Type*>( cur ); \
				Code \
				; \
		} \
	delete objects; \
} \

#define FOR_ALL_PLAYERS( Code ) FOR_ALL( Player, player, Code )
#define FOR_ALL_TABLES( Code ) FOR_ALL( Table, table, Code )

	namespace {
		void set_sock_options(int fd)
		{		// FIXME: remove these options for a real, i.e. production version.
			linger lin;
			lin.l_onoff = 1;
			lin.l_linger = 0;
			setsockopt(fd,SOL_SOCKET,SO_LINGER,&lin,sizeof(lin));
		}
	}


Server::Server( QObject* parent )
	:QObject( parent ),
socket_()
{
	socket_.setSocketFlags( KExtendedSocket::passiveSocket | 
			KExtendedSocket::inetSocket |
			KExtendedSocket::streamSocket |
			KExtendedSocket::bufferedSocket);
	socket_.setPort( Network::Port );
	socket_.listen();
	socket_.enableRead( true );
	set_sock_options( socket_.fd() );
	connect( &socket_, SIGNAL( readyAccept() ), SLOT( acceptSlot() ) );
}

void Server::acceptSlot()
{
	KExtendedSocket* ext = 0;
	LOG_PLACE_NL();
	socket_.accept( ext );
	massert( ext );
	Player* p = new Player( this, ext );
	connect( p, SIGNAL( createTable( QString ) ), SLOT( createTable( QString ) ) );
	connect( p, SIGNAL( joinTable( QString ) ), SLOT( joinTable( QString ) ) );
	FOR_ALL_TABLES( p->lookAt( table ) );
}

void Server::joinTable( table_id tableName )
{
	LOG_PLACE_NL();
	Player* player = static_cast<Player*>( const_cast<QObject*>( sender() ) );

	LOG_PLACE() << " player " <<  player->name().ascii() << " joining " << tableName.ascii() << std::endl;

	//FIXME do not use QObject::sender !!

	Table* found = 0;
	FOR_ALL_TABLES( 
			LOG_PLACE() << " looking at table \'" << table->name().latin1() << "\'\n";
			if ( table->name() == tableName ) 
			{
			found = table;
			break;
			}
		)
	if ( found )
	{
		if ( player->table() ) player->table()->removePlayer( player );
		player->table( found );
		found->addPlayer( player );
		showTable( found );
	} else {
		LOG_PLACE() << " I did not find table \'" << tableName.ascii() << "\'\n";
	}
}

void Server::showTable( Table* table )
{
	LOG_PLACE_NL();
	FOR_ALL_PLAYERS( player->lookAt( table ) );
}


void Server::createTable( QString name )
{
	LOG_PLACE() << " creating table = " << name.ascii() << std::endl;
	Table* table = new Table( this, name );
	showTable( table );
	connect( table, SIGNAL( tableFull( Table* ) ), SLOT( tableFull( Table* ) ) );
}

void Server::tableFull( Table* table )
{
	LOG_PLACE_NL();
	int stat = fork();
	if ( stat < 0 )
	{
		LOG_PLACE() << "fork failed: " << strerror( errno ) << '\n';
	} else if ( stat == 0 ) {
		// child
		// FIXME: factor out
		char buf[ 64 ];
		char* cur = buf;
		strcpy( cur,"--fds=" );
		for ( int i = 0; i != 4; ++i )
		{
			table->player( i )->changeProtocol();
			while ( *cur ) ++cur;
			sprintf( cur, "%d,", table->player( i )->socket()->fd() );
			table->player( i )->socket()->enableRead( false );
		}
		bool goOn = false;
		do {
			goOn = false;
			for ( int i = 0; i != 4; ++i ) 
			{
				KExtendedSocket* socket = table->player( i )->socket();
				if ( socket->bytesToWrite() )
				{
					LOG_PLACE() << " i = " << i << " socket = " << socket << " bytesToWrite = " << socket->bytesToWrite() << '\n';
					goOn = true;
					socket->flush();
				}
			}
			sleep( 1 );
			LOG_PLACE_NL();
		} while ( goOn );
		for ( int i = 0; i != 4; ++i )
		{
			table->player( i )->socket()->release(); // DON'T CLOSE THE FD!
		}
		FOR_ALL_PLAYERS( delete player );
		FOR_ALL_TABLES( delete table ); // IMPORTANT: close the fds we don't need!
		execlp( "heartsserver","heartsserver",buf,"--wait-zero",( char* )0 );
		LOG_PLACE() << "Failed exec: " << strerror( errno ) << "\n\n";
		exit( 1 );
	} else {
		for ( int i = 0; i != 4; ++i )
		{
			table->player( 0 )->close(); // it is always zero, bc deleting a player removes it!
			delete table->player( 0 );
		}
		delete table;
	}
	LOG_PLACE_NL();
}


#include "server.moc"


