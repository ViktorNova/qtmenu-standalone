qtmenu-standalone
=================

Classic 'start menu' style standalone application launcher written in QT, that can be used with any panel (or without one)
#### By Will Brokenbourgh
#### *http://www.pismotek.com/brainout/content/qtmenu.php*

Update - 2014-02-25
I removed this project from Github as it wasn't worth the effort. All updates and support should be through this blog now. Thanks! :-)
As if there aren't enough software projects in the world, I am adding yet another one. I'm tentively calling it 'Qt Menu - Standalone'.

I created Qt Menu Standalone because I use Fluxbox as my window manager on Linux and I'm pretty happy with it. The problem is that Fluxbox's built-in toolbar doesn't have launchers nor does it have the kind of menu you might find on lxpanel or xfce4-panel. For a while I was using lxpanel with Fluxbox, but it kept crashing when Thunderbird would display Lightning alerts. I couldn't find anything in the Debian or Ubuntu repos that would do what I wanted, so...

Let me be honest and up-front here...this is my first Qt project. For ages I've been using Gtk2 / PyGtk2 and usually got it to do what I want, but it sometimes was a bother. And with Gtk3 (and Gnome 3 in general) being so buggy and unstable, I decided to try out Qt. I really like it! It's almost fun to develop in Qt Creator. I am a decent programmer, but right now I admit that I'm not completely up-to-date on XDG specifications, so this menu might not work exactly as it should (yet). Also Qt Menu is NOT YET LOCALIZED for other languages, currently only English.

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
 
 
