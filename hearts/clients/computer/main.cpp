#include "computerplayer.h"
#include "options.h"
#include "general/utilitario.h"
#include "communication/open_connections.h"

#include <iostream>

int main(int argc, char* argv[]) {
	std::cerr << "HELLO\n";
	int fd = open_client_connection(argc,argv);
	Options::parse_args(argv);
	ComputerPlayer player(fd);
	while (Utility::Poll(player.get_pollfd(),Utility::Poll_Forever))
	{
		player.poll_success();
	}
}

