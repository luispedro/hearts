
/***************************************************************************
                          open.cpp  -  description
                             -------------------
    begin                : Qui Jul 20 20:14:12 WEST 2000
    copyright            : (C) 2000 by Luis Pedro Coelho
    email                : luis_pedro@netcabo.pt
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "server.h"
#include "options.h"
#include "general/error.h"
#include "communication/constants.h"
#include "id_to_fd.h"
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cerrno>
#include <cstdio>

void set_sock_options(int fd)
{		// FIXME: remove these options for a real, i.e. production version.
	linger lin;
	lin.l_onoff = 1;
	lin.l_linger = 0;
	setsockopt(fd,SOL_SOCKET,SO_LINGER,&lin,sizeof(lin));
}

void open_connections()
{ // FIXME: this code kind of sucks, and it is too trusting 
	int listen_tcp_fd = socket(PF_INET,SOCK_STREAM,0);
	{
		sockaddr_in addr;
		memset(&addr,0,sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(options->tcp_port() );
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		set_sock_options(listen_tcp_fd);
		if (bind(listen_tcp_fd,(sockaddr*)&addr,sizeof(addr)) < 0)
			std::cerr << "Error in bind: " << strerror(errno) << ".\n";
		listen(listen_tcp_fd,4);
	}
	int listen_local_fd = socket(PF_LOCAL,SOCK_STREAM,0);
	{	
		sockaddr_un addr;
		memset(&addr,0,sizeof(addr));
		addr.sun_family = AF_LOCAL;
		unlink(options->unix_address() );
		strcpy(addr.sun_path,options->unix_address() );
		if (bind(listen_local_fd,reinterpret_cast<sockaddr*>(&addr),sizeof(addr)) < 0)
			std::cerr << "Error in local bind: " << strerror(errno) << ".\n";
		else listen(listen_local_fd,4);
	}
	pollfd listen[2];
	memset(listen,0,sizeof(listen));
	enum { tcp, local };
	listen[tcp].fd = listen_tcp_fd;
	listen[tcp].events = POLLIN;
	listen[local].fd = listen_local_fd;
	listen[local].events = POLLIN;
	for (int i = 0; i != 4; ++i) 
	{
		union {
			sockaddr_in i;
			sockaddr_un u;
		} addr;
		int stat;
		do {
			stat = poll(listen,2,-1);
		} while (stat < 0);	
		int listen_fd = -1;
		if (listen[tcp].revents) listen_fd = listen_tcp_fd;
		else if (listen[local].revents) listen_fd = listen_local_fd;
		socklen_t s = sizeof(addr);
		int fd = accept(listen_fd,(sockaddr*)&addr,&s);
		register_fd(static_cast<player_id::type>(i),fd);
		set_sock_options(fd);
		LOG_PLACE() << " accepted " << i + 1 << " with fd = " << fd << ".\n";
	}
	close(listen_tcp_fd);
	close(listen_local_fd);
}

