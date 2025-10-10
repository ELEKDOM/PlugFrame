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


#ifndef GUIDISPLAY_FORWARD_H
#define GUIDISPLAY_FORWARD_H

#include <QSharedPointer>

namespace elekdom
{
namespace plugframe
{
namespace guidisplay
{
    class Gui;
    class GuiPageSelector;
    class GuiHook;
    class GuiLogsView;
    class GuiLogsController;

    namespace bundle
    {
        class GuiDisplay;
    }
    namespace service
    {
        class GuiDisplayService;
        class GuiBuilderService;

        using QspSmfGuiDisplayService = QSharedPointer<GuiDisplayService>;
        using QspSmfGuiBuilderService = QSharedPointer<GuiBuilderService>;
    }
} //namespace guidisplay
} //namespace plugframe
} //namespace elekdom
#endif // GUIDISPLAY_FORWARD_H
