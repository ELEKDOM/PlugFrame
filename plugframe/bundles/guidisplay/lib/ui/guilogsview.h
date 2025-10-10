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


#ifndef GUILOGSVIEW_H
#define GUILOGSVIEW_H

#include "gui/guipageview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class logsView;
}
QT_END_NAMESPACE

using namespace elekdom::plugframe::core::gui;

namespace elekdom
{
namespace plugframe
{
namespace guidisplay
{

class GuiLogsView : public GuiPageView
{
    Q_OBJECT

public:
    GuiLogsView(QWidget *parent = nullptr);
    ~GuiLogsView() override;

public:
    void log(QString msg);

private slots:
    void onClear();

private:
    Ui::logsView *ui;
};

} //namespace guidisplay
} //namespace plugframe
} //namespace elekdom

#endif // GUILOGSVIEW_H
