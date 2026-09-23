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
#ifndef GUIFILECONFIGURATORVIEW_H
#define GUIFILECONFIGURATORVIEW_H

#include "gui/guipageview.h"
#include "configurator-lib_export.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class fileConfiguratorView;
}
QT_END_NAMESPACE

namespace configurator
{
class GuiEditableWidget;
class CONFIGURATORLIB_EXPORT GuiFileConfiguratorView : public plugframe::GuiPageView
{
    Q_OBJECT

public:
    GuiFileConfiguratorView(QWidget *parent = nullptr);
    ~GuiFileConfiguratorView() override;

public:
    virtual void createEditor() =0;

public slots:
    virtual void onEditConfFiles(QString artefactSourcePath,QString projectName,QString artefactName,QString filesRepository)=0;
    virtual void onDisplayFile(QString filePath) =0;
    void onRefreshFiles();

signals:
    void selectedConfFileToImport(QString filePath,QString repository,QString artefactName,QWidget *view);
    void selectedConfFileFromRepository(QString filePath);

protected:
    void setArtefactSourcePath(const QString& label,const QString& text);
    void setProjectName(const QString& projectName);
    void setArtefactName(const QString& label,const QString& text);
    void setConfigurationFilesRepository(const QString& filesRepository);
    void hideCentralWidget();
    void setCentralWidget(GuiEditableWidget *w,QString filePath);

private slots:
    void onImportFile();
    void onItemActivated(int index);
    void onCentralWidgetIsClean();
    void onCentralWidgetIsDirty();

private:
    Ui::fileConfiguratorView *ui;
    GuiEditableWidget        *m_centralWidget;
    QString                   m_selectedFileName;
};
}//namespace configurator
#endif // GUIFILECONFIGURATORVIEW_H
