qtmenu-standalone
=================

Classic 'start menu' style standalone application launcher written in QT, that can be used with any panel (or without one)
#### By Will Brokenbourgh
#### *http://www.pismotek.com/brainout/content/qtmenu.php*

Features
 • Checks /usr/share/applications and ~/.local/share/applications.
 • Checks every time menu is shown -- newly installed apps should appear right away.
 • Foreground and background colors can be customized.
 • Qt Menu Standalone position can be customized (defaults to lower-left).
 • Custom frequently-used programs can be displayed (at top of menu).
 • Commands for Run..., Exit, Reboot and Shutdown can be customized.
 • Menu item icon theme can be customized
 • All options are set in the .qtmenu config file
 • Using default options, should respect settings by Qt Config (possibly KDE...don't know yet)
 • Hide / show Gnome, KDE, LXDE and other desktop environment items
Qt Menu

Current Issues
 • Only displays English text
 • Only complete icon themes should be used otherwise huge icons may appear (is Qt4 problem)
 • Has problems finding icons for certain apps (Qt issue, Gtk finds them fine)
 • No tooltips for menu items. I do not want them. Feel free to hack and add that! erp
 • Is my first Qt project...gimme a break! erp
 
 
