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
#include <QFile>
#include "guidevelopermodectrl.h"
#include "guidevelopermodectrlfactory.h"
#include "guidevelopermodectrllogchannel.h"
#include "ui/guidevelopermodecontroller.h"

GuiDeveloperModeCtrl::GuiDeveloperModeCtrl():
    plugframe::GuiControllerViewsLoader{s_GuiDeveloperModeCtrlLogChannel},
    m_generator{new InstallationScriptGenerator(this)}
{

}

GuiDeveloperModeCtrl::~GuiDeveloperModeCtrl()
{

}

plugframe::BundleFactory *GuiDeveloperModeCtrl::createFactory()
{
    return new GuiDeveloperModeCtrlFactory;
}

void GuiDeveloperModeCtrl::postBuildController(plugframe::QspGuiPageController guiCtrl)
{
    QspGuiDeveloperModeController developerModePageController{guiCtrl.dynamicCast<GuiDeveloperModeController>()};

    developerModePageController->bundleHook(this);
}

void GuiDeveloperModeCtrl::dbOpen()
{
    bool fileExists;
    QString dataPath(getDataPath());

    m_dataBase.reset(new XmlDeveloperModeSettingsDocument{dataPath});
    fileExists = QFile::exists(dataPath);
    if (!fileExists)
    {
        m_dataBase->init();
    }
    else
    {
        m_dataBase->open();
    }
}

bool GuiDeveloperModeCtrl::dbGetGlobalSettings(QString& defaultScriptName,
                                               QString& defaultProjectSourcePath)
{
    return m_dataBase->getGlobalSettings(defaultScriptName,
                                         defaultProjectSourcePath);
}

QString GuiDeveloperModeCtrl::dbGetSelectedPlatformInstallationIdentifier()
{
    return m_dataBase->dbGetSelectedPlatformInstallationIdentifier();
}

QStringList GuiDeveloperModeCtrl::dbGetInstallationIdentifierList()
{
    return m_dataBase->getInstallationIdentifierList();
}

InstallationSettings *GuiDeveloperModeCtrl::dbGetInstallationSettings(const QString &installationIdentifier)
{
    return m_dataBase->getInstallationSettings(installationIdentifier);
}

void GuiDeveloperModeCtrl::dbSetDefaultProjectSourcePath(const QString &defaultProjectSourcePath)
{
    m_dataBase->setDefaultProjectSourcePath(defaultProjectSourcePath);
}

void GuiDeveloperModeCtrl::dbSetDefaultScriptName(const QString &defaultScriptName)
{
    m_dataBase->setDefaultScriptName(defaultScriptName);
}

void GuiDeveloperModeCtrl::dbSetSelectedPlatformInstallation(QString &platformInstallationIdentifier)
{
    m_dataBase->setSelectedPlatformInstallation(platformInstallationIdentifier);
}

void GuiDeveloperModeCtrl::dbAddInstallationSettings(const InstallationSettings &installationSettings)
{
    m_dataBase->addInstallationSettings(installationSettings);

}

void GuiDeveloperModeCtrl::dbUpdateInstallationSettings(const InstallationSettings &installationSettings)
{
    m_dataBase->updateInstallationSettings(installationSettings);
}

void GuiDeveloperModeCtrl::dbDeleteInstallationSettings()
{
    m_dataBase->deleteInstallationSettings();
}

void GuiDeveloperModeCtrl::generateInstallationScript(InstallationSettings installationSettings,QWidget *view)
{
    m_generator->generateInstallationScript(installationSettings,view);
}

void GuiDeveloperModeCtrl::removeInstallation(QString projectBuildRoot,QWidget *view)
{
    m_generator->removeInstallation(projectBuildRoot,view);
}

QStringList GuiDeveloperModeCtrl::getLauncherConfFileList(const QString &projectName, const QString &applicationName)
{
    QStringList ret;
    configurator::GuiConfiguratorEngineServiceInterface *configuratorServiceItf{configuratorService()};

    if (configuratorServiceItf)
    {
        ret = configuratorServiceItf->getLauncherConfFileList(projectName,applicationName);
    }

    return ret;
}

QStringList GuiDeveloperModeCtrl::getBundleConfFileList(const QString &projectName, const QString &applicationName, const QString &bundleName)
{
    QStringList ret;
    configurator::GuiConfiguratorEngineServiceInterface *configuratorServiceItf{configuratorService()};

    if (configuratorServiceItf)
    {
        ret = configuratorServiceItf->getBundleConfFileList(projectName,applicationName,bundleName);
    }

    return ret;
}

configurator::GuiConfiguratorEngineServiceInterface *GuiDeveloperModeCtrl::configuratorService()
{
    configurator::GuiConfiguratorEngineServiceInterface *configuratorServiceItf;
    configuratorServiceItf = bundleContext()->getService<configurator::GuiConfiguratorEngineServiceInterface>(configurator::GuiConfiguratorEngineServiceInterface::serviceName());

    return configuratorServiceItf;
}

PF_qtServiceInterface_DEF(GuiDeveloperModeCtrl)