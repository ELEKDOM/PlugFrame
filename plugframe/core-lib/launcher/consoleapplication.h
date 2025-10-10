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


#ifndef CONSOLE_APPLICATION_H
#define CONSOLE_APPLICATION_H

#include "pfcore-lib_export.h"
#include "launcher.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace launcher
{

class PFCORELIB_EXPORT ConsoleApplication : public Launcher
{
public:
    ConsoleApplication();
    ~ConsoleApplication() override;

protected:
    void createApp(int& argc, char *argv[]) override;
};

} // namespace smf
} // namespace core
} // namespace launcher
} // namespace elekdom

#endif // CONSOLE_APPLICATION_H
