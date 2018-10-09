
Debian
====================
This directory contains files used to package vecod/veco-qt
for Debian-based Linux systems. If you compile vecod/veco-qt yourself, there are some useful files here.

## veco: URI support ##


veco-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install veco-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your veco-qt binary to `/usr/bin`
and the `../../share/pixmaps/veco128.png` to `/usr/share/pixmaps`

veco-qt.protocol (KDE)

