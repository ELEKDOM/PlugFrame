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
#ifndef GUILAUNCHERSCONFIGURATORCONTROLLER_H
#define GUILAUNCHERSCONFIGURATORCONTROLLER_H

#include "guifileconfiguratorcontroller.h"

namespace configurator
{
class CONFIGURATORLIB_EXPORT GuiLaunchersConfiguratorController : public GuiFileConfiguratorController
{
public:
    static QString appPlugFrame() {return QStringLiteral("plugframe");}
    static QString appGuiPlugFrame() {return QStringLiteral("guiplugframe");}
    static QString appPlugFrameConfigurator() {return QStringLiteral("configurator");}

    Q_OBJECT

public:
    GuiLaunchersConfiguratorController(QObject *parent = nullptr);
    ~GuiLaunchersConfiguratorController() override;

public:
    QStringList getLauncherConfFileList(const QString& confFilesRepository,const QString& applicationName);
    bool hasLauncherConfFiles(const QString& applicationName);
    bool editLauncherConfFiles(const QString &projectSourcePath,
                               const QString &projectName,
                               const QString &applicationName,
                               const QString &confFilesRepository);

protected:
    GuiFileConfiguratorView *createFileConfiguratorView() override;

protected:
    virtual bool forMe(const QString& applicationName);

};
using QspGuiLaunchersConfiguratorController = QSharedPointer<GuiLaunchersConfiguratorController>;
}//namespace configurator
#endif // GUILAUNCHERSCONFIGURATORCONTROLLER_H
