
include_directories(${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} ..)


########### next target ###############


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
