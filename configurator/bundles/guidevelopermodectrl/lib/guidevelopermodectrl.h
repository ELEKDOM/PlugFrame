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
#ifndef GUIDEVELOPERMODECTRL_H
#define GUIDEVELOPERMODECTRL_H

#include "abstract_controllerviews_loader/guicontrollerviewsloader.h"
#include "ui/guidevelopermodectrlhook.h"
#include "database/xmldevelopermodesettingsdocument.h"
#include "generator/installationscriptgenerator.h"
#include "service-int/guiconfiguratorengineserviceinterface.h"

class GuiDeveloperModeCtrl : public plugframe::GuiControllerViewsLoader, public GuiDeveloperModeCtrlHook, public GeneratorDeveloperModeHook
{
public:
    GuiDeveloperModeCtrl();
    ~GuiDeveloperModeCtrl() override;

protected:
    plugframe::BundleFactory* createFactory() override;
    void postBuildController(plugframe::QspGuiPageController guiCtrl) override;
    PF_qtServiceInterface_DECL

protected:
    // GuiDeveloperModeControllerHook
    //-------------------------------
    // Db access
    void dbOpen() override;
    bool dbGetGlobalSettings(QString& defaultScriptName,
                             QString& defaultProjectSourcePath) override;
    QString dbGetSelectedPlatformInstallationIdentifier() override;
    QStringList dbGetInstallationIdentifierList() override;
    InstallationSettings *dbGetInstallationSettings(const QString& installationIdentifier) override;
    void dbSetDefaultProjectSourcePath(const QString& defaultProjectSourcePath) override;
    void dbSetDefaultScriptName(const QString& defaultScriptName) override;
    void dbSetSelectedPlatformInstallation(QString& platformInstallationIdentifier) override;
    void dbAddInstallationSettings(const InstallationSettings& installationSettings) override;
    void dbUpdateInstallationSettings(const InstallationSettings& installationSettings) override;
    void dbDeleteInstallationSettings() override;

    // Script generating
    void generateInstallationScript(InstallationSettings installationSettings,QWidget *view) override;
    void removeInstallation(QString projectBuildRoot,QWidget *view) override;

    // GeneratorDeveloperModeHook
    //---------------------------
    QStringList getLauncherConfFileList(const QString& projectName,const QString& applicationName) override;
    QStringList getBundleConfFileList(const QString& projectName,const QString& applicationName,const QString& bundleName) override;

private:
    configurator::GuiConfiguratorEngineServiceInterface *configuratorService();

private:
    QspXmlDeveloperModeSettingsDocument m_dataBase;
    QspInstallationScriptGenerator      m_generator;
};

#endif // GUIDEVELOPERMODECTRL_H
