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
#include <QDir>
#include "guiapplicationsettingsitem.h"
#include "ui/guidevelopermodeview.h"
#include "ui_guiapplicationsettings.h"

GuiApplicationSettingsItem::GuiApplicationSettingsItem(qsizetype dIndex, GuiDeveloperModeView *developerView, QWidget *parent):
    plugframe::GuiWidgetListItem{dIndex,parent},
    ui(new Ui::guiApplicationSettings),
    m_view(developerView)
{
    ui->setupUi(this);

    connect(ui->applicationNameBrowseButton,SIGNAL(clicked(bool)),this,SLOT(onApplicationNameBrowse()));

    // Bundles settings
    m_bundlesSettings = new GuiBundlesSettings{dataIndex(),developerView};
    ui->bundlesSettingsLocationLayout->addWidget(m_bundlesSettings);
}

GuiApplicationSettingsItem::GuiApplicationSettingsItem(qsizetype dIndex,
                                                       const QString &appliName,
                                                       const QList<BundleArtefact> &bundleArtefactList,
                                                       GuiDeveloperModeView *developerView):
    GuiApplicationSettingsItem{dIndex,developerView}
{
    ui->applicationNameLineEdit->setText(appliName);

    // Display all bundle settings
    m_bundlesSettings->display(dIndex,bundleArtefactList);
}

GuiApplicationSettingsItem::~GuiApplicationSettingsItem()
{
    delete ui;
    delete m_bundlesSettings;
}

QString GuiApplicationSettingsItem::applicationName()
{
    return ui->applicationNameLineEdit->text();
}

void GuiApplicationSettingsItem::onApplicationNameBrowse()
{
    QString buildRoot{m_view->projectBuildRoot()};

    if (buildRoot.isEmpty())
    {
        QMessageBox::warning(this,tr("Developer mode"),tr("You must first define [Project build root]"));
    }
    else
    {
        QFileDialog dialog(this);
        QStringList dirNames;

        dialog.setFileMode(QFileDialog::Directory);
        dialog.setViewMode(QFileDialog::List);

        dialog.setDirectory(buildRoot);

        if (dialog.exec())
        {
            dirNames = dialog.selectedFiles();
        }

        if (dirNames.size() > 0)
        {
            QDir tmp{dirNames[0]};

            ui->applicationNameLineEdit->setText(tmp.dirName());
        }
    }
}
