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
#ifndef XMLDEVELOPERMODESETTINGSDOCUMENT_H
#define XMLDEVELOPERMODESETTINGSDOCUMENT_H

#include <QSharedPointer>
#include <QDomElement>
#include <QDomNodeList>
#include <QStringList>
#include "xmldom/xmleditabledocument.h"
#include "installationsettings.h"

class XmlDeveloperModeSettingsDocument : public plugframe::XmlEditableDocument, public plugframe::XmlBrowserHook
{
private:
    static QString developerModeSettingsTag() {return QStringLiteral("developer-mode-settings");}
    static QString globalSettingsTag() {return QStringLiteral("global-settings");}
    static QString platformInstallationsTag() {return QStringLiteral("platform-installations");}
    static QString platformInstallationSettingsTag() {return QStringLiteral("platform-installation-settings");}
    static QString libsToInstallTag() {return QStringLiteral("libs-to-install");}
    static QString libArtefactTag() {return QStringLiteral("lib-artefact");}
    static QString applisToInstallTag() {return QStringLiteral("applis-install");}
    static QString appliArtefactTag() {return QStringLiteral("application-installation");}
    static QString bundleArtefactTag() {return QStringLiteral("bundle-artefact");}

    static QString defaultScriptNameAttr() {return QStringLiteral("default-script-name");}
    static QString defaultProjectSourcePathAttr() {return QStringLiteral("default-project-source-path");}
    static QString selectedPlatformInstallationAttr() {return QStringLiteral("selected-platform-installation");}
    static QString installationSettingsIdentifierAttr() {return QStringLiteral("installation-settings-identifier");}
    static QString projectNameAttr() {return QStringLiteral("project-name");}
    static QString projectSourcePathAttr() {return QStringLiteral("project-source-path");}
    static QString projectBuildRootAttr() {return QStringLiteral("project-build-root");}
    static QString scriptNameAttr() {return QStringLiteral("script-name");}
    static QString configurationFilesRepositoryAttr() {return QStringLiteral("configuration-files-repository");}
    static QString configurationProfileAttr() {return QStringLiteral("configuration-profile");}
    static QString relativeLibNameFromProjectBuildRootAttr() {return QStringLiteral("relative-libname-from-project-build-root");}
    static QString relativeLibSoNameFromProjectBuildRootAttr() {return QStringLiteral("relative-libsoname-from-project-build-root");}
    static QString relativeLibLinkerNameFromProjectBuildRootAttr() {return QStringLiteral("relative-liblinkername-from-project-build-root");}
    static QString applicationDirNameAttr() {return QStringLiteral("application-dir-name");}
    static QString bundleDirNameAttr() {return QStringLiteral("bundle-dir-name");}
    static QString pluginPathToInstallAttr() {return QStringLiteral("plugin-path-to-install");}

    static QString defaultScriptName() {return QStringLiteral("plugframe_configurator_runtime_install.cmake");}

public:
    XmlDeveloperModeSettingsDocument(const QString& dataFilePath);
    ~XmlDeveloperModeSettingsDocument() override;

public:
    bool getGlobalSettings(QString& defaultScriptName,
                           QString& defaultProjectSourcePath);
    QString dbGetSelectedPlatformInstallationIdentifier();
    QStringList getInstallationIdentifierList();
    InstallationSettings *getInstallationSettings(const QString &installationIdentifier);
    void setDefaultProjectSourcePath(const QString& defaultProjectSourcePath);
    void setDefaultScriptName(const QString& defaultScriptName);
    void setSelectedPlatformInstallation(QString& platformInstallationIdentifier);
    void addInstallationSettings(const InstallationSettings &installationSettings);
    void updateInstallationSettings(const InstallationSettings &installationSettings);
    void deleteInstallationSettings();

protected: // XmlDocument
    QString rootNodeName() override;
    bool _browse() override;

protected: // XmlEditableDocument
     void createNewDoc() override;

protected: // XmlBrowserHook
    void browseBegin() override;
    void browseEnd() override;

private:
    void lookupInstallationElem(const QString &installationIdentifier);

private:
    // Xml Element writtors
    void createGlobalSettingsElement();
    void createPlatformInstallationsElement();
    void appendLibsToInstall(const InstallationSettings &installationSettings);
    void appendApplicationsToInstall(const InstallationSettings &installationSettings);
    void appendBundleArtefacts(QDomElement& appliArtefact,QList<BundleArtefact>& bundleArtefactList);
    // Xml Element readors
    void fillinInstallationSettings(InstallationSettings *out);
    void fillinLibsSettings(InstallationSettings *out);
    void fillinApplicationsSettings(InstallationSettings *out);
    void fillinBundlesSettings(const QDomElement appliArtefactElem,QList<BundleArtefact>& out);

private:
    QDomElement  m_rootElem;
    bool         m_rootElemOk;
    QDomElement  m_globalSettingsElem;
    bool         m_globalSettingsElemOk;
    QDomElement  m_platformInstallationsElem;
    bool         m_platformInstallationsElemOk;
    QDomNodeList m_installationSettingsNodeList;
    bool         m_installationSettingsNodeListOk;
    QDomElement  m_selectedInstallationSettingsElem;
    bool         m_selectedInstallationSettingsElemOk;
};
using QspXmlDeveloperModeSettingsDocument = QSharedPointer<XmlDeveloperModeSettingsDocument>;
#endif // XMLDEVELOPERMODESETTINGSDOCUMENT_H
