# coding: utf-8
#
# Part of kde-hearts (http://hearts.luispedro.org/)
# Copyright 2007 by Luís Pedro Coelho <luis@luispedro.org>
#
# Distributed under GNU Public License, version 2

from change_protocol import change_protocol
from environment import *
class Table(object):
    def __init__(self,name):
        self.name=name
        self.members=[]
        self.owner=None
        self.nbots=0

    def cleanup(self):
        del tables[self.name]
        self.name=None

    def add(self,player):
        if self.full():
            raise Exception('Too many players!')
        self.members.append(player)
        if self.full():
            self._launch_game()

    def _launch_game(self):
        fds=[]
        names=[]
        for p in self.members: 
            fd=p.socket.fileno()
            del listeners[fd]
            sockets.unregister(fd)
            fds.append(fd)
            names.append(p.name)
            p.changeProtocol()
        del tables[self.name]
        change_protocol(names,fds,self.nbots)

    def remove(self,player):
        self.members.remove(player)

    def addBot(self):
        self.nbots = self.nbots + 1
        if self.full():
            self._launch_game()

    def full(self):
        return len(self.members)+self.nbots >= 4

    def empty(self):
        return len(self.members) > 0

    def playernames(self):
        return [p.name for p in self.members]

# vim: set ts=4 sts=4 sw=4 expandtab smartindent:
