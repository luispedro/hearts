#) coding: utf-8
#
# Part of kde-hearts (http://hearts.luispedro.org/)
# Copyright 2007 by Luís Pedro Coelho <luis@luispedro.org>
#
# Distributed under GNU Public License, version 2

from select import * # get all of POLLIN, POLLPRI,...*
from player import Player
import environment
from environment import *
import sys
import traceback

def greet(nsocket):
    print 'New Player (%s)' % nsocket.fileno()
    player=Player(nsocket)
    listeners[nsocket.fileno()]=player
    player.greet()

def launch_server(listener):
    pollmask=(POLLIN|POLLPRI|POLLERR|POLLHUP)
    sockets.register(listener,pollmask)
    while True:
        try:
            print 'poll()'
            ready=environment.sockets.poll()
            for fd, event in ready:
                if fd == listener.fileno():
                    nsocket=listener.accept()
                    environment.sockets.register(nsocket[0], pollmask)
                    print nsocket[0]
                    print type(nsocket[0])
                    greet(nsocket[0])
                else:
                    if event & POLLIN:
                        alive=listeners[fd].process_input()
                        if not alive:
                            environment.sockets.unregister(fd)
                    if event & (POLLERR|POLLHUP):
                        print 'Bye bye ', fd
                        environment.sockets.unregister(fd)
        except Exception, e:
            print 'Something wrong!', e
            traceback.print_exc(file=sys.stderr)


# vim: set ts=4 sts=4 sw=4 expandtab smartindent:
