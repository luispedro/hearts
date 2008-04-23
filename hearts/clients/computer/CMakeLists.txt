include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${KDE3_INCLUDE_DIR} ${QT_INCLUDE_DIR} ../../common)


########### next target ###############

SET(heartscomputerclient_SRCS
   computerplayer.cpp
   computerplayer3_2.cpp
   computerplayer4.cpp
   computerplayerbase.cpp
   main.cpp
   options.cpp
)

kde3_automoc(${heartscomputerclient_SRCS})

kde3_add_executable(heartscomputerclient ${heartscomputerclient_SRCS})

target_link_libraries(heartscomputerclient ${QT_AND_KDECORE_LIBS} comhearts heartslib genhearts)

install(TARGETS heartscomputerclient DESTINATION bin)


########### install files ###############




#original Makefile.am contents follow:

#bin_PROGRAMS = heartscomputerclient
#
#heartscomputerclient_SOURCES = computerplayer.cpp computerplayer3_2.cpp computerplayer4.cpp computerplayerbase.cpp main.cpp options.cpp
#EXTRA_DIST = computerplayer.h computerplayer3_2.h computerplayer4.h computerplayerbase.h computerplayer.cpp computerplayer3_2.cpp computerplayer4.cpp computerplayerbase.cpp main.cpp options.h options.cpp
#
#heartscomputerclient_LDADD = ../../common/communication/libcomhearts.a ../../common/hearts/libhearts.a ../../common/general/libgenhearts.a   
#
#INCLUDES = -I../../common
#
