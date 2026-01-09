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

#include <QApplication>
#include <QIcon>
#include <QFile>
#include "guiapplication.h"
#include "launcher/launchingproperties.h"

plugframe::GuiApplication::GuiApplication()
{

}

plugframe::GuiApplication::~GuiApplication()
{

}

void plugframe::GuiApplication::createApp(int& argc, char *argv[])
{
    m_spApp.reset(new QApplication(argc, argv));
    QIcon icon;
    icon.addFile(":/img/app_icon16.png", QSize(16,16));
    icon.addFile(":/img/app_icon32.png", QSize(32,32));
    icon.addFile(":/img/app_icon48.png", QSize(48,48));
    icon.addFile(":/img/app_icon128.png", QSize(128,128));
    QApplication::setWindowIcon(icon);
}

void plugframe::GuiApplication::setStyleSheet()
{
    const plugframe::QspLaunchingProperties& properties{launchingProperties()};

    if (!properties.isNull() && properties->hasStyleSheet())
    {
        QString fileName{properties->getStyleSheetFile()};
        QFile file("conf/" + fileName);
        file.open(QFile::ReadOnly);

        QString styleSheet = QString::fromUtf8(file.readAll());
        qApp->setStyleSheet(styleSheet);
    }
}

