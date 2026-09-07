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
#ifndef GUIWIDGETLIST_H
#define GUIWIDGETLIST_H

#include <QObject>
#include <QScrollArea>
#include <QBoxLayout>
#include "pfgui-lib_export.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class guiWidgetList;
}
QT_END_NAMESPACE

///
/// \brief The GuiWidgetList class
///        Simple class for displaying a list of widgets (GuiWidgetListItem)
/// \details A class inheriting from QScrollArea for simple widget display.
///          It allows items to be displayed in one of two possible orientations: vertical or horizontal.
///          The class implements an optional lockable edit/view mode.

namespace plugframe
{
class GuiWidgetListItem;
class WidgetItemContents;
class PFGUILIB_EXPORT GuiWidgetList : public QWidget
{
    Q_OBJECT

public:
    explicit GuiWidgetList(bool controlPanelActivated = true,
                           bool initialLockedState = true,
                           bool verticalListOrientation = true,
                           bool itemControlPanelActivated = true,
                           QFrame::Shape initialItemShape = QFrame::NoFrame,
                           QFrame::Shape enterEventItemShape = QFrame::Panel,
                           QFrame::Shape leaveEventItemShape = QFrame::NoFrame,
                           QFrame::Shape selectedItemShape = QFrame::WinPanel,
                           bool selectableItem = true,
                           QWidget *parent = nullptr);
    ~GuiWidgetList() override;

signals:
    void deletedItemWidget(qsizetype dataIndex);
    void updatedItemWidget(plugframe::GuiWidgetListItem *item);

public:
    void reset();

protected:
    void setScrollListMinimumSize(const QSize &s);
    virtual GuiWidgetListItem *createItem(QWidget *parent) = 0;
    virtual WidgetItemContents *createItemContents(bool controlPanelActivated,
                                                   QFrame::Shape initialItemShape,
                                                   QFrame::Shape enterEventShape,
                                                   QFrame::Shape leaveEventShape,
                                                   QFrame::Shape selectedItemShape,
                                                   bool selectableItem,
                                                   QWidget *parent);
    void displayItem(plugframe::GuiWidgetListItem *item);
    void setEnabledLockUnlockButton(bool enabled = true);

private slots:
    void onLockUnlockButton();
    void onAddButton();
    void onUpdateButton();
    void onDeleteButton();
    void onItemLeaveEvent(plugframe::WidgetItemContents *item);
    void onItemEnterEvent(plugframe::WidgetItemContents *item);
    void onItemMouseReleaseEvent(plugframe::WidgetItemContents *item);
    void onUpdatedItemContainer(plugframe::WidgetItemContents *item);

private:
    void lockList();
    void lockControlPanel();
    void unlockControlPanel();
    void editStateControlPanel(bool edit=false);
    plugframe::WidgetItemContents *addListItemContents();
    void addItem(plugframe::WidgetItemContents *container,GuiWidgetListItem *content);
    void selectItemContents(WidgetItemContents *item);

private:
    Ui::guiWidgetList *ui;
    bool                m_toLock;
    bool                m_itemControlPanelActivated;
    QFrame::Shape       m_initialItemShape;
    QFrame::Shape       m_enterEventItemShape;
    QFrame::Shape       m_leaveEventItemShape;
    QFrame::Shape       m_selectedItemShape;
    bool                m_selectableItem;
    WidgetItemContents *m_selectedItem;
};
}//namespace plugframe
#endif // GUIWIDGETLIST_H
