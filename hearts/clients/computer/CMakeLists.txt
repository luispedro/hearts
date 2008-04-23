
include_directories(${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} ../../common)


########### next target ###############

set(heartscomputerclient_SRCS
    computerplayer.cpp
    computerplayer3_2.cpp
    computerplayer4.cpp
    computerplayerbase.cpp
    main.cpp
    options.cpp)

kde4_add_executable(heartscomputerclient ${heartscomputerclient_SRCS})

target_link_libraries(heartscomputerclient ${KDE4_KDECORE_LIBS} comhearts hearts genhearts)

install(TARGETS heartscomputerclient DESTINATION ${BIN_INSTALL_DIR})


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
