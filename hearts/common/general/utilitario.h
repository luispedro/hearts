#ifndef DB_UTILITARIO_H_INCLUDE_GUARD_
#define DB_UTILITARIO_H_INCLUDE_GUARD_

#include <vector>
#include <memory>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>

struct pollfd;

namespace Utility
{
/** Appends up to maxlen bytes to the buffer */
int read_to_vector( int fd,
					 std::vector<char>& buffer,
					 std::vector<char>::size_type maxlen = 512 );

void write_from_vector( int fd, std::vector<char>& buffer );

/** Coloca pfd para escutar flags no descritor fd */
void init_pollfd( pollfd& pfd, int fd, int flags = POLLIN | POLLERR );

int Poll( std::vector<pollfd>&, int );
const int Poll_Forever = -1;
int Recvfrom( int, void*, size_t, int, void*, socklen_t* );
int Bind( int, void*, socklen_t );
int Socket( int, int, int );
void Listen( int, int );
void Connect( int, void*, socklen_t );
void Sendto( int, const void*, int, int, void*, socklen_t );
}




#endif /* DB_UTILITARIO_H_INCLUDE_GUARD_ */
