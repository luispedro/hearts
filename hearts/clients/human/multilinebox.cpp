/***************************************************************************
                          multilinebox.cpp  -  description
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

#include "multilinebox.h"
#include "general/helper.h"
#include "general/widget_placement.h"

#include <qfontmetrics.h>
#include <kapp.h>
#include <klocale.h>

PointsBox::PointsBox(const char* name )
         : KMainWindow(0,name),
           text(new QMultiLineEdit(this)),
           Ok(new QPushButton(i18n("Close"),this)),
		   selfLabel(new QLabel(this,"self-points-label")),
		   rightLabel(new QLabel(this)),
		   frontLabel(new QLabel(this)),
		   leftLabel(new QLabel(this))
{
//        setFontPropagation(AllChildren);

		const int width = 140;
		selfLabel->move(10 + width * 0,10);
		rightLabel->move(10 + width * 1,10);
		frontLabel->move(10 + width * 2,10);
		leftLabel->move(10 + width * 3,10);
		
        text->setReadOnly(true);
        text->move(25,below(selfLabel) + 3);
        text->setBackgroundColor(QColor(200,200,200));

         connect(Ok,SIGNAL(clicked()),SLOT(hide()));
         QPaintEvent tmp(geometry());
         paintEvent(&tmp);
}
PointsBox::~PointsBox(){
}

void PointsBox::insertLine(const QString& str)
{
        text->insertLine(str);
        QPaintEvent tmp(geometry());
        paintEvent(&tmp);
}

void PointsBox::setName(player_id::type who, QString name)
{
		using namespace player_id;
		switch (who)
		{
				case self: selfLabel->setText(name); break;
				case right: rightLabel->setText(name); break;
				case front: frontLabel->setText(name); break;
				case left: leftLabel->setText(name); break;
				default: massert(0);
		}
}

void PointsBox::paintEvent(QPaintEvent* ev)
{
        KMainWindow::paintEvent(ev);
        const int font_height = QFontMetrics(this->font()).height() + 1;


        text->setGeometry(0,below(selfLabel) + 3,650,text->numLines() * font_height+4);
        Ok->setGeometry(340,text->y() + text->height()+10, 100, 25);
        resize(text->width()+ 50, text->height() + selfLabel->height() + Ok->height() + 40);
        text->show();
}

/** Clears all the displayed text. */
void PointsBox::clearText()
{
        text->clear();
}

#include "multilinebox.moc"
