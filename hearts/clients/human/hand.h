/***************************************************************************
			  hand.h  -  description
			     -------------------
    begin		: Thu Jan 27 2000
    copyright	    : (C) 2000 by Luis Pedro Coelho
    email		: luis@luispedro.org
 ***************************************************************************/

/***************************************************************************
 *									 *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.				   *
 *									 *
 ***************************************************************************/

#ifndef HAND_H
#define HAND_H

#include <qwidget.h>
#include "carddisplay.h"
#include "hearts/deck.h"
#include <vector>

/**
  *@author Luis Pedro Coelho
  */

class Hand : public QWidget  {
	Q_OBJECT
	public:
		Hand(QWidget *parent=0, const char *name=0);
		/** The name says it all. */
		void unselectAll();
		/** This call the homonimous method in all member CardDisplay objects */
		void setSelectable(bool);
	public slots:

		/** Sets the displayed hand. */
		void setHand(const Deck&);

	signals: // Signals
		/** Emited whenever a card gets clicked on, no matter what else happens */
		void clicked(Card);
		/** Gets emited everytime one of the displayed cards gets clicked upon */
		void selected(Card);
		/** This is emited whenever a card is unselected. */
		void unselected(Card);

	private: // Private attributes
		typedef std::vector<CardDisplay*> vector_type;
		vector_type displayers;

	private slots: // Private slots
		/** Every displayer has the clicked signal connected to this  */
		void gotClicked(Card);
		/** This is used for communication.
		Every displayer has its selected signal connected to this. 
		This emits our own selected signal */
		void got_selected(Card);
		/** This is used for communication. */
		void gotUnselected(Card);
};

#endif
