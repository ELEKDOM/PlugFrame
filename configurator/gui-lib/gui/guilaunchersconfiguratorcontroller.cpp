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
#include <QDir>
#include "guilaunchersconfiguratorcontroller.h"
#include "guilaunchersconfiguratorcontrollertype.h"
#include "guilaunchersconfiguratorview.h"

configurator::GuiLaunchersConfiguratorController::GuiLaunchersConfiguratorController(QObject *parent):
    GuiFileConfiguratorController{configurator::GuiLaunchersConfiguratorControllerType::s_ctrlType,
                                  parent}
{}

configurator::GuiLaunchersConfiguratorController::~GuiLaunchersConfiguratorController()
{

}

///
/// \brief configurator::GuiLaunchersConfiguratorController::getLauncherConfFileList
/// returns the list of configuration files present in the repository for this launcher
/// \param confFilesRepository
/// \param applicationName
/// \return
///
QStringList configurator::GuiLaunchersConfiguratorController::getLauncherConfFileList(const QString& confFilesRepository,
                                                                                      const QString& applicationName)
{
    QStringList ret;
    QDir confDir{confFilesRepository + QDir::separator() + applicationName};
    QStringList nameFilters{"*.ini","*.qss","*.qm"};

    ret = confDir.entryList(nameFilters,QDir::Files);
    return ret;
}

bool configurator::GuiLaunchersConfiguratorController::hasLauncherConfFiles(const QString &applicationName)
{
    return forMe(applicationName);
}

bool configurator::GuiLaunchersConfiguratorController::editLauncherConfFiles(const QString &projectSourcePath,
                                                                             const QString &projectName,
                                                                             const QString &applicationName,
                                                                             const QString &confFilesRepository)
{
    bool ret{forMe(applicationName)};

    if (ret)
    {
        emit editConfFiles(projectSourcePath,projectName,applicationName,confFilesRepository);
        currentCtrl(); // show the controller view !
    }

    return ret;
}

bool configurator::GuiLaunchersConfiguratorController::forMe(const QString &applicationName)
{
    return applicationName == appPlugFrame() ||  applicationName == appGuiPlugFrame() || applicationName == appPlugFrameConfigurator();
}

configurator::GuiFileConfiguratorView *configurator::GuiLaunchersConfiguratorController::createFileConfiguratorView()
{
    return new configurator::GuiLaunchersConfiguratorView;
}
