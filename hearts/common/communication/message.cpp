/***************************************************************************
                     message.cpp  -  description
                        -------------------
begin                : Wed Apr 5 2000
copyright            : (C) 2000 by Luis Pedro Coelho
email                : luis@luispedro.org
***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "message.h"
#include "general/helper.h"
#include "protocol.h"
#include <string>
#include <cstring>
#include <errno.h>
#include <iostream>

Message::Message( MessageTypes::type typ, string m )
		: myType( typ ),
		myRest( m )
{}

Message::Message( MessageTypes::type typ )
		: myType( typ )
{}

ostream& MessageTypes::operator << ( ostream& out, MessageTypes::type t )
{
	return out << Protocol::encode( Message( t ) );
}
