/***************************************************************************
                          computerplayerbase.h  -  description
                             -------------------
    begin                : Tue Oct 10 2000
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

#ifndef COMPUTERPLAYERBASE_H
#define COMPUTERPLAYERBASE_H

#include "hearts/card.h"
#include "hearts/player_id.h"
#include "hearts/table.h"
#include "hearts/holder3.h"

#include <vector>
#include <algorithm>
#include "general/helper.h"
#include "general/auto_init.h"

/**
        This is ComputerPlayer done right
        It provides a framework for computer players maintaining the basic information that is needed.
        If you derive from this, you should *only* override the private virtuals.

        It works like this:
                - This class does the accounting, you provide the intelligence.
                - There is internally a hand container which is accessed using the handIterator typedef
                        and handBegin, handEnd. Note that handIterator is const_iterator.
                - When something must be decided, one of the pure virtuals gets called and you make the decision.
                - You should use the protected functions to interrogate this object for information.

  *@author Luis Pedro Coelho
  */


class ComputerPlayerBase {
        public:
				virtual ~ComputerPlayerBase() { }

                /** Do not override. Thank you. */
                Card play();
                /** Remember to call this version if overridden */
                void inform(Card,player_id::type);
                /** Calls giveOne three times */
                Holder3 give();
                /** Logs the error and aborts */
                void invalidPlay(Card attempt, const char* errorMsg)
                        { LOG_PLACE() << errorMsg << ", for card = " << attempt << '\n'; massert(0); }
                /** Should not be overridden.
                        If it is, at least call this version. */
                void receive(Card c);
  /**  */
  				void reset();

				void hand_end();
  /** This is to identify the type in the config file */
				 virtual const char* type() const = 0;


        protected:
                typedef std::vector<Card>::const_iterator handIterator;
                handIterator handBegin() const { return hand.begin(); }
                handIterator handEnd() const { return hand.end(); }

                bool hasQueen() const { return hasQueen_; }
                bool hasHighSpades() const { return hasHighSpades_; }
                bool heartsPlayed() const { return heartsPlayed_; }
                bool queenOut() const { return queenOut_; }

                int suitPlayed(Card::suit_t t)  const { return suitInfo[t].played; }
                bool suitHasIt(Card::suit_t t)  const { return suitInfo[t].hasIt; }
                bool suitSkipped(Card::suit_t t)  const { return suitInfo[t].skipped; }
                bool suitSkippedAll(Card::suit_t t) const {return suitInfo[t].skippedAll; }

                Table currentTable() const { return table; }

                Card::suit_t push() const { return push_; }
                enum doingItAll_t
            { self = player_id::self, left = player_id::left, right = player_id::right, front = player_id::front, none = 5, impossible };

                doingItAll_t doingItAll() const;

                /** Not really necessary, but a nice feature to have, anyway.
                        It returns the highest card of a given suite or handEnd(), if the suite isn't available */
                handIterator highestOf(Card::suit_t) const;

        private:
                 class SuitInfo {
                        public:
                        SuitInfo(): played(0),
                                               skipped(false),
                                               skippedAll(false),
                                               hasIt(false) { }

                        void reset() { *this = SuitInfo(); }

                        short played;
                        bool skipped;
                        bool skippedAll;
                        bool hasIt;
                };
                Table table;
                std::vector<Card> hand;
                auto_init<bool> queenOut_;
                auto_init<bool> hasQueen_;
                auto_init<bool> heartsPlayed_;
                auto_init<bool> hasHighSpades_;
                auto_init<doingItAll_t,none> whoDoingItAll;
                Card::suit_t push_;

                SuitInfo suitInfo[4]; // the four suits

                virtual handIterator playAssist() = 0;
                virtual handIterator playNotAssist() = 0;
                virtual handIterator playStart() = 0;
                virtual handIterator giveOne() = 0;
                /** This informs that the hand is over. It is called at the end of the last public inform.
                        Notice that it is not a pure virtual. Default action is do nothing
                 */
                virtual void handIsOver() { }
  /** This removes the card pointed by its arg, which must not be handEnd().
			It makes sure that the invariants are maintained. */
				  Card remove(handIterator);
  /** This tries to check as many facts as possible. */
			  void assertInvariants();
};

#endif
