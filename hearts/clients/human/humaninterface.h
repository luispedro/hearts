/***************************************************************************
                       humaninterface.h  -  description
                          -------------------
 begin                : Thu Jan 27 2000
 copyright            : (C) 2000 by Luis Pedro Coelho
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

#ifndef HUMANINTERFACE_H
#define HUMANINTERFACE_H

#include "hearts/card.h"
#include "hand.h"
#include "tabledisplayer.h"
#include "hearts/deck.h"
#include "hearts/holder3.h"
#include "hearts/player_id.h"

#include <qwidget.h>
#include <qstatusbar.h>
#include <qpushbutton.h>
#include <qlabel.h>

#include <string>


/**
  *@author Luis Pedro Coelho
  */

class HumanInterface : public QWidget
{
		Q_OBJECT
	public:
		HumanInterface( QWidget *parent = 0, const char *name = 0 );
		~HumanInterface();

	public slots:    // Public slots
		/** Clears the playing table */
		void clearTable( player_id::type );
		/** Sets the status bar to display its arg */
		void setStatus( const QString& );
		/** This sets the Card of the player */
		void setCard( player_id::type who, Card which );

		void play();
		void choose3();

		void addCard( Card );
		void removeCard( Card );

		void setName( player_id::type who, QString name );


	signals:

		void played( Card );
		void chose( const Holder3& );


	protected:    // Protected methods
		virtual void resizeEvent( QResizeEvent* ev );

	private slots:    // Private slots
		/** This is used to implement choose(). Basically Hand's selected
		      signal is connected to this. This sets result to the card and valid_result to true. */
		void gotSelected( Card );
		/** This is connected to each of the CardDisplay's unselected signals. */
		void gotUnselected( Card );
		/** This is what the button is connected to. */
		void passCards();
		void gotClicked( Card );
		void moveTable();

		void adjustLabels();

	private:    // Private attributes

		/** This is to implement the move of the table to show who won. */
		struct move_info_type
		{
			static const int counter_init = 10;
			static const int offset[ counter_init ];
			int counter;
			int x; // 3 possibilities: -1, 0, 1
			int y;
		}
		move_info;

		TableDisplay* table;
		Hand* hand;
		std::vector<Card> cards;


		QStatusBar* status;
		/** This is where the player name is shown */
		QLabel* selfLabel;
		/** This is the name of the person on the right. */
		QLabel* rightLabel;
		/** This is the name of the person on the front. */
		QLabel* frontLabel;
		/** This is the button that appears when the user is asked to select three cards to pass. */
		QPushButton* pass;
		/** This is what keeps the result for choose3 */
		Holder3 result3;
		/** This is the name of the person on the left. */
		QLabel* leftLabel;
		/** This is to remember what we are doing. */
		enum { idle, play_wait, give3_wait } mode;
};

#endif
