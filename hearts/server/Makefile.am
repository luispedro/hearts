####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = heartsserver
heartsserver_SOURCES = connectingplayer.cpp gamemanager.cpp main.cpp player.cpp options.cpp server.cpp id_to_fd.cpp open.cpp 
heartsserver_LDADD   = ../common/communication/libcomhearts.a ../common/hearts/libhearts.a ../common/general/libgenhearts.a
AM_CXXFLAGS = -foperator-names -fexceptions -fexceptions
SUBDIRS = 

EXTRA_DIST = connectingplayer.cpp gamemanager.cpp id_to_fd.cpp main.cpp options.cpp player.cpp server.cpp table.cpp connectingplayer.h gamemanager.h id_to_fd.h options.h player.h server.h table.h

INCLUDES := $(all_includes) -I../common

