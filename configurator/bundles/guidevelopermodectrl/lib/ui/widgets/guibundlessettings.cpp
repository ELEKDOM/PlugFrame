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
#include <QFileDialog>
#include <QMessageBox>
#include "guibundlessettings.h"
#include "guibundlesettingsitem.h"

GuiBundlesSettings::GuiBundlesSettings(qsizetype applicationItemDataIndex,GuiDeveloperModeView *parent):
    plugframe::GuiWidgetList(parent),
    m_applicationItemDataIndex(applicationItemDataIndex),
    m_view(parent)
{
    setScrollListMinimumSize(QSize(0,300));

    connect(this,SIGNAL(deletedItemWidget(qsizetype)),this,SLOT(onDeletedItemWidget(qsizetype)));
    connect(this,SIGNAL(updatedItemWidget(plugframe::GuiWidgetListItem*)),this,SLOT(onUpdatedItem(plugframe::GuiWidgetListItem*)));
}

GuiBundlesSettings::~GuiBundlesSettings()
{

}

void GuiBundlesSettings::setListEditable(bool editable)
{
    setEnabledLockUnlockButton(editable);
}

void GuiBundlesSettings::display(qsizetype applicationDataIndex,const QList<BundleArtefact> &bundleArtefactList)
{
    for (auto i=0;i<bundleArtefactList.size();i++)
    {
        plugframe::GuiWidgetListItem *item;
        QString bundleName{bundleArtefactList[i].m_bundleName};
        QString bundlePlugin{bundleArtefactList[i].m_bundlePlugin};

        item = new GuiBundleSettingsItem{i,applicationDataIndex,bundleName,bundlePlugin,m_view};
        displayItem(item);
    }
}

plugframe::GuiWidgetListItem *GuiBundlesSettings::createItem(QWidget *parent)
{
    qsizetype nextDataIndex;
    plugframe::GuiWidgetListItem *item;

    nextDataIndex = m_view->bundleArtefactsNextDataIndex(m_applicationItemDataIndex);
    item = new GuiBundleSettingsItem{nextDataIndex,m_applicationItemDataIndex,m_view,parent};

    return item;
}

void GuiBundlesSettings::onDeletedItemWidget(qsizetype dataIndex)
{
    m_view->deleteBundleArtefact(m_applicationItemDataIndex,dataIndex);
}

void GuiBundlesSettings::onUpdatedItem(plugframe::GuiWidgetListItem *item)
{
    GuiBundleSettingsItem *bundleSettingsItem{dynamic_cast<GuiBundleSettingsItem *>(item)};

    if (bundleSettingsItem)
    {
        QString bName{bundleSettingsItem->bundleName()};
        QString bPlugin{bundleSettingsItem->bundlePlugin()};

        if (bName.isEmpty())
        {
            QMessageBox::warning(this,tr("Developer mode"),tr("You must first select the name for [Bundle name]"));
        }
        else if (bPlugin.isEmpty())
        {
            QMessageBox::warning(this,tr("Developer mode"),tr("You must first select the plugin [Bundle plugin]"));
        }
        else
        {
            m_view->updateBundleArtefact(m_applicationItemDataIndex,item->dataIndex(),bName,bPlugin);
        }
    }
}
