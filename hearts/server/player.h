#ifndef DB_PLAYER_H_INCLUDE_GUARD_
#define DB_PLAYER_H_INCLUDE_GUARD_

/***************************************************************************
                          Player.h  -  description
                             -------------------
    begin                : Thu Dec 16 1999
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
 #include <string>
 #include <memory>

 #include "hearts/card.h"
 #include "hearts/holder3.h"
 #include "hearts/player_id.h"
 #include "hearts/player_status.h"

/** @short this is the basic player functions
  * This all works in an assyncrounous fashion. You call x_query() and a 
  * an answer is given when ready and x_reply is called on the receiver 
  * object associated with the player.
  */

 class Player
 {
        public:
			class Receiver;

            virtual ~Player();

		/** This sets the receiver for the answers. 
		  * A call to this erases the previous held object.
		  * It is a mistake to call any function before this is called, or if the current receiver is null
		  */ 
			void set_receiver(std::auto_ptr<Receiver>);

        /** very descriptive */
            virtual void play() = 0;

        /** This informs the player that attempt was an invalid move and has an english 
		  * error message in errorMsg. The choice to use an english message was deliberate since it is the
		  * players job to know how it should be translated if at all.
		  */
                virtual void invalidPlay(std::string errorMsg) = 0;

        /** This gives the player a card. This can either happen at the very begginning of the game as cards
          *     are distributed among players as when cards are passed between players.*/
                virtual void receive(Card) = 0;

        /** This asks the player to give 3 cards to pass to the side */
                virtual void give() = 0;


        /** This informs the player of a move made by some player.
          *     @param  by: can be self if it reports a move made by this player through play() */
                virtual void inform(Card,player_id::type by) = 0;


        /** A code describing the state of the game.
		  * A human-interface player will wish to translate this to a message 
		  * and show it to the human.
		  * A computer player will generally ignore this, except perhaps for the gameOver status.
		  */	
                 virtual void currentStatus(player_status::type) = 0;

  /** This sets the player in a stable initial position. May be called at any time.
    *     Might mean that the game was abruptly interrupted. Might be called right after creation in a
    *     post-constructor faction (this is not however the intended behaviour and child classes should not
    *     rely on this method being called after creation).
    */
                virtual void reset() = 0;

       protected:
			std::auto_ptr<Receiver> receiver;
};

class Player::Receiver 
{
	public:
		virtual void play_reply(Card) = 0;
		virtual void give_reply(const Holder3&) = 0;
};

#endif /* DB_PLAYER_H_INCLUDE_GUARD_ */

