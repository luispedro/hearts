#ifndef PLAYERID_H
#define PLAYERID_H


namespace Network {
// This should have been Player::id EXCEPT
// that we'd have a circular include dependency
// player.h <- table.h <- player.h

typedef int player_id;
}
#endif // PLAYERID_H

