include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${KDE3_INCLUDE_DIR} ${QT_INCLUDE_DIR} ..)


########### next target ###############

SET(comhearts_STAT_SRCS
   dispatch.cpp
   factory.cpp
   fdconnection.cpp
   message.cpp
   protocol.cpp
   open_connections.cpp
   translator.cpp
   typicalclient.cpp
   typicalserver.cpp
)

kde3_automoc(${comhearts_STAT_SRCS})

add_library(comhearts STATIC ${comhearts_STAT_SRCS})


########### install files ###############




#original Makefile.am contents follow:

#noinst_LIBRARIES = libcomhearts.a
#
#libcomhearts_a_SOURCES = dispatch.cpp factory.cpp fdconnection.cpp message.cpp protocol.cpp open_connections.cpp translator.cpp typicalclient.cpp typicalserver.cpp
#
#EXTRA_DIST = connection.h dispatch.h factory.h fdconnection.h message.h open_connections.h protocol.h translator.h typicalclient.h typicalserver.h dispatch.cpp factory.cpp fdconnection.cpp message.cpp open_connections.cpp protocol.cpp translator.cpp typicalclient.cpp typicalserver.cpp constants.h
#
#INCLUDES = -I..
#
#AM_CXXFLAGS = -foperator-names -g
#
