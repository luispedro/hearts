#include "open_connections.h"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <string>

#include "constants.h"
#include "general/helper.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h> 


int open_client_connection(int argc,char* argv[])
{
	const char* address = local_address;
	for (int i = 0; i != argc; ++i)
	{
		if (std::string(argv[i]) == "--address")
		{
			address = argv[i + 1];
			if (!address)
			{
				std::cerr << " missing argument for --address.\n";
				return -connection_errors::no_address;
			}
		}
	}
	return open_client_connection(address);
}

	namespace {
		int open_client_local_connection(const char* address)
		{	
			int fd = socket(PF_LOCAL,SOCK_STREAM,0);
			if ( fd < 0 ) {
				std::cerr << "Error creating socket (local): " << strerror( errno ) << ".\n";
				return -connection_errors::unix_error;
			}
			sockaddr_un addr;
			memset(&addr,0,sizeof(addr));
			addr.sun_family = AF_LOCAL;
			strcpy(addr.sun_path,address);
			if (connect(fd,reinterpret_cast<sockaddr*>(&addr),sizeof(addr)) < 0)
			{
				if (errno == EINTR) return -connection_errors::interrupted;
				std::cerr << "Error opening the connection (local): " << strerror(errno) << ".\n";
				return -connection_errors::unix_error;
			}
			LOG_PLACE() << " opened local connection.\n";
			return fd;
		}


		int open_client_tcp_connection(const char* address, short port = tcp_port)
		{
			int fd = socket(PF_INET,SOCK_STREAM,0);
			if ( fd < 0 ) {
				std::cerr << "Error creating socket (local): " << strerror( errno ) << ".\n";
				return -connection_errors::unix_error;
			}
			sockaddr_in addr;
			memset(&addr,0,sizeof(addr));
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
			addr.sin_addr.s_addr = inet_addr(address);
			if (connect(fd,(sockaddr*)&addr,sizeof(addr)) < 0)
			{
				if (errno == EINTR) return -connection_errors::interrupted;
				std::cerr << " Error opening the connection (tcp): " << strerror(errno) << ".\n";
				return -connection_errors::unix_error;
			}	
			LOG_PLACE() << " connecting opened with fd = " << fd << ".\n";
			return fd;
		}
	}

int open_client_connection(const char* address)
{
	if (address[0] == '/') return open_client_local_connection(address);
	else return open_client_tcp_connection(address);
}

int open_client_connection(const char* address, short port ) { return open_client_tcp_connection( address, port ); }

