
Debian
====================
This directory contains files used to package swampd/swamp-qt
for Debian-based Linux systems. If you compile swampd/swamp-qt yourself, there are some useful files here.

## swamp: URI support ##


swamp-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install swamp-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your swamp-qt binary to `/usr/bin`
and the `../../share/pixmaps/swamp128.png` to `/usr/share/pixmaps`

swamp-qt.protocol (KDE)

