#include "fdconnection.h"
#include "protocol.h"
#include "general/utilitario.h"
#include "general/helper.h"

#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>
#include <sys/poll.h>

FDConnection::FDConnection( int fd )
		: fd_( fd ),
		pfd_( 0 )
{
	// check if it is a valid file descriptor
	assert( fcntl( fd, F_GETFL, 0 ) != -1 );
}

void FDConnection::register_pollfd( pollfd& new_pfd )
{
	pfd_ = &new_pfd;
	pfd_->fd = fd_;
	pfd_->events = POLLIN | POLLERR;
	if ( !out_buffer_.empty() )
		pfd_->events |= POLLOUT;
}

void FDConnection::poll_success()
{
	assert( pfd_ );
	assert( fd_ == pfd_->fd );
	const int revents = pfd_->revents;
	if ( revents & POLLIN ) {
		std::vector<char> buf;
		Utility::read_to_vector( fd_, buf );
		if ( buf.empty() )      // EOF
		{
			LOG_PLACE() << " EOF\n";
			exit( 2 );
		}
		in_buffer_.put( buf );
	}
	if ( revents & POLLOUT ) {
		Utility::write_from_vector( fd_, out_buffer_ );
		if ( out_buffer_.empty() )
			pfd_->events &= ~POLLOUT;
	}
	if ( revents & POLLERR ) {
		char c;
		::read( fd_, &c, 0 );
		LOG_PLACE() << " Poll error: " << strerror( errno ) << ".\n";
		exit( 2 );
		//throw UnixError();
	}
}


bool FDConnection::message_available() const
{
	return in_buffer_.messageAvailable();
}

Message FDConnection::get_message()
{
	return in_buffer_.get();
}

void FDConnection::write( Message m )
{
	const std::string encoded_msg = Protocol::encode_term( m );
	out_buffer_.reserve( out_buffer_.size() + encoded_msg.size() ); // avoid copies
	std::copy( encoded_msg.begin(), encoded_msg.end(), back_inserter( out_buffer_ ) );
	pfd_->events |= POLLOUT;
}


