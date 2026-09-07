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
#include "guidevelopermodecontroller.h"
#include "gui/guidevelopermodecontrollertype.h"

GuiDeveloperModeController::GuiDeveloperModeController(QObject *parent):
    configurator::GuiConfiguratorModeController{configurator::GuiDeveloperModeControllerType::s_ctrlType,
                                                parent},
    m_bundleHook{nullptr}
{}

GuiDeveloperModeController::~GuiDeveloperModeController()
{

}

void GuiDeveloperModeController::buildViews()
{
    GuiDeveloperModeView *view{new GuiDeveloperModeView};

    bundleHook()->dbOpen();
    initDeveloperModeView(view);
    addView(view);
}

void GuiDeveloperModeController::onGlobalProjectSourcePathChanged(const QString &text)
{
    bundleHook()->dbSetDefaultProjectSourcePath(text);
}

void GuiDeveloperModeController::onGlobalDefaultScriptNameChanged(const QString &text)
{
    bundleHook()->dbSetDefaultScriptName(text);
}

void GuiDeveloperModeController::onAddNewConfiguration()
{
    QString defaultScriptName,defaultProjectSourcePath,selectedPlatformInstallation;

    bundleHook()->dbGetGlobalSettings(defaultScriptName,defaultProjectSourcePath);
    m_displayedInstalationSettings.reset(new InstallationSettings{defaultProjectSourcePath,defaultScriptName});
    emit newConfiguration(m_displayedInstalationSettings.data());
}

void GuiDeveloperModeController::onSaveConfiguration()
{
    if (!m_displayedInstalationSettings.isNull())
    {
        QStringList identifierList;

        if (m_displayedInstalationSettings->m_newFlag)
        {
            bundleHook()->dbAddInstallationSettings(*m_displayedInstalationSettings);
            m_displayedInstalationSettings->m_newFlag = false;
        }
        else
        {
            bundleHook()->dbUpdateInstallationSettings(*m_displayedInstalationSettings);
        }
        bundleHook()->dbSetSelectedPlatformInstallation(m_displayedInstalationSettings->m_installationSettingsIdentifier);
        identifierList = bundleHook()->dbGetInstallationIdentifierList();

        emit configurationList(identifierList,m_displayedInstalationSettings->m_installationSettingsIdentifier);
    }
}

void GuiDeveloperModeController::onCancelConfiguration()
{
    initConfigurationFromDb();
}

void GuiDeveloperModeController::onDeleteConfiguration()
{
    bundleHook()->dbDeleteInstallationSettings();
    m_displayedInstalationSettings.reset();
    dataLoading();
}

void GuiDeveloperModeController::onCloneConfiguration()
{
    QString identifier{m_displayedInstalationSettings->m_installationSettingsIdentifier};

    m_displayedInstalationSettings->m_installationSettingsIdentifier = identifier + "*";
    m_displayedInstalationSettings->m_newFlag = true;
    emit newConfiguration(m_displayedInstalationSettings.data());
}

void GuiDeveloperModeController::onInstallationSelectionChanged(QString installationIdentifier)
{
    bool retrieveInstallation{false};

    if (m_displayedInstalationSettings.isNull())
    {
        // Start-up !
        QString selectedIdentifier{bundleHook()->dbGetSelectedPlatformInstallationIdentifier()};

        if (selectedIdentifier == installationIdentifier)
        {
            retrieveInstallation = true;
        }
    }
    else
    {
        // Retain the identifier of the selected installation settings
        bundleHook()->dbSetSelectedPlatformInstallation(installationIdentifier);
        retrieveInstallation = true;
    }

    if (retrieveInstallation)
    {
        // Retrieve the installation settings to display
        InstallationSettings *tmp{bundleHook()->dbGetInstallationSettings(installationIdentifier)};
        if (tmp)
        {
            m_displayedInstalationSettings.reset(tmp);
            emit newConfiguration(m_displayedInstalationSettings.data());
        }
    }
}

void GuiDeveloperModeController::onGenerateScript(QWidget *view)
{
    if (!m_displayedInstalationSettings.isNull())
    {
        m_bundleHook->generateInstallationScript(*m_displayedInstalationSettings,view);
    }
}

void GuiDeveloperModeController::onRemoveInstallation(QWidget *view)
{
    if (!m_displayedInstalationSettings.isNull())
    {
        m_bundleHook->removeInstallation(m_displayedInstalationSettings->m_projectBuildRoot,view);
    }
}

void GuiDeveloperModeController::initDeveloperModeView(GuiDeveloperModeView *view)
{
    // Controller/View connections
    //----------------------------
    connect(this,SIGNAL(globalSettings(QString,QString)),view,SLOT(globalSettings(QString,QString)));
    connect(this,SIGNAL(newConfiguration(InstallationSettings*)),view, SLOT(newConfiguration(InstallationSettings*)));
    connect(this,SIGNAL(configurationList(QStringList,QString)),view, SLOT(configurationList(QStringList,QString)));

    // View/Controller connections
    //----------------------------
    connect(view,SIGNAL(globalProjectSourcePathChanged(QString)),this,SLOT(onGlobalProjectSourcePathChanged(QString)));
    connect(view,SIGNAL(globalDefaultScriptNameChanged(QString)),this,SLOT(onGlobalDefaultScriptNameChanged(QString)));
    connect(view,SIGNAL(addNewConfiguration()),this,SLOT(onAddNewConfiguration()));
    connect(view,SIGNAL(saveConfiguration()),this,SLOT(onSaveConfiguration()));
    connect(view,SIGNAL(cancelConfiguration()),this,SLOT(onCancelConfiguration()));
    connect(view,SIGNAL(deleteConfiguration()),this,SLOT(onDeleteConfiguration()));
    connect(view,SIGNAL(cloneConfiguration()),this,SLOT(onCloneConfiguration()));
    connect(view,SIGNAL(installationSelectionChanged(QString)),this,SLOT(onInstallationSelectionChanged(QString)));
    connect(view,SIGNAL(generateInstallationScript(QWidget*)),this,SLOT(onGenerateScript(QWidget*)));
    connect(view,SIGNAL(removeInstallation(QWidget*)),this,SLOT(onRemoveInstallation(QWidget*)));

    // Data loading
    //-------------
    dataLoading();
 }

void GuiDeveloperModeController::dataLoading()
{
    QString defaultScriptName,defaultProjectSourcePath,selectedPlatformInstallation;
    QStringList identifierList;

    if (bundleHook()->dbGetGlobalSettings(defaultScriptName,defaultProjectSourcePath))
    {
        emit globalSettings(defaultScriptName,defaultProjectSourcePath);

        // retrieve and display the installation list
        selectedPlatformInstallation = bundleHook()->dbGetSelectedPlatformInstallationIdentifier();
        identifierList = bundleHook()->dbGetInstallationIdentifierList();
        emit configurationList(identifierList,selectedPlatformInstallation);
    }
}

///
/// \brief GuiDeveloperModeController::initConfigurationFromDb
/// Initialize the view with initials values from database
///
void GuiDeveloperModeController::initConfigurationFromDb()
{
     QString selectedPlatformInstallation;

     selectedPlatformInstallation = bundleHook()->dbGetSelectedPlatformInstallationIdentifier();
     if (!selectedPlatformInstallation.isEmpty())
     {
         // retrieve the installation settings to display
         InstallationSettings *tmp{bundleHook()->dbGetInstallationSettings(selectedPlatformInstallation)};
         if (tmp)
         {
             m_displayedInstalationSettings.reset(tmp);
             emit newConfiguration(m_displayedInstalationSettings.data());
         }
     }
 }