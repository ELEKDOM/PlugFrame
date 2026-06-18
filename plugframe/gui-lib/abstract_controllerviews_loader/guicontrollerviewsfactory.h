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
#ifndef GUICONTROLLERVIEWSFACTORY_H
#define GUICONTROLLERVIEWSFACTORY_H

#include "factory/defaultbundlefactory.h"
#include "gui/guipagecontroller.h"
#include "pfgui-lib_export.h"

namespace plugframe
{
class PFGUILIB_EXPORT GuiControllerViewsFactory : public DefaultBundleFactory
{
public:
    GuiControllerViewsFactory();
    ~GuiControllerViewsFactory() override;

public:
    virtual GuiPageController *createGuiController() = 0;
};
}//namespace plugframe
#endif // GUICONTROLLERVIEWSFACTORY_H
