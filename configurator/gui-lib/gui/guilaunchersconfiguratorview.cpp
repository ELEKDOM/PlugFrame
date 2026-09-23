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
#include "guilaunchersconfiguratorview.h"
#include "widgets/guisimplefileeditor.h"

configurator::GuiLaunchersConfiguratorView::GuiLaunchersConfiguratorView(QWidget *parent):
    GuiFileConfiguratorView{parent},
    m_editor{nullptr}
{
}

configurator::GuiLaunchersConfiguratorView::~GuiLaunchersConfiguratorView()
{
    delete m_editor;
}

void configurator::GuiLaunchersConfiguratorView::createEditor()
{
    m_editor = new GuiSimpleFileEditor;
}

void configurator::GuiLaunchersConfiguratorView::onEditConfFiles(QString artefactSourcePath,
                                                                 QString projectName,
                                                                 QString artefactName,
                                                                 QString filesRepository)
{
    setArtefactSourcePath(tr("Project source path :"),artefactSourcePath);
    setProjectName(projectName);
    setArtefactName(tr("Application name :"),artefactName);
    setConfigurationFilesRepository(filesRepository);
    hideCentralWidget();
}

void configurator::GuiLaunchersConfiguratorView::onDisplayFile(QString filePath)
{
    setCentralWidget(m_editor,filePath);
}



