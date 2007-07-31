AUTOMAKE_OPTIONS = foreign 

SUBDIRS = common server misc po clients

EXTRA_DIST = admin README TODO COPYING


#common flags
AM_CXXFLAGS = -foperator-names -Wall

dist-hook:
	cd $(top_distdir) && perl admin/am_edit

messages: rc.cpp
	$(EXTRACTRC) `find -name \*.ui` > rc.cpp
	FILES=`find -name \*.cpp -o -name \*.h`; \
	$(XGETTEXT) --keyword=i18n --keyword=I18N_NOOP $$FILES --c++ -o ./po/hearts.pot

$(top_srcdir)/acinclude.m4: $(top_srcdir)/admin/acinclude.m4.in $(top_srcdir)/admin/libtool.m4.in
	@cd $(top_srcdir) && cat admin/acinclude.m4.in admin/libtool.m4.in > acinclude.m4

