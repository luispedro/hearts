# coding: utf-8
#
# Part of kde-hearts (http://hearts.luispedro.org/)
# Copyright 2007 by Luís Pedro Coelho <luis@luispedro.org>
#
# Distributed under GNU Public License, version 2

class User(object):
    def __init__(self,username):
        self.username = username

    def passwd(self):
        return 'secret'

    def username(self):
        return self.username

def get_user(name):
    return User('Mario')
#    connection=get_database()
#    record=connection.q('SELECT * FROM %(prefix)susers WHERE name = %s',name)
#    return record
# vim: set ts=4 sts=4 sw=4 expandtab smartindent:
