#include "computerplayer.h"
#include "options.h"
#include "general/utilitario.h"
#include "communication/open_connections.h"

#include <iostream>
#include <unistd.h>

int main(int argc, char* argv[]) {
	std::cerr << "HELLO\n";
	int fd = open_client_connection(argc,argv);
	Options::parse_args(argv);
	if ( Options::send_zero() ) {
		char zero = 0;
		if ( write( fd, &zero, 1 ) < 0 ) {
			std::cerr << "Sending initial zero failed.\n";
			return 1;
		}
	}
	ComputerPlayer player(fd);
	while (Utility::Poll(player.get_pollfd(),Utility::Poll_Forever))
	{
		player.poll_success();
	}
}

