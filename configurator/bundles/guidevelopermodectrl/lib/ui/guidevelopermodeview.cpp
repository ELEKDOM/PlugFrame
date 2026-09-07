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
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>
#include "guidevelopermodeview.h"
#include "ui/widgets/guilibsinstallationssettings.h"
#include "ui/widgets/guiapplicationssettings.h"
#include "ui_developermodeview.h"

GuiDeveloperModeView::GuiDeveloperModeView(QWidget *parent):
    GuiPageView{"",parent},
    ui(new Ui::developerModeView),
    m_curInstallationSettings{nullptr}
{
    ui->setupUi(this);

    // Tab1 : Global settings
    connect(ui->tab1Area1BrowseButton,SIGNAL(clicked(bool)),this,SLOT(onGlobalBrowseProjectSourcePath()));
    connect(ui->tab1Area1LineEdit,SIGNAL(editingFinished()),this,SLOT(onGlobalProjectSourcePathEdited()));
    connect(ui->tab1Area2LineEdit,SIGNAL(editingFinished()),this,SLOT(onGlobalDefaultScriptNameEdited()));

    // Tab2 : Platform installation settings

    // Combo box for installation settings selection
    connect(ui->tab2Area1ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onInstallationIdentifierChanged(int)));

    // Control buttons
    connect(ui->tab2Area1AddButton,SIGNAL(clicked(bool)),this,SLOT(onAddConfiguration()));
    connect(ui->tab2Area1UpdateButton,SIGNAL(clicked(bool)),this,SLOT(onUpdateConfiguration()));
    connect(ui->tab2Area1DeleteButton,SIGNAL(clicked(bool)),this,SLOT(onDeleteConfiguration()));
    connect(ui->tab2Area1CloneButton,SIGNAL(clicked(bool)),this,SLOT(onCloneConfiguration()));
    connect(ui->tab2Area1SaveButton,SIGNAL(clicked(bool)),this,SLOT(onSaveConfiguration()));
    connect(ui->tab2Area1CancelButton,SIGNAL(clicked(bool)),this,SLOT(onCancelConfiguration()));

    // General settings
    connect(ui->tab2Area2LineEdit,SIGNAL(editingFinished()),this,SLOT(onInstallationSettingsIdentifiantEdited()));
    connect(ui->tab2Area2LineEditProjectName,SIGNAL(editingFinished()),this,SLOT(onProjectNameEdited()));
    connect(ui->tab2Area2BrowseButton,SIGNAL(clicked(bool)),this,SLOT(onBrowseProjectSourcePath()));
    connect(ui->tab2Area2LineEdit_2,SIGNAL(editingFinished()),this,SLOT(onProjectSourcePathEdited()));
    connect(ui->tab2Area2BrowseButton_2,SIGNAL(clicked(bool)),this,SLOT(onBrowseProjectBuildRoot()));
    connect(ui->tab2Area2LineEdit_3,SIGNAL(editingFinished()),this,SLOT(onProjectBuildRootEdited()));
    connect(ui->tab2Area2BrowseButton_3,SIGNAL(clicked(bool)),this,SLOT(onBrowseConfigurationFilesRepository()));
    connect(ui->tab2Area2LineEdit_5,SIGNAL(editingFinished()),this,SLOT(onConfigurationFilesRepositoryEdited()));
    connect(ui->tab2Area2BrowseButton_4,SIGNAL(clicked(bool)),this,SLOT(onBrowseConfigurationProfile()));
    connect(ui->tab2Area2LineEdit_6,SIGNAL(editingFinished()),this,SLOT(onConfigurationProfileEdited()));

    // Generating buttons
    connect(ui->tab2Area5GenerateButton,SIGNAL(clicked(bool)),this,SLOT(onGenerateScript()));
    connect(ui->tab2Area5RemoveButton,SIGNAL(clicked(bool)),this,SLOT(onRemoveInstallation()));

    // Libs settings
    m_libsInstallationsSettings = new GuiLibsInstallationsSettings{this};
    ui->libsArtefactSettingsLocationLayout->addWidget(m_libsInstallationsSettings);

    // Applications settings
    m_applicationsSettings = new GuiApplicationsSettings{this};
    ui->applicationsArtefactsSettingsLocationLayout->addWidget(m_applicationsSettings);

    // Initial form
    hideInstallationSettingsArea();
}

GuiDeveloperModeView::~GuiDeveloperModeView()
{
    delete ui;
    delete m_libsInstallationsSettings;
    delete m_applicationsSettings;
}

void GuiDeveloperModeView::globalSettings(QString defaultScriptName,
                                          QString defaultProjectSourcePath)
{
    setDefaultProjectSourcePath(defaultProjectSourcePath);
    setDefaultScriptName(defaultScriptName);
}

void GuiDeveloperModeView::newConfiguration(InstallationSettings* installationSettings)
{
    m_curInstallationSettings = installationSettings;
    if (m_curInstallationSettings)
    {
        displayCurInstallationSettings(m_curInstallationSettings->m_newFlag);
        if (m_curInstallationSettings->m_newFlag)
        {
            controlButtonsSaveSettingsState();
        }
        else
        {
            controlButtonsShowSettingsState();
        }
    }
    else
    {
        hideInstallationSettingsArea();
    }
}

void GuiDeveloperModeView::configurationList(QStringList list, QString selected)
{
    int selectedIdx = -1;

    // remove all items
    ui->tab2Area1ComboBox->clear();
    for (auto i = 0; i < list.size(); i++)
    {
        ui->tab2Area1ComboBox->addItem(list.at(i));
        if (list.at(i) == selected)
        {
            selectedIdx = i;
        }
    }

    if (selectedIdx >= 0)
    {
        ui->tab2Area1ComboBox->setCurrentIndex(selectedIdx);
    }
}

qsizetype GuiDeveloperModeView::libsArtefactsNextDataIndex()
{
    qsizetype ret{-1};

    if (m_curInstallationSettings)
    {
        ret = m_curInstallationSettings->libsArtefactsNextDataIndex();
    }

    return ret;
}

QString GuiDeveloperModeView::projectBuildRoot()
{
    return ui->tab2Area2LineEdit_3->text();
}

void GuiDeveloperModeView::updateLibsArtefact(qsizetype dataIndex, const QString &libName, const QString &soName, const QString &linkerName)
{
    m_curInstallationSettings->updateLibsArtefact(dataIndex,libName,soName,linkerName);
}

void GuiDeveloperModeView::deleteLibsArtefact(qsizetype dataIndex)
{
    m_curInstallationSettings->deleteLibsArtefact(dataIndex);
}

qsizetype GuiDeveloperModeView::applicationArtefactsNextDataIndex()
{
    qsizetype ret{-1};

    if (m_curInstallationSettings)
    {
        ret = m_curInstallationSettings->applicationArtefactsNextDataIndex();
    }

    return ret;
}

void GuiDeveloperModeView::updateApplicationArtefact(qsizetype dataIndex, const QString &applicationName)
{
    m_curInstallationSettings->updateApplicationArtefact(dataIndex,applicationName);
}

void GuiDeveloperModeView::deleteApplicationArtefact(qsizetype dataIndex)
{
    m_curInstallationSettings->deleteApplicationArtefact(dataIndex);
}

qsizetype GuiDeveloperModeView::bundleArtefactsNextDataIndex(qsizetype applicationItemDataIndex)
{
    qsizetype ret{-1};

    if (m_curInstallationSettings)
    {
        ret = m_curInstallationSettings->bundleArtefactsNextDataIndex(applicationItemDataIndex);
    }

    return ret;
}

void GuiDeveloperModeView::updateBundleArtefact(qsizetype applicationItemDataIndex, qsizetype dataIndex, const QString &bundleName, const QString &bundlePlugin)
{
    m_curInstallationSettings->updateBundleArtefact(applicationItemDataIndex,dataIndex,bundleName,bundlePlugin);
}

void GuiDeveloperModeView::deleteBundleArtefact(qsizetype applicationItemDataIndex, qsizetype dataIndex)
{
    m_curInstallationSettings->deleteBundleArtefact(applicationItemDataIndex,dataIndex);

}

void GuiDeveloperModeView::onGlobalBrowseProjectSourcePath()
{
    QFileDialog dialog(this);
    QStringList dirNames;

    dialog.setFileMode(QFileDialog::Directory);
    dialog.setViewMode(QFileDialog::List);

    if (dialog.exec())
    {
        dirNames = dialog.selectedFiles();
    }

    if (dirNames.size() > 0)
    {
        setDefaultProjectSourcePath(dirNames[0]);
        emit globalProjectSourcePathChanged(ui->tab1Area1LineEdit->text());
    }
}

void GuiDeveloperModeView::onGlobalProjectSourcePathEdited()
{
    emit globalProjectSourcePathChanged(ui->tab1Area1LineEdit->text());
}

void GuiDeveloperModeView::onGlobalDefaultScriptNameEdited()
{
    emit globalDefaultScriptNameChanged(ui->tab1Area2LineEdit->text());
}

void GuiDeveloperModeView::onInstallationIdentifierChanged(int index)
{
    QString selectedId;

    if (index > -1)
    {
        selectedId = ui->tab2Area1ComboBox->itemText(index);

        if(m_curInstallationSettings)
        {
            if (selectedId != m_curInstallationSettings->m_installationSettingsIdentifier)
            {
                emit installationSelectionChanged(selectedId);
            }
        }
        else
        {
            // Start-up !
            emit installationSelectionChanged(selectedId);
        }
    }
}

void GuiDeveloperModeView::onAddConfiguration()
{

    emit addNewConfiguration();
}

void GuiDeveloperModeView::onUpdateConfiguration()
{
    controlButtonsSaveSettingsState();
    showTopInstallationSettings();
    setSettingsFormEditable(true);
}

void GuiDeveloperModeView::onDeleteConfiguration()
{
    ui->tab2Area1ComboBox->clear(); // clear all identifiers
    m_curInstallationSettings = nullptr;
    hideInstallationSettingsArea();
    controlButtonsShowSettingsState();
    showTopInstallationSettings();
    emit deleteConfiguration();
}

void GuiDeveloperModeView::onCloneConfiguration()
{
    emit cloneConfiguration();
}

void GuiDeveloperModeView::onSaveConfiguration()
{
    if (ui->tab2Area2LineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,tr("Developer mode"),tr("You must define [Installation setting identifier]"));
    }
    else
    {
        controlButtonsShowSettingsState();
        setSettingsFormEditable(false);
        showTopInstallationSettings();
        emit saveConfiguration();
    }
}

void GuiDeveloperModeView::onCancelConfiguration()
{
    controlButtonsShowSettingsState();
    setSettingsFormEditable(false);
    showTopInstallationSettings();
    emit cancelConfiguration();
}

void GuiDeveloperModeView::onInstallationSettingsIdentifiantEdited()
{
    m_curInstallationSettings->m_installationSettingsIdentifier = ui->tab2Area2LineEdit->text();
}

void GuiDeveloperModeView::onProjectNameEdited()
{
    m_curInstallationSettings->m_projectName = ui->tab2Area2LineEditProjectName->text();
}

void GuiDeveloperModeView::onBrowseProjectSourcePath()
{
    QFileDialog dialog(this);
    QStringList dirNames;

    dialog.setFileMode(QFileDialog::Directory);
    dialog.setViewMode(QFileDialog::List);
    dialog.setDirectory(ui->tab2Area2LineEdit_2->text());

    if (dialog.exec())
    {
        dirNames = dialog.selectedFiles();
    }

    if (dirNames.size() > 0)
    {
        ui->tab2Area2LineEdit_2->setText(dirNames[0]);
        onProjectSourcePathEdited();
    }
}

void GuiDeveloperModeView::onProjectSourcePathEdited()
{
    m_curInstallationSettings->m_projectSourcePath = ui->tab2Area2LineEdit_2->text();
}

void GuiDeveloperModeView::onBrowseProjectBuildRoot()
{
    QFileDialog dialog(this);
    QStringList dirNames;

    dialog.setFileMode(QFileDialog::Directory);
    dialog.setViewMode(QFileDialog::List);

    if (ui->tab2Area2LineEdit_3->text().isEmpty())
    {
        dialog.setDirectory(ui->tab2Area2LineEdit_2->text());
    }
    else
    {
        dialog.setDirectory(ui->tab2Area2LineEdit_3->text());
    }

    if (dialog.exec())
    {
        dirNames = dialog.selectedFiles();
    }

    if (dirNames.size() > 0)
    {
        ui->tab2Area2LineEdit_3->setText(dirNames[0]);
        onProjectBuildRootEdited();
    }
}

void GuiDeveloperModeView::onProjectBuildRootEdited()
{
    m_curInstallationSettings->m_projectBuildRoot = ui->tab2Area2LineEdit_3->text();
}

void GuiDeveloperModeView::onBrowseConfigurationFilesRepository()
{
    QFileDialog dialog(this);
    QStringList dirNames;

    dialog.setFileMode(QFileDialog::Directory);
    dialog.setViewMode(QFileDialog::List);

    if (ui->tab2Area2LineEdit_5->text().isEmpty())
    {
        dialog.setDirectory(ui->tab2Area2LineEdit_2->text());
    }
    else
    {
        dialog.setDirectory(ui->tab2Area2LineEdit_5->text());
    }

    if (dialog.exec())
    {
        dirNames = dialog.selectedFiles();
    }

    if (dirNames.size() > 0)
    {
        ui->tab2Area2LineEdit_5->setText(dirNames[0]);
        onConfigurationFilesRepositoryEdited();
    }
}

void GuiDeveloperModeView::onConfigurationFilesRepositoryEdited()
{
    m_curInstallationSettings->m_configurationFilesRepository = ui->tab2Area2LineEdit_5->text();
}

void GuiDeveloperModeView::onBrowseConfigurationProfile()
{
    QFileDialog dialog(this);
    QStringList dirNames;

    dialog.setFileMode(QFileDialog::Directory);
    dialog.setViewMode(QFileDialog::List);
    dialog.setDirectory(ui->tab2Area2LineEdit_5->text());

    if (dialog.exec())
    {
        dirNames = dialog.selectedFiles();
    }

    if (dirNames.size() > 0)
    {
        QDir tmp{dirNames[0]};

        ui->tab2Area2LineEdit_6->setText(tmp.dirName());
        onConfigurationProfileEdited();
    }
}

void GuiDeveloperModeView::onConfigurationProfileEdited()
{
    m_curInstallationSettings->m_configurationProfile = ui->tab2Area2LineEdit_6->text();
}

void GuiDeveloperModeView::onGenerateScript()
{
    emit generateInstallationScript(this);
}

void GuiDeveloperModeView::onRemoveInstallation()
{
    emit removeInstallation(this);
}

void GuiDeveloperModeView::hideInstallationSettingsArea()
{
    // Active configuration control buttons
    controlButtonsShowSettingsState();

    // Input areas
    ui->tab2Area2->hide();
    ui->tab2Area3->hide();
    ui->tab2Area4->hide();
    ui->tab2Area5->hide();
}

void GuiDeveloperModeView::setDefaultProjectSourcePath(QString &defaultProjectSourcePath)
{
    ui->tab1Area1LineEdit->setText(defaultProjectSourcePath);
}

void GuiDeveloperModeView::setDefaultScriptName(QString defaultScriptName)
{
    ui->tab1Area2LineEdit->setText(defaultScriptName);
}

void GuiDeveloperModeView::controlButtonsShowSettingsState()
{
    ui->tab2Area1ComboBox->show();
    ui->tab2Area1CancelButton->hide();
    ui->tab2Area1AddButton->show();
    ui->tab2Area1SaveButton->hide();

    if (m_curInstallationSettings)
    {
        ui->tab2Area1CloneButton->show();
        ui->tab2Area1DeleteButton->show();
        ui->tab2Area1UpdateButton->show();
    }
    else
    {
        ui->tab2Area1CloneButton->hide();
        ui->tab2Area1DeleteButton->hide();
        ui->tab2Area1UpdateButton->hide();
    }
}

void GuiDeveloperModeView::controlButtonsSaveSettingsState()
{
    ui->tab2Area1ComboBox->hide();
    ui->tab2Area1AddButton->hide();
    ui->tab2Area1CancelButton->show();
    ui->tab2Area1CloneButton->hide();
    ui->tab2Area1DeleteButton->hide();
    ui->tab2Area1UpdateButton->hide();
    ui->tab2Area1SaveButton->show();
}

void GuiDeveloperModeView::displayCurInstallationSettings(bool editable)
{
    setSettingsFormEditable(editable);

    // General installation settings
    //------------------------------
    ui->tab2Area2LineEdit->setText(m_curInstallationSettings->m_installationSettingsIdentifier);
    ui->tab2Area2LineEditProjectName->setText(m_curInstallationSettings->m_projectName);
    ui->tab2Area2LineEdit_2->setText(m_curInstallationSettings->m_projectSourcePath);
    ui->tab2Area2LineEdit_3->setText(m_curInstallationSettings->m_projectBuildRoot);
    ui->tab2Area2LineEdit_4->setText(m_curInstallationSettings->m_scriptName);
    ui->tab2Area2LineEdit_5->setText(m_curInstallationSettings->m_configurationFilesRepository);
    ui->tab2Area2LineEdit_6->setText(m_curInstallationSettings->m_configurationProfile);

    // Libs installation settings
    //---------------------------
    m_libsInstallationsSettings->reset();
    m_libsInstallationsSettings->display(m_curInstallationSettings->m_libsArtefactList);

    // Applications installation settings
    //-----------------------------------
    m_applicationsSettings->reset();
    m_applicationsSettings->display(m_curInstallationSettings->m_applicationArtefactList);

}

void GuiDeveloperModeView::setSettingsFormEditable(bool editable)
{
    ui->tab2Area2->show();
    ui->tab2Area3->show();
    ui->tab2Area4->show();
    if (editable)
    {
        ui->tab2Area5->hide();
    }
    else
    {
        ui->tab2Area5->show();
    }

    // General installation settings widgets
    //--------------------------------------
    ui->tab2Area2LineEdit->setEnabled(editable);
    ui->tab2Area2LineEditProjectName->setEnabled(editable);
    ui->tab2Area2LineEdit_2->setEnabled(editable);
    ui->tab2Area2BrowseButton->setEnabled(editable);
    ui->tab2Area2LineEdit_3->setEnabled(editable);
    ui->tab2Area2BrowseButton_2->setEnabled(editable);
    ui->tab2Area2LineEdit_4->setEnabled(editable);
    ui->tab2Area2LineEdit_5->setEnabled(editable);
    ui->tab2Area2BrowseButton_3->setEnabled(editable);
    ui->tab2Area2LineEdit_6->setEnabled(editable);
    ui->tab2Area2BrowseButton_4->setEnabled(editable);

    // Libs installation settings widgets
    //-----------------------------------
    m_libsInstallationsSettings->setListEditable(editable);

    // Applications installations settings
    //------------------------------------
    m_applicationsSettings->setListEditable(editable);
}

void GuiDeveloperModeView::showTopInstallationSettings()
{
    ui->platformInstallationScrollArea->verticalScrollBar()->setValue(0);
}