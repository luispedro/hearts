/***************************************************************************
                          message.h  -  description
                             -------------------
    begin                : Wed Apr 5 2000
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

#ifndef MESSAGE_H
#define MESSAGE_H

#include <map>

#include "error.h"
#include <string>
#include <iostream>


/** This is a namespace so that one can use it better (pun intended) */
namespace MessageTypes {
		enum type { 
				Name, 
				Opponentname, 
				Receive, 
    		    Invalidmove, 
				Inform, 
				Status, 
				Points, 
				Ignored, 
				NameQuery,
				NameReply,	
				PlayQuery,	
				PlayReply,
				Give3Query,
				Give3Reply,
		    	Terminate, 
				Reset,
				Unknown 
		};
		std::ostream& operator << (std::ostream&,type);
}

/** This is a value based class which only holds a pair which is the type and 
	* body of the message.
	*   TODO: change this to an opaque type. Only namespace Factory, Translator 
	* and Dispatch need to access the type and body of a message. It would be
	* very good if others could only construct and decode messages.
    *@author Luis Pedro Coelho
    */

using namespace std;

class Message {
        public:
                Message(MessageTypes::type typ, std::string);
                explicit Message(MessageTypes::type);
				Message():myType(MessageTypes::Unknown) { }

                typedef MessageTypes::type type_t;
                
				type_t type() const { return myType; }
                std::string body() const { return myRest; }

        /** This returns a string which may be constructed 
		 * when the function is called, in a lazy fashion */
        private:
                type_t myType;
                std::string myRest;
};

#endif
