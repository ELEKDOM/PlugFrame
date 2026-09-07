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
#include "guibundlesettingsitem.h"
#include "ui/guidevelopermodeview.h"
#include "ui_guibundlesettings.h"

GuiBundleSettingsItem::GuiBundleSettingsItem(qsizetype dIndex,
                                             qsizetype applicationItemDataIndex,
                                             GuiDeveloperModeView *developerView,
                                             QWidget *parent):
    plugframe::GuiWidgetListItem{dIndex,parent},
    ui(new Ui::guiBundleSettings),
    m_applicationItemDataIndex(applicationItemDataIndex),
    m_view(developerView)
{
    ui->setupUi(this);

    connect(ui->bundlePluginBrowseButton,SIGNAL(clicked(bool)),this,SLOT(onBundlePluginBrowse()));
}

GuiBundleSettingsItem::GuiBundleSettingsItem(qsizetype dIndex,
                                             qsizetype applicationItemDataIndex,
                                             const QString &bundleName,
                                             const QString &bundlePlugin,
                                             GuiDeveloperModeView *developerView):
    GuiBundleSettingsItem{dIndex,applicationItemDataIndex,developerView}
{
    ui->bundleNameLineEdit->setText(bundleName);
    ui->bundlePluginLineEdit->setText(bundlePlugin);
}

GuiBundleSettingsItem::~GuiBundleSettingsItem()
{
    delete ui;
}

QString GuiBundleSettingsItem::bundleName()
{
    return ui->bundleNameLineEdit->text();
}

QString GuiBundleSettingsItem::bundlePlugin()
{
    return ui->bundlePluginLineEdit->text();
}

void GuiBundleSettingsItem::onBundlePluginBrowse()
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

        dialog.setFileMode(QFileDialog::ExistingFiles);
        dialog.setViewMode(QFileDialog::List);

        dialog.setDirectory(buildRoot);

        if (dialog.exec())
        {
            dirNames = dialog.selectedFiles();
        }

        if (dirNames.size() > 0)
        {
            QString tmp{dirNames[0]};

            ui->bundlePluginLineEdit->setText(tmp.remove(buildRoot));
        }
    }
}
