####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = hearts
hearts_SOURCES = carddisplay.cpp hand.cpp humanclient.cpp humaninterface.cpp main.cpp multilinebox.cpp qtconnection.cpp tabledisplayer.cpp serveraddressdialog.cpp options.cpp

AM_CXXFLAGS = -foperator-names

INCLUDES := $(all_includes) -I../../common

hearts_METASOURCES = AUTO

EXTRA_DIST = carddisplay.h hand.h humanclient.h humanclientoptions.h humaninterface.h multilinebox.h options.h qtconnection.h tabledisplayer.h carddisplay.cpp hand.cpp humanclient.cpp humaninterface.cpp main.cpp multilinebox.cpp qtconnection.cpp tabledisplayer.cpp serveraddressdialog.cpp serveraddressdialog.h options.h options.cpp

SUBDIRS = pics setup 

hearts_LDFLAGS = $(all_libraries) $(KDE_RPATH) 

hearts_LDADD = setup/libheartssetup.a ../../common/communication/libcomhearts.a ../../common/hearts/libhearts.a ../../common/general/libgenhearts.a  -lkdeui -lkdecore -lXext -lX11 $(LIBSOCKET) ../../common/network/libnethearts.a

messages: 
	$(XGETTEXT) --keyword=i18n --keyword=I18N_NOOP *cpp *h --c++ -o messages.pot 
