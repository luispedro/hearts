bin_PROGRAMS = hearts
hearts_SOURCES = carddisplay.cpp hand.cpp humanclient.cpp humaninterface.cpp main.cpp qtconnection.cpp tabledisplayer.cpp options.cpp pointsbox.cpp networkdialog.ui privategamedialog.ui exec.cpp

AM_CXXFLAGS = -foperator-names

INCLUDES := $(all_includes) -I../../common

hearts_METASOURCES = AUTO

EXTRA_DIST = carddisplay.h hand.h humanclient.h humanclientoptions.h humaninterface.h pointsbox.h options.h qtconnection.h tabledisplayer.h carddisplay.cpp hand.cpp humanclient.cpp humaninterface.cpp main.cpp pointsbox.cpp qtconnection.cpp tabledisplayer.cpp options.h options.cpp privategamedialog.ui.h

SUBDIRS = pics 

hearts_LDFLAGS = $(all_libraries) $(KDE_RPATH) $(LIB_KIO)

hearts_LDADD = ../../common/communication/libcomhearts.a ../../common/hearts/libhearts.a ../../common/general/libgenhearts.a  -lkdeui -lkdecore -lXext -lX11 $(LIBSOCKET) ../../common/network/libnethearts.a

messages: rc.cpp
	$(XGETTEXT) --keyword=i18n --keyword=I18N_NOOP *cpp *h --c++ -o messages.pot 

