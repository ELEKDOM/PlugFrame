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
#ifndef GUIFILECONFIGURATORCONTROLLER_H
#define GUIFILECONFIGURATORCONTROLLER_H

#include "gui/guipagecontroller.h"
#include "guifileconfiguratorview.h"
#include "configurator-lib_export.h"

namespace configurator
{
class CONFIGURATORLIB_EXPORT GuiFileConfiguratorController : public plugframe::GuiPageController
{
    Q_OBJECT

public:
    GuiFileConfiguratorController(plugframe::GuiControllerType ctrlType,QObject *parent = nullptr);
    ~GuiFileConfiguratorController() override;

signals:
    void editConfFiles(QString artefactSourcePath,QString projectName,QString applicationName,QString filesRepository);
    void editFile(QString filePath);
    void refreshFileList();

protected:
    void buildViews() override;
    virtual GuiFileConfiguratorView *createFileConfiguratorView() =0;

private slots:
    void onSelectedConfFileToImport(QString filePath,QString repositoryPath,QString artefactName,QWidget *view);
    void onSelectedConfFileFromRepository(QString filePath);
};
using QspGuiFileConfiguratorController = QSharedPointer<GuiFileConfiguratorController>;
}//namespace configurator
#endif // GUIFILECONFIGURATORCONTROLLER_H
