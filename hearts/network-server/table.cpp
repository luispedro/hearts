#include "table.h"
#include "player.h"
#include <cassert>
#include <algorithm>
#include <qtimer.h>

Table::Table( QObject* parent, QString name )
		:QObject( parent, name.ascii() ),
		 name_( name )
{
}

void Table::addPlayer( Player* p )
{
	assert( !full() );
	players_.push_back( p );
	connect( p, SIGNAL( destroyed( QObject* ) ),SLOT( removePlayer( QObject* ) ) );
	if ( full() ) QTimer::singleShot( 0, this, SLOT( delayedTableFull() ) );
}

void Table::delayedTableFull()
{
	if ( full() ) emit tableFull( this );
}

void Table::removePlayer( QObject* p )
{
	Player* pl  = static_cast<Player*>( p );
	assert( pl );
	removePlayer( pl );
}

void Table::removePlayer( Player* p )
{
	players_.erase( std::find( players_.begin(), players_.end(), p ) );
}

bool Table::full() const
{
	return players_.size() == 4;
}

Player* Table::player( int idx ) const
{
	if ( idx < 0 or idx >= players_.size() ) return 0;
	return players_[ idx ];
}

#include "table.moc"

