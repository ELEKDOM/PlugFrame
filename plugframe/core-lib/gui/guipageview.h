// Copyright (C) 2025 ELEKDOM Christophe Mars c.mars@elekdom.fr
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


#ifndef GUIPAGEVIEW_H
#define GUIPAGEVIEW_H

#include <QWidget>
#include <QString>
#include "pfcore-lib_export.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace gui
{

class PFCORELIB_EXPORT GuiPageView : public QWidget
{
    Q_OBJECT

public:
    explicit GuiPageView(QString toolActionName,
                         QWidget *parent = nullptr);
    ~GuiPageView() override;

public:
    const QString& toolActionName() {return m_toolActionName;}
    const QString& pageName() {return m_toolActionName;}
    void stackedPageIndex(int idx) {m_stackedIndex = idx;}
    int stackedPageIndex() {return m_stackedIndex;}

signals:

private:
    QString m_toolActionName; // To manage action insertion into toolbar if not empty
    int     m_stackedIndex; // Index into the central widget
};

}//namespace gui
}//namespace core
}//namespace plugframe
}//namespace elekdom

#endif // GUIPAGEVIEW_H
