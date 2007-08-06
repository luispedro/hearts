# coding: utf-8
#
# Part of kde-hearts (http://hearts.luispedro.org/)
# Copyright 2007 by Luís Pedro Coelho <luis@luispedro.org>
#
# Distributed under GNU Public License, version 2

import sys
from ConfigParser import ConfigParser
from optparse import OptionParser
from os.path import exists

class Options(object):
    def __init__(self,options,inputfile):
        self.options=options
        self.config=ConfigParser()
        self.config.read(inputfile)

    def getopt(self,group,opt):
        assert group in ['database']
        return self.config.get(group,opt)

    def getdbopt(self,opt):
        return self.getopt('database',opt)

    def daemon(self):
        return self.options.daemon

_options = None
def readoptions():
    global _options
    if _options: return _options
    parser=OptionParser()
    parser.add_option('--daemon',action='store_true',dest='daemon',help='Run in daemon mode')
    parser.add_option('--deamon',action='store_true',dest='daemon') # For bad spellers
    parser.add_option('--conffile',dest='conffile',help='Path to configuration file')
    (options, args) = parser.parse_args()
    bases=['/etc/','/etc/heartsd/','./']
    fnames=['heartsd.conf','heartsdconf','conf/heartsd']
    if options.conffile:
        if exists(options.conffile):
            _options=Options(options,options.conffile)
            return _options
        else:
            raise Exception('The configuration file specified on the command line [%s] does not exist.' % options.conffile)
    for b in bases:
        for f in fnames:
            if exists(b+f):
                _options=Options(options,b+f)
                return _options
    raise Exception('No configuration file found!')

if __name__ == '__main__':
    options=readoptions()
    print 'Daemon: ', options.daemon()
# vim: set ts=4 sts=4 sw=4 expandtab smartindent:
