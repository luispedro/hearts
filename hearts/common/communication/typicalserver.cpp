#include "typicalserver.h"


void TypicalServer::namequery_message()
{ 
	wrong_message("namequery"); 
} 

void TypicalServer::playquery_message()
{ 
	wrong_message("playquery"); 
} 

void TypicalServer::give3query_message()

{ 
	wrong_message("give3query"); 

} 

void TypicalServer::receive_message(Card)
{ 
	wrong_message("receive(Card)"); 
} 

void TypicalServer::inform_message(Card,player_id::type)
{ 
	wrong_message("inform"); 
}

void TypicalServer::invalidmove_message(std::string)
{ 
	wrong_message("invalidmove"); 
}

void TypicalServer::opponentname_message(player_id::type,std::string)
{
	wrong_message("opponentname");
}

void TypicalServer::status_message(player_status::type)
{
		wrong_message("status");
}

void TypicalServer::points_message(unsigned,unsigned,unsigned,unsigned)
{
		wrong_message("points");
}

void TypicalServer::inform_message(player_id::type,Card)
{
		wrong_message("inform");
}

