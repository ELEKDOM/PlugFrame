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
#ifndef GUIAPPLICATIONSCONFFILESSELECTORITEM_H
#define GUIAPPLICATIONSCONFFILESSELECTORITEM_H

#include "gui/widgets/guiwidgetlistitem.h"
#include "database/installationsettings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class guiApplicationConfFilesSelector;
}
QT_END_NAMESPACE

class GuiDeveloperModeView;
class GuiBundlesConfFilesSelector;
class GuiApplicationsConfFilesSelectorItem : public plugframe::GuiWidgetListItem
{

    Q_OBJECT

public:
    GuiApplicationsConfFilesSelectorItem(qsizetype dIndex,
                                         const QString& appliName,
                                         const QList<BundleArtefact>& bundleArtefactList,
                                         GuiDeveloperModeView *developerView);
    ~GuiApplicationsConfFilesSelectorItem() override;

signals:

private slots:
    void onConfFileClicked();

private:
    Ui::guiApplicationConfFilesSelector *ui;
    GuiBundlesConfFilesSelector         *m_bundlesConfFilesSelector;
    GuiDeveloperModeView                *m_view;
};

#endif // GUIAPPLICATIONSCONFFILESSELECTORITEM_H
