#include "buffer.h"
#include <algorithm>
#include <qstringlist.h>

InBuffer& InBuffer::operator >> ( Message& m )
{
		if ( queue_.empty() )
		{
				ok_ = false;
		} 
		else 
		{
				m = queue_.front();
				queue_.pop();
		}
		return *this;
}

namespace {
		Message decodeMessage( QString encoded )
		{
				MessageConstructor res;
				Message::typeEnum type;
				QStringList parts = QStringList::split( ' ',encoded );
				type = Message::typeEnum( -1 );
#define HANDLE( x ) if ( parts[ 0 ] == #x ) type = Message::x;
				HANDLE_ALL_MESSAGE_TYPES;
		
	
				res << type;
				switch ( type )
				{
						case Message::joinTable:
						case Message::leaveTable:
								{
										res << parts[ 1 ]; // table name
								}
						default:
								assert( 0 );
				}
				return res;
		}
}

void InBuffer::putLine( const char* line )
{
		queue_.push( decodeMessage( QString::fromUtf8( line ) ) );
}

				
