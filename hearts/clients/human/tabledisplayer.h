/***************************************************************************
                          tabledisplayer.h  -  description
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

#ifndef TABLEDISPLAYER_H
#define TABLEDISPLAYER_H

#include "hearts/player_id.h"
#include <qwidget.h>
#include <carddisplay.h>
#include <vector>

/**
  *@author Luis Pedro Coelho
  */

class TableDisplay : public QWidget  {
        Q_OBJECT
        public:
                TableDisplay(QWidget *parent=0, const char *name=0);
                ~TableDisplay();

                /** The following are 'get' methods  */
                Card rightCard();
                Card selfCard();
                Card leftCard();
                Card frontCard();

        public slots: // Public slots

                /**  */
                void clear();
          /** This simply causes the card to be changed or displayed*/
                  void setCard(player_id::type who, Card which);
        private: // Private attributes

                /**  */
                CardDisplay* self;
                CardDisplay* right;
                CardDisplay* front;
                CardDisplay* left;
};

typedef TableDisplay TableDisplayer;

#endif
