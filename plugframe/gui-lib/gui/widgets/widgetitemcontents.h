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
#ifndef WIDGETITEMCONTENTS_H
#define WIDGETITEMCONTENTS_H

#include <QFrame>
#include "pfgui-lib_export.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class widgetItemContents;
}
QT_END_NAMESPACE

namespace plugframe
{
class GuiWidgetListItem;
class PFGUILIB_EXPORT WidgetItemContents : public QFrame
{
    Q_OBJECT

public:
    explicit WidgetItemContents(bool controlPanelActivated = true,
                                QWidget *parent = nullptr);
    ~WidgetItemContents() override;

public:
    void edit(bool state = true);
    qsizetype dataIndex();
    GuiWidgetListItem *item() {return m_item;}
    void item(GuiWidgetListItem *i);

signals:
    void leaveEvent(plugframe::WidgetItemContents *item);
    void enterEvent(plugframe::WidgetItemContents *item);
    void mouseReleaseEvent(plugframe::WidgetItemContents *item);
    void selectedItem(plugframe::WidgetItemContents *item);
    void updatedItemContainer(plugframe::WidgetItemContents *item);

protected:
    void leaveEvent(QEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void onSaveButton();

private:
    void associateWidget(GuiWidgetListItem *item);

private:
    Ui::widgetItemContents *ui;
    GuiWidgetListItem      *m_item;
};
}//namespace plugframe
#endif // WIDGETITEMCONTENTS_H
