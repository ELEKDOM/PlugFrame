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
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include "guifileconfiguratorcontroller.h"

configurator::GuiFileConfiguratorController::GuiFileConfiguratorController(plugframe::GuiControllerType ctrlType,QObject *parent):
    GuiPageController{ctrlType,
                      parent}
{}

configurator::GuiFileConfiguratorController::~GuiFileConfiguratorController()
{

}

void configurator::GuiFileConfiguratorController::buildViews()
{
    GuiFileConfiguratorView *view{createFileConfiguratorView()};

    if (view)
    {
        view->createEditor();

        connect(this,SIGNAL(editConfFiles(QString,QString,QString,QString)),view,SLOT(onEditConfFiles(QString,QString,QString,QString)));
        connect(this,SIGNAL(editFile(QString)),view,SLOT(onDisplayFile(QString)));
        connect(this,SIGNAL(refreshFileList()),view,SLOT(onRefreshFiles()));
        connect(view,SIGNAL(selectedConfFileToImport(QString,QString,QString,QWidget*)),this,SLOT(onSelectedConfFileToImport(QString,QString,QString,QWidget*)));
        connect(view,SIGNAL(selectedConfFileFromRepository(QString)),this,SLOT(onSelectedConfFileFromRepository(QString)));

        addView(view);
    }
}

///
/// \brief configurator::GuiFileConfiguratorController::onSelectedConfFileToImport
/// \param filePath
/// \param repository
/// \param artefactName
/// \param view
///
void configurator::GuiFileConfiguratorController::onSelectedConfFileToImport(QString filePath, QString repositoryPath, QString artefactName, QWidget *view)
{
    QDir artefactRepository{repositoryPath + QDir::separator() + artefactName};
    QString fileName{QDir(filePath).dirName()};

    // Check for artefact repository first
    //------------------------------------
    if (!artefactRepository.exists())
    {
        artefactRepository.setPath(repositoryPath);
        artefactRepository.mkdir(artefactName);
        artefactRepository.cd(artefactName);
    }

    // 1 check if the file already exists in the repository
    //-----------------------------------------------------
    if (artefactRepository.exists(fileName))
    {
        QMessageBox::StandardButton rep;

        rep = QMessageBox::question(view,tr("Repository"),tr("The file already exists. Do you want to replace it?"));
        if (rep == QMessageBox::Yes)
        {
            artefactRepository.remove(fileName);
        }
    }

    // 2 copy the src file into the artefact repository
    //-------------------------------------------------
    if (!artefactRepository.exists(fileName))
    {
        QString targetPath{artefactRepository.absoluteFilePath(fileName)};
        QFile sourceFile{filePath};
        bool ok{sourceFile.copy(targetPath)};

        if (!ok)
        {
            QMessageBox::information(view,targetPath,tr("Copy error !"));
        }
        else
        {
            emit refreshFileList();
        }
    }
}

void configurator::GuiFileConfiguratorController::onSelectedConfFileFromRepository(QString filePath)
{
    QString ext{filePath.sliced(filePath.lastIndexOf("."))};

    if (ext != ".qm")
    {
        emit editFile(filePath);
    }
}