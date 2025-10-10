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


#ifndef CONSOLEEXIT_H
#define CONSOLEEXIT_H

#include "worker/workerwatcher.h"
#include "console_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace console
{
namespace bundle
{

class ConsoleExit : public core::worker::WorkerWatcher
{
private:
    Console& m_console;

public:
    ConsoleExit(Console& console);
    virtual ~ConsoleExit();

protected:
    virtual void onWorkFinished(QSharedPointer<core::worker::WorkerOuts> outs);
};

using QspConsoleExit = QSharedPointer<ConsoleExit>;

} //namespace bundle
} //namespace console
} //namespace plugframe
} //namespace elekdom

#endif // CONSOLEEXIT_H
