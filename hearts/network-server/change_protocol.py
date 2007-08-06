# coding: utf-8
#
# Part of kde-hearts (http://hearts.luispedro.org/)
# Copyright 2007 by Luís Pedro Coelho <luis@luispedro.org>
#
# Distributed under GNU Public License, version 2

from os import fdopen
from execute import execute_server, execute_computer_server
import threading
import re
import random
_botNames=['Rita','Anna','Jacob','Ahmet','Ming','Tom','Sarah','Justin']
_winner_pattern=re.compile('^winner: ([a-z]*)$')
class _WaitServer(threading.Thread):
    def __init__(self,names,fds,nbots):
        self.names=names
        self.fds=fds
        self.nbots=nbots
        assert len(fds)+nbots == 4
        threading.Thread.__init__(self)

    def run(self):
        bnames=random.sample(_botNames,self.nbots)
        for n in bnames:
            self.fds.append(execute_computer_server(n))
        pid,read_fd=execute_server(*self.fds)
        for line in fdopen(read_fd):
            M=_winner_pattern.match(line)
            if M:
                winner=M.group(1)
                winner2idx={'self' : 0, 'right' : 1, 'front' : 2, 'left' : 3 }
                print 'Winner: ', winner, winner2idx[winner], self.names[winner]
        while True:
            p=wait4(pid,10000)
            if p == pid: return
        

def change_protocol(names,fds,nbots):
    _WaitServer(names,fds,nbots).start()

# vim: set ts=4 sts=4 sw=4 expandtab smartindent:
