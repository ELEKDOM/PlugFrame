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


#ifndef GUICONSOLECONTROLLER_H
#define GUICONSOLECONTROLLER_H

#include "gui/guipagecontroller.h"
#include "service-int/systemserviceinterface.h"
#include "plugin/bundleinterface.h"
#include "guiconsole_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace guiconsole
{

class GuiConsoleController : public core::gui::GuiPageController
{
    Q_OBJECT

private:
    static inline QString ConsoleMenuName() {return tr("&Console");}
    static inline QString ConsolePageCtrlName() {return QStringLiteral("Console");}

public:
    GuiConsoleController(framework::service::SystemServiceInterface *systemServiceItf,QObject *parent = nullptr);
    ~GuiConsoleController() override;

protected:
    void buildViews() override;
    virtual GuiConsoleView *createConsoleView();

signals:
    void sigPrint(QString msg);

private slots:
    void onLevelCmd();
    void onLoadedCmd();
    void onStartedCmd();

private:
    void displayBundlesList(core::plugin::BundleInterface::BundleState state);
    core::plugin::BundleList bundlesList(core::plugin::BundleInterface::BundleState state);
    int padding(core::plugin::BundleList& listToDisplay);

private:
    framework::service::SystemServiceInterface *m_systemServiceItf;
};

}//namespace guiconsole
}//namespace plugframe
}//namespace elekdom
#endif // GUICONSOLECONTROLLER_H
