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
#include "guifileconfiguratorview.h"
#include "ui_fileconfiguratorview.h"
#include "widgets/guieditablewidget.h"

configurator::GuiFileConfiguratorView::GuiFileConfiguratorView(QWidget *parent):
    GuiPageView{"",parent},
    ui(new Ui::fileConfiguratorView),
    m_centralWidget{nullptr}
{
    ui->setupUi(this);
    ui->verticalLayout_2->setAlignment(Qt::AlignTop);

    connect(ui->importButton,SIGNAL(clicked(bool)),this,SLOT(onImportFile()));
    connect(ui->refreshButton,SIGNAL(clicked(bool)),this,SLOT(onRefreshFiles()));
    connect(ui->filesComboBox,SIGNAL(activated(int)),this,SLOT(onItemActivated(int)));
}

configurator::GuiFileConfiguratorView::~GuiFileConfiguratorView()
{

}

void configurator::GuiFileConfiguratorView::setArtefactSourcePath(const QString& label, const QString& text)
{
    ui->artefactSourcePathLabel->setText(label);
    ui->artefactSourcePathLineEdit->setText(text);
}

void configurator::GuiFileConfiguratorView::setProjectName(const QString &projectName)
{
    ui->projectNameLineEdit->setText(projectName);
}

void configurator::GuiFileConfiguratorView::setArtefactName(const QString &label, const QString &text)
{
    ui->artefactNameLabel->setText(label);
    ui->artefactNameLineEdit->setText(text);
}

void configurator::GuiFileConfiguratorView::setConfigurationFilesRepository(const QString &filesRepository)
{
    ui->repositoryLineEdit->setText(filesRepository);
    onRefreshFiles();
}

void configurator::GuiFileConfiguratorView::hideCentralWidget()
{
    if (m_centralWidget)
    {
        m_centralWidget->hide();
    }
}

void configurator::GuiFileConfiguratorView::setCentralWidget(GuiEditableWidget *w, QString filePath)
{
    if (m_centralWidget)
    {
        ui->centralWidgetLocationLayout->removeWidget(m_centralWidget);
        disconnect(m_centralWidget,SIGNAL(isClean()),this,SLOT(onCentralWidgetIsClean()));
        disconnect(m_centralWidget,SIGNAL(isDirty()),this,SLOT(onCentralWidgetIsDirty()));
    }

    m_centralWidget = w;
    if (m_centralWidget)
    {
        connect(m_centralWidget,SIGNAL(isClean()),this,SLOT(onCentralWidgetIsClean()));
        connect(m_centralWidget,SIGNAL(isDirty()),this,SLOT(onCentralWidgetIsDirty()));
        ui->centralWidgetLocationLayout->addWidget(m_centralWidget);
        m_centralWidget->show();

        m_centralWidget->edit(filePath);
    }
}

void configurator::GuiFileConfiguratorView::onImportFile()
{
    QFileDialog dialog;
    QStringList files;
    QString filePath;

    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::List);
    dialog.setDirectory(ui->artefactSourcePathLineEdit->text());
    dialog.setWindowTitle(QObject::tr("Select a file to import in the repository"));

    if (dialog.exec())
    {
        files = dialog.selectedFiles();
        filePath = files[0];
        if (!filePath.isEmpty())
        {
            emit selectedConfFileToImport(filePath,
                                          ui->repositoryLineEdit->text(),
                                          ui->artefactNameLineEdit->text(),
                                          this);
        }
    }
}

void configurator::GuiFileConfiguratorView::onRefreshFiles()
{
    QDir artefactRepos{ui->repositoryLineEdit->text() + QDir::separator() + ui->artefactNameLineEdit->text()};
    QStringList files,nameFilters{"*.ini","*.qss","*.qm","*.xml"};

    files = artefactRepos.entryList(nameFilters);
    ui->filesComboBox->clear();
    for (auto i=0;i<files.size();i++)
    {
        ui->filesComboBox->addItem(files[i]);
    }
}

void configurator::GuiFileConfiguratorView::onItemActivated(int index)
{
    if (m_selectedFileName !=  ui->filesComboBox->itemText(index))
    {
        m_selectedFileName = ui->filesComboBox->itemText(index);
        QString filePalth{ui->repositoryLineEdit->text() + QDir::separator() + ui->artefactNameLineEdit->text() + QDir::separator() + m_selectedFileName};

        emit selectedConfFileFromRepository(filePalth);
    }
}

void configurator::GuiFileConfiguratorView::onCentralWidgetIsClean()
{
    ui->filesComboBox->setEnabled(true);
}

void configurator::GuiFileConfiguratorView::onCentralWidgetIsDirty()
{
    ui->filesComboBox->setEnabled(false);
}
