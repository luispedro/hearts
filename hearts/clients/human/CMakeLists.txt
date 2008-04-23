add_subdirectory(pics)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${KDE3_INCLUDE_DIR} ${QT_INCLUDE_DIR} ../../common)


########### next target ###############

SET(hearts_SRCS
   carddisplay.cpp
   hand.cpp
   humanclient.cpp
   humaninterface.cpp
   main.cpp
   qtconnection.cpp
   tabledisplayer.cpp
   options.cpp
   pointsbox.cpp
   exec.cpp
   networkmanager.cpp
)

kde3_automoc(${hearts_SRCS})

set(hearts_UI
    networkdialog.ui
    privategamedialog.ui
    preferencesdialog.ui
)

kde3_add_ui_files(hearts_SRCS ${hearts_UI})

kde3_add_executable(hearts ${hearts_SRCS})

target_link_libraries(hearts ${QT_AND_KDECORE_LIBS} kio crypto comhearts heartslib genhearts kdeui kdecore Xext X11 nethearts)

install(TARGETS hearts DESTINATION bin)


########### install files ###############




#original Makefile.am contents follow:

#bin_PROGRAMS = hearts
#hearts_SOURCES = carddisplay.cpp hand.cpp humanclient.cpp humaninterface.cpp main.cpp qtconnection.cpp tabledisplayer.cpp options.cpp pointsbox.cpp networkdialog.ui privategamedialog.ui exec.cpp preferencesdialog.ui networkmanager.cpp
#
#AM_CXXFLAGS = -foperator-names
#
#INCLUDES := $(all_includes) -I../../common
#
#hearts_METASOURCES = AUTO
#
#EXTRA_DIST = carddisplay.h hand.h humanclient.h humanclientoptions.h humaninterface.h pointsbox.h options.h qtconnection.h tabledisplayer.h carddisplay.cpp hand.cpp humanclient.cpp humaninterface.cpp main.cpp pointsbox.cpp qtconnection.cpp tabledisplayer.cpp options.h options.cpp privategamedialog.ui.h preferencesdialog.ui.h networkmanager.h
#
#SUBDIRS = pics 
#
#hearts_LDFLAGS = $(all_libraries) $(KDE_RPATH) $(LIB_KIO) -lcrypto
#
#hearts_LDADD = ../../common/communication/libcomhearts.a ../../common/hearts/libhearts.a ../../common/general/libgenhearts.a  -lkdeui -lkdecore -lXext -lX11 $(LIBSOCKET) ../../common/network/libnethearts.a
#
#messages: rc.cpp
#	$(XGETTEXT) --keyword=i18n --keyword=I18N_NOOP *cpp *h --c++ -o messages.pot 
#
