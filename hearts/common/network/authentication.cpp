#include "authentication.h"
#include <kmdcodec.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#ifdef TEST_ME
#include <iostream>
#endif

void pretty_printing( const char* input, char** result )
{
	const unsigned res_size = 128/8 * 2 + 1;
	*result = static_cast<char*>( std::malloc( res_size ) );
	( *result )[ res_size - 1 ] = '\0';
	for ( unsigned i = 0; i != res_size; ++i ) {
		switch ( 0xf & ( input[ i / 2 ] >> ( ( i%2 )* 4 ) ) ) {
#define			CASE( X ) case 0x ## X : ( *result )[ i ] = #X [ 0 ]; break
			CASE( 0 );
			CASE( 1 );
			CASE( 2 );
			CASE( 3 );
			CASE( 4 );
			CASE( 5 );
			CASE( 6 );
			CASE( 7 );
			CASE( 8 );
			CASE( 9 );
			CASE( a );
			CASE( b );
			CASE( c );
			CASE( d );
			CASE( e );
			CASE( f );
			default: 
//			fprintf( stderr, "\n\n ----- %d ----\n\n",
//					( unsigned ) (  0xf & (  input[  i / 2 ] >> (  (  i%2 )* 4 ) ) ) );
			assert( 0 );
		}
	}
}

void do_md5( const char* input, char* result )
{
	KMD5 calculator( input );
	unsigned char dig[ 16 ];
	calculator.rawDigest( dig );
	std::strcpy( result, ( const char* )dig );
#ifdef TEST_ME
	char* pretty;
	pretty_printing( result, &pretty );
	std::cout << "md5( . ): " << pretty << std::endl;
	std::free( pretty );
#endif
}

void do_xor( char* io, const char* input, unsigned nbytes )
{
	unsigned char* u_io = reinterpret_cast<unsigned char*>( io );
	const unsigned char* u_input = reinterpret_cast<const unsigned char*>( input );
	while ( nbytes ) {
		*u_io ^= *u_input;
		++u_io;
		++u_input;
		--nbytes;
	}
}

int repeatedMD5Authenticator::generate( const char* password, const char* cookie, char** result)
{
	if ( !password || !cookie ) return 1;
	const unsigned nbytes_for_hash = 128/8;
	char password5[ nbytes_for_hash ];
	char cookie5[ nbytes_for_hash ];
	char result5[ nbytes_for_hash ];
	do_md5( password, password5 );
	do_md5( cookie, cookie5 );
	do_xor( password5, cookie5, nbytes_for_hash );
	do_md5( password5, result5 );
	pretty_printing( result5, result );
	return 0;
}

unsigned rand_mod( unsigned max ) {
	return unsigned( rand() ) % max;
}

QCString repeatedMD5Authenticator::generateCookie()
{
	char buff[ 24 ];
	const unsigned size = rand_mod( 12 ) + 12;
	buff[ size ] = '\0';
	for ( unsigned i = 0; i != size; ++i ) {
		static const char possibilities[] = "1234567890poiuytrewqasdfghjklmnbvcxzMNBVCXZASDFGHJKLPOIUYTREWQ";
		buff[ i ] = possibilities[ rand_mod( sizeof( possibilities ) ) ];
	}
	return QCString( buff );
}


#ifdef TEST_ME

int main() {
	repeatedMD5Authenticator auth;
	std::string pass, cookie;
	std::cin >> pass >> cookie;
	char* result;
	if ( auth.generate( pass.c_str(), cookie.c_str(), &result ) ) return 1;
	std::cout << result << std::endl;
	std::cout << ( const char* )auth.generateCookie() << std::endl;
	std::cout << ( const char* )auth.generateCookie() << std::endl;
	std::cout << ( const char* )auth.generateCookie() << std::endl;
	std::cout << ( const char* )auth.generateCookie() << std::endl;
	return 0;
}
#endif

