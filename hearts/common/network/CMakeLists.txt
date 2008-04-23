
include_directories(${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} ..)


########### next target ###############


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
