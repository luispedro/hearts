/***************************************************************************
                          pointsbox.h  -  description
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
#include <qlayout.h>
#include <qguardedptr.h>
#include <qptrlist.h>
#include <kmainwindow.h>
#include <kdialogbase.h>

#include "hearts/player_id.h"

/**
  *@author Luis Pedro Coelho
  */

class PointsBoxWidget;
class QGrid;
class QLabel;

class PointsBox : public KDialogBase
{
        Q_OBJECT
        public:
                PointsBox(const char* name="");
                ~PointsBox();

        public slots:
                /** Clears all the results. */
                void clear();
		void insertLine( unsigned, unsigned, unsigned, unsigned );
		void setName(player_id::type,QString);

        private:
		QWidget* widget_;
		QGridLayout* layout_;
		QPtrList<QLabel> labels_;

		QLabel* selfLabel_;
		QLabel* rightLabel_;
		QLabel* frontLabel_;
		QLabel* leftLabel_;

		QGuardedPtr<QLabel> selfLastLabel_;
		QGuardedPtr<QLabel> rightLastLabel_;
		QGuardedPtr<QLabel> frontLastLabel_;
		QGuardedPtr<QLabel> leftLastLabel_;

};

#endif

