#include <qstring.h>

#include "hearts/player_id.h"

namespace Options
{
QString playerName( player_id::type who );
void savePlayerName( player_id::type, const QString& );
}


