#include "utilitario.h"
#include "error.h"
#include <sys/poll.h>
#include <unistd.h>
#include <iostream>

int Utility::read_to_vector( int fd, std::vector<char>& buffer, std::vector<char>::size_type rao )
{
	std::vector<char>::size_type current = buffer.size();
	buffer.resize( current + rao );
	int stat = read( fd, &buffer[ current ], rao );
	std::cerr << "Read returned: " << stat << std::endl;
	if ( stat < 0 ) {
		buffer.resize( current );
	} else {
			buffer.resize( current + stat );
	}
	return stat;
}

void Utility::write_from_vector( int fd, std::vector<char>& out )
{
	int res = ::write( fd, &out[ 0 ], out.size() );
	if ( res < 0 )
		exit( 1 );
	out.erase( out.begin(), out.begin() + res );
}


void Utility::init_pollfd( pollfd& p, int fd, int flags )
{
	std::memset( &p, 0, sizeof( pollfd ) );
	p.fd = fd;
	p.events = flags;
}


int Utility::Bind( int fd, void* addr, socklen_t len )
{
	int stat = ::bind( fd, ( sockaddr* ) addr, len );
	if ( stat < 0 )
		exit( 1 ); //	throw UnixError("bind");
	return stat;
}

int Utility::Recvfrom( int fd, void* buf, size_t len, int flags, void* addr, socklen_t* slen )
{
	int stat = ::recvfrom( fd, buf, len, flags, ( sockaddr* ) addr, slen );
	if ( stat < 0 )
		exit( 1 ); // throw UnixError("recvfrom");
	return stat;
}


int Utility::Socket( int a, int b, int c )
{
	int stat = socket( a, b, c );
	if ( stat < 0 )
		exit( 1 ); // throw UnixError("socket");
	return stat;
}

void Utility::Connect( int fd, void* add
						   , socklen_t len )
{
	if ( connect( fd, ( sockaddr* ) add
					  , len ) < 0 ) exit( 1 ); //throw UnixError("connect");
}

/*int Utility::address2fd(const Address& addr)
{
	int fd;
	if (addr.domain() == AF_UNIX) fd = Utility::Socket(PF_UNIX,SOCK_DGRAM,0);
	else fd = Utility::Socket(PF_INET,SOCK_DGRAM,0);
	Utility::Connect(fd,addr.sockaddr(),addr.len());
	return fd;
}*/

void Utility::Listen( int a, int b )
{
	int stat = listen( a, b );
	if ( stat < 0 )
		exit( 1 ); // throw UnixError("listen");
}

void Utility::Sendto( int fd, const void* buf, int len, int f, void* addr, socklen_t addlen )
{
	int stat = sendto( fd, const_cast<void*>( buf ), len, f, ( sockaddr* ) addr, addlen );
	if ( stat < 0 )
		exit( 1 ); // throw UnixError("sendto");
}

int Utility::Poll( std::vector<pollfd>& pfd, int timeout )
{
	int stat = poll( &pfd[ 0 ], pfd.size(), timeout );
	if ( stat < 0 )
		exit( 1 );
	return stat;
}

