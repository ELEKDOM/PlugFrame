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

#ifndef GUICONSOLEVIEW_H
#define GUICONSOLEVIEW_H

#include "gui/guipageview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class consoleView;
}
QT_END_NAMESPACE

class GuiConsoleView : public plugframe::GuiPageView
{
    Q_OBJECT

public:
    GuiConsoleView(QWidget *parent = nullptr);
    ~GuiConsoleView() override;

public slots:
    void print(QString msg);

signals:
    void sigLevelCmd();
    void sigLoadedCmd();
    void sigStartedCmd();

private slots:
    void onClear();

private:
    Ui::consoleView *ui;
};
#endif // GUICONSOLEVIEW_H
