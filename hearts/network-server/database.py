# coding: utf-8
#
# Part of kde-hearts (http://hearts.luispedro.org/)
# Copyright 2007 by Luís Pedro Coelho <luis@luispedro.org>
#
# Distributed under GNU Public License, version 2

import MySQLdb
from string import Template
from options import readoptions
class Database(object):
    def __init__(self,options):
        self.db=MySQLdb.connect(host=options.getdbopt('host'),user=options.getdbopt('user'),passwd=options.getdbopt('password'),db=options.getdbopt('database'))


    def query(self, q, *args):
        """
        q is a query. Two types of substitution are perfomed, using different notations:
            * The first uses string.Template notation and substitutes the following strings,
            all refering to table names:

                    - userstable
                    - gamestable

                Remember to use '$$' if you want a '$'
            * The second if performed by MySQLdb module and uses args to fill in.
            See MySQLdb documentation for details
        """
        q=Template(q).substitute({'userstable' : 'users', 'gamestable' : 'games'})
        cursor=self.db.cursor()
        cursor.execute(q,*args)
        return cursor

def get_database():
    return Database(readoptions())
# vim: set ts=4 sts=4 sw=4 expandtab smartindent:
