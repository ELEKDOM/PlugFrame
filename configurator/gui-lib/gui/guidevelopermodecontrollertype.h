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
#ifndef GUIDEVELOPERMODECONTROLLERTYPE_H
#define GUIDEVELOPERMODECONTROLLERTYPE_H

#include "gui/guicontrollertype.h"
#include "configurator-lib_export.h"

namespace configurator
{
class CONFIGURATORLIB_EXPORT GuiDeveloperModeControllerType
{
public:
    static const plugframe::GuiControllerType s_ctrlType {10};

public:
    GuiDeveloperModeControllerType() {}
};

}//namespace configurator
#endif // GUIDEVELOPERMODECONTROLLERTYPE_H
