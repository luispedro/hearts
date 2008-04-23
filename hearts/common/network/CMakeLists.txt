include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${KDE3_INCLUDE_DIR} ${QT_INCLUDE_DIR} ..)


########### next target ###############

SET(nethearts_STAT_SRCS
   buffer.cpp
   connection.cpp
   message.cpp
   authentication.cpp
   user_status.cpp
)

kde3_automoc(${nethearts_STAT_SRCS})

add_library(nethearts STATIC ${nethearts_STAT_SRCS})


########### install files ###############




#original Makefile.am contents follow:

#noinst_LIBRARIES = libnethearts.a
#
#libnethearts_a_SOURCES = buffer.cpp connection.cpp message.cpp  authentication.cpp user_status.cpp
#
#AM_CXXFLAGS = -foperator-names -g
#
#METASOURCES = AUTO
#
#EXTRA_DIST = authentication.h buffer.h connection.h message.h playerid.h  tableid.h Makefile.am Makefile.in user_status.h
#
#INCLUDES = $(all_includes) -I../../common
#
