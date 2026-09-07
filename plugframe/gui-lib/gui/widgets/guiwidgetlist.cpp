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
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "guiwidgetlist.h"
#include "guiwidgetlistitem.h"
#include "widgetitemcontents.h"
#include "ui_guiwidgetlist.h"

plugframe::GuiWidgetList::GuiWidgetList(bool controlPanelActivated,
                             bool initialLockedState,
                             bool verticalListOrientation,
                             bool itemControlPanelActivated,
                             QFrame::Shape initialItemShape,
                             QFrame::Shape enterEventItemShape,
                             QFrame::Shape leaveEventItemShape,
                             QFrame::Shape selectedItemShape,
                             bool selectableItem,
                             QWidget *parent):
    QWidget{parent},
    ui(new Ui::guiWidgetList),
    m_toLock(initialLockedState),
    m_itemControlPanelActivated{itemControlPanelActivated},
    m_initialItemShape(initialItemShape),
    m_enterEventItemShape(enterEventItemShape),
    m_leaveEventItemShape(leaveEventItemShape),
    m_selectedItemShape(selectedItemShape),
    m_selectableItem(selectableItem),
    m_selectedItem(nullptr)
{
    ui->setupUi(this);

    // Should the control panel be displayed?
    if (!controlPanelActivated)
    {
        ui->widgetListControlPanel->hide();
    }

    // Set initial locked state
    onLockUnlockButton();

    connect(ui->lockUnlockButton,SIGNAL(clicked(bool)),this,SLOT(onLockUnlockButton()));
    connect(ui->addButton,SIGNAL(clicked(bool)),this,SLOT(onAddButton()));
    connect(ui->updateButton,SIGNAL(clicked(bool)),this,SLOT(onUpdateButton()));
    connect(ui->deleteButton,SIGNAL(clicked(bool)),this,SLOT(onDeleteButton()));
}

plugframe::GuiWidgetList::~GuiWidgetList()
{
    delete ui;
}

void plugframe::GuiWidgetList::reset()
{
    QWidget *w;
    QLayoutItem *il;

    m_selectedItem = nullptr;
    // As long as the layout is not empty, remove widget
    while(ui->widgetListContentsLayout->count() > 0)
    {
        il = ui->widgetListContentsLayout->itemAt(0);
        if (il)
        {
            w = il->widget();
            ui->widgetListContentsLayout->removeWidget(w);
            w->deleteLater();
        }
    }
}

void plugframe::GuiWidgetList::setScrollListMinimumSize(const QSize &s)
{
    ui->guiWidgetListScrollArea->setMinimumSize(s);
}

void plugframe::GuiWidgetList::displayItem(GuiWidgetListItem *item)
{
    WidgetItemContents *itemContents;

    // item container
    itemContents = createItemContents(m_itemControlPanelActivated,
                                      m_initialItemShape,
                                      m_enterEventItemShape,
                                      m_leaveEventItemShape,
                                      m_selectedItemShape,
                                      m_selectableItem,
                                      ui->widgetListContents);
    // append into the list view
    addItem(itemContents,item);

    // Set initial locked state
    if (m_toLock)
    {
        // the list is unlocked
        itemContents->edit(true);
    }
    else
    {
        // the list is locked
        itemContents->edit(false);
    }
}

void plugframe::GuiWidgetList::setEnabledLockUnlockButton(bool enabled)
{
    ui->lockUnlockButton->setEnabled(enabled);
    ui->guiWidgetListScrollArea->setEnabled(enabled);
    lockList();
}

plugframe::WidgetItemContents *plugframe::GuiWidgetList::createItemContents(bool controlPanelActivated,
                                                      QFrame::Shape initialItemShape,
                                                      QFrame::Shape enterEventShape,
                                                      QFrame::Shape leaveEventShape,
                                                      QFrame::Shape selectedItemShape,
                                                      bool selectableItem,
                                                      QWidget *parent)
{
    return new WidgetItemContents{controlPanelActivated,parent};
}

void plugframe::GuiWidgetList::onLockUnlockButton()
{
    if (m_toLock)
    {
        if (m_selectedItem)
        {
            m_selectedItem->setFrameShape(QFrame::NoFrame);
            m_selectedItem->edit(false);
            m_selectedItem = nullptr;
        }
        lockControlPanel();
    }
    else
    {
        unlockControlPanel();
    }
}

void plugframe::GuiWidgetList::onAddButton()
{
    WidgetItemContents *item;

    editStateControlPanel();
    item = addListItemContents();
    selectItemContents(item);
    item->edit();
}

void plugframe::GuiWidgetList::onUpdateButton()
{
    editStateControlPanel();
    if (m_selectedItem)
    {
        m_selectedItem->edit();
    }
}

void plugframe::GuiWidgetList::onDeleteButton()
{
    editStateControlPanel();
    if (m_selectedItem)
    {
        qsizetype removedDataIndex;

        removedDataIndex = m_selectedItem->dataIndex();

        // The widget item is removed from the layout and deleted later !
        ui->widgetListContentsLayout->removeWidget(m_selectedItem);
        m_selectedItem->deleteLater();
        m_selectedItem = nullptr;

        emit deletedItemWidget(removedDataIndex);
    }
    editStateControlPanel(true);
}

void plugframe::GuiWidgetList::onItemLeaveEvent(WidgetItemContents *item)
{
    if(m_toLock)
    {
        // The list is currently unlocked
        if (!m_selectedItem)
        {
            item->setFrameShape(m_leaveEventItemShape);
        }
    }
}

void plugframe::GuiWidgetList::onItemEnterEvent(WidgetItemContents *item)
{
    if(m_toLock)
    {
        // The list is currently unlocked
        if (!m_selectedItem)
        {
            item->setFrameShape(m_enterEventItemShape);
        }
    }
}

void plugframe::GuiWidgetList::onItemMouseReleaseEvent(WidgetItemContents *item)
{
    if(m_toLock)
    {
        // The list is currently unlocked
        selectItemContents(item);
        editStateControlPanel(true);
    }
}

void plugframe::GuiWidgetList::onUpdatedItemContainer(WidgetItemContents *item)
{
    if (m_selectedItem == item)
    {
        emit updatedItemWidget(m_selectedItem->item());

        m_selectedItem->setFrameShape(QFrame::NoFrame);
        m_selectedItem->setEnabled(false);
        m_selectedItem = nullptr;
    }
    editStateControlPanel(true);
}

void plugframe::GuiWidgetList::lockList()
{
    int nbItemContents;
    WidgetItemContents *itemContents;
    QLayoutItem *il;

    nbItemContents = ui->widgetListContentsLayout->count();
    for (auto i=0;i<nbItemContents;i++)
    {
        il = ui->widgetListContentsLayout->itemAt(i);
        if (il)
        {
            itemContents = dynamic_cast<WidgetItemContents*>(il->widget());
            if (itemContents)
            {
                itemContents->edit(false);
            }
        }
    }
}

void plugframe::GuiWidgetList::lockControlPanel()
{
    //lockList();
    ui->lockUnlockButton->setText(tr("Unlock"));
    editStateControlPanel();
    m_toLock = false;
}

void plugframe::GuiWidgetList::unlockControlPanel()
{
    //unlockList();
    ui->lockUnlockButton->setText(tr("Lock"));
    editStateControlPanel(true);
    m_toLock = true;
}

void plugframe::GuiWidgetList::editStateControlPanel(bool edit)
{
    if (edit)
    {
        if(m_selectedItem)
        {
            ui->addButton->setEnabled(false);
            ui->updateButton->setEnabled(true);
            ui->deleteButton->setEnabled(true);
        }
        else
        {
            ui->addButton->setEnabled(true);
            ui->updateButton->setEnabled(false);
            ui->deleteButton->setEnabled(false);
        }
    }
    else
    {
        ui->addButton->setEnabled(false);
        ui->updateButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
    }
}

plugframe::WidgetItemContents *plugframe::GuiWidgetList::addListItemContents()
{
    WidgetItemContents *itemContents;
    GuiWidgetListItem  *widgetItem;

    // item container
    itemContents = createItemContents(m_itemControlPanelActivated,
                                      m_initialItemShape,
                                      m_enterEventItemShape,
                                      m_leaveEventItemShape,
                                      m_selectedItemShape,
                                      m_selectableItem,
                                      ui->widgetListContents);

    // content
    widgetItem = createItem(itemContents);

    // append into the list view
    addItem(itemContents,widgetItem);

    return itemContents;
}

void plugframe::GuiWidgetList::addItem(WidgetItemContents *container, GuiWidgetListItem *content)
{
    if (content)
    {
        container->item(content);

        // Compute maximum size constraints
        QSize totalSize{container->maximumSize()};

        totalSize.setHeight(container->maximumSize().height() + content->maximumSize().height());
        container->setMaximumSize(totalSize);
    }

    connect(container,SIGNAL(enterEvent(plugframe::WidgetItemContents*)),this,SLOT(onItemEnterEvent(plugframe::WidgetItemContents*)));
    connect(container,SIGNAL(leaveEvent(plugframe::WidgetItemContents*)),this,SLOT(onItemLeaveEvent(plugframe::WidgetItemContents*)));
    connect(container,SIGNAL(updatedItemContainer(plugframe::WidgetItemContents*)),this,SLOT(onUpdatedItemContainer(plugframe::WidgetItemContents*)));
    if (m_selectableItem)
    {
        connect(container,SIGNAL(mouseReleaseEvent(plugframe::WidgetItemContents*)),this,SLOT(onItemMouseReleaseEvent(plugframe::WidgetItemContents*)));
    }

    ui->widgetListContentsLayout->addWidget(container);
}

void plugframe::GuiWidgetList::selectItemContents(WidgetItemContents *item)
{
    if(m_selectableItem && !m_selectedItem)
    {
        m_selectedItem = item;
        m_selectedItem->setFrameShape(m_selectedItemShape);
        m_selectedItem->edit();
    }
}
