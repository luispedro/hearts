/***************************************************************************
                          messagetranslator.cpp  -  description
                             -------------------
    begin                : Mon Sep 18 2000
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

#include "general/helper.h"
#include "translator.h"
#include "protocol.h"

#include <algorithm> // find
#include <strstream>

Translator::~Translator(){
        massert(read.empty());
}
/** This function gets a message from the internal buffer. It also removes this message. */
Message Translator::get() // throw(NotAvailable)
{
		assert(messageAvailable());
        Message res = read.front();
		LOG_PLACE() << " message popped: " << res.type() << " body = " << res.body() << ".\n";
        read.pop();
        return res;
}
/** This returns true if a message is available for reading */
bool Translator::messageAvailable() const
{
        return !read.empty();
}
/** This stores len bytes starting at data and attempts to translate them into Messages. If any extra data is fed into it, it is kept in a buffer.  */
void Translator::put(const std::vector<char>& data)
{
		buffer.reserve(buffer.size() + data.size());
        std::copy(data.begin(),data.end(),back_inserter(buffer));
		while (decode())
				;

}

bool Translator::decode()
{
		std::vector<char>::iterator last = find(buffer.begin(),buffer.end(),
						Protocol::terminator[0]);
		if (last == buffer.end()) return false;
		*last = '\0';
		Message res;
		std::istrstream in(&buffer[0],last - buffer.begin());
		std::string code;
		std::string rest;
		in >> code;
		getline(in,rest);
		Message::type_t type = Protocol::string2code(code);
		if (type == MessageTypes::Unknown) res = Message(type,&buffer[0]);
		else res = Message(type,rest);
		last = (last == buffer.end() ? last : last + 1);
		buffer.erase(buffer.begin(),last);
		read.push(res);
		return true;
}

