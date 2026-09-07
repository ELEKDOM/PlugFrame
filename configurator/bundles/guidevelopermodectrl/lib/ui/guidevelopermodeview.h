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
#ifndef GUIDEVELOPERMODEVIEW_H
#define GUIDEVELOPERMODEVIEW_H

#include "gui/guipageview.h"
#include "database/installationsettings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class developerModeView;
}
QT_END_NAMESPACE

class GuiLibsInstallationsSettings;
class GuiApplicationsSettings;
class GuiDeveloperModeView : public plugframe::GuiPageView
{
    Q_OBJECT

public:
    GuiDeveloperModeView(QWidget *parent = nullptr);
    ~GuiDeveloperModeView() override;

public slots:
    // Tab : Global settings
    void globalSettings(QString defaultScriptName,
                        QString defaultProjectSourcePath);

    // Tab : Platform installation settings
    void newConfiguration(InstallationSettings* installationSettings);
    void configurationList(QStringList list,QString selected);

public:
    //For m_libsInstallationsSettings
    QString projectBuildRoot();
    qsizetype libsArtefactsNextDataIndex();
    void updateLibsArtefact(qsizetype dataIndex,const QString& libName,const QString& soName,const QString& linkerName);
    void deleteLibsArtefact(qsizetype dataIndex);

    // For m_applicationsSettings
    qsizetype applicationArtefactsNextDataIndex();
    void updateApplicationArtefact(qsizetype dataIndex,const QString& applicationName);
    void deleteApplicationArtefact(qsizetype dataIndex);

    qsizetype bundleArtefactsNextDataIndex(qsizetype applicationItemDataIndex);
    void updateBundleArtefact(qsizetype applicationItemDataIndex,qsizetype dataIndex,const QString& bundleName,const QString& bundlePlugin);
    void deleteBundleArtefact(qsizetype applicationItemDataIndex,qsizetype dataIndex);

signals:
    // Tab : Global settings
    void globalProjectSourcePathChanged(const QString& text);
    void globalDefaultScriptNameChanged(const QString& text);

    // Tab : Platform installation settings
    void addNewConfiguration();
    void saveConfiguration();
    void cancelConfiguration();
    void deleteConfiguration();
    void cloneConfiguration();
    void installationSelectionChanged(QString installationIdentifier);
    void generateInstallationScript(QWidget *view);
    void removeInstallation(QWidget *view);

private slots:
    // Tab : Global settings
    void onGlobalBrowseProjectSourcePath();
    void onGlobalProjectSourcePathEdited();
    void onGlobalDefaultScriptNameEdited();

    // Tab : Platform installation settings
    //-------------------------------------
    // Area1 : Control buttons
    void onInstallationIdentifierChanged(int index);
    void onAddConfiguration();
    void onUpdateConfiguration();
    void onDeleteConfiguration();
    void onCloneConfiguration();
    void onCancelConfiguration();
    void onSaveConfiguration();
    // Area 2 : General installation settings
    void onInstallationSettingsIdentifiantEdited();
    void onProjectNameEdited();
    void onBrowseProjectSourcePath();
    void onProjectSourcePathEdited();
    void onBrowseProjectBuildRoot();
    void onProjectBuildRootEdited();
    void onBrowseConfigurationFilesRepository();
    void onConfigurationFilesRepositoryEdited();
    void onBrowseConfigurationProfile();
    void onConfigurationProfileEdited();

    // Area 5 :: Script generating
    void onGenerateScript();
    void onRemoveInstallation();

private:
    void hideInstallationSettingsArea();
    void setDefaultProjectSourcePath(QString& defaultProjectSourcePath);
    void setDefaultScriptName(QString defaultScriptName);
    void controlButtonsShowSettingsState();
    void controlButtonsSaveSettingsState();
    void displayCurInstallationSettings(bool editable = true);
    void setSettingsFormEditable(bool editable = true);
    void showTopInstallationSettings();

private:
    Ui::developerModeView        *ui;
    GuiLibsInstallationsSettings *m_libsInstallationsSettings; // Area3
    GuiApplicationsSettings      *m_applicationsSettings; // Area4
    InstallationSettings         *m_curInstallationSettings;
};
#endif // GUIDEVELOPERMODEVIEW_H
