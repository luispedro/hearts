/***************************************************************************
                       messagetranslator.h  -  description
                          -------------------
 begin                : Mon Sep 18 2000
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

#ifndef MESSAGETRANSLATOR_H
#define MESSAGETRANSLATOR_H

#include "message.h"

#include <cstdlib>
#include <vector>
#include <queue>

/**This concrete class is used to transform an incoming char stream to an outgoing stream
    * of objects of type Message.
    *@author Luis Pedro Coelho
    */

class Translator
{
	public:
		~Translator();
		/** This stores len bytes starting at data and attempts to translate them into Messages. If any extra data is fed into it, it is kept in a buffer.  */
		void put( const std::vector<char>& );
		/** This returns true if a message is available for reading */
		bool messageAvailable() const ;
		/** This function gets a message from the internal buffer.
		* It also removes this message. 
		* It is an error to call this if (!messageAvailable())
		*/
		Message get
			() ; // throw(NotAvailable);
	private:    // Private attributes
		/** This tries to get a message from buffer and puts it into read.
		  * If one is found it returns true.
		  */
		bool decode();
		/** This is where read message are kept. */
		std::queue<Message> read;
		/** This is where 'half read' messages are kept. */
		std::vector<char> buffer;
};

#endif

