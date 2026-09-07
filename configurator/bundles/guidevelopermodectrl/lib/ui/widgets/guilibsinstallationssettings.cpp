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
#include <QMessageBox>
#include "guilibsinstallationssettings.h"
#include "guilibssettingsitem.h"

GuiLibsInstallationsSettings::GuiLibsInstallationsSettings(GuiDeveloperModeView  *parent):
    plugframe::GuiWidgetList(parent),
    m_view(parent)
{
    setScrollListMinimumSize(QSize(0,300));

    connect(this,SIGNAL(deletedItemWidget(qsizetype)),this,SLOT(onDeletedItemWidget(qsizetype)));
    connect(this,SIGNAL(updatedItemWidget(plugframe::GuiWidgetListItem*)),this,SLOT(onUpdatedItem(plugframe::GuiWidgetListItem*)));
}

GuiLibsInstallationsSettings::~GuiLibsInstallationsSettings()
{

}

void GuiLibsInstallationsSettings::setListEditable(bool editable)
{
    setEnabledLockUnlockButton(editable);
}

void GuiLibsInstallationsSettings::display(const QList<LibsArtefact> &libsArtefactList)
{
    for (auto i=0;i<libsArtefactList.size();i++)
    {
        plugframe::GuiWidgetListItem *item;
        QString name{libsArtefactList[i].m_libName};
        QString soName{libsArtefactList[i].m_soName};
        QString linkerName{libsArtefactList[i].m_linkerName};

        item = new GuiLibsSettingsItem{i,name,soName,linkerName,m_view};
        displayItem(item);
    }
}

plugframe::GuiWidgetListItem *GuiLibsInstallationsSettings::createItem(QWidget *parent)
{
    qsizetype nextDataIndex;
    plugframe::GuiWidgetListItem *item;

    nextDataIndex = m_view->libsArtefactsNextDataIndex();
    item = new GuiLibsSettingsItem{nextDataIndex,m_view,parent};

    return item;
}

void GuiLibsInstallationsSettings::onDeletedItemWidget(qsizetype dataIndex)
{
    m_view->deleteLibsArtefact(dataIndex);
}

void GuiLibsInstallationsSettings::onUpdatedItem(plugframe::GuiWidgetListItem *item)
{
    GuiLibsSettingsItem *libsSettingsItem{dynamic_cast<GuiLibsSettingsItem *>(item)};

    if (libsSettingsItem)
    {
        QString libName{libsSettingsItem->libName()};

        if (libName.isEmpty())
        {
            QMessageBox::warning(this,tr("Developer mode"),tr("You must select a library"));
        }
        else
        {
            m_view->updateLibsArtefact(libsSettingsItem->dataIndex(),libName,libsSettingsItem->soName(),libsSettingsItem->linkerName());
        }
    }
}
