/***************************************************************************
                          main.cpp  -  description
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
#include "open.h"
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


int main(int argc, char **argv)
{
	Options::init(argc,argv);
	if ( !all_registered() ) open_connections();
	Server serv;
	return serv.exec();
	srand(time(0));
}

