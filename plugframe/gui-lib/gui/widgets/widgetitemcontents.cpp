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
#include "widgetitemcontents.h"
#include "guiwidgetlistitem.h"
#include "ui_widgetitemcontents.h"

plugframe::WidgetItemContents::WidgetItemContents(bool controlPanelActivated,
                                       QWidget *parent):
    QFrame{parent},
    ui(new Ui::widgetItemContents),
    m_item{nullptr}
{
    ui->setupUi(this);

    // Should the control panel be displayed?
    if (!controlPanelActivated)
    {
        ui->itemControlPanel->hide();
    }

    //initial state
    edit(false);

    connect(ui->saveItemButton,SIGNAL(clicked(bool)),this,SLOT(onSaveButton()));
}

plugframe::WidgetItemContents::~WidgetItemContents()
{
    delete ui;
}

void plugframe::WidgetItemContents::edit(bool state)
{
    QLayoutItem *itemLayout{ui->widgetItemLocation->itemAt(0)};

    if (itemLayout)
    {
        itemLayout->widget()->setEnabled(state);
    }
    if (state)
    {
        ui->itemControlPanel->show();
    }
    else
    {
        ui->itemControlPanel->hide();
    }
}

qsizetype plugframe::WidgetItemContents::dataIndex()
{
    qsizetype ret{-1};

    if (m_item)
    {
        ret = m_item->dataIndex();
    }
    return ret;
}

void plugframe::WidgetItemContents::item(GuiWidgetListItem *i)
{
    m_item = i;

    // Set the item
    if (m_item)
    {
        ui->widgetItemLocation->addWidget(m_item);
    }
}

void plugframe::WidgetItemContents::leaveEvent(QEvent *event)
{
    QFrame::leaveEvent(event);
    emit leaveEvent(this);
}

void plugframe::WidgetItemContents::enterEvent(QEnterEvent *event)
{
    QFrame::enterEvent(event);
    emit enterEvent(this);
}

void plugframe::WidgetItemContents::mouseReleaseEvent(QMouseEvent *event)
{
    QFrame::mouseReleaseEvent(event);
    emit mouseReleaseEvent(this);
}

void plugframe::WidgetItemContents::onSaveButton()
{
    edit(false);
    emit updatedItemContainer(this);
}
