/***************************************************************************
                          computerplayer3_2.h  -  description
                             -------------------
    begin                : Wed Oct 25 2000
    copyright            : (C) 2000 by Luis Pedro Coelho
    email                : luis_pedro@netcabo.pt
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef COMPUTERPLAYER3_2_H
#define COMPUTERPLAYER3_2_H

#include <computerplayerbase.h>

/**This is like ComputerPlayer3, except it is done inheriting from ComputerPlayerBase which simplifies a lot of code.
  *@author Luis Pedro Coelho
  */

class ComputerPlayer3_2 : public ComputerPlayerBase  {
        public:
  /**  */
                virtual const char* type() const;
        private: // Private methods
        /**  */
                virtual ComputerPlayerBase::handIterator playAssist();
        /**  */
                virtual ComputerPlayerBase::handIterator playNotAssist();
                virtual ComputerPlayerBase::handIterator giveOne();
                virtual ComputerPlayerBase::handIterator playStart();
};

#endif
