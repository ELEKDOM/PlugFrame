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
#ifndef GUIBUNDLESETTINGSITEM_H
#define GUIBUNDLESETTINGSITEM_H

#include "gui/widgets/guiwidgetlistitem.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class guiBundleSettings;
}
QT_END_NAMESPACE

class GuiDeveloperModeView;
class GuiBundleSettingsItem : public plugframe::GuiWidgetListItem
{
    Q_OBJECT

public:
    explicit GuiBundleSettingsItem(qsizetype dIndex,
                                   qsizetype applicationItemDataIndex,
                                   GuiDeveloperModeView *developerView,
                                   QWidget *parent = nullptr);
             GuiBundleSettingsItem(qsizetype dIndex,
                                   qsizetype applicationItemDataIndex,
                                   const QString& bundleName,
                                   const QString& bundlePlugin,
                                   GuiDeveloperModeView *developerView);
    ~GuiBundleSettingsItem() override;

signals:

public:
    QString bundleName();
    QString bundlePlugin();

private slots:
    void onBundlePluginBrowse();

private:
    Ui::guiBundleSettings *ui;
    qsizetype              m_applicationItemDataIndex;
    GuiDeveloperModeView  *m_view;
};

#endif // GUIBUNDLESETTINGSITEM_H
