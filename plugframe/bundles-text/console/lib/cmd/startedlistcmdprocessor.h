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

#ifndef STARTEDLISTCMDPROCESSOR_H
#define STARTEDLISTCMDPROCESSOR_H

#include "cmd/cmdprocessor.h"

class StartedListCmdProcessor : public CmdProcessor
{
public:
    StartedListCmdProcessor(const QString& logChannel,
                            Console& console);
    virtual ~StartedListCmdProcessor();

protected:
    virtual bool exec(const RawCmd& cmd);
};

#endif // STARTEDLISTCMDPROCESSOR_H
