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
#include "guibundleconfiguratorcontroller.h"
#include "guibundleconfiguratorcontrollertype.h"

configurator::GuiBundleConfiguratorController::GuiBundleConfiguratorController(const QString &associatedBundleName, QObject *parent):
    GuiFileConfiguratorController{configurator::GuiBundleConfiguratorControllerType::s_ctrlType,
                                  parent},
    m_associatedBundleName{associatedBundleName}
{

}

configurator::GuiBundleConfiguratorController::~GuiBundleConfiguratorController()
{

}

QStringList configurator::GuiBundleConfiguratorController::getBundleConfFileList(const QString &confFilesRepository, const QString &bundleName)
{
    QStringList ret;

    if (bundleName == m_associatedBundleName)
    {
        QDir confDir{confFilesRepository + QDir::separator() + bundleName};
        QStringList nameFilters{"*.ini","*.xml"};

        ret = confDir.entryList(nameFilters,QDir::Files);
    }

    return ret;
}

bool configurator::GuiBundleConfiguratorController::hasBundleConfFiles(const QString &bundleName)
{
    return bundleName == m_associatedBundleName;
}

bool configurator::GuiBundleConfiguratorController::editBundleConfFiles(const QString &projectSourcePath,
                                                                        const QString &projectName,
                                                                        const QString &applicationName,
                                                                        const QString &bundleName,
                                                                        const QString &confFilesRepository)
{
    bool ret{bundleName == m_associatedBundleName};

    if (ret)
    {
        QString repos{confFilesRepository + QDir::separator() + applicationName};

        emit editConfFiles(projectSourcePath,projectName,bundleName,repos);
        currentCtrl(); // show the controller view !
    }

    return ret;
}
