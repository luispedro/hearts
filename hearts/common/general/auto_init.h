#ifndef DB_AUTO_INIT_H_INCLUDE_GUARD_
#define DB_AUTO_INIT_H_INCLUDE_GUARD_

/***************************************************************************
                          auto_init.h  -  description
                             -------------------
    begin                : Mon Oct 23 2000
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


 template <typename T, T init = T()>
struct auto_init {
        auto_init():object(init) { }
        auto_init(const T& other):object(other) { }
        operator T& () { return object; }
        operator const T& () const { return object; }
        T& operator = (const T& other) { object = other; return object; }
		void reset() { object = init; }
        T object;
};



#endif /* DB_AUTO_INIT_H_INCLUDE_GUARD_ */
