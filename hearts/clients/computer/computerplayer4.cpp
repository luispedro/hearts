/***************************************************************************
                     computerplayer4.cpp  -  description
                        -------------------
begin                : Tue Oct 17 2000
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

#include "computerplayer4.h"
#include "hearts/cards.h"

/** The code in this file was done taking computerplayer3_2.cpp as a basis */

namespace
{
inline bool byValue( Card a, Card b )
{
	return a.value() < b.value();
}
}



ComputerPlayerBase::handIterator ComputerPlayer4::playAssist()
{
	const std::vector<Card> tableState = currentTable().state();
	if ( push() == Card::spades ) {
		if ( hasQueen() ) {
			if ( std::find ( tableState.begin(), tableState.end(), Cards::spadesKing ) != tableState.end() or
					std::find ( tableState.begin(), tableState.end(), Cards::spadesAce ) != tableState.end() ) {
				LOG_PLACE() << " playing the queen, s.o. will get it.\n";
				return std::find( handBegin(), handEnd(), Cards::spadesQueen );
			}
			handIterator res = std::find_if ( handBegin(), handEnd(), OfSuite( Card::spades ) );
			if ( res->value() == Card::queen ) {
				handIterator next = res;
				++next; // This is better than doing a (res + 1)->suit() == Card::spades
				if ( next != handEnd() and next->suit() == Card::spades ) {
					LOG_PLACE() << " I have the queen, but I can still play a high spade.\n";
					return next;
				}
				//                                LOG_PLACE() << " I am forced to play the queen. I will probably get to keep it.\n";
				return res;
			}
			while ( res->value() != Card::queen )
				++res;
			--res;
			return res;
		}
		if ( hasHighSpades() ) {
			LOG_PLACE() << " I have high spades (but not the queen).\n";
			if ( tableState.size() == 3 and
					std::find ( tableState.begin(), tableState.end(), Cards::spadesQueen ) == tableState.end() ) {
				LOG_PLACE() << " Since this is the last card of hand, I'm getting rid of a high spade.\n";
				return highestOf( Card::spades );
			}
			handIterator res = std::find_if ( handBegin(), handEnd(), OfSuite( Card::spades ) );
			if ( res->value() == Card::ace or res->value() == Card::king ) {
				LOG_PLACE() << " All I have is high spades.\n";
				return res;
			}
			while ( res->value() < Card::king )
				++res;
			--res;
			return res;
		}
		LOG_PLACE() << " playing my highest spade.\n";
		return highestOf( Card::spades );
	}

	std::vector<Card> tmp = tableState;
	std::sort( tmp.begin(), tmp.end(), byValue );
	Card highestOnTable = tmp.back();

	if ( push() == Card::hearts ) {
		LOG_PLACE() << " hearts on the table, I'll try not to win.\n";
		handIterator res = find_if( handBegin(), handEnd(), OfSuite( Card::hearts ) );
		if ( res->value () > highestOnTable.value() ) {
			if ( tableState.size() == 3 ) { // we're gonna get it anyway
				return highestOf( Card::hearts );
			}
			if ( tableState.size() == 2 and res->value() > highestOnTable.value() + 3 ) { // we'd probably get it anyway
				return highestOf( Card::hearts );
			}
			return res;
		}
		while ( res != handEnd() and res->value() < highestOnTable.value() )
			++res;
		--res;
		return res;
	}

	if ( suitPlayed( push() ) < 2 ) {
		if ( std::find ( tableState.begin(), tableState.end(), Cards::spadesQueen ) == tableState.end() ) {
			LOG_PLACE() << " the queen isn't on the table, so I might just play high.\n";
			return highestOf( push() );
		}
	}

	if ( tableState.size() == 3 and
			std::find ( tableState.begin(), tableState.end(), Cards::spadesQueen ) == tableState.end() ) {
		return highestOf( push() );
	}

	// play highest of suit which doesn't win

	handIterator res = std::find_if( handBegin(), handEnd(), OfSuite( push() ) );
	if ( res->value() > highestOnTable.value() )
		return res;

	while ( ( res + 1 ) != handEnd() and
			( res + 1 ) ->suit() == push() and
			( res + 1 ) ->value() < highestOnTable.value() ) {
		++res; // res = res + 1;
	}
	return res;
}


/**  */
ComputerPlayerBase::handIterator ComputerPlayer4::playNotAssist()
{
	if ( handEnd() - handBegin() == 13 ) {
		if ( hasHighSpades() and !hasQueen() ) {
			//                        LOG_PLACE() << " getting rid of a high spade, first hand.\n";
			return highestOf( Card::spades );
		}
		if ( suitHasIt( Card::diamonds ) )
			return highestOf( Card::diamonds );
		else if ( suitHasIt( Card::spades ) ) {
			handIterator spade = highestOf( Card::spades );
			if ( spade->value() == Card::queen ) {
				if ( spade == std::find_if( handBegin(), handEnd(), OfSuite( Card::spades ) ) ) {       // it is the lowest spade, besides this there are only hearts.
					return spade;
				} else if ( spade != handBegin() and ( spade - 1 ) ->suit() == Card::spades )
					return spade -1;
				else {
					LOG_PLACE() << "OOPS.\n";
					massert( 0 );
				}
			}
			return spade;
		} // has all the hearts!
		LOG_PLACE() << "I have ALL the hearts!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		return highestOf( Card::hearts );
	}

	if ( hasQueen() ) {
		LOG_PLACE() << " dumping the queen.\n";
		return std::find( handBegin(), handEnd(), Cards::spadesQueen );
	}
	if ( hasHighSpades() ) {
		LOG_PLACE() << " dumping a high spade.\n";
		return highestOf( Card::spades );
	}
	handIterator highest = handBegin();
	{
		handIterator it = handBegin();
		++it;
		while ( it != handEnd() ) {        // From here till end of func is where it differs from ComputerPlayerBase3_2
			if ( doingItAll() != ComputerPlayerBase::impossible and * it == Cards::heartsAce )
				if ( it->value() > highest->value() )
					highest = it;
			++it;
		}
	}
	if ( highest->value() > Card::eight
			or !suitHasIt( Card::hearts ) ) {
		return highest;
	}
	ComputerPlayerBase::handIterator res = highestOf( Card::hearts );
	if ( doingItAll() != ComputerPlayerBase::impossible and * res == Cards::heartsAce and res != handBegin() ) {
		--res;
	}
	return res;
}

/**  */
ComputerPlayerBase::handIterator ComputerPlayer4::giveOne()
{
	if ( hasQueen() )
		return std::find( handBegin(), handEnd(), Cards::spadesQueen );
	if ( hasHighSpades() ) {
		LOG_PLACE() << " getting rid of a high spade.\n";
		return highestOf( Card::spades );
	}
	LOG_PLACE() << " giving my highest card, not spades.\n";
	handIterator highest = handBegin();
	handIterator it = handBegin();
	++it;
	while ( it != handEnd() ) {
		if ( it->suit() != Card::spades and it->value() > highest->value() ) {
			highest = it;
		}
		++it;
	}
	return highest;
}

ComputerPlayerBase::handIterator ComputerPlayer4::playStart()
{
	if ( std::find_if( handBegin(), handEnd(), not1( OfSuite( Card::hearts ) ) ) == handEnd() ) { // if I only have hearts, then it doesn't matter whether they have been played
		//                LOG_PLACE() << " all I got is hearts.\n";
		return handBegin(); // might as well play the lowest
	}
	if ( handEnd() - handBegin() == 13 ) {
		return std::find( handBegin(), handEnd(), Cards::clubsTwo );
	}
	if ( !hasQueen() and
			!hasHighSpades() and
			suitHasIt( Card::spades ) and
			!queenOut() ) {       // spades are a good bet if the queen isn't out yet.
		return highestOf( Card::spades );
	}

	// try a suit which hasn't been played much
	if ( suitPlayed( Card::diamonds ) < 2 and suitHasIt( Card::diamonds ) ) {
		//                LOG_PLACE() << " playing a high diamond 'cause they only came out " << suitInfo[Card::diamonds].played << " times.\n";
		return highestOf( Card::diamonds );
	}
	if ( suitPlayed( Card::clubs ) == 1 and suitHasIt( Card::clubs ) ) {
		//                LOG_PLACE() << " playing a high club 'cause they only came out " << suitInfo[Card::clubs].played << " times.\n";
		return highestOf( Card::clubs );
	}

	// try low cards now.

	// maybe a low heart just to give them trouble.
	if ( heartsPlayed() and suitHasIt( Card::hearts ) ) {
		handIterator heart = std::find_if( handBegin(), handEnd(), OfSuite( Card::hearts ) );
		int max = Card::two;
		max += ( suitPlayed( Card::hearts ) + 1 ) * 3;
		if ( heart->value() <= max ) {
			//                        LOG_PLACE() << " a low heart which will probably screw them.\n";
			return heart;
		}
	}

	// check out which suits are available
	//        LOG_PLACE() << " I'll just find a low card.\n";
	std::vector<Card::suit_t> suitsToTry;
	if ( suitHasIt( Card::diamonds )
			and !suitSkippedAll( Card::diamonds )
			and suitPlayed( Card::diamonds ) < 4 ) {
		suitsToTry.push_back( Card::diamonds );
	}

	if ( suitHasIt( Card::clubs ) and
			!suitSkippedAll( Card::clubs ) and
			suitPlayed( Card::clubs ) < 4 ) {
		suitsToTry.push_back( Card::clubs );
	}

	if ( heartsPlayed()
			and suitHasIt( Card::hearts )
			and !suitSkippedAll( Card::hearts )
			and suitPlayed( Card::hearts ) < 4 ) {
		suitsToTry.push_back( Card::hearts );
	}
	if ( queenOut()
			and suitHasIt( Card::spades )
			and !suitSkippedAll( Card::spades )
			and suitPlayed( Card::spades ) < 4 ) {
		suitsToTry.push_back( Card::spades );
	}

	random_shuffle( suitsToTry.begin(), suitsToTry.end() ); // might as well do this

	handIterator best = handEnd();
	int bestScore = 0;
	for ( std::vector<Card::suit_t>::iterator it = suitsToTry.begin(); it != suitsToTry.end(); ++it ) {
		handIterator maybe = std::find_if( handBegin(), handEnd(), OfSuite( *it ) );
		int max = Card::two;
		max += suitPlayed( *it ) * 3;
		if ( suitSkipped( *it ) )
			max -= 2;
		int thisScore = max - ( int ) maybe->value();
		//               LOG_PLACE() << " maybe: " << *maybe << " with score = " << thisScore << ".\n";

		if ( thisScore > bestScore ) {
			bestScore = thisScore;
			best = maybe;
		}
	}
	if ( best != handEnd() )
		return best;
	//        LOG_PLACE() << " I'm going to try my luck.\n";
	do {
		best = handBegin();
		advance( best, rand() % ( handEnd() - handBegin() ) );
	} while ( !heartsPlayed() and best->suit() == Card::hearts );
	return best;
}
/**  */
const char* ComputerPlayer4::type() const
{
	return "ComputerPlayer4";
}

