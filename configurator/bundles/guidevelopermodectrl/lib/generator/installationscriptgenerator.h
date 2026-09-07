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
#ifndef INSTALLATIONSCRIPTGENERATOR_H
#define INSTALLATIONSCRIPTGENERATOR_H

#include <QObject>
#include <QWidget>
#include <QProgressDialog>
#include <QSharedPointer>
#include "database/installationsettings.h"
#include "generator/generatordevelopermodehook.h"

class InstallationScriptGenerator : public QObject
{
    Q_OBJECT
private:
    static QString s_runtimeInstall_in;
    static int s_lastStep;

public:
    explicit InstallationScriptGenerator(GeneratorDeveloperModeHook *bundleHook,QObject *parent = nullptr);
    ~InstallationScriptGenerator() override;

public:
    void generateInstallationScript(InstallationSettings installationSettings,QWidget *view);
    void removeInstallation(QString projectBuildRoot,QWidget *view);

signals:
    void startStep(int step);
    void stepFinished(int step);
    void startRemoving(QString dirPath, QWidget *view);
    void removingFinished(bool ok,QWidget *view);

private slots:
    void onStartStep(int step);
    void onStepFinished(int step);
    void onStartRemoving(QString dirPath, QWidget *view);
    void onRemovingFinished(bool ok,QWidget *view);

private:
    void fillinTagScriptName();
    void fillinTagProjectSource();
    void fillinTagBuildRoot();
    void fillinTagAppsDir();
    void fillinTagLibs();
    void fillinTagAppsBundles();
    void fillinTagConfProfilesRootDir();
    void fillinTagConfSelectedProfile();
    void fillinTagAppsConfFiles();
    void fillinTagBundlesConfFiles();

    void writeToFile();

private:
    GeneratorDeveloperModeHook *m_bundleHook;
    QProgressDialog            *m_processingProgressDisplay;
    InstallationSettings        m_scriptGenerationSettings;
    QString                     m_runtimeInstall_out;
};
using QspInstallationScriptGenerator = QSharedPointer<InstallationScriptGenerator>;
#endif // INSTALLATIONSCRIPTGENERATOR_H
