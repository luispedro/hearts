#ifndef DB_PLAYER_STATUS_H_INCLUDE_GUARD_
#define DB_PLAYER_STATUS_H_INCLUDE_GUARD_

#include <iostream>

namespace player_status
{
enum type {
	wait_left,
	wait_front,
	wait_right,
	game_over,
	hand_over_self_win,
	hand_over_right_win,
	hand_over_front_win,
	hand_over_left_win
};
std::ostream& operator << ( std::ostream&, type );
std::istream& operator >> ( std::istream&, type& );
}



#endif /* DB_PLAYER_STATUS_H_INCLUDE_GUARD_ */
