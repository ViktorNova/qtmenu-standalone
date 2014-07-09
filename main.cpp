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


#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QAction *qaAction;
    QMenu *menMain = new QMenu();

    QMenu *menPref = new QMenu();
    QMenu *menAcc = new QMenu();
    QMenu *menDevel = new QMenu();
    QMenu *menEdu = new QMenu();
    QMenu *menGraph = new QMenu();
    QMenu *menHam = new QMenu();
    QMenu *menInter = new QMenu();
    QMenu *menMulti = new QMenu();
    QMenu *menOffic = new QMenu();
    QMenu *menOth = new QMenu();
    QMenu *menSci = new QMenu();
    QMenu *menSys = new QMenu();

    QDesktopWidget *qDesktop = new QDesktopWidget();
    QRect qrDesktop = qDesktop->availableGeometry();
    QFile file(QDir::homePath() + "/.qtmenu");
    QString strProcess;
    QString strForeColor;
    QString strBackColor;
    int nLeft = -1;
    int nTop = -1;

    QDir qdDir = QDir(strSysApps);
    QFileInfoList qflList = qdDir.entryInfoList();

    QString strRunCommand = "fbrun -nearmouse";
    QString strExitCommand = "fluxbox-remote quit";
    QString strRebootCommand = "sudo reboot";
    QString strPoweroffCommand = "sudo poweroff";
    QStringList strlistCustoms;
    QString strTheme;

    bool blShowGNOME = true;
    bool blShowLXDE = true;
    bool blShowKDE = true;
    bool blShowMATE = true;
    bool blShowXFCE = true;


    QList<MenuListItem> mliList;
    MenuListItem mliListTemp;
    QMenu *menTemp;
    int nCount = qflList.count() - 1;
    bool blFirstLoop = true;
    bool blHasCustoms = false;

    bool blIconHasPath = false;
    bool blIconHasExt = false;

    // process config file
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while (!file.atEnd())
        {
            strProcess = file.readLine().trimmed();

            // left positioning
            if (strProcess.toLower().startsWith("left=")) {
                strProcess.remove(0, 5);
                nLeft = strProcess.toInt();
            } else
            // top positioning
            if (strProcess.toLower().startsWith("top=")) {
                strProcess.remove(0, 4);
                nTop = strProcess.toInt();
            } else
            // custom menu items
            if (strProcess.toLower().startsWith("custom=")) {
                strProcess.remove(0, 7);
                strlistCustoms.append(strProcess);
            } else
            // theme
            if (strProcess.toLower().startsWith("icontheme=")) {
                strProcess.remove(0, 10);
                strTheme = strProcess;
            } else
            // foreground
            if (strProcess.toLower().startsWith("fg=")) {
                strProcess.remove(0, 3);
                if (strProcess != "") {
                    strForeColor = strProcess;
                }
            } else
            // background
            if (strProcess.toLower().startsWith("bg=")) {
                strProcess.remove(0, 3);
                if (strProcess != "") {
                    strBackColor = strProcess;
                }
            } else
            // show gnome items?
            if (strProcess.toLower().startsWith("showgnomeitems=")) {
                strProcess.remove(0, 15);
                if (strProcess.contains("true") ) {
                    blShowGNOME = true;
                } else {
                    blShowGNOME = false;
                }
            } else
            // show lxde items?
            if (strProcess.toLower().startsWith("showlxdeitems=")) {
                strProcess.remove(0, 14);
                if (strProcess.contains("true") ) {
                    blShowLXDE = true;
                } else {
                    blShowLXDE = false;
                }
            } else
            // show kde items?
            if (strProcess.toLower().startsWith("showkdeitems=")) {
                strProcess.remove(0, 14);
                if (strProcess.contains("true") ) {
                    blShowKDE = true;
                } else {
                    blShowKDE = false;
                }
            } else
            // show mate items?
            if (strProcess.toLower().startsWith("showmateitems=")) {
                strProcess.remove(0, 14);
                if (strProcess.contains("true") ) {
                    blShowMATE = true;
                } else {
                    blShowMATE = false;
                }
            } else
            // show xfce items?
            if (strProcess.toLower().startsWith("showxfceitems=")) {
                strProcess.remove(0, 14);
                if (strProcess.contains("true") ) {
                    blShowXFCE = true;
                } else {
                    blShowXFCE = false;
                }
            } else
            // run command
            if (strProcess.toLower().startsWith("runcommand=")) {
                strProcess.remove(0, 11);
                if (strProcess != "") {
                    strRunCommand = strProcess;
                }
            } else
            // exit command
            if (strProcess.toLower().startsWith("exitcommand=")) {
                strProcess.remove(0, 12);
                if (strProcess != "") {
                    strExitCommand = strProcess;
                }
            } else
            // reboot command
            if (strProcess.toLower().startsWith("restartcommand=")) {
                strProcess.remove(0, 15);
                if (strProcess != "") {
                    strRebootCommand = strProcess;
                }
            } else
            // poweroff command
            if (strProcess.toLower().startsWith("poweroffcommand=")) {
                strProcess.remove(0, 16);
                if (strProcess != "") {
                    strPoweroffCommand = strProcess;
                }
            }
        }
    }

    // set icon theme
    if (strTheme != "") {
        QIcon::setThemeName(strTheme);
    } else {
        QIcon::setThemeName("hicolor");
    }

    // custom menu items from config file
    for (int n = 0; n < strlistCustoms.count(); n++)
    {
        MenuListItem mi;

        strProcess = strlistCustoms.at(n);
        mi.strName = strProcess.section("|", 0, 0);
        mi.strExec = strProcess.section("|", 1, 1);
        mi.strIcon = strProcess.section("|", 2, 2);
        mi.strCategory = "CustomItems";

        mliList.append(mi);

        blHasCustoms = true;
    }

    // read desktop files and insert menu items
    for (int n = 0; n < nCount;)
    {
        QFileInfo fileInfo = qflList.at(n);
        QFile qfFile(fileInfo.absoluteFilePath());
        MenuListItem mi;
        bool blNoShow = false;
        bool blOkToParse = false;

        if (qfFile.open(QIODevice::ReadOnly|QIODevice::Text)) {
            while (!qfFile.atEnd())
            {
                strProcess = qfFile.readLine();

                // set parse flag if we are in the Desktop Entry section
                if (strProcess.startsWith("[") && strProcess.contains("Desktop Entry")) {
                    blOkToParse = true;
                }
                if (blOkToParse) {
                    // app name
                    if (strProcess.startsWith("Name=")) {
                        strProcess.remove(0,5);
                        mi.strName = strProcess.trimmed().remove("_");
                    } else
                    // app icon
                    if (strProcess.startsWith("Icon=")) {
                        strProcess.remove(0,5);
                        mi.strIcon = strProcess.trimmed();
                    } else
                    // app exec line
                    if (strProcess.startsWith("Exec=")) {
                        strProcess.remove(0,5);
                        mi.strExec = strProcess.trimmed();
                        mi.strExec.remove("%F");
                        mi.strExec.remove("%f");
                        mi.strExec.remove("%U");
                        mi.strExec.remove("%u");
                    } else
                    // app category
                    if (strProcess.startsWith("Categories=")) {
                        if (blFirstLoop) {
                            strProcess.remove(0,11);
                            mi.strCategory = strProcess.trimmed();
                        } else {
                            mi.strCategory = "Other";
                        }
                    } else
                    // needs terminal?
                    if (strProcess.startsWith("Terminal=")) {
                        strProcess.remove(0,9);

                        if (strProcess.toLower().contains("true")) {
                            mi.blNeedsTerminal = true;
                        } else {
                            mi.blNeedsTerminal = false;
                        }
                    } else
                    // don't display?
                    if (strProcess.startsWith("NoDisplay=")) {
                        strProcess.remove(0,10);
                        if (strProcess.contains("True") ||
                           strProcess.contains("true")
                           ) {
                            blNoShow = true;
                        }
                    } else
                    // show gnome stuff?
                    if (strProcess.contains("OnlyShowIn=GNOME")) {
                        if (blShowGNOME == true) {
                            blNoShow = false;
                        } else {
                            blNoShow = true;
                        }
                    } else
                    // show lxde stuff?
                    if (strProcess.contains("OnlyShowIn=LXDE")) {
                        if (blShowLXDE == true) {
                            blNoShow = false;
                        } else {
                            blNoShow = true;
                        }
                    } else
                    // show kde stuff?
                    if (strProcess.contains("OnlyShowIn=KDE")) {
                        if (blShowKDE == true) {
                            blNoShow = false;
                        } else {
                            blNoShow = true;
                        }
                    } else
                    // show mate stuff?
                    if (strProcess.contains("OnlyShowIn=MATE")) {
                        if (blShowMATE == true) {
                            blNoShow = false;
                        } else {
                            blNoShow = true;
                        }
                    } else
                    // show xfce stuff?
                    if (strProcess.contains("OnlyShowIn=XFCE")) {
                        if (blShowXFCE == true) {
                            blNoShow = false;
                        } else {
                            blNoShow = true;
                        }
                    } else
                    // stop parsing if there are other sections
                    if (strProcess.startsWith("[") && !strProcess.contains("Desktop Entry")) {
                        break;
                    }
                }
            }

            if (mi.strName != "" && !blNoShow) {
                if (mi.blNeedsTerminal) {
                    mi.strExec = "x-terminal-emulator -e " + mi.strExec;
                }
                mliList.append(mi);
            }

        }

        if (qfFile.isOpen()) {
            qfFile.close();
        }

        // switch to local app folder and start over
        if (n == (nCount - 1) && blFirstLoop) {
            qdDir = QDir(QDir::homePath() + "/.local/share/applications");
            qflList = qdDir.entryInfoList();
            nCount = qflList.count() - 1;
            n = 0;
            blFirstLoop = false;
            QApplication::beep();
        } else {
            n++;
        }
    }


    // sort items alphabetically
    qSort(mliList);

    // set up category sub-menus
    menPref->setIcon(QIcon::fromTheme("preferences-desktop", QIcon::fromTheme("document-send")));
    menPref->setTitle("Preferences");
    menAcc->setIcon(QIcon::fromTheme("applications-accessories", QIcon::fromTheme("document-send")));
    menAcc->setTitle("Accessories");
    menDevel->setIcon(QIcon::fromTheme("applications-development", QIcon::fromTheme("document-send")));
    menDevel->setTitle("Development");
    menEdu->setIcon(QIcon::fromTheme("applications-science", QIcon::fromTheme("document-send")));
    menEdu->setTitle("Education");
    menGraph->setIcon(QIcon::fromTheme("applications-graphics", QIcon::fromTheme("document-send")));
    menGraph->setTitle("Graphics");
    menHam->setIcon(QIcon::fromTheme("applications-other", QIcon::fromTheme("document-send")));
    menHam->setTitle("Ham Radio");
    menInter->setIcon(QIcon::fromTheme("applications-internet", QIcon::fromTheme("document-send")));
    menInter->setTitle("Network");
    menMulti->setIcon(QIcon::fromTheme("applications-multimedia", QIcon::fromTheme("document-send")));
    menMulti->setTitle("Multimedia");
    menOffic->setIcon(QIcon::fromTheme("applications-office", QIcon::fromTheme("document-send")));
    menOffic->setTitle("Office");
    menOth->setIcon(QIcon::fromTheme("applications-other", QIcon::fromTheme("document-send")));
    menOth->setTitle("Other");
    menSci->setIcon(QIcon::fromTheme("applications-science", QIcon::fromTheme("document-send")));
    menSci->setTitle("Science");
    menSys->setIcon(QIcon::fromTheme("applications-system", QIcon::fromTheme("document-send")));
    menSys->setTitle("System");


    // *** collate by standard categories ***
    for (int i = mliList.size() - 1; i > -1; --i) {

        menTemp = menOth;

        mliListTemp = mliList.at(i);

        // custom items
        if (mliListTemp.strCategory.contains("CustomItems")) {
            menTemp = menMain;
        } else
        // settings / preferences
        if (mliListTemp.strCategory.contains("=Settings") ||
            mliListTemp.strCategory.contains(";Settings")
           ) {
            menTemp = menPref;
        } else
        // system
        if (mliListTemp.strCategory.contains("System")) {
            menTemp = menSys;
        } else
        // hamradio
        if (mliListTemp.strCategory.contains("HamRadio")) {
            menTemp = menHam;
        } else
        // science
        if (mliListTemp.strCategory.contains("Science")) {
            menTemp = menSci;
        } else
        // accessories / utility
        if (mliListTemp.strCategory.contains("Accessories") ||
            mliListTemp.strCategory.contains("Utility")
           ) {
            menTemp = menAcc;
        } else
        // development / programming
        if (mliListTemp.strCategory.contains("Development")) {
            menTemp = menDevel;
        } else
        // education / science
        if (mliListTemp.strCategory.contains("Education") ||
            mliListTemp.strCategory.contains("Science")
           ) {
            menTemp = menEdu;
        } else
        // graphics
        if (mliListTemp.strCategory.contains("Graphics")) {
            menTemp = menGraph;
        } else
        // internet / network
        if (mliListTemp.strCategory.contains("Internet") ||
                mliListTemp.strCategory.contains("WebBrowser") ||
                mliListTemp.strCategory.contains("Network")
                )
        {
            menTemp = menInter;
        } else

        // multimedia / sound/video
        if (mliListTemp.strCategory.contains("Audio") ||
                mliListTemp.strCategory.contains("AudioVideo") ||
                mliListTemp.strCategory.contains("Multimedia")
                )
        {
            menTemp = menMulti;
        } else
        // office / productivity
        if (mliListTemp.strCategory.contains("Office")  ||
                mliListTemp.strCategory.contains("Productivity")  ||
                mliListTemp.strCategory.contains("WordProcessor")
                )
        {
            menTemp = menOffic;
        }

        /* insert into menu */
        qaAction = new QAction(mliListTemp.strName, NULL);

        // figure out icon
        blIconHasExt = false;
        blIconHasPath = false;

        // has path
        if (mliListTemp.strIcon.contains("/")) {
            blIconHasPath = true;
        }

        // has extension
        if (mliListTemp.strIcon.contains(".png") ||
            mliListTemp.strIcon.contains(".xpm") ||
            mliListTemp.strIcon.contains(".svg")
            ) {
                blIconHasExt = true;
        }

        // no path and no extension
        if (blIconHasExt == false && blIconHasPath == false) {
            qaAction->setIcon(QIcon::fromTheme(mliListTemp.strIcon));
        } else
        // path
        if (blIconHasPath == true) {
            qaAction->setIcon(QIcon(mliListTemp.strIcon));
        } else
        // extension but no path
        if (blIconHasExt == true && blIconHasPath == false) {
            qaAction->setIcon(QIcon::fromTheme(mliListTemp.strIcon));
        }

        if (qaAction->icon().isNull()) {
            if (file.exists(strSysPix + "/" + mliListTemp.strIcon)) {
                qaAction->setIcon(QIcon(strSysPix + "/" + mliListTemp.strIcon));
            } else
            if (file.exists(strSysIco + "/" + mliListTemp.strIcon + ".png")) {
                qaAction->setIcon(QIcon(strSysIco + "/" + mliListTemp.strIcon + ".png"));
            } else
            if (file.exists(strSysIco + "/hicolor/scalable/apps/" + mliListTemp.strIcon + ".svg")) {
                qaAction->setIcon(QIcon(strSysIco + "/hicolor/scalable/apps/" + mliListTemp.strIcon + ".svg"));
            } else
            if (file.exists(strSysPix + "/" + mliListTemp.strIcon + ".png")) {
                qaAction->setIcon(QIcon(strSysPix + "/" + mliListTemp.strIcon + ".png"));
            } else
            if (file.exists(strSysPix + "/" + mliListTemp.strIcon + ".xpm")) {
                qaAction->setIcon(QIcon(strSysPix + "/" + mliListTemp.strIcon + ".xpm"));
            } else
            if (file.exists(strSysPix + "/" + mliListTemp.strIcon + ".svg")) {
                qaAction->setIcon(QIcon(strSysPix + "/" + mliListTemp.strIcon + ".svg"));
            }
        }

        qaAction->setIconVisibleInMenu(true);
        qaAction->setData(mliListTemp.strExec);

        menTemp->addAction(qaAction);
    }


    // add separator if there are customs
    if (blHasCustoms) {
        menMain->addSeparator();
    }

    // preferences
    if (menPref->actions().count() > 0) {
        menMain->addMenu(menPref);
        menMain->addSeparator();
    }

    // accessories
    if (menAcc->actions().count() > 0) {
        menMain->addMenu(menAcc);
    }

    // development
    if (menDevel->actions().count() > 0) {
        menMain->addMenu(menDevel);
    }

    // education
    if (menEdu->actions().count() > 0) {
        menMain->addMenu(menEdu);
    }

    // graphics
    if (menGraph->actions().count() > 0) {
        menMain->addMenu(menGraph);
    }

    // ham radio
    if (menHam->actions().count() > 0) {
        menMain->addMenu(menHam);
    }

    // internet/networking
    if (menInter->actions().count() > 0) {
        menMain->addMenu(menInter);
    }

    // multimedia / sound/video
    if (menMulti->actions().count() > 0) {
        menMain->addMenu(menMulti);
    }

    // office
    if (menOffic->actions().count() > 0) {
        menMain->addMenu(menOffic);
    }

    // other
    if (menOth->actions().count() > 0) {
        menMain->addMenu(menOth);
    }

    // science
    if (menSci->actions().count() > 0) {
        menMain->addMenu(menSci);
    }

    // system
    if (menSys->actions().count() > 0) {
        menMain->addMenu(menSys);
    }

    menMain->addSeparator();

    qaAction = new QAction("About...", NULL);
    qaAction->setData("...about...");
    qaAction->setIcon(QIcon::fromTheme("dialog-information"));
    menMain->addAction(qaAction);

    menMain->addSeparator();

    qaAction = new QAction("Run...", NULL);
    qaAction->setData(strRunCommand);
    menMain->addAction(qaAction);

    menMain->addSeparator();

    qaAction = new QAction("Exit", NULL);
    qaAction->setData(strExitCommand);
    qaAction->setIcon(QIcon::fromTheme("system-log-out"));
    menMain->addAction(qaAction);

    qaAction = new QAction("Reboot", NULL);
    qaAction->setData(strRebootCommand);
    qaAction->setIcon(QIcon::fromTheme("view-refresh"));
    menMain->addAction(qaAction);

    qaAction = new QAction("Shutdown", NULL);
    qaAction->setData(strPoweroffCommand);
    qaAction->setIcon(QIcon::fromTheme("system-shutdown"));
    menMain->addAction(qaAction);

    // set correct positioning
    if (nLeft == -1) {
        nLeft = qrDesktop.left();
    }

    if (nTop == -1) {
        nTop = qrDesktop.bottom();
    }

    // show menu
    qaAction = menMain->exec(QPoint(nLeft, nTop));

    // perform/run selected action
    if (qaAction != 0) {
        QString qsExec = qaAction->data().toString();
        if (qsExec == "...about...") {
            QMessageBox::about(NULL,
                               "About Qt Menu - Standalone",
                                "<h3>Qt Menu - Standalone</h3><br><br>"
                                "Copyright 2014 - Will Brokenbourgh<br>"
                                "Blog: http://www.pismotek.com/brainout/<br><br>"
                                "Version 0.1.1");
        } else {
            QProcess *qp = new QProcess();
            qp->setWorkingDirectory(QDir::homePath());
            qp->start(qsExec);
        }
    }
}
