/***************************************************************************
                          Table.cpp  -  description
                             -------------------
    begin                : Sun Dec 19 1999
    copyright            : (C) 1999 by Luis Pedro Coelho
    email                : luis.coelho@netc.pt
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

 #include "table.h"

 unsigned winner(const Table& tab) throw()
 {
        Card::suit_t pushed = tab.push();
        unsigned res = 0;
        const std::vector<Card>& played = tab.state();
        for (unsigned i = 1; i < played.size(); ++i)
        {
                if (played[i].suit() == pushed && played[i].value() > played[res].value()) res = i;
        }

        return res;
 }
