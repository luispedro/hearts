#ifndef LPC_ID_TO_FD_H1082425633_INCLUDE_GUARD_
#define LPC_ID_TO_FD_H1082425633_INCLUDE_GUARD_

#include "hearts/player_id.h"
int id_to_fd( player_id::type );
void register_fd( player_id::type, int );
void register_fd( int );
bool all_registered();



#endif /* LPC_ID_TO_FD_H1082425633_INCLUDE_GUARD_ */
