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
#ifndef INSTALLATIONSETTINGS_H
#define INSTALLATIONSETTINGS_H

#include <QSharedPointer>
#include <QList>
#include <QString>


///
/// \brief The LibsArtefact class
///
class LibsArtefact
{
public:
    LibsArtefact():m_deletedFlag{false},m_newlyFlag{true} {}
    LibsArtefact(const QString& libName,const QString& soName,const QString& linkerName):LibsArtefact() {m_libName = libName; m_soName = soName ; m_linkerName = linkerName;}
    LibsArtefact(const LibsArtefact& a) {m_deletedFlag=a.m_deletedFlag;m_newlyFlag=a.m_newlyFlag;m_libName=a.m_libName;m_soName=a.m_soName;m_linkerName=a.m_linkerName;}

public:
    bool m_deletedFlag;
    bool m_newlyFlag;
    QString m_libName;
    QString m_soName;
    QString m_linkerName;
};

///
/// \brief The BundleArtefact class
///
class BundleArtefact
{
public:
    BundleArtefact():m_deletedFlag{false},m_newlyFlag{true}{}
    BundleArtefact(const QString& bundleName,const QString& bundlePlugin):BundleArtefact(){m_newlyFlag=false;m_bundleName=bundleName;m_bundlePlugin=bundlePlugin;}
    BundleArtefact(const BundleArtefact& b){m_deletedFlag=b.m_deletedFlag;m_newlyFlag=b.m_newlyFlag;m_bundleName=b.m_bundleName;m_bundlePlugin=b.m_bundlePlugin;}

public:
    bool m_deletedFlag;
    bool m_newlyFlag;
    QString m_bundleName;
    QString m_bundlePlugin;
};

///
/// \brief The ApplicationArtefact class
///
class ApplicationArtefact
{
public:
    ApplicationArtefact():m_deletedFlag{false},m_newlyFlag{true} {}
    ApplicationArtefact(const QString& appliName,const QList<BundleArtefact>& bundleArtefactList):ApplicationArtefact(){m_newlyFlag=false;m_applicationName=appliName;m_bundleArtefactList=bundleArtefactList;}

public:
    qsizetype bundleArtefactsNextDataIndex();
    void updateBundleArtefact(qsizetype dataIndex,const QString& m_bundleName,const QString& m_bundlePlugin);
    void deleteBundleArtefact(qsizetype dataIndex);

public:
    bool m_deletedFlag;
    bool m_newlyFlag;
    QString m_applicationName;
    QList<BundleArtefact> m_bundleArtefactList;
};

///
/// \brief The InstallationSettings class
///
class InstallationSettings
{
public:
    InstallationSettings(const QString& projectSourcePath,
                         const QString& scriptName,
                         bool newFlag = true);
    InstallationSettings(const InstallationSettings& is);
    InstallationSettings();


public:
    qsizetype libsArtefactsNextDataIndex();
    void updateLibsArtefact(qsizetype dataIndex,const QString& libName,const QString& soName,const QString& linkerName);
    void deleteLibsArtefact(qsizetype dataIndex);

    qsizetype applicationArtefactsNextDataIndex();
    void updateApplicationArtefact(qsizetype dataIndex,const QString& applicationName);
    void deleteApplicationArtefact(qsizetype dataIndex);

    qsizetype bundleArtefactsNextDataIndex(qsizetype applicationItemDataIndex);
    void updateBundleArtefact(qsizetype applicationItemDataIndex,qsizetype dataIndex,const QString& bundleName,const QString& bundlePlugin);
    void deleteBundleArtefact(qsizetype applicationItemDataIndex,qsizetype dataIndex);

public:
    bool m_newFlag;
    QString m_installationSettingsIdentifier;
    QString m_projectName;
    QString m_projectSourcePath;
    QString m_projectBuildRoot;
    QString m_scriptName;
    QString m_configurationFilesRepository;
    QString m_configurationProfile;
    QList<LibsArtefact> m_libsArtefactList;
    QList<ApplicationArtefact> m_applicationArtefactList;
};
using QspInstallationSettings = QSharedPointer<InstallationSettings>;
#endif // INSTALLATIONSETTINGS_H
