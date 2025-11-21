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

#ifndef GUIAPPLICATION_H
#define GUIAPPLICATION_H

#include <QScopedPointer>
#include "pfcore-lib_export.h"
#include "launcher.h"

namespace plugframe
{
class PFCORELIB_EXPORT GuiApplication : public Launcher
{
public:
    GuiApplication();
    ~GuiApplication() override;

protected:
    void createApp(int& argc, char *argv[]) override;
    void setStyleSheet() override;
};
} // namespace plugframe

#endif // GUIAPPLICATION_H
