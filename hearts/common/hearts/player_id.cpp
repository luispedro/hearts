/***************************************************************************
                          playedby_t.cpp  -  description
                             -------------------
    begin                : Mon May 1 2000
    copyright            : (C) 2000 by Luis Pedro Coelho
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

 #include "player_id.h"
#include <string>

 std::istream& operator >> (std::istream& in, player_id::type& res)
 {
        std::string temp;
        in >> temp;
        #define CASE(x) else if (temp == #x){ res = player_id::x; }
        if (0) ;
        CASE(self)
        CASE(right)
        CASE(front)
        CASE(left)
        else { in.setstate(std::ios::failbit); }
        #undef CASE

        return in;
 }

 std::ostream& operator << (std::ostream& out, player_id::type obj)
 {
        #define CASE(x) else if (obj == player_id::x) { out  << #x; }
        if (0)  ;
        CASE(self)
        CASE(right)
        CASE(front)
        CASE(left)
        #undef CASE

        return out;
 }
