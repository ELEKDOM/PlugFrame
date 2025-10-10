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


#ifndef GUIPAGESELECTOR_H
#define GUIPAGESELECTOR_H

#include <QAction>
#include "pfcore-lib_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace guidisplay
{

class GuiPageSelector : public QAction
{
    Q_OBJECT

public:
    explicit GuiPageSelector(int idx,
                             QString name,
                             core::gui::GuiPageController *ctrl,
                             QWidget *parent = nullptr);
    ~ GuiPageSelector() override;

public:
    int idx() {return m_idx;}
    core::gui::GuiPageController *ctrl(){return m_ctrl;}

signals:
    void selectedPage(int idx);

private slots:
    void onTriggered(bool);

private:
    int m_idx;
    core::gui::GuiPageController *m_ctrl;
};

} //namespace guidisplay
} //namespace plugframe
} //namespace elekdom

#endif // GUIPAGESELECTOR_H
