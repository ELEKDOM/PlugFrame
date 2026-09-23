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
#include <QFileDialog>
#include "guidevelopermodectrl.h"
#include "guidevelopermodectrlfactory.h"
#include "guidevelopermodectrl_logchannel.h"
#include "ui/guidevelopermodecontroller.h"

GuiDeveloperModeCtrl::GuiDeveloperModeCtrl():
    plugframe::GuiControllerViewsLoader{s_GuiDeveloperModeCtrl_LogChannel},
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
    return m_dataBase->getSelectedPlatformInstallationIdentifier();
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

void GuiDeveloperModeCtrl::backupDatabase(QWidget *view)
{
    QFileDialog dialog{view};
    QStringList files;
    QDir        dataToBackup{getDataPath()};
    QString     fileName{dataToBackup.dirName()};
    QFile       srcFile{getDataPath()};

    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::List);
    dialog.selectFile(fileName);
    dialog.setWindowTitle(QObject::tr("Select a backup directory"));
    if (dialog.exec())
    {
        files = dialog.selectedFiles();
        srcFile.copy(files[0]);
    }
}

bool GuiDeveloperModeCtrl::hasLauncherConfFiles(const QString &applicationName)
{
    bool ret{false};
    configurator::GuiConfiguratorEngineServiceInterface *configuratorServiceItf{configuratorService()};

    if (configuratorServiceItf)
    {
        ret = configuratorServiceItf->hasLauncherConfFiles(applicationName);
    }

    return ret;
}

bool GuiDeveloperModeCtrl::hasBundleConfFiles(const QString &bundleName)
{
    bool ret{false};
    configurator::GuiConfiguratorEngineServiceInterface *configuratorServiceItf{configuratorService()};

    if (configuratorServiceItf)
    {
        ret = configuratorServiceItf->hasBundleConfFiles(bundleName);
    }
    return ret;
}

QStringList GuiDeveloperModeCtrl::getLauncherConfFileList(const QString& confFilesRepository, const QString &applicationName)
{
    QStringList ret;
    configurator::GuiConfiguratorEngineServiceInterface *configuratorServiceItf{configuratorService()};

    if (configuratorServiceItf)
    {
        ret = configuratorServiceItf->getLauncherConfFileList(confFilesRepository,applicationName);
    }

    return ret;
}

QStringList GuiDeveloperModeCtrl::getBundleConfFileList(const QString &confFilesRepository, const QString &bundleName)
{
    QStringList ret;
    configurator::GuiConfiguratorEngineServiceInterface *configuratorServiceItf{configuratorService()};

    if (configuratorServiceItf)
    {
        ret = configuratorServiceItf->getBundleConfFileList(confFilesRepository,bundleName);
    }

    return ret;
}

void GuiDeveloperModeCtrl::editLauncherConfFiles(const QString &projectSourcePath,
                                                 const QString &projectName,
                                                 const QString &applicationName,
                                                 const QString &confFilesRepository)
{
    configurator::GuiConfiguratorEngineServiceInterface *configuratorServiceItf{configuratorService()};

    if (configuratorServiceItf)
    {
        configuratorServiceItf->editLauncherConfFiles(projectSourcePath,projectName,applicationName,confFilesRepository);
    }
}

void GuiDeveloperModeCtrl::editBundleConfFiles(const QString &projectSourcePath, const QString &projectName, const QString &applicationName, const QString &bundleName, const QString &confFilesRepository)
{
    configurator::GuiConfiguratorEngineServiceInterface *configuratorServiceItf{configuratorService()};

    if (configuratorServiceItf)
    {
        configuratorServiceItf->editBundleConfFiles(projectSourcePath,projectName,applicationName,bundleName,confFilesRepository);
    }
}

configurator::GuiConfiguratorEngineServiceInterface *GuiDeveloperModeCtrl::configuratorService()
{
    configurator::GuiConfiguratorEngineServiceInterface *configuratorServiceItf;
    configuratorServiceItf = bundleContext()->getService<configurator::GuiConfiguratorEngineServiceInterface>(configurator::GuiConfiguratorEngineServiceInterface::serviceName());

    return configuratorServiceItf;
}

void GuiDeveloperModeCtrl::backupDatabase()
{

}

PF_qtServiceInterface_DEF(GuiDeveloperModeCtrl)