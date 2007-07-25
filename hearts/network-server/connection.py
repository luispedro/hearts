import socket
HEARTS_PORT=1443
def open_connection():
    serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serversocket.bind((socket.gethostname(), HEARTS_PORT))
    serversocket.listen(5)
    return serversocket

# vim: set ts=4 sts=4 sw=4 expandtab smartindent:
