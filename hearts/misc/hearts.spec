%define KDE_DATADIR /usr/share/apps
%define KDE_DOCDIR /usr/doc/kde/HTML
%define KDE_BINDIR /usr/bin
%define KDE_ICONSDIR /usr/share/icons
%define KDE_APPLNKDIR /usr/share/applnk
%define KDE_TRANSLDIR /usr/share/locale

Summary: A card game for the K Desktop Environment
Name: hearts
Version: VERSION
Release: 1
Copyright: GPL
Group: Amusements/Games
Source: http://prdownloads.sourceforge.net/hearts/hearts-VERSION.tar.gz

%description
This is a clone of Ms windows' hearts game for the KDE.

%prep
%setup
%build
./configure
make
%install
make install
%files
%doc README
%doc TODO
%{KDE_DATADIR}/hearts/C10.bmp
%{KDE_DATADIR}/hearts/C2.bmp
%{KDE_DATADIR}/hearts/C3.bmp
%{KDE_DATADIR}/hearts/C4.bmp
%{KDE_DATADIR}/hearts/C5.bmp
%{KDE_DATADIR}/hearts/C6.bmp
%{KDE_DATADIR}/hearts/C7.bmp
%{KDE_DATADIR}/hearts/C8.bmp
%{KDE_DATADIR}/hearts/C9.bmp
%{KDE_DATADIR}/hearts/Ca.bmp
%{KDE_DATADIR}/hearts/Cj.bmp
%{KDE_DATADIR}/hearts/Ck.bmp
%{KDE_DATADIR}/hearts/Cq.bmp
%{KDE_DATADIR}/hearts/D10.bmp
%{KDE_DATADIR}/hearts/D2.bmp
%{KDE_DATADIR}/hearts/D3.bmp
%{KDE_DATADIR}/hearts/D4.bmp
%{KDE_DATADIR}/hearts/D5.bmp
%{KDE_DATADIR}/hearts/D6.bmp
%{KDE_DATADIR}/hearts/D7.bmp
%{KDE_DATADIR}/hearts/D8.bmp
%{KDE_DATADIR}/hearts/D9.bmp
%{KDE_DATADIR}/hearts/Da.bmp
%{KDE_DATADIR}/hearts/Dj.bmp
%{KDE_DATADIR}/hearts/Dk.bmp
%{KDE_DATADIR}/hearts/Dq.bmp
%{KDE_DATADIR}/hearts/H10.bmp
%{KDE_DATADIR}/hearts/H2.bmp
%{KDE_DATADIR}/hearts/H3.bmp
%{KDE_DATADIR}/hearts/H4.bmp
%{KDE_DATADIR}/hearts/H5.bmp
%{KDE_DATADIR}/hearts/H6.bmp
%{KDE_DATADIR}/hearts/H7.bmp
%{KDE_DATADIR}/hearts/H8.bmp
%{KDE_DATADIR}/hearts/H9.bmp
%{KDE_DATADIR}/hearts/Ha.bmp
%{KDE_DATADIR}/hearts/Hj.bmp
%{KDE_DATADIR}/hearts/Hk.bmp
%{KDE_DATADIR}/hearts/Hq.bmp
%{KDE_DATADIR}/hearts/S10.bmp
%{KDE_DATADIR}/hearts/S2.bmp
%{KDE_DATADIR}/hearts/S3.bmp
%{KDE_DATADIR}/hearts/S4.bmp
%{KDE_DATADIR}/hearts/S5.bmp
%{KDE_DATADIR}/hearts/S6.bmp
%{KDE_DATADIR}/hearts/S7.bmp
%{KDE_DATADIR}/hearts/S8.bmp
%{KDE_DATADIR}/hearts/S9.bmp
%{KDE_DATADIR}/hearts/Sa.bmp
%{KDE_DATADIR}/hearts/Sj.bmp
%{KDE_DATADIR}/hearts/Sk.bmp
%{KDE_DATADIR}/hearts/Sq.bmp


%{KDE_ICONSDIR}/locolor/32x32/apps/hearts.png
%{KDE_ICONSDIR}/locolor/16x16/apps/hearts.png

%{KDE_BINDIR}/hearts
%{KDE_BINDIR}/heartshumanclient
%{KDE_BINDIR}/heartsserver
%{KDE_BINDIR}/heartscomputerclient

%{KDE_APPLNKDIR}/Games/Card/hearts.desktop

