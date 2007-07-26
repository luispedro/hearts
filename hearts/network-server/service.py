#
# Part of kde-hearts (http://hearts.luispedro.org/)
# Copyright 2007 by Luís Pedro Coelho <luis@luispedro.org>
#
# Distributed under GNU Public License, version 2

from select import * # get all of POLLIN, POLLPRI,...*
from player import Player
from environment import *

def greet(nsocket):
    print 'New Player (%s)' % nsocket.fileno()
    player=Player(nsocket)
    players[nsocket.fileno()]=player
    player.greet()

def launch_server(listener):
    sockets=poll()
    pollmask=(POLLIN|POLLPRI|POLLERR|POLLHUP)
    sockets.register(listener,pollmask)
    while True:
        try:
            print 'will poll()'
            ready=sockets.poll()
            print 'poll()ed'
            for fd, event in ready:
                if fd == listener.fileno():
                    nsocket=listener.accept()
                    print 'a'
                    sockets.register(nsocket[0], pollmask)
                    print nsocket[0]
                    print type(nsocket[0])
                    greet(nsocket[0])
                else:
                    if event & POLLIN:
                        players[fd].hasinput()
                    if event & (POLLERR|POLLHUP):
                        print 'Bye bye ', fd
                        sockets.unregister(fd)
        except Exception, e:
            print 'Something wrong!'
            print e	


# vim: set ts=4 sts=4 sw=4 expandtab smartindent:
