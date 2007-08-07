# coding: utf-8
#
# Part of kde-hearts (http://hearts.luispedro.org/)
# Copyright 2007 by Luís Pedro Coelho <luis@luispedro.org>
#
# Distributed under GNU Public License, version 2

from database import get_database

class User(object):
    def __init__(self,uid,username,pwd):
        self.username = username
        self.uid=uid
        self.passwd=pwd

    def username(self):
        return self.username

def get_user(name):
    connection=get_database()
    record=connection.query('SELECT * FROM ${userstable} WHERE name = %s',name)
    A=record.fetchone()
    return User(*A)
#    return User(A['uid'],A['name'],A['pass'])

# vim: set ts=4 sts=4 sw=4 expandtab smartindent:
