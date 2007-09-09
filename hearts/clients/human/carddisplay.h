/***************************************************************************
                       carddisplay.h  -  description
                          -------------------
 begin                : Tue Dec 28 1999
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

#ifndef CARDDISPLAY_H
#define CARDDISPLAY_H

#include "hearts/card.h"
#include <qwidget.h>
#include <qpixmap.h>
#include <map>

/** This is a QWidget which displays a Card object.
  * The cards are sto red in kde_datadir()/hearts/pics and are loaded on demand, but then kept on memory.
  *This helps to make the game loading fast. Images are shared between CardDisplay objects to keep memory
  * consumption low.
  *
  * There are two basic states to every card: selected and not-selected. The toggle between these is achieved with a
  * of the mouse upon the card. There is also a flag which regulates whether the card is selectable or not, through
  * clicks. Note that a CardDisplay is also selectable explicitably through the select and unselect members.
  *
  * CardDisplay objects emit three signals: a clicked(Card) signal which is emited every time a card is clicked on,
  * no matter what other signals may be emited too; a selected(Card) and a unselected(Card) signals whose names
  * are descriptive. N ote that these are emited indepent of whethe r the event occured due to a mouse click
  * (assuming a set selectable flag) or due to select()/unselect().
  *
  * As a QWidget, CardDisplay is unresizable. Its maximum an minimum sizes set to (cardWidth,cardHeight).
  *
  * Through the use of a (private) static special object, on program exit all of the allocated memory is disposed of.
  * There is no way (at the moment) of controlling this event.
  *
  *@author Luis Pedro Coelho
  */

class CardDisplay : public QWidget
{
		Q_OBJECT
	public:
		/** This construct an object which is not selected, not selectable and has the image of its first argument */
		CardDisplay( Card, QWidget *parent = 0, const char *name = 0 );

		/** This checks whether the card is selected */
		bool selected()
		{
			return isSelected;
		}
		bool selectable()
		{
			return isSelectable;
		}
		Card card() const
		{
			return ref;
		}

		static const int CardWidth;
		static const int CardHeight;

	public slots:
		/** It has no effect if the object is already selected.
		    * If it isn't, it turns the card to selected and emits the selected signal.
		    * A paintEvent is also triggered */
		void select();
		/** It has no effect if the object is already not selected.
		    * If it isn't, it turns the card to not selected and emits the unselected signal.
		    * A paintEvent is also triggered */
		void unselect();
		void setCard( Card );
		/**
 		 * Sets the selectable flag
 		 *
 		 * The actual selected flag is maintained.
 		 */
		void setSelectable( bool );
	signals:
		/** This is emited whenever the card is clicked upon with the mouse, no matter what else */
		void clicked( Card );
		/** This is emited when the card is selected either through a mouse click or through the select() member */
		void selected( Card );
		/** This is the opposite of the above. It gets emited whenever the display goes from selected to unselected. */
		void unselected( Card );

	protected:
		void mousePressEvent( QMouseEvent* );
		void repaint();
		void paintEvent( QPaintEvent* );

	private:
		typedef std::map<Card, QPixmap*> cache_t;
		static cache_t images;
		static cache_t selected_images;
		static cache_t::iterator load( Card );
		static cache_t::iterator load_selected( Card );
		static void unload_all();
		static QPixmap* get_image( Card );
		static QPixmap* get_selected_image( Card );

		struct cleaner
		{
			~cleaner()
			{
				CardDisplay::unload_all();
			}
		};
		friend struct cleaner;
		static cleaner cleaner_obj;

		Card ref;
		bool isSelected;
		bool isSelectable;

};

#endif
