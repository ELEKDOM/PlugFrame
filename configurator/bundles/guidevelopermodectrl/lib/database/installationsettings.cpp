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
#include "installationsettings.h"

InstallationSettings::InstallationSettings(const QString &projectSourcePath,
                                           const QString &scriptName,
                                           bool newFlag):
    m_newFlag{newFlag},
    m_projectSourcePath{projectSourcePath},
    m_scriptName{scriptName}
{

}

InstallationSettings::InstallationSettings(const InstallationSettings &is) :
    m_newFlag{is.m_newFlag},
    m_installationSettingsIdentifier{is.m_installationSettingsIdentifier},
    m_projectName{is.m_projectName},
    m_projectSourcePath{is.m_projectSourcePath},
    m_projectBuildRoot{is.m_projectBuildRoot},
    m_scriptName{is.m_scriptName},
    m_configurationFilesRepository{is.m_configurationFilesRepository},
    m_configurationProfile{is.m_configurationProfile},
    m_libsArtefactList{is.m_libsArtefactList},
    m_applicationArtefactList{is.m_applicationArtefactList}
{
}

InstallationSettings::InstallationSettings():
    m_newFlag{false}
{

}

// Append a empty artefact
qsizetype InstallationSettings::libsArtefactsNextDataIndex()
{
    qsizetype ret;

    m_libsArtefactList.append(LibsArtefact());
    ret = m_libsArtefactList.size() - 1;

    return ret;
}

// Fillin the newly artefact
void InstallationSettings::updateLibsArtefact(qsizetype dataIndex,const QString &libName, const QString &soName, const QString &linkerName)
{
    if (dataIndex >= 0 && dataIndex < m_libsArtefactList.size())
    {
        LibsArtefact& newly{m_libsArtefactList[dataIndex]};

        newly.m_newlyFlag = false;
        newly.m_libName = libName;
        newly.m_soName = soName;
        newly.m_linkerName = linkerName;
    }
}

void InstallationSettings::deleteLibsArtefact(qsizetype dataIndex)
{
    if (dataIndex >= 0 && dataIndex < m_libsArtefactList.size())
    {
        LibsArtefact& deletedElem{m_libsArtefactList[dataIndex]};

        // Note: There is no physical deletion, only an indicator to check!
        deletedElem.m_deletedFlag = true;
    }
}

qsizetype InstallationSettings::applicationArtefactsNextDataIndex()
{
    qsizetype ret;

    m_applicationArtefactList.append(ApplicationArtefact());
    ret = m_applicationArtefactList.size() - 1;

    return ret;
}

void InstallationSettings::updateApplicationArtefact(qsizetype dataIndex, const QString &applicationName)
{
    if (dataIndex >= 0 && dataIndex < m_applicationArtefactList.size())
    {
        ApplicationArtefact& newly{m_applicationArtefactList[dataIndex]};

        newly.m_newlyFlag = false;
        newly.m_applicationName = applicationName;
    }
}

void InstallationSettings::deleteApplicationArtefact(qsizetype dataIndex)
{
    if (dataIndex >= 0 && dataIndex < m_applicationArtefactList.size())
    {
        ApplicationArtefact& deletedElem{m_applicationArtefactList[dataIndex]};

        // Note: There is no physical deletion, only an indicator to check!
        deletedElem.m_deletedFlag = true;
    }
}

qsizetype InstallationSettings::bundleArtefactsNextDataIndex(qsizetype applicationItemDataIndex)
{
    qsizetype ret{-1};

    if (applicationItemDataIndex >= 0 && applicationItemDataIndex < m_applicationArtefactList.size())
    {
        ret = m_applicationArtefactList[applicationItemDataIndex].bundleArtefactsNextDataIndex();
    }

    return ret;
}

void InstallationSettings::updateBundleArtefact(qsizetype applicationItemDataIndex, qsizetype dataIndex, const QString &bundleName, const QString &bundlePlugin)
{
    if (applicationItemDataIndex >= 0 && applicationItemDataIndex < m_applicationArtefactList.size())
    {
        m_applicationArtefactList[applicationItemDataIndex].updateBundleArtefact(dataIndex,bundleName,bundlePlugin);
    }
}

void InstallationSettings::deleteBundleArtefact(qsizetype applicationItemDataIndex, qsizetype dataIndex)
{
    if (applicationItemDataIndex >= 0 && applicationItemDataIndex < m_applicationArtefactList.size())
    {
        m_applicationArtefactList[applicationItemDataIndex].deleteBundleArtefact(dataIndex);
    }
}

// Class ApplicationArtefact

qsizetype ApplicationArtefact::bundleArtefactsNextDataIndex()
{
    qsizetype ret;

    m_bundleArtefactList.append(BundleArtefact());
    ret = m_bundleArtefactList.size() - 1;

    return ret;
}

void ApplicationArtefact::updateBundleArtefact(qsizetype dataIndex, const QString &m_bundleName, const QString &m_bundlePlugin)
{
    if (dataIndex >= 0 && dataIndex < m_bundleArtefactList.size())
    {
        BundleArtefact& newly{m_bundleArtefactList[dataIndex]};

        newly.m_newlyFlag = false;
        newly.m_bundleName = m_bundleName;
        newly.m_bundlePlugin = m_bundlePlugin;
    }
}

void ApplicationArtefact::deleteBundleArtefact(qsizetype dataIndex)
{
    if (dataIndex >= 0 && dataIndex < m_bundleArtefactList.size())
    {
        BundleArtefact& deletedElem{m_bundleArtefactList[dataIndex]};

        // Note: There is no physical deletion, only an indicator to check!
        deletedElem.m_deletedFlag = true;
    }
}
