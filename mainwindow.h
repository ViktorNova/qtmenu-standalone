/*
 * qtmenu-standalone
 * ==================
 * (C) Will Brokenbourgh
 * will_brokenbourgh@yahoo.com
 * http://www.pismotek.com/brainout/
 * - - - -
 * Thank you Jesus!  To God be the glory!  C programming is fun!! :-D
 * - - - -
 * Copyright (C) 2014 - Will Brokenbourgh - will_brokenbourgh@yahoo.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileInfo>
#include <QDir>
#include <QList>
#include <QIcon>
#include <QString>
#include <QStringList>
#include <QProcess>
#include <QMessageBox>
#include <QSize>
#include <QMenu>
#include <QDesktopWidget>
#include <QDebug>

#ifdef __linux__
QString strSysApps = "/usr/share/applications";
QString strSysPix = "/usr/share/pixmaps";
QString strSysIco = "/usr/share/icons";
#endif

#ifdef __FreeBSD__
QString strSysApps = "/usr/local/share/applications";
QString strSysPix = "/usr/local/share/pixmaps";
QString strSysIco = "/usr/local/share/icons";
#endif

class MenuListItem {
public:
    bool operator < (MenuListItem) const;
    bool operator > (MenuListItem) const;
    QString strCategory;
    QString strExec;
    QString strIcon;
    QString strName;

    bool blNeedsTerminal;
};

bool MenuListItem::operator < (MenuListItem mi) const
{
    if (mi.strName < this->strName) {
        return true;
    } else {
        return false;
    }
}


bool MenuListItem::operator > (MenuListItem mi) const
{
    if (mi.strName > this->strName) {
        return true;
    } else {
        return false;
    }
}

#endif // MAINWINDOW_H
