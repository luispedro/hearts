#ifndef _HOME_LUIS_HEARTS_NETWORK_BUFFER_H
#define _HOME_LUIS_HEARTS_NETWORK_BUFFER_H
#include <vector>
#include <queue>
#include <ksock.h>

#include "message.h"

class InBuffer
{
		public:
				
				InBuffer& operator >> ( Message& );
				operator const volatile void* () const volatile
				{
						if ( ok_ ) return this;
						return 0;
				}

				void clearError() { ok_ = true; }
				void putLine( const char* );
		private:
				std::queue<Message> queue_;
				bool ok_;
};

class OutBuffer
{
		public:
				OutBuffer& operator << ( const Message& );
//X 				operator const volatile void
				void write( char*, size_t );
				bool empty() const { return buffer_.empty(); }
		private:
				std::vector<char> buffer_;
};
#endif // /HOME/LUIS/HEARTS/NETWORK/BUFFER_H
