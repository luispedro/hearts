bin_PROGRAMS = networkserver
networkserver_SOURCES = main.cpp player.cpp server.cpp table.cpp
networkserver_LDFLAGS = $(all_libraries) $(KDE_RPATH)

networkserver_LDADD   = ../common/network/libnethearts.a ../common/communication/libcomhearts.a ../common/hearts/libhearts.a ../common/general/libgenhearts.a  ../common/network/libnethearts.a -lkdeui -lkdecore -lXext -lX11 $(LIBSOCKET) -lqt-mt

AM_CXXFLAGS = -foperator-names -I../common -g


SUBDIRS = 

METASOURCES = AUTO

EXTRA_DIST = player.cpp player.h table.cpp table.h main.cpp

INCLUDES := $(all_includes) -I../common

