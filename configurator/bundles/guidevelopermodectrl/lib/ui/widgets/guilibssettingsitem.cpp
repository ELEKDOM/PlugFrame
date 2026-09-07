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
#include "guilibssettingsitem.h"
#include "ui/guidevelopermodeview.h"
#include "ui_guilibssettingsitem.h"

GuiLibsSettingsItem::GuiLibsSettingsItem(qsizetype dataIndex,
                                         GuiDeveloperModeView *developerView,
                                         QWidget *parent):
    plugframe::GuiWidgetListItem{dataIndex,parent},
    ui(new Ui::guiLibsSettingsItem),
    m_view(developerView)
{
    ui->setupUi(this);

    connect(ui->libNameBrowseButton,SIGNAL(clicked(bool)),this,SLOT(onBrowseLibName()));
    connect(ui->libSoNameBrowseButton,SIGNAL(clicked(bool)),this,SLOT(onBrowseSoName()));
    connect(ui->libLinkerNameBrowseButton,SIGNAL(clicked(bool)),this,SLOT(onBrowseLinkerName()));
}

GuiLibsSettingsItem::GuiLibsSettingsItem(qsizetype dataIndex,
                                         const QString &libName,
                                         const QString &soName,
                                         const QString &linkerName,
                                         GuiDeveloperModeView *developerView):
    GuiLibsSettingsItem{dataIndex,developerView}
{
    ui->libNameLineEdit->setText(libName);
    ui->libSoNameLineEdit->setText(soName);
    ui->libLinkerNameLineEdit->setText(linkerName);
}

GuiLibsSettingsItem::~GuiLibsSettingsItem()
{
    delete ui;
}

QString GuiLibsSettingsItem::libName()
{
    return ui->libNameLineEdit->text();
}

QString GuiLibsSettingsItem::soName()
{
    return ui->libSoNameLineEdit->text();
}

QString GuiLibsSettingsItem::linkerName()
{
    return ui->libLinkerNameLineEdit->text();
}

void GuiLibsSettingsItem::onBrowseLibName()
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

        dialog.setFileMode(QFileDialog::ExistingFile);
        dialog.setViewMode(QFileDialog::List);

        dialog.setDirectory(buildRoot);

        if (dialog.exec())
        {
            dirNames = dialog.selectedFiles();
        }

        if (dirNames.size() > 0)
        {
            QString tmp{dirNames[0]};

            ui->libNameLineEdit->setText(tmp.remove(buildRoot));
        }
    }
}

void GuiLibsSettingsItem::onBrowseSoName()
{
    QString tmp;

    if (getSymbolicName(tmp))
    {
        ui->libSoNameLineEdit->setText(tmp);
    }
}

void GuiLibsSettingsItem::onBrowseLinkerName()
{
    QString tmp;

    if (getSymbolicName(tmp))
    {
        ui->libLinkerNameLineEdit->setText(tmp);
    }
}

bool GuiLibsSettingsItem::getSymbolicName(QString &name)
{
    bool ret{false};

    ret = !ui->libNameLineEdit->text().isEmpty();
    if (!ret)
    {
        QMessageBox::warning(this,tr("Developer mode"),tr("You must first define [Lib name]"));
    }
    else
    {
        QString buildRoot{m_view->projectBuildRoot()};
        QDir libPath{buildRoot + ui->libNameLineEdit->text()};
        QString libDirPath;
        QFileDialog dialog(this);
        QStringList dirNames;

        name = "";
        libDirPath = libPath.absolutePath();
        libDirPath = libDirPath.remove(libPath.dirName());
        dialog.setFileMode(QFileDialog::ExistingFile);
        dialog.setViewMode(QFileDialog::List);
        dialog.setDirectory(libDirPath);

        if (dialog.exec())
        {
            dirNames = dialog.selectedFiles();
        }

        if (dirNames.size() > 0)
        {
            QDir tmp{dirNames[0]};

            libDirPath = libDirPath.remove(buildRoot);
            name = libDirPath + tmp.dirName();
        }
    }

    return ret;
}
