#ifndef HELPER_H_INCLUDE_GUARD_DB
#define HELPER_H_INCLUDE_GUARD_DB

#include <cstdlib>
#include <iostream>

#define LOG_PLACE() std::cerr << __PRETTY_FUNCTION__ << " in file " << __FILE__ << ':' <<  __LINE__

#define massert(x) do { if (!(x)) { LOG_PLACE() << " ASSERTION FAILED: " << #x << ".\n"; abort(); }} while (0);

#define LOG_PUT(x) "  |" #x " = " << x

#define LOG_PLACE_NL() LOG_PLACE() << '\n';

#endif /* HELPER_H_INCLUDE_GUARD_DB */

