// Copyright (C) 2026 ELEKDOM Christophe Mars c.mars@elekdom.fr
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
#ifndef GUIDEVELOPERMODECTRLHOOK_H
#define GUIDEVELOPERMODECTRLHOOK_H

#include <QString>
#include <QStringList>
#include "database/installationsettings.h"

class QWidget;
class GuiDeveloperModeCtrlHook
{
public:
    // Data Base access
    virtual void dbOpen() = 0;
    virtual bool dbGetGlobalSettings(QString& defaultScriptName,
                                     QString& defaultProjectSourcePath) = 0;
    virtual QString dbGetSelectedPlatformInstallationIdentifier() = 0;
    virtual QStringList dbGetInstallationIdentifierList() = 0;
    virtual InstallationSettings *dbGetInstallationSettings(const QString& installationIdentifier) = 0;

    virtual void dbSetDefaultProjectSourcePath(const QString& defaultProjectSourcePath) = 0;
    virtual void dbSetDefaultScriptName(const QString& defaultScriptName) = 0;
    virtual void dbSetSelectedPlatformInstallation(QString& platformInstallationIdentifier) =0;
    virtual void dbAddInstallationSettings(const InstallationSettings& installationSettings) = 0;
    virtual void dbUpdateInstallationSettings(const InstallationSettings& installationSettings) = 0;
    virtual void dbDeleteInstallationSettings() = 0;

    // Installation managment
    virtual void generateInstallationScript(InstallationSettings installationSettings,QWidget *view) = 0;
    virtual void removeInstallation(QString projectBuildRoot,QWidget *view) = 0;
};
#endif // GUIDEVELOPERMODECTRLHOOK_H
