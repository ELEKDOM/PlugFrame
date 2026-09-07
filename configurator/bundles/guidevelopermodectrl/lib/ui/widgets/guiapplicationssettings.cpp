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
#include "guiapplicationssettings.h"
#include "guiapplicationsettingsitem.h"

GuiApplicationsSettings::GuiApplicationsSettings(GuiDeveloperModeView *parent) :
    plugframe::GuiWidgetList(parent),
    m_view(parent)
{
    setScrollListMinimumSize(QSize(0,600));

    connect(this,SIGNAL(deletedItemWidget(qsizetype)),this,SLOT(onDeletedItemWidget(qsizetype)));
    connect(this,SIGNAL(updatedItemWidget(plugframe::GuiWidgetListItem*)),this,SLOT(onUpdatedItem(plugframe::GuiWidgetListItem*)));
}

GuiApplicationsSettings::~GuiApplicationsSettings()
{

}

void GuiApplicationsSettings::setListEditable(bool editable)
{
    setEnabledLockUnlockButton(editable);
}

void GuiApplicationsSettings::display(const QList<ApplicationArtefact> &applicationArtefactList)
{
    for (auto i=0;i<applicationArtefactList.size();i++)
    {
        plugframe::GuiWidgetListItem *item;
        QString appliName{applicationArtefactList[i].m_applicationName};
        QList<BundleArtefact> bundleArtefactList{applicationArtefactList[i].m_bundleArtefactList};

        item = new GuiApplicationSettingsItem{i,appliName,bundleArtefactList,m_view};
        displayItem(item);
    }
}

plugframe::GuiWidgetListItem *GuiApplicationsSettings::createItem(QWidget *parent)
{
    qsizetype nextDataIndex;
    plugframe::GuiWidgetListItem *item;

    nextDataIndex = m_view->applicationArtefactsNextDataIndex();
    item = new GuiApplicationSettingsItem{nextDataIndex,m_view,parent};

    return item;
}

void GuiApplicationsSettings::onDeletedItemWidget(qsizetype dataIndex)
{
    m_view->deleteApplicationArtefact(dataIndex);
}

void GuiApplicationsSettings::onUpdatedItem(plugframe::GuiWidgetListItem *item)
{
    GuiApplicationSettingsItem *wItem{dynamic_cast<GuiApplicationSettingsItem*>(item)};

    if (wItem)
    {
        m_view->updateApplicationArtefact(item->dataIndex(),wItem->applicationName());
    }
}
