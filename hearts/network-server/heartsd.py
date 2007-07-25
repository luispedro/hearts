from options import readoptions
from connection import open_connection
from service import launch_server
if __name__ == '__main__':
    try:
        options=readoptions()
        #if options.daemon():
        #    daemon()
        listener=open_connection()
        launch_server(listener)
    except Exception, e:
        print 'Sorry', e
        

# vim: set ts=4 sts=4 sw=4 expandtab smartindent:
