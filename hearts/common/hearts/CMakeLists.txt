include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${KDE3_INCLUDE_DIR} ${QT_INCLUDE_DIR} ..)


########### next target ###############

SET(heartslib_STAT_SRCS
   card.cpp
   deck.cpp
   holder3.cpp
   player_id.cpp
   table.cpp
   player_status.cpp
)

kde3_automoc(${heartslib_STAT_SRCS})

add_library(heartslib STATIC ${heartslib_STAT_SRCS})


########### install files ###############




#original Makefile.am contents follow:

#
#AUTOMAKE_OPTIONS = foreign
#noinst_LIBRARIES = libhearts.a
#libhearts_a_SOURCES = card.cpp deck.cpp holder3.cpp player_id.cpp table.cpp player_status.cpp
#INCLUDES = -I..
#AM_CXXFLAGS = -foperator-names
#
#EXTRA_DIST = card.h cards.h deck.h holder3.h player_id.h player_status.h table.h card.cpp deck.cpp holder3.cpp player_id.cpp player_status.cpp table.cpp
