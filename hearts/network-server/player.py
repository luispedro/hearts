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
from users import get_user
from validate import validate

_Authentication_Method='md5(md5(pass)*md5(cookie))'

def stringify(s):
    s=s.replace('\\','\\\\')
    s=s.replace('\n','\\n')
    s=s.replace('\t','\\t')
    s=s.replace(' ','\\_')
    return '"%s"' % s

_players=[]

class Player(object):
    def __init__(self,socket):
        self.socket=socket
        self.buffer=''
        self.user=None
        self.table=None
        _players.append(self)
        self.name='Unkown'


    def process_input(self):
        """
        Player.process_input(self)
        
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
            del listeners[self.socket.fileno()]
            _players.remove(self)
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
        self.user=get_user(self.name)
        if not self.user:
            self.error('unknownUser','Did you register at http://hearts.luispedro.org/?')
        else:
            self.cookie='chocolate_chip'
            self.output('authQ %s %s' % (_Authentication_Method,self.cookie))

    def authR(self,args):
        cookie,key = args.split(' ')
        if not self.user or not self.cookie:
           self.error('unexpectedMessage','Your software seems to be malfunctioning<br />Technical note: it sent message authR without a previous authQ')
        elif cookie != self.cookie:
           self.error('unexpectedMessage','Your software seems to be malfunctioning<br />Technical note: It replied with a different cookie')
        elif not validate(_Authentication_Method,self.cookie,self.user.passwd(),key):
            self.error('authenticationError','Authentication error. Please check your user name and password')
        else:
            self.authenticated=True

    def createTable(self, args):
        name = args.strip()
        tables[name]=Table(name)
        for p in _players:
            p.announcetable(name)

    def announcetable(self,tablename):
        print 1
        table=tables[tablename]
        print 2
        msg = 'lookAt %s' % tablename
        print 3
        for p in table.playernames():
            msg += ' %s' % p
        print 4
        self.output(msg)

    def joinTable(self,args):
        tname=args.strip()
        table=tables.get(tname,None)
        if table:
            if not table.full():
                table.add(self)
                self.table=table
                for p in _players:
                    p.announcetable(tname)
            else:
                self.error(INEXISTANT_TABLE,'Table full') # FIXME: Maybe a better error code ?
        else:
            self.error(INEXISTANT_TABLE,'What table?')

    def changeProtocol(self):
        self.output('changeProtocol')

    def greet(self):
        self.output('motd %s' % stringify(motd()))
        for t in tables.keys():
            self.announcetable(t)

    def error(self,code,msg):
        self.output('error %s %s' % (code,stringify(msg)))

    def output(self,msg):
        print "OUTPUT(-%s-)" % msg
        self.socket.send(msg + '\n')


# vim: set ts=4 sts=4 sw=4 expandtab smartindent:
