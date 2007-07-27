# coding: utf-8
#
# Part of kde-hearts (http://hearts.luispedro.org/)
# Copyright 2007 by Luís Pedro Coelho <luis@luispedro.org>
#
# Distributed under GNU Public License, version 2
import md5

def _do_md5(s):
    M=md5.new()
    M.update(s)
    return M.hexdigest()

def _char_xor(ca,cb):
    return hex(int(ca,16) ^ int(cb,16))[-1]
def _string_xor(sa,sb):
    return "".join([_char_xor(ca,cb) for ca, cb in zip(sa,sb)])

def validate(method,cookie,pwd,result):
    if method == 'md5(md5(cookie)*md5(result))':
        mcookie=_do_md5(cookie)
        mpwd=_do_md5(result)
        expected=_do_md5(_string_xor(mcookie,mpwd))
        return expected == result
    else:
        raise Exception("validate(): Unkown method '%s'" % method)

# vim: set ts=4 sts=4 sw=4 expandtab smartindent:
