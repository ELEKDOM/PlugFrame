// Copyright (C) 2025 ELEKDOM Christophe Mars c.mars@elekdom.fr
// 
// This file is part of PlugFrame.
// 
// PlugFrame is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// PlugFrame is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with PlugFrame. If not, see <https://www.gnu.org/licenses/>.
//

#include "launchingproperties.h"

// Framework launching properties
const QString plugframe::LaunchingProperties::PF_GROUP = "plugframe properties";
const QString plugframe::LaunchingProperties::PF_FRAMEWORK_STARTLEVEL = "plugframe.framework.startlevel";

// Qt StyleSheet for gui
const QString plugframe::LaunchingProperties::QT_GROUP = "qt properties";
const QString plugframe::LaunchingProperties::GUI_STYLESHEET_FILE = "qt.styleSheet.file";

plugframe::LaunchingProperties::LaunchingProperties(const QString &fileName) :
    QSettings{fileName, QSettings::IniFormat}
{

}

bool plugframe::LaunchingProperties::hasStartlevel()
{
    bool ret{false};

    beginGroup(PF_GROUP);
    ret = contains(PF_FRAMEWORK_STARTLEVEL);
    endGroup();
    return ret;
}

QString plugframe::LaunchingProperties::getStartlevel()
{
    QString ret;

    beginGroup(PF_GROUP);
    ret = value(PF_FRAMEWORK_STARTLEVEL).toString();
    endGroup();

    return ret;
}

bool plugframe::LaunchingProperties::hasStyleSheet()
{
    bool ret{false};

    beginGroup(QT_GROUP);
    ret = contains(GUI_STYLESHEET_FILE);
    endGroup();
    return ret;
}

QString plugframe::LaunchingProperties::getStyleSheetFile()
{
    QString ret;

    beginGroup(QT_GROUP);
    ret = value(GUI_STYLESHEET_FILE).toString();
    endGroup();

    return ret;
}
