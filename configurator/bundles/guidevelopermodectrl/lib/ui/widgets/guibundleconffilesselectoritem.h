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
#ifndef GUIBUNDLECONFFILESSELECTORITEM_H
#define GUIBUNDLECONFFILESSELECTORITEM_H

#include "gui/widgets/guiwidgetlistitem.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class guiBundleConfFilesSelector;
}
QT_END_NAMESPACE

class GuiDeveloperModeView;
class GuiBundleConfFilesSelectorItem : public plugframe::GuiWidgetListItem
{
    Q_OBJECT

public:
    GuiBundleConfFilesSelectorItem(qsizetype dIndex,
                                   const QString& appliName,
                                   const QString& bundleName,
                                   GuiDeveloperModeView *developerView);
    ~GuiBundleConfFilesSelectorItem() override;

signals:

private slots:
    void onConfFileClicked();

private:
    Ui::guiBundleConfFilesSelector *ui;
    GuiDeveloperModeView           *m_view;
    QString                         m_appliName;
};

#endif // GUIBUNDLECONFFILESSELECTORITEM_H
