
include_directories(${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )


########### install files ###############


kde4_install_icons(${ICON_INSTALL_DIR})



#original Makefile.am contents follow:

#EXTRA_DIST = hearts.desktop hearts.lsm hearts.spec hi16-app-hearts.png hi32-app-hearts.png Makefile.am
#
#KDE_ICON = AUTO
#
#install-data-local:
#	$(mkinstalldirs) $(kde_appsdir)/Games/Card
#	$(INSTALL_DATA) hearts.desktop $(kde_appsdir)/Games/Card/hearts.desktop
#
#uninstall-local:
#	-rm -f $(kde_appsdir)/Games/Card/hearts.desktop
#
