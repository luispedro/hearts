#include "gamemanager.h"
#include "general/helper.h"
#include "hearts/cards.h"
#include "hearts/deck.h"
#include <unistd.h>
#include <cassert>

#define I18N_NOOP(x) x // I don't want to include KDE's headers, but I'll use the same name for consistency

GameManager::GameManager()
		: players( 4 ),
		to_move( players.begin(), players.begin(), players.end() ),
		given_cards( 4 ),
		current_state( Init )
{
	LOG_PLACE_NL();
}


GameManager::~GameManager()
{ // Just to avoid dangling pointers, there is an extra layer of protection
	// It should be unneeded, though
	circler last = to_move;
	do {
		to_move->player->set_receiver( std::auto_ptr<Player::Receiver>( 0 ) );
		++to_move;
	} while ( to_move != last );
}


void GameManager::register_player( Player& p, player_id::type id )
{
	LOG_PLACE() << "Registering " << id << ".\n";
	assert( !( players[ id ].player ) );
	assert( current_state == Init );
	players[ id ].player = &p;
	p.set_receiver( std::auto_ptr<Player::Receiver>( new GameManager::Receiver( *this, id ) ) );
	for ( control_cont_type::iterator iter = players.begin(); iter != players.end(); ++iter ) {
		if ( iter->player == 0 )
			return ;
	}
	LOG_PLACE() << ", registered four players.\n";
	current_state = Idle; // We already have four players
}

void GameManager::start_game()
{
	assert( current_state == Idle );
	LOG_PLACE() << ".\n";
	give_cards();
	LOG_PLACE() << ".\n";
	bool must_wait = ask_for_cards();
	if ( !must_wait )
		start_first_hand();
}



// From here on these are all private methods:


void GameManager::start_first_hand()
{
	while ( to_move->hand.count( Cards::clubsTwo ) == 0 )
		++to_move;
	to_move->player->play();
	current_state = WaitPlay;
}

void GameManager::give_cards()
{
	std::vector<Card> cards = randomDeck();
	typedef std::vector<Player_Control>::iterator iter;
	while ( !cards.empty() ) {       // could be better, but cards are dealt like this in real life, why not here too ?
		for ( iter it = players.begin(); it != players.end(); ++it ) {
			Card current = cards.back();
			cards.pop_back();

			it->player->receive( current );
			it->hand.insert( current );
		}
	}
}

bool GameManager::ask_for_cards()
{
	if ( number_games % 4 == 3 ) {
		return false;
	}
	for ( control_cont_type::iterator iter = players.begin(); iter != players.end(); ++iter ) {
		LOG_PLACE() << " asking for cards.\n";
		iter->player->give();
	}
	current_state = WaitGive3;
	return true;
}

void GameManager::give3_reply( player_id::type id, const Holder3& cards )
{
	assert( current_state == WaitGive3 );
	LOG_PLACE() << " Receiving cards from " << id << ".\n";
	given_cards[ id ] = cards.vector();

	// I had written this as a nice std::find_if, but it didn't compile
	bool start = true;
	for ( given_cont_type::iterator iter = given_cards.begin();
			iter != given_cards.end();
			++iter ) {
		if ( iter->empty() )
			start = false;
	}
	if ( start ) {
		LOG_PLACE() << " starting a game.\n";
		distribute_cards();
		start_first_hand();
	}
}

void GameManager::distribute_cards()
{
	LOG_PLACE() << "distributing cards.\n";
	// TODO: fix so that it doesn't always go right;
	for ( unsigned i = 0; i != 4; ++i ) {
		for ( unsigned j = 0; j != 3; ++j ) {
			unsigned index = ( i + 1 ) % 4;
			players[ index ].player->receive( given_cards[ i ][ j ] );
			players[ index ].hand.insert( given_cards[ i ][ j ] );
			players[ i ].hand.erase( players[ i ].hand.find( given_cards[ i ][ j ] ) );
		}
		given_cards[ i ].clear();
	}
}

void GameManager::play_reply( player_id::type id, const Card& attempt )
{
	LOG_PLACE() << " Receiving a play reply.\n";
	const char* error = validate( attempt );
	if ( error ) {
		to_move->player->invalidPlay( error );
		return ;
	}
	warn_about_move( attempt );
	to_move->hand.erase( to_move->hand.find( attempt ) );
	++to_move;
	table.add( attempt );
	hearts_been_played = hearts_been_played or ( attempt.suit() == Card::hearts );
	if ( table.full() ) {
		hand_end();
	} else {
		to_move->player->play();
	}
}

void GameManager::warn_about_move( Card c )
{
	// must remember that ++circler always works clockwise.
	const player_id::type relative[] = {
										   player_id::self,
										   player_id::right,
										   player_id::front,
										   player_id::left
									   };
	unsigned i = 0;
	circler iter = to_move;
	do {
		iter->player->inform( c, relative[ i ] );
		++i;
		++iter;
	} while ( iter != to_move ) ;
}


void GameManager::status_every_player( player_status::type s )
{
	for ( unsigned i = 0; i != 4; ++i ) {
		players[ i ].player->currentStatus( s );
	}
}


void GameManager::hand_end()

{
	to_move += winner( table );
	to_move->gotten.insert( table.state().begin(), table.state().end() );
	table.reset();
	{
		using namespace player_status;
		type hand_over[] = { hand_over_self_win, hand_over_right_win, hand_over_front_win, hand_over_left_win };
		for ( int i = 0; i != 4; ++i )
			( to_move + i ) ->player->currentStatus( hand_over[ i ] );
	}
	if ( to_move->hand.empty() ) { // checking this player is as good as checking any other
		assign_points();
		reset_game_data();
		status_every_player( player_status::game_over );
		current_state = Idle;
		if ( game_over_callback )
			( *game_over_callback ) ();
	} else {
		to_move->player->play();
	}
}

namespace
{
inline unsigned points_for( const Card& c )
{
	if ( c == Cards::spadesQueen )
		return 13;
	if ( c.suit() == Card::hearts )
		return 1;
	return 0;
}
}

void GameManager::assign_points()
// If someone manages to get all points on one game it is the other players who get 26 points
// This is why this must be done in two parts: collect & distribute
{
	std::vector<unsigned> points_gotten( 4 );
	for ( unsigned i = 0; i != 4; ++i )
	{
		for ( std::set<Card>::iterator iter = players[ i ].gotten.begin();
				iter != players[ i ].gotten.end();
				++iter ) {
				points_gotten[ i ] += points_for( *iter );
			}
	}

	std::vector<unsigned>::iterator done_all = std::find( points_gotten.begin(), points_gotten.end(), 26 );
	if ( done_all != points_gotten.end() )
	{
		unsigned done_all_index = done_all - points_gotten.begin(); // 4 if none found
		for ( unsigned i = 0; i != 4; ++i ) {
			if ( i != done_all_index )
				players[ i ].points += 26;
		}
	} else
	{
		for ( unsigned i = 0; i != 4; ++i ) {
			players[ i ].points += points_gotten[ i ];
		}
	}
}

const char* GameManager::validate( const Card& attempt ) const
{ 
		  /***********************
				* This  validates move from the to_move player
				* If it is valid it returns 0, else it returns an error message.
				*
				* RULES:
				*    1. You cannot play a card you do not have.
				*    2. You must always follow suit if possible
				*    3. On the first hand:
				*             a. you must start the hand with the two of clubs
				*             b. you cannot play any points cards. Unless all you have are hearts
				*    4. You can only start a hand with hearts if hearts have been played
				*
			**********************/

	if ( to_move->hand.count( attempt ) == 0 ) {
		return error_msgs[ dont_have_card ];
	}

	if ( to_move->hand.size() == 13 )      // if (first_hand)
	{
		if ( table.empty() )
		{
			if ( attempt != Cards::clubsTwo ) {
				return error_msgs[ play_two ];
			}
			return 0;
		} else if ( attempt.suit() != Card::clubs )
		{
			if ( has_suite( *to_move, Card::clubs ) ) {
				return error_msgs[ must_assist_clubs ];
			} else if ( points_for( attempt ) ) {
				if ( std::find_if( to_move->hand.begin(), to_move->hand.end(), not1( OfSuite( Card::hearts ) ) ) != to_move->hand.end() ) {
						  // the player has at least one non-hearts card
					return error_msgs[ no_points ];
				}
				// amazing, all the hearts.
				// That's a 1 in 52!/((52-13)!13!)  shot. [1 in 635013559600 according to bc]
				// that doesn't account for trading cards, but still mighty unprobable
				return 0;
			} else
				return 0;
		} else
			return 0; //playing clubs
	} else // not first hand
	{
		if ( table.empty() ) {
			if ( !hearts_been_played and attempt.suit() == Card::hearts ) {
				if ( find_if( to_move->hand.begin(), to_move->hand.end(), not1( OfSuite( Card::hearts ) ) )
						== to_move->hand.end() )
					return 0;	    // hearts all the way down
				return error_msgs[ no_hearts ];
			}
			return 0;
		} else {
			Card::suit_t push = table.push();
			if ( push != attempt.suit() and has_suite( *to_move, push ) ) {
				return error_msgs[ suit_to_enum( push ) ];
			}
			return 0;
		}
	}
	massert ( !"unreachable code." );
	return 0;
}

void GameManager::reset_game_data()
{
	hearts_been_played.reset();
	for ( control_cont_type::iterator iter = players.begin(); iter != players.end(); ++iter ) {
		iter->gotten.clear();
	}
}

const char* GameManager::error_msgs[] =
	{
		I18N_NOOP( "Unknown error" ),
		I18N_NOOP( "You do not have that card in your hand!" ),
		I18N_NOOP( "You must start the game with a two of clubs" ),
		I18N_NOOP( "You must not play any points card on your first move" ),
		I18N_NOOP( "You cannot start a hand with hearts until they have been played unless you do not have anything else" ),
		I18N_NOOP( "You must play clubs" ),
		I18N_NOOP( "You must play hearts" ),
		I18N_NOOP( "You must play spades" ),
		I18N_NOOP( "You must play diamonds" ),
	};

unsigned GameManager::suit_to_enum( Card::suit_t s )
{
	switch ( s ) {
#define CASE(x) case Card::x: return must_assist_##x;
		CASE( hearts )
		CASE( diamonds )
		CASE( spades )
		CASE( clubs )
#undef CASE

	}
	return 0;
}


bool GameManager::has_suite( const Player_Control& pl, Card::suit_t s ) const
{
	return std::find_if( pl.hand.begin(), pl.hand.end(), OfSuite( s ) ) != pl.hand.end();
}

unsigned GameManager::points( player_id::type who ) const
{
	return players[ who ].points;
}


unsigned most_points( const GameManager& m )
{
	using namespace player_id;
	unsigned res = m.points( self );
	res = std::max( res, m.points( right ) );
	res = std::max( res, m.points( front ) );
	res = std::max( res, m.points( left ) );
	return res;
}

