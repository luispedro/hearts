/***************************************************************************
			  hand.cpp  -  description
			     -------------------
    begin		: Thu Jan 27 2000
    copyright	    : (C) 2000 by Luis Pedro Coelho
    email		: luis.coelho@netc.pt
 ***************************************************************************/

/***************************************************************************
 *									 *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.				   *
 *									 *
 ***************************************************************************/

#include "general/helper.h"
#include "hand.h"

#include <algorithm>
#include <functional>

Hand::Hand(QWidget *parent, const char *name )
	: QWidget(parent,name)
{
}
/** Sets the displayed hand. */
void Hand::setHand(const Deck& hand)
{
	if (hand.empty())
	{
		std::for_each(displayers.begin(),displayers.end(),std::mem_fun(&CardDisplay::hide));
		setMinimumSize(0,0);
	}
	setMinimumSize(CardDisplay::CardWidth,CardDisplay::CardHeight);

	const int dist = 40; // hand.size() / (this->width() - CardDisplay::CardWidth);

//      LOG_PLACE() << '\n';
	// enlarge displayers if needed
	while (displayers.size() < hand.size())
	{
		displayers.push_back(new CardDisplay(Card(),this));
		connect(displayers.back(),SIGNAL(clicked(Card)),SLOT(gotClicked(Card)));
		connect(displayers.back(),SIGNAL(selected(Card)),SLOT(got_selected(Card)));
		connect(displayers.back(),SIGNAL(unselected(Card)),SLOT(gotUnselected(Card)));
	}
	
	// hide what you need to
	unsigned n = hand.size();
	while (n < displayers.size())
	{
		displayers[n]->hide();
		++n;
	}
	
	// finally set and show what is visible
	n = 0;
	while (n < hand.size())
	{
		displayers[n]->setCard(hand[n]);
		displayers[n]->show();
		displayers[n]->move(dist*n,0);
		++n;
	}
	this->resize(CardDisplay::CardWidth + 40 * hand.size(),CardDisplay::CardHeight);
}

/** This is used for communication.
Every displayer has its selected signal connected to this. 
This emits our own selected signal */
void Hand::got_selected(Card c)
{
	emit selected(c);
}
/** This is used for communication. */
void Hand::gotUnselected(Card c)
{
	emit unselected(c);
}
/** This call the homonimous method in all member CardDisplay objects */
void Hand::setSelectable(bool b)
{
	for (std::vector<CardDisplay*>::iterator it =displayers.begin(); it != displayers.end(); ++it)
	{
		(*it)->setSelectable(b);
	}
}

/** The name says it all. */
void Hand::unselectAll()
{
	std::for_each(displayers.begin(),displayers.end(),std::mem_fun(&CardDisplay::unselect));
}
/**  */
void Hand::gotClicked(Card c)
{
	emit clicked(c);
}

#include "hand.moc"
