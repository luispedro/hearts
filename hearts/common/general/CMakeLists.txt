include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${KDE3_INCLUDE_DIR} ${QT_INCLUDE_DIR} ..)


########### next target ###############

SET(genhearts_STAT_SRCS
   error.cpp
   utilitario.cpp
   min_time.cpp
)

kde3_automoc(${genhearts_STAT_SRCS})

add_library(genhearts STATIC ${genhearts_STAT_SRCS})


########### install files ###############




#original Makefile.am contents follow:

#noinst_LIBRARIES = libgenhearts.a
#
#libgenhearts_a_SOURCES = error.cpp utilitario.cpp min_time.cpp
#
#
#EXTRA_DIST = auto_init.h circular_iterator.h error.h helper.h min_time.h utilitario.h error.cpp min_time.cpp utilitario.cpp
#AM_CXXFLAGS = -fexceptions
