/***************************************************************************
                          tabledisplay.cpp  -  description
                             -------------------
    begin                : Wed Jan 5 2000
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

#include <kapp.h>
#include "tabledisplayer.h"
#include "general/helper.h"



TableDisplay::TableDisplay(QWidget *parent, const char *name )
        : QWidget(parent,name),
        self(new CardDisplay(Card(),this)),
        right(new CardDisplay(Card(),this)),
        front(new CardDisplay(Card(),this)),
        left(new CardDisplay(Card(),this))
{
        self->setSelectable(false);
        right->setSelectable(false);
        front->setSelectable(false);
        left->setSelectable(false);

        left->move(0,60) ;
        self->move(CardDisplay::CardWidth + 15,CardDisplay::CardHeight + 15);
        front->move(CardDisplay::CardWidth + 15, 0);
        right->move(self->x() + CardDisplay::CardWidth + 15, left->y());

        setMinimumSize(right->x() + CardDisplay::CardWidth, self->y() + CardDisplay::CardHeight);
}

TableDisplay::~TableDisplay(){
}

void TableDisplay::clear()
{
        self->hide();
        right->hide();
        left->hide();
        front->hide();
//      LOG_PLACE() << '\n';
        QPaintEvent t(rect());
        paintEvent(&t);
}
/**  */
Card TableDisplay::frontCard(){
        return front->card();
}
/**  */
Card TableDisplay::leftCard(){
        return left->card();
}
/**  */
Card TableDisplay::selfCard(){
        return self->card();
}
/**  */
Card TableDisplay::rightCard(){
        return right->card();
}
/**  */
void TableDisplay::setCard(player_id::type who, Card which){

        #define CASE(x) \
                case player_id::x: \
                {       \
                        x->setCard(which);\
                         x->show();\
                          break;\
                }
        switch (who)
        {
                CASE(left)
                CASE(right)
                CASE(front)
                CASE(self)
                default:
                        massert(0);
        }
        #undef CASE

}


#include "tabledisplayer.moc"
