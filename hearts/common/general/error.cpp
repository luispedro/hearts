/***************************************************************************
                          error.cpp  -  description
                             -------------------
    begin                : Thu Jul 27 2000
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

#include "error.h"

std::string Error::what() const 
{
        return message;
}


