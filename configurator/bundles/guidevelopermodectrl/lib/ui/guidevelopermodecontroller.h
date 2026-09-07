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
#ifndef GUIDEVELOPERMODECONTROLLER_H
#define GUIDEVELOPERMODECONTROLLER_H

#include "gui/guiconfiguratormodecontroller.h"
#include "guidevelopermodectrlhook.h"
#include "guidevelopermodeview.h"

class GuiDeveloperModeController : public configurator::GuiConfiguratorModeController
{
    Q_OBJECT

public:
    GuiDeveloperModeController(QObject *parent = nullptr);
    ~GuiDeveloperModeController() override;

public:
    void bundleHook(GuiDeveloperModeCtrlHook *bundleHook) {m_bundleHook = bundleHook;}

protected:
    void buildViews() override;

signals:
    void globalSettings(QString defaultScriptName,
                        QString defaultProjectSourcePath);
    void newConfiguration(InstallationSettings* installationSettings);
    void configurationList(QStringList list,QString selected);

private slots:
    void onGlobalProjectSourcePathChanged(const QString& text);
    void onGlobalDefaultScriptNameChanged(const QString& text);
    void onAddNewConfiguration();
    void onSaveConfiguration();
    void onCancelConfiguration();
    void onDeleteConfiguration();
    void onCloneConfiguration();
    void onInstallationSelectionChanged(QString installationIdentifier);
    void onGenerateScript(QWidget *view);
    void onRemoveInstallation(QWidget *view);

private:
    GuiDeveloperModeCtrlHook *bundleHook() {return m_bundleHook;}
    void initDeveloperModeView(GuiDeveloperModeView *view);
    void dataLoading();
    void initConfigurationFromDb();

private:
    GuiDeveloperModeCtrlHook *m_bundleHook;
    QspInstallationSettings   m_displayedInstalationSettings;
};
using QspGuiDeveloperModeController = QSharedPointer<GuiDeveloperModeController>;
#endif // GUIDEVELOPERMODECONTROLLER_H
