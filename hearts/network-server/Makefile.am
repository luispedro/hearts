bin_PROGRAMS = heartsd
heartsd_SOURCES = main.cpp player.cpp server.cpp table.cpp options.cpp logfile.cpp motd.cpp inifile.cpp
heartsd_LDFLAGS = $(all_libraries) $(KDE_RPATH)

heartsd_LDADD   = ../common/network/libnethearts.a ../common/communication/libcomhearts.a ../common/hearts/libhearts.a ../common/general/libgenhearts.a  ../common/network/libnethearts.a -lkdeui -lkdecore -lXext -lX11 $(LIBSOCKET) -lqt-mt

AM_CXXFLAGS = -foperator-names -I../common -g


SUBDIRS = 

METASOURCES = AUTO

EXTRA_DIST = player.h table.cpp table.h main.cpp options.h

INCLUDES := $(all_includes) -I../common

inifiletest: inifile.h inifile.cpp
	$(CXX) -g -DTEST_INIFILE -o $@ inifile.cpp 
