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
#ifndef GUIWIDGETLISTITEM_H
#define GUIWIDGETLISTITEM_H

#include <QFrame>
#include "pfgui-lib_export.h"

namespace plugframe
{
class PFGUILIB_EXPORT GuiWidgetListItem : public QFrame
{
    Q_OBJECT
public:
    explicit GuiWidgetListItem(qsizetype dataIndex, QWidget *parent = nullptr);
    ~GuiWidgetListItem();

public:
    qsizetype dataIndex() {return m_dataIndex;}

signals:

private:
    qsizetype m_dataIndex;

};
}//namespace plugframe
#endif // GUIWIDGETLISTITEM_H
