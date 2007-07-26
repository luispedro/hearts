#
# Part of kde-hearts (http://hearts.luispedro.org/)
# Copyright 2007 by Luís Pedro Coelho <luis@luispedro.org>
#
# Distributed under GNU Public License, version 2

from environment import *
class Table(object):
    def __init__(self,name):
        self.name=name
        self.members=[]

    def add(self,player):
        if self.full():
            raise Exception('Too many players!')
        self.members.append(player)
        if full():
            assert False
    def full(self):
        return len(self.members) <= 4

    def playernames(self):
        return [p.name for p in self.members]
# vim: set ts=4 sts=4 sw=4 expandtab smartindent:
