#include "typicalclient.h"

void TypicalClient::playreply_message(Card)
{
	server_message("Play Reply");
}

void TypicalClient::give3reply_message(const Holder3&)
{
	server_message("Give3 Reply");
}

void TypicalClient::namereply_message(std::string)
{
	server_message("Name Reply");
}



