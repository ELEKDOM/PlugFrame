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

#ifndef GUILOGSCONTROLLER_H
#define GUILOGSCONTROLLER_H

#include "gui/guipagecontroller.h"

class GuiLogsController : public plugframe::GuiPageController
{
    Q_OBJECT

public:
    static inline QString logsMenuName() {return tr("&Logs");}
    static inline QString logsPageCtrlName() {return QStringLiteral("Logs");}

public:
    GuiLogsController(QObject *parent = nullptr);
    ~GuiLogsController() override;

protected:
    void buildViews() override;
    virtual plugframe::GuiPageView *createLogsView();
};
#endif // GUILOGSCONTROLLER_H
