# coding: utf-8
#
# Part of kde-hearts (http://hearts.luispedro.org/)
# Copyright 2007 by Luís Pedro Coelho <luis@luispedro.org>
#
# Distributed under GNU Public License, version 2
import md5

def _do_md5_hex(s):
    M=md5.new()
    M.update(s)
    return M.hexdigest()

def _do_md5(s):
    M=md5.new()
    M.update(s)
    return M.digest()


def _string_xor(sa,sb):
    return "".join([chr( ord(ca) ^ ord(cb) ) for ca, cb in zip(sa,sb)])

def validate(method,cookie,pwd,key):
    """
    validate(method, cookie, pwd, key)

    Returns whether the key fits the (cookie,pwd) under method.
    @param method: Algorithm to use. Currently only md5(md5(pass)*md5(cookie)) is supported.
    @param cookie: The cookie used
    @param pwd: The actual password
    @param key: The key given by the user
    """
    print "pwd\t\t", pwd
    if method == 'md5(md5(pass)*md5(cookie))':
        mcookie=_do_md5(cookie)
        mpwd=_do_md5(pwd)
        expected=_do_md5_hex(_string_xor(mcookie,mpwd))
        print "key\t\t", key
        print "expected\t", expected
        return expected == key
    else:
        raise Exception("validate(): Unkown method '%s'" % method)

if __name__ == '__main__':
    tcookie='chocolate-chip'
    tpwd='big-secret'
    tres=_do_md5_hex(_string_xor(_do_md5(tcookie),_do_md5(tpwd)))
    assert validate('md5(md5(pass)*md5(cookie))',tcookie,tpwd,tres)
    tres=_do_md5_hex(_string_xor(_do_md5(tpwd),_do_md5(tcookie)))
    assert validate('md5(md5(pass)*md5(cookie))',tcookie,tpwd,tres)
    tres=_do_md5_hex(_string_xor(_do_md5(tcookie),_do_md5(tcookie)))
    assert not validate('md5(md5(pass)*md5(cookie))',tcookie,tpwd,tres)
    print 'OK'
# vim: set ts=4 sts=4 sw=4 expandtab smartindent:
