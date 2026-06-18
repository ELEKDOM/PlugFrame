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

#include "guiconsolectrl.h"
#include "guiconsolectrlfactory.h"
#include "ui/guiconsolecontroller.h"

GuiConsoleCtrl::GuiConsoleCtrl():
    plugframe::GuiControllerViewsLoader{"GuiConsoleCtrl"}
{

}

GuiConsoleCtrl::~GuiConsoleCtrl()
{

}

plugframe::BundleFactory *GuiConsoleCtrl::createFactory()
{
    return new GuiConsoleCtrlFactory;
}

void GuiConsoleCtrl::postBuildController(plugframe::QspGuiPageController guiCtrl)
{
    QspGuiConsoleController consoleCtrl{guiCtrl.dynamicCast<GuiConsoleController>()};
    plugframe::SystemServiceInterface *systemServiceItf{bundleContext()->getService<plugframe::SystemServiceInterface>(plugframe::SystemServiceInterface::serviceName())};

    if (!consoleCtrl.isNull())
    {
        consoleCtrl->platformItf(systemServiceItf);
    }
}

PF_qtServiceInterface_DEF(GuiConsoleCtrl)