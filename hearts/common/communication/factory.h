#ifndef DB_FACTORY_H_INCLUDE_GUARD_
#define DB_FACTORY_H_INCLUDE_GUARD_

#include <string>

#include "message.h"

#include "hearts/player_id.h"
#include "hearts/player_status.h"
#include "hearts/card.h"
#include "hearts/holder3.h"

namespace Factory
{
namespace Common
{
Message terminate( std::string );
Message ignored( Message );
}
namespace Server
{
Message version( unsigned, unsigned );
Message opponentname( std::string, player_id::type );

Message receive( Card );
Message status( player_status::type );
Message points( unsigned, unsigned, unsigned, unsigned );

Message give3query();
Message playquery();
Message namequery();
Message usingquery( int, int );
Message inform( Card, player_id::type );
Message invalidplay( std::string );
}

namespace Client
{
Message heartsclient();
Message namechange( std::string );

Message give3reply( Holder3 );
Message playreply( Card );
Message namereply( std::string );
Message usingreply( int, int );
}
}





#endif /* DB_FACTORY_H_INCLUDE_GUARD_ */
