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


#ifndef GUIHOOK_H
#define GUIHOOK_H

#include <QObject>
#include "guidisplay_forward.h"
#include "pfcore-lib_forward.h"

using namespace elekdom::plugframe::core::gui;

namespace elekdom
{
namespace plugframe
{
namespace guidisplay
{

class GuiHook : public QObject
{
    Q_OBJECT

public:
    explicit GuiHook(Gui* parent,bundle::GuiDisplay& bundle);
    ~GuiHook();

public:
    virtual void initGui();
    void showGui();
    void log(const QString &msg);
    void statusMessage(const QString& msg);
    void clearStatusMessages();
    void addGuiController(const core::gui::QspGuiPageController &controller);
    void removeAllPages(QspGuiPageController controller);
    void setMainWindowTitle(const QString& title);

signals:
    void sigLog(QString msg);
    void sigStatusMessage(QString msg);
    void sigClearStatusMessages();
    void sigAddGuiController(QspGuiPageController controller);
    void sigRemoveAllPages(QspGuiPageController controller);
    void sigSetWindowTitle(const QString& title);

private slots:
    void onGuiCloseEvt();

private:
    Gui                *m_mainWindow;
    bundle::GuiDisplay& m_bundle;
};

} //namespace guidisplay
} //namespace plugframe
} //namespace elekdom

#endif // GUIHOOK_H
