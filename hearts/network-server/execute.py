# coding: utf-8
#
# Part of kde-hearts (http://hearts.luispedro.org/)
# Copyright 2007 by Luís Pedro Coelho <luis@luispedro.org>
#
# Distributed under GNU Public License, version 2

from os import *
from subprocess import *
from socket import socketpair

def Fork():
    b = fork()
    if b < 0:
        raise Exception('fork() failed')
    return b

def execute_computer_server(name):
    sock_parent, sock_child = socketpair()
    b = fork()
    if b > 0:
        sock_child.close()
        return dup(sock_parent.fileno()), b
    else:
        sock_parent.close()
        execlp('heartscomputerclient',\
                'heartscomputerclient',\
                '--playername', name, \
                '--fd',str(sock_child.fileno()),\
                '--zero')
        print 'EXECL(heartscomputerclient) FAILED!'

def execute_server(fd1,fd2,fd3,fd4):
    print "Executing server..."
    fds=[fd1,fd2,fd3,fd4]
    return Popen(('heartsserver',\
            'heartsserver',\
            '--wait-zero',\
            '--fds',",".join([str(f) for f in fds])),
            stdout=PIPE)
# vim: set ts=4 sts=4 sw=4 expandtab smartindent:
