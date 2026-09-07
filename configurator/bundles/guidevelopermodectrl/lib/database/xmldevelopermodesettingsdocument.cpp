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
#include "xmldevelopermodesettingsdocument.h"

XmlDeveloperModeSettingsDocument::XmlDeveloperModeSettingsDocument(const QString &dataFilePath):
    plugframe::XmlEditableDocument{*this,dataFilePath},
    m_rootElemOk{false},
    m_globalSettingsElemOk{false},
    m_platformInstallationsElemOk{false},
    m_installationSettingsNodeListOk{false},
    m_selectedInstallationSettingsElemOk{false}
{

}

XmlDeveloperModeSettingsDocument::~XmlDeveloperModeSettingsDocument()
{

}

bool XmlDeveloperModeSettingsDocument::getGlobalSettings(QString& defaultScriptName,
                                                         QString& defaultProjectSourcePath)
{
    if (m_globalSettingsElemOk)
    {
        defaultScriptName = m_globalSettingsElem.attribute(defaultScriptNameAttr());
        defaultProjectSourcePath = m_globalSettingsElem.attribute(defaultProjectSourcePathAttr());
    }

    return m_globalSettingsElemOk;
}

QString XmlDeveloperModeSettingsDocument::dbGetSelectedPlatformInstallationIdentifier()
{
    return m_globalSettingsElem.attribute(selectedPlatformInstallationAttr());
}

QStringList XmlDeveloperModeSettingsDocument::getInstallationIdentifierList()
{
    QStringList ret;

    if (m_installationSettingsNodeListOk)
    {
        QDomElement curElem;
        for (auto i = 0; i < m_installationSettingsNodeList.size(); i++)
        {
            curElem = m_installationSettingsNodeList.at(i).toElement();
            ret.append(curElem.attribute(installationSettingsIdentifierAttr()));
        }
    }

    return ret;
}

InstallationSettings *XmlDeveloperModeSettingsDocument::getInstallationSettings(const QString &installationIdentifier)
{
    InstallationSettings *ret{nullptr};

    if(m_installationSettingsNodeListOk)
    {
        lookupInstallationElem(installationIdentifier);

        if (m_selectedInstallationSettingsElemOk)
        {
            ret = new InstallationSettings;
            if (ret)
            {
                fillinInstallationSettings(ret);
            }
        }
    }

    return ret;
}

void XmlDeveloperModeSettingsDocument::setDefaultProjectSourcePath(const QString &defaultProjectSourcePath)
{
    if (m_globalSettingsElemOk)
    {
        m_globalSettingsElem.setAttribute(defaultProjectSourcePathAttr(),defaultProjectSourcePath);
        writeIntoFile();
    }
}

void XmlDeveloperModeSettingsDocument::setDefaultScriptName(const QString &defaultScriptName)
{
    if (m_globalSettingsElemOk)
    {
        m_globalSettingsElem.setAttribute(defaultScriptNameAttr(),defaultScriptName);
        writeIntoFile();
    }
}

void XmlDeveloperModeSettingsDocument::setSelectedPlatformInstallation(QString &platformInstallationIdentifier)
{
    if (m_globalSettingsElemOk)
    {
        m_globalSettingsElem.setAttribute(selectedPlatformInstallationAttr(),platformInstallationIdentifier);
        writeIntoFile();
    }
}

///
/// \brief XmlDeveloperModeSettingsDocument::addInstallationSettings
/// Adds a new node "platform-installations-settings" into the xml doc
/// \param installationSettings
///
void XmlDeveloperModeSettingsDocument::addInstallationSettings(const InstallationSettings &installationSettings)
{
    if (m_platformInstallationsElemOk)
    {
        m_selectedInstallationSettingsElem = createElement(platformInstallationSettingsTag());  // create a new xml element "platform-installation-settings"

        m_selectedInstallationSettingsElem.setAttribute(installationSettingsIdentifierAttr(),installationSettings.m_installationSettingsIdentifier);
        m_selectedInstallationSettingsElem.setAttribute(projectNameAttr(),installationSettings.m_projectName);
        m_selectedInstallationSettingsElem.setAttribute(projectSourcePathAttr(),installationSettings.m_projectSourcePath);
        m_selectedInstallationSettingsElem.setAttribute(projectBuildRootAttr(),installationSettings.m_projectBuildRoot);
        m_selectedInstallationSettingsElem.setAttribute(scriptNameAttr(),installationSettings.m_scriptName);
        m_selectedInstallationSettingsElem.setAttribute(configurationFilesRepositoryAttr(),installationSettings.m_configurationFilesRepository);
        m_selectedInstallationSettingsElem.setAttribute(configurationProfileAttr(),installationSettings.m_configurationProfile);

        // Libs artefacts part
        appendLibsToInstall(installationSettings);

        // Applicationa artefact part
        appendApplicationsToInstall(installationSettings);

        // A new installation settings into "platform-installations" element
        m_platformInstallationsElem.appendChild(m_selectedInstallationSettingsElem);
        m_selectedInstallationSettingsElemOk = true;

        m_installationSettingsNodeList = m_platformInstallationsElem.elementsByTagName(platformInstallationSettingsTag());
        m_installationSettingsNodeListOk = true;

        // Save
        writeIntoFile();
    }
}

void XmlDeveloperModeSettingsDocument::updateInstallationSettings(const InstallationSettings &installationSettings)
{
    if (m_selectedInstallationSettingsElemOk) // installationSettings is the buffer of m_selectedInstallationSettingsElem
    {
        QDomNode removedNode;

        // remove first
        removedNode = m_platformInstallationsElem.removeChild(m_selectedInstallationSettingsElem);
        if (!removedNode.isNull())
        {
            // add the modified element
            addInstallationSettings(installationSettings);

            // update the installation list
            m_installationSettingsNodeList = m_platformInstallationsElem.elementsByTagName(platformInstallationSettingsTag());
            m_installationSettingsNodeListOk = true;

            // retrieve the index
            m_selectedInstallationSettingsElemOk = false;
            lookupInstallationElem(installationSettings.m_installationSettingsIdentifier);
        }
    }
}

void XmlDeveloperModeSettingsDocument::deleteInstallationSettings()
{
    if (m_selectedInstallationSettingsElemOk)
    {
        m_platformInstallationsElem.removeChild(m_selectedInstallationSettingsElem);

        // update the installation list
        m_installationSettingsNodeList = m_platformInstallationsElem.elementsByTagName(platformInstallationSettingsTag());
        m_installationSettingsNodeListOk = true;

        // select a new instalation identifier
        QString identifier;
        m_selectedInstallationSettingsElemOk = false;
        if (m_installationSettingsNodeList.size() > 0)
        {
            QDomElement first{m_installationSettingsNodeList.at(0).toElement()};

            identifier= first.attribute(installationSettingsIdentifierAttr());
        }
        setSelectedPlatformInstallation(identifier);

        // select a new installation settings
        if (!identifier.isEmpty())
        {
            lookupInstallationElem(identifier);
        }
    }
}

QString XmlDeveloperModeSettingsDocument::rootNodeName()
{
    return developerModeSettingsTag();
}

bool XmlDeveloperModeSettingsDocument::_browse()
{
    m_rootElem = documentElement();

    if (m_rootElem.tagName() == developerModeSettingsTag())
    {
        QDomNodeList descendants;

        m_rootElemOk = true;

        // Tag : "global-settings"
        //------------------------
        descendants = m_rootElem.elementsByTagName(globalSettingsTag());

        if (descendants.size() == 1) // only one element expected !
        {
            m_globalSettingsElem = descendants.at(0).toElement();
            m_globalSettingsElemOk = true;
        }

        // Tag : "platform-installations"
        //-------------------------------
        descendants = m_rootElem.elementsByTagName(platformInstallationsTag());
        if (descendants.size() == 1) // only one element expected !
        {
            m_platformInstallationsElem = descendants.at(0).toElement();
            m_platformInstallationsElemOk = true;

            m_installationSettingsNodeList = m_platformInstallationsElem.elementsByTagName(platformInstallationSettingsTag());
            m_installationSettingsNodeListOk = true;
        }
    }

    return m_rootElemOk;
}

///
/// \brief XmlDeveloperModeSettingsDocument::createNewDoc
/// Create an empty xml doc
void XmlDeveloperModeSettingsDocument::createNewDoc()
{
    QDomProcessingInstruction headInstruction{createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"")};

    m_rootElem = createElement(developerModeSettingsTag());
    m_rootElemOk = true;
    appendChild(m_rootElem);
    insertBefore(headInstruction,m_rootElem); // xml head
    createGlobalSettingsElement();
    createPlatformInstallationsElement();
}

void XmlDeveloperModeSettingsDocument::browseBegin()
{
}

void XmlDeveloperModeSettingsDocument::browseEnd()
{
}

void XmlDeveloperModeSettingsDocument::lookupInstallationElem(const QString &installationIdentifier)
{
    QDomElement curInstallationSettingsElem;

    m_selectedInstallationSettingsElemOk = false;
    for(auto i = 0; i < m_installationSettingsNodeList.size() && !m_selectedInstallationSettingsElemOk; i++)
    {
        curInstallationSettingsElem = m_installationSettingsNodeList.at(i).toElement();
        if (curInstallationSettingsElem.attribute(installationSettingsIdentifierAttr()) == installationIdentifier)
        {
            m_selectedInstallationSettingsElem = curInstallationSettingsElem;
            m_selectedInstallationSettingsElemOk = true;
        }
    }
}

void XmlDeveloperModeSettingsDocument::createGlobalSettingsElement()
{
    m_globalSettingsElem = createElement(globalSettingsTag());
    m_globalSettingsElemOk = true;
    m_globalSettingsElem.setAttribute(defaultScriptNameAttr(),defaultScriptName());
    m_globalSettingsElem.setAttribute(defaultProjectSourcePathAttr(),"");
    m_globalSettingsElem.setAttribute(selectedPlatformInstallationAttr(),"");

    m_rootElem.appendChild(m_globalSettingsElem);
}

void XmlDeveloperModeSettingsDocument::createPlatformInstallationsElement()
{
    m_platformInstallationsElem = createElement(platformInstallationsTag());
    m_platformInstallationsElemOk = true;

    m_rootElem.appendChild(m_platformInstallationsElem);
}

void XmlDeveloperModeSettingsDocument::fillinInstallationSettings(InstallationSettings *out)
{
    if (m_selectedInstallationSettingsElemOk)
    {
        // General settings
        out->m_installationSettingsIdentifier = m_selectedInstallationSettingsElem.attribute(installationSettingsIdentifierAttr());
        out->m_projectName = m_selectedInstallationSettingsElem.attribute(projectNameAttr());
        out->m_projectSourcePath = m_selectedInstallationSettingsElem.attribute(projectSourcePathAttr());
        out->m_projectBuildRoot = m_selectedInstallationSettingsElem.attribute(projectBuildRootAttr());
        out->m_scriptName = m_selectedInstallationSettingsElem.attribute(scriptNameAttr());
        out->m_configurationFilesRepository = m_selectedInstallationSettingsElem.attribute(configurationFilesRepositoryAttr());
        out->m_configurationProfile = m_selectedInstallationSettingsElem.attribute(configurationProfileAttr());

        // Libs settings
        fillinLibsSettings(out);

        // Applications settings
        fillinApplicationsSettings(out);
    }
}

void XmlDeveloperModeSettingsDocument::fillinLibsSettings(InstallationSettings *out)
{
    QDomNodeList descendants;

    descendants = m_selectedInstallationSettingsElem.elementsByTagName(libsToInstallTag());
    if (descendants.size() == 1) // only one element expected !
    {
        QDomElement libsToInstallElem{descendants.at(0).toElement()};
        QDomNodeList libArtefactNodeList{libsToInstallElem.elementsByTagName(libArtefactTag())};

        for(auto i = 0; i < libArtefactNodeList.size(); i++)
        {
            QDomElement libArtefactElem{libArtefactNodeList.at(i).toElement()};
            QString libName{libArtefactElem.attribute(relativeLibNameFromProjectBuildRootAttr())};
            QString soName{libArtefactElem.attribute(relativeLibSoNameFromProjectBuildRootAttr())};
            QString linkerName{libArtefactElem.attribute(relativeLibLinkerNameFromProjectBuildRootAttr())};
            LibsArtefact lart{libName,soName,linkerName};

            lart.m_newlyFlag = false;
            out->m_libsArtefactList.append(lart);
        }
    }
}

void XmlDeveloperModeSettingsDocument::fillinApplicationsSettings(InstallationSettings *out)
{
    QDomNodeList descendants;

    descendants = m_selectedInstallationSettingsElem.elementsByTagName(applisToInstallTag());
    if (descendants.size() == 1) // only one element expected !
    {
        QDomElement applisToInstallElem{descendants.at(0).toElement()};
        QDomNodeList appliArtefactNodeList{applisToInstallElem.elementsByTagName(appliArtefactTag())};

        for(auto i = 0; i < appliArtefactNodeList.size(); i++)
        {
            QDomElement appliArtefactElem{appliArtefactNodeList.at(i).toElement()};
            QString appliName{appliArtefactElem.attribute(applicationDirNameAttr())};
            QList<BundleArtefact> bundleArtefactList;

            fillinBundlesSettings(appliArtefactElem,bundleArtefactList);

            ApplicationArtefact aart{appliName,bundleArtefactList};

            out->m_applicationArtefactList.append(aart);
        }
    }

}

void XmlDeveloperModeSettingsDocument::fillinBundlesSettings(const QDomElement appliArtefactElem, QList<BundleArtefact> &out)
{
    QDomNodeList descendants;

    descendants = appliArtefactElem.elementsByTagName(bundleArtefactTag());
    for(auto i = 0; i < descendants.size(); i++)
    {
        QDomElement bundleArtefactElem{descendants.at(i).toElement()};
        QString bundleName{bundleArtefactElem.attribute(bundleDirNameAttr())};
        QString bundlePlugin{bundleArtefactElem.attribute(pluginPathToInstallAttr())};

        BundleArtefact bart{bundleName,bundlePlugin};
        out.append(bart);
    }
}

void XmlDeveloperModeSettingsDocument::appendLibsToInstall(const InstallationSettings &installationSettings)
{
    QDomElement libsToInstall{createElement(libsToInstallTag())};  // create a new xml element "libs-to-install"
    QDomElement libArtefact;

    // A new "libs-to-install" element
    m_selectedInstallationSettingsElem.appendChild(libsToInstall);

    // Add all lib artefacts
    for (auto i=0;i<installationSettings.m_libsArtefactList.size();i++)
    {
        LibsArtefact cur{installationSettings.m_libsArtefactList[i]};

        //Only valid elements are to be added!
        if (!cur.m_deletedFlag && !cur.m_newlyFlag)
        {
            libArtefact = createElement(libArtefactTag());
            libArtefact.setAttribute(relativeLibNameFromProjectBuildRootAttr(),cur.m_libName);
            libArtefact.setAttribute(relativeLibSoNameFromProjectBuildRootAttr(),cur.m_soName);
            libArtefact.setAttribute(relativeLibLinkerNameFromProjectBuildRootAttr(),cur.m_linkerName);

            libsToInstall.appendChild(libArtefact);
        }
    }
}

void XmlDeveloperModeSettingsDocument::appendApplicationsToInstall(const InstallationSettings &installationSettings)
{
    QDomElement applisToInstall{createElement(applisToInstallTag())};  // create a new xml element "applis-to-install"
    QDomElement appliArtefact;

    // A new "applis-to-install" element
    m_selectedInstallationSettingsElem.appendChild(applisToInstall);

    // Add all appli artefacts
    for (auto i=0;i<installationSettings.m_applicationArtefactList.size();i++)
    {
        ApplicationArtefact cur{installationSettings.m_applicationArtefactList[i]};

        //Only valid elements are to be added!
        if (!cur.m_deletedFlag && !cur.m_newlyFlag)
        {
            appliArtefact = createElement(appliArtefactTag());
            appliArtefact.setAttribute(applicationDirNameAttr(),cur.m_applicationName);
            appendBundleArtefacts(appliArtefact,cur.m_bundleArtefactList);

            applisToInstall.appendChild(appliArtefact);
        }
    }
}

void XmlDeveloperModeSettingsDocument::appendBundleArtefacts(QDomElement &appliArtefact, QList<BundleArtefact> &bundleArtefactList)
{
    QDomElement bundleArtefact;

    for (auto i=0;i<bundleArtefactList.size();i++)
    {
        BundleArtefact cur{bundleArtefactList[i]};

        //Only valid elements are to be added!
        if (!cur.m_deletedFlag && !cur.m_newlyFlag)
        {
            bundleArtefact = createElement(bundleArtefactTag());

            bundleArtefact.setAttribute(bundleDirNameAttr(),cur.m_bundleName);
            bundleArtefact.setAttribute(pluginPathToInstallAttr(),cur.m_bundlePlugin);

            appliArtefact.appendChild(bundleArtefact);
        }
    }
}
