#include <sys/time.h>
class MinTime
{
	public:

		MinTime( unsigned usecs );
		~MinTime();
	private:
		timeval begin;
};

