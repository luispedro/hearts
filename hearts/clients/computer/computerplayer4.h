/***************************************************************************
                          computerplayer4.h  -  description
                             -------------------
    begin                : Tue Oct 17 2000
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

#ifndef COMPUTERPLAYER4_H
#define COMPUTERPLAYER4_H

#include "computerplayerbase.h"

/**This is a reimplementation of ComputerPlayer3.
  *@author Luis Pedro Coelho
  */

class ComputerPlayer4 : public ComputerPlayerBase  {
        public:
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
