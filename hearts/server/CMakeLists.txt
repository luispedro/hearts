include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${KDE3_INCLUDE_DIR} ${QT_INCLUDE_DIR} ../common)


########### next target ###############

SET(heartsserver_SRCS
   connectingplayer.cpp
   gamemanager.cpp
   main.cpp
   player.cpp
   options.cpp
   server.cpp
   id_to_fd.cpp
   open.cpp
)

kde3_automoc(${heartsserver_SRCS})

kde3_add_executable(heartsserver ${heartsserver_SRCS})

target_link_libraries(heartsserver ${QT_AND_KDECORE_LIBS} comhearts heartslib genhearts)

install(TARGETS heartsserver DESTINATION bin)


########### install files ###############




#original Makefile.am contents follow:

######## kdevelop will overwrite this part!!! (begin)##########
#bin_PROGRAMS = heartsserver
#heartsserver_SOURCES = connectingplayer.cpp gamemanager.cpp main.cpp player.cpp options.cpp server.cpp id_to_fd.cpp open.cpp 
#heartsserver_LDADD   = ../common/communication/libcomhearts.a ../common/hearts/libhearts.a ../common/general/libgenhearts.a
#AM_CXXFLAGS = -foperator-names -fexceptions -fexceptions
#SUBDIRS = 
#
#EXTRA_DIST = connectingplayer.cpp gamemanager.cpp id_to_fd.cpp main.cpp options.cpp player.cpp server.cpp table.cpp connectingplayer.h gamemanager.h id_to_fd.h options.h player.h server.h table.h
#
#INCLUDES := $(all_includes) -I../common
#
