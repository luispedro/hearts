#include "min_time.h"
#include <unistd.h>
#include "helper.h"

MinTime::MinTime( unsigned usecs )
{
	gettimeofday( &begin, 0 );
	begin.tv_usec += usecs;
	while ( begin.tv_usec >= 1000000 ) {
		begin.tv_sec += 1;
		begin.tv_usec -= 1000000;
	}
}

MinTime::~MinTime()
{
	timeval end;
	do {
		gettimeofday( &end, 0 );
		usleep( 100 );
	} while ( timercmp( &begin, &end, > ) );
}



