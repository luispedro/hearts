/***************************************************************************
                          Card.cc  -  description
                             -------------------
    begin                : Wed Dec 29 1999
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
 #include "card.h"
 #include "general/helper.h"
 #include <cctype>

  /**
    *
    * ostream& operator << (ostream&,Card);
    * istream& operator >> (istream&,Card&);
    * ostream& operator << (ostream&,Card::suit_t)
    *
    *  These functions write and read Cards. They are not supposed to be user friendly nor are they supposed to
    * to be used with anything other than debugging and internal Card passing. One simple way to pass Cards
    * through char* holes is to write the card to a strstream and read it back at the other end.
    * The last function is there to make debugging more readable.
    *
    */

//const Card Card::defaultCard;

std::ostream& operator << (std::ostream& out, Card c)
 {
        switch (c.suit())
        {
                case Card::clubs:
                        out << 'C';
                        break;
                case Card::spades:
                        out << 'S';
                        break;
                case Card::diamonds:
                        out << 'D';
                        break;
                case Card::hearts:
                        out << 'H';
                        break;
        }
        switch (c.value())
        {
                case Card::jack:
                        out << 'j';
                        break;
                case Card::queen:
                        out << 'q';
                        break;
                case Card::king:
                        out << 'k';
                        break;
                case Card::ace:
                        out << 'a';
                        break;
                default:
                        out << (static_cast<int>(c.value()) + 2);
                        break;
        }
        return out;
 }

std::istream& operator >> (std::istream& in, Card& ref)
 {
        if (!in) return in;

        Card::suit_t n;
        Card::value_t v;
        char c;
        in >> c;
        if (!in) return in;
        switch(c)
        {
              case 'C':
                      n = Card::clubs;
                       break;
                case 'S':
                        n = Card::spades;
                        break;
                case 'D':
                        n = Card::diamonds;
                        break;
                case 'H':
                        n = Card::hearts;
                        break;
                default:
                        in.putback(c);
                        in.setstate(std::ios::failbit);
                        return in;
        }

        switch(c = in.get())
        {
                case 'j':
                        v = Card::jack;
                        break;
                case     'q':
                        v = Card::queen;
                        break;
                case   'k':
                        v =  Card::king;
                        break;
                case   'a':
                        v = Card::ace;
                        break;
                case '1':
                {
                        char next = in.peek();
                        if (next == '0')
                        {
                                in.ignore();
                                v = Card::ten;
                        }
                        else
                        {
                                in.setstate(std::ios::failbit);
				return in;
                        }
                        break;
                }
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9': 
                        v = static_cast<Card::value_t>(Card::two + (c - '2'));
                        break;

                default:
                        if (in.eof()) return in;
                        in.setstate(std::ios::failbit);
                        return in;
        }
        ref = Card(n,v);
        return in;
 }



 std::ostream& operator << (std::ostream& out, Card::suit_t s)
 {
        switch (s)
        {
                #define SUIT(suit) \
                        case Card::suit: \
                                out << #suit; \
                                break;

                SUIT(spades)
                SUIT(hearts)
                SUIT(diamonds)
                SUIT(clubs)
                default:
                        massert(0);
        }
        return out;
 }

