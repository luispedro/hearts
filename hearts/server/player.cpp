/***************************************************************************
                     player.cpp  -  description
                        -------------------
begin                : Fri Dec 31 1999
copyright            : (C) 1999 by Luis Pedro Coelho
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

#include "player.h"
#include "general/helper.h"

Player::~Player()
{
	;
}

void Player::set_receiver( std::auto_ptr<Receiver> recv )
{
	LOG_PLACE_NL();
	receiver = recv;
}



