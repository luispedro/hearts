/***************************************************************************
                          humaninterface.cpp  -  description
                             -------------------
    begin                : Thu Jan 27 2000
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

#include "humaninterface.h"
#include "general/helper.h"
#include "general/widget_placement.h"
#include "options.h"

#include <kapp.h>
#include <klocale.h>
#include <qtimer.h>

#include <unistd.h>

#include <cstdlib>
#include <algorithm>



HumanInterface::HumanInterface(QWidget *parent, const char *name )
        : QWidget(parent,name),
          table(new TableDisplay(this,"user interface table display")),
          hand(new Hand(this)),
          status(new QStatusBar(this,"User status bar")),
          selfLabel(new QLabel(Options::playerName(player_id::self),this)),
          rightLabel(new QLabel(Options::playerName(player_id::right),this)),
          frontLabel(new QLabel(Options::playerName(player_id::front),this)),
          pass(new QPushButton(i18n("Pass cards"),this,"passing button")),
          leftLabel(new QLabel("Calvin",this)),//(HumanClientOptions::options()->playerName(player_id::left),this)),
          mode(idle)
{
		const QColor table_green(40,160,40);
		setBackgroundColor(table_green);
		table->setBackgroundColor(table_green);
		hand->setBackgroundColor(table_green);
	    selfLabel->setBackgroundColor(table_green);
        leftLabel->setBackgroundColor(table_green);
        rightLabel->setBackgroundColor(table_green);
        frontLabel->setBackgroundColor(table_green);



        // table->move(75,below(frontLabel) + 5);

        hand->move(50, table->y() + table->height() + 10);
        hand->resize(CardDisplay::CardWidth + 40 * 12,CardDisplay::CardHeight);
        hand->setSelectable(false);

        table->clear();
        status->resize(width(),20);
        status->move(0,height() - status->height());
        status->message("");
        setMinimumSize(hand->width() + 10, 10 + frontLabel->height() + 10 
				                        + table->height() + 10
										+ status->height() + 10 
										+ hand->height() + 10); // the 10s are for spacing

        pass->move (width() - pass->width()  - 5, height() - status->height() - pass->height() - 5);
        pass->hide();

        connect(hand,SIGNAL(selected(Card)),SLOT(gotSelected(Card)));
        connect(hand,SIGNAL(unselected(Card)),SLOT(gotUnselected(Card)));
        connect(hand,SIGNAL(clicked(Card)),SLOT(gotClicked(Card)));
        connect(pass,SIGNAL(clicked()),SLOT(passCards()));

        LOG_PLACE() << " finished.\n";		
}

HumanInterface::~HumanInterface(){
}
/**  */
void HumanInterface::clearTable(player_id::type who)
{
        LOG_PLACE() << "who  = " << who << '\n';
		using namespace player_id;
		move_info.x = 0;
		move_info.y = 0;
		switch (who)
		{
				case self:
					move_info.y = 1;
					break;
				case right:
					move_info.x = 1;
					break;
				case front:
					move_info.y = -1;
					break;
				case left:
					move_info.x = -1;
					break;
		}
		
        move_info.counter = 10;
		moveTable();
}

void HumanInterface::moveTable()
{
		unsigned dist[10] = { 32, 32, 32, 32, 24, 24, 16, 8, 4, 2  };
		table->move(table->x() + dist[move_info.counter - 1] * move_info.x, table->y() + dist[move_info.counter - 1] * move_info.y);
		LOG_PLACE() << " counter = " << move_info.counter << " table->x() = " << table->x() << ".\n";
		--move_info.counter;
		if (move_info.counter) 
		{
				QTimer::singleShot(20,this,SLOT(moveTable()));
		}
		else 
		{ 
				table->clear(); 
				table->move(width() / 2 - table->width()/2, frontLabel->y() + frontLabel->height() + 5); 
		}
}

void HumanInterface::setStatus(const QString& m)
{
		status->message(m,1500);
}

void HumanInterface::setName(player_id::type who,QString name)
{
		switch (who)
		{
#define CASE(x) case player_id::x: x##Label->setText(name); break
				CASE(self);
				CASE(right);
				CASE(front);
				CASE(left);
#undef CASE
		}
		adjustLabels();
}


/*void HumanInterface::setHand(const Deck& newhand){
//        LOG_PLACE() << " with hand->x() = " << hand->x() << "; hand->y() = " << hand->y() << ".\n";
        hand->setHand(newhand);
}*/

/**  */
void HumanInterface::play()
{
		assert(mode == idle);
		mode = play_wait;
}
/** This is used to implement choose(). Basically Hand's selected
signal is connected to this. This sets result to the card and valid_result to true. */
void HumanInterface::gotSelected(Card c)
{
		assert (mode == give3_wait);
		assert (!result3.full());
		result3.push(c);
		if (result3.full())
		{
				hand->setSelectable(false);
				pass->show();
		}
}


void HumanInterface::resizeEvent(QResizeEvent* ev)
{
		using std::max;
		const int tableX = max(width() / 2 - table->width() / 2, 0);
		const int tableY = frontLabel->height() + frontLabel->y() + 5;
		const int handY = max(height() - status->height() - hand->height() - selfLabel->height() - 20, 0);
		const int handX = max(width() / 2 - (CardDisplay::CardWidth + 40* 12) / 2, 0);
		
		LOG_PLACE() << " handX = " << handX << ", handY = " << handY << ".\n";

		table->move (tableX,tableY);
		hand->move(handX,handY);
		selfLabel->move(width() / 2, height() - status->height() -  selfLabel->height() - 5);
		leftLabel->move(10, table->y() + table->height() / 2);
		rightLabel->move(width() - rightLabel->width() - 5, table->y() + table->height() / 2);
		frontLabel->move(width() / 2 - frontLabel->width() / 2, 25);

		QWidget::resizeEvent(ev);
		pass->move (width() - pass->width()  - 5, height() - status->height() - pass->height() - 5);
		status->setGeometry(0,height() - status->height(),width(),status->height());
}

/** This gets three cards from the player. */
void HumanInterface::choose3()
{
		LOG_PLACE_NL();
		mode = give3_wait;
		result3.clear();
		hand->setSelectable(true);
}
/** This is connected to each of the CardDisplay's unselected signals. */
void HumanInterface::gotUnselected(Card res)
{
		if (mode != give3_wait) return;
		const bool wasFull = result3.full();
	    result3.erase(res);
    	if (wasFull)
		{
    		 	pass->hide();
				hand->setSelectable(true);
		}
}
/**  */
void HumanInterface::gotClicked(Card c)
{
		if (mode == play_wait)
		{
				LOG_PLACE() << " playing " << c << ".\n";
				mode = idle;
				emit played(c);
		}
}

/** This is what the button is connected to. */
void HumanInterface::passCards()
{
		LOG_PLACE() << " passing " << result3 << ".\n";
    	LOG_PLACE() << " size = " << result3.vector().size() << ".\n";
		mode = idle;
		pass->hide();
		assert(result3.full());
		hand->unselectAll();
		hand->setSelectable(false);
		LOG_PLACE() << " size = " << result3.vector().size() << ".\n";
		emit chose(result3);
		for (int i = 0; i != 3; ++i) removeCard(result3.vector()[i]);
}
/** Causes the widget to redraw itself and it's child widget taking into account the current options.
	This is to be called after the options have changed.
void HumanInterface::refresh()
{
	#define SET_LABEL(x)
		SET_LABEL(self)
		SET_LABEL(right)
		SET_LABEL(front)
		SET_LABEL(left)
	#undef SET_LABEL
} */

/** This sets the Card of the player */
void HumanInterface::setCard(player_id::type who, Card which)
{
		table->setCard(who,which);
}


void HumanInterface::addCard(Card c)
{
		cards.push_back(c);
		std::sort(cards.begin(),cards.end());
		hand->setHand(cards);
}

void HumanInterface::removeCard(Card c)
{
		cards.erase(std::find(cards.begin(),cards.end(),c));
		hand->setHand(cards);
}

void HumanInterface::adjustLabels()
{
		adjust_size(selfLabel);
		adjust_size(rightLabel);
		adjust_size(frontLabel);
		adjust_size(leftLabel);

        selfLabel->move(width() / 2 - selfLabel->width() / 2, height() - status->height() -  selfLabel->height() - 5);
        leftLabel->move(10, table->y() + table->height() / 2);
        rightLabel->move(width() - rightLabel->width() - 5, table->y() + table->height() / 2);
        frontLabel->move(width() / 2 - frontLabel->width() / 2, 25);
}

#include "humaninterface.moc"
