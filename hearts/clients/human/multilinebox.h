/***************************************************************************
                          multilinebox.h  -  description
                             -------------------
    begin                : Fri Dec 31 1999
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

#ifndef MULTILINEBOX_H
#define MULTILINEBOX_H

#include <qwidget.h>
#include <qdialog.h>
#include <qmultilinedit.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <kmainwindow.h>

#include "hearts/player_id.h"

/**
  *@author Luis Pedro Coelho
  */

class PointsBox : public KMainWindow
{
        Q_OBJECT
        public:
                PointsBox(const char* name="");
                ~PointsBox();
                /** Clears all the displayed text. */
                void clearText();
        public slots:
		void insertLine( unsigned, unsigned, unsigned, unsigned );
		void setName(player_id::type,QString);

	private:
                void insertLine(const QString&);
        protected:
                virtual void paintEvent(QPaintEvent*);

        private:
                QMultiLineEdit* text;
                QPushButton* Ok;
                QLabel* selfLabel;
				QLabel* rightLabel;
				QLabel* frontLabel;
				QLabel* leftLabel;
};

#endif
