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
#ifndef GUILIBSINSTALLATIONSSETTINGS_H
#define GUILIBSINSTALLATIONSSETTINGS_H

#include "gui/widgets/guiwidgetlist.h"
#include "ui/guidevelopermodeview.h"

class GuiLibsInstallationsSettings : public plugframe::GuiWidgetList
{
    Q_OBJECT

public:
    explicit GuiLibsInstallationsSettings(GuiDeveloperModeView *parent = nullptr);
    ~GuiLibsInstallationsSettings() override;

public:
    void setListEditable(bool editable = true);
    void display(const QList<LibsArtefact>& libsArtefactList);

protected:
    plugframe::GuiWidgetListItem *createItem(QWidget *parent = nullptr) override;

signals:

private slots:
    void onDeletedItemWidget(qsizetype dataIndex);
    void onUpdatedItem(plugframe::GuiWidgetListItem *item);

private:
    GuiDeveloperModeView *m_view;
};

#endif // GUILIBSINSTALLATIONSSETTINGS_H
