#ifndef DB_OPEN_CONNECTIONS_H1053543733_INCLUDE_GUARD_
#define DB_OPEN_CONNECTIONS_H1053543733_INCLUDE_GUARD_

namespace connection_errors
{
enum type { no_address = 1, interrupted = 2, unix_error = 3 };
}

int open_client_connection( int argc, char* argv[] );
int open_client_connection( const char* );
int open_client_connection( const char*, short );


#endif /* DB_OPEN_CONNECTIONS_H1053543733_INCLUDE_GUARD_ */
