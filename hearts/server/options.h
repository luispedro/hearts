/***************************************************************************
                          options.h  -  Holds the options for the game
                             -------------------
    begin                : Sun Jan 2 2000
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

 /**This class manages the options of the user hiding away the details of KConfig.
    *
    * class OptionsSelectionDialog is declared a friend for it to acess the set functions. These are
    * however not available to the general user.
    *
    * @author Luís Coelho <luis_pedro@netcabo.pt>
    */

 #ifndef OPTIONS_H_
 #define OPTIONS_H_

// #include "hearts.h"
// #include "optionsselectiondialog.h"

 #include <player.h>
 #include <string>

 class Options;

extern  const Options* &options;


 class Options {
        /** Private and undefined */
                Options();
        /** Private and undefined */
                Options(const Options&);
        /** Private and undefined */
                Options& operator = (const Options&);


        public:

        /** This is for the result of playingDirection(); */
                enum PlayDirection { Clockwise , AntiClockwise };

//X 		/** This returns the address of the player as a ip:port string for 
//X 		* TCP/IP or a file:port for Unix Local socket */
//X 				std::string player_address(player_id::type);


        /** this is the  maximum number of points a player can 
		* make without losing, i.e. the game ends when
		* a player has more than maxPoints points. */
                unsigned maxPoints() const;


        /** This returns the same as the global options 
		* pointer reference and should be used where that options 
		* pointer unusable. */
                static const Options* appOptions();

		static void init(int,char**);

		bool wait_zero() const { return wait_zero_; }
		bool daemon() const { return daemon_; }

		short tcp_port() const { return tcp_port_; }
		const char* unix_address() const { return unix_address_.c_str(); } 

		Options( int );
		
        private: // Private methods

		short tcp_port_;
		std::string unix_address_;
		bool wait_zero_;
		bool daemon_;
		
                static Options* singleton;
        /** returns the non const singleton. It is to be used by OptionsSelectionDialog. */
                static Options* unconstAppOptions();
};

#endif
 
