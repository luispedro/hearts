/***************************************************************************
                       error.h  -  description
                          -------------------
 begin                : Tue Apr 4 2000
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

#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <cstring>
#include <errno.h>

/**This is to be thrown as an exception and carries a message.
   * This allocates memory so don't use it as part of a out of memory thing. 
Rely on std::bad_alloc for that
   * @author Luis Pedro Coelho
  */

class Error
{
	public:
		/** Both constructors construct an encapsulation around its argument */
		Error( const char* m ) : message( m )
		{ }
		Error( std::string m ) : message( m )
		{ }
		virtual ~Error()
		{ }
		/** The error. */
		std::string what() const;
	protected:
		void setMessage( std::string newMsg )
		{
			message = newMsg;
		}
	private:
		std::string message;
};

class UnixError : public Error
{
	public:
		UnixError()
				: Error( strerror( errno ) )
		{ }
		explicit UnixError( std::string funcName )
				: Error( std::string( "Error in " ) + funcName + strerror( errno ) )
		{ }
		UnixError( std::string funcName, int err )
				: Error( std::string( "Error in " ) + funcName + strerror( err ) )
		{ }
}
;


#define EXCEPTION(CName,Message) \
	struct CName : Error { \
			explicit CName(std::string extra = ""):Error(std::string(Message) + extra) { } \
	};

#endif

