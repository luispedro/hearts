# coding: utf-8
#
# Part of kde-hearts (http://hearts.luispedro.org/)
# Copyright 2007 by Luís Pedro Coelho <luis@luispedro.org>
#
# Distributed under GNU Public License, version 2

from environment import *
from table import Table
from errors import *
from motd import motd

def stringify(s):
    s.replace('\\','\\\\')
    s.replace('\n','\\n')
    s.replace('\t','\\t')
    return '"%s"' % s

class Player(object):
    def __init__(self,socket):
        self.socket=socket
        self.buffer=''
        self.table=None


    def hasinput(self):
        """
        Player.hasinput(self)
        
        Process input
        Returns true if this player is to be kept alive and false if it is dead
        """
        print '%s has input' % self.socket.fileno()
        input=self.socket.recv(255)
        if input:
            self.buffer += input
            self.process()
            return True
        else:
            # cleanup
            if self.table:
                self.table.remove(self)
            del players[self.socket.fileno()]
            self.socket.close()
            return False

    def process(self):
        print 'PROCESS(-%s-)' % self.buffer
        newline=self.buffer.find('\n')
        if newline < 0:
            return
        msg=self.buffer[:newline-1]
        print 'Got (%s)' % msg
        self.buffer=self.buffer[newline+1:]
        self.handlemsg(msg)
        self.process()

    def handlemsg(self,msg):
        code,args=msg.split(' ',1)

        if code == 'hello':
            self.hello(args)
        elif code == 'createTable':
            self.createTable(args)
        elif code == 'joinTable':
            self.joinTable(args)
        elif code == 'leaveTable':
            self.leaveTable(args)
        elif code == 'authR':
            self.authR(args)
        else:
            print 'Unknown message code: (%s)' % code

    def hello(self,args):
        self.name=args.strip()
        self.cookie='chocolate_chip'
        self.output('authQ md5(md5(pass)*md5(cookie)) %s' % self.cookie)

    def authR(self,args):
        print 'authR -%s-' % args

    def createTable(self, args):
        name = args.strip()
        tables[name]=Table(name)
        for p in players.values():
            p.announcetable(name)

    def announcetable(self,tablename):
        table=tables[tablename]
        msg = 'lookAt %s' % tablename
        for p in table.playernames():
            msg += ' %s' % p
        self.output(msg)

    def joinTable(self,args):
        name=args.strip()
        table=tables.get(name,None)
        if table:
            if not table.full():
                table.add(self)
                self.table=table
            else:
                self.error(INEXISTANT_TABLE,'Table full') # FIXME: Maybe a better error code ?
        else:
            self.error(INEXISTANT_TABLE,'What table?')

    def greet(self):
        self.output('motd %s' % stringify(motd()))

    def error(self,code,msg):
        self.output('error %s %s' % (code,stringify(msg)))

    def output(self,msg):
        print "OUTPUT(-%s-)" % msg
        self.socket.send(msg + '\n')


# vim: set ts=4 sts=4 sw=4 expandtab smartindent:
