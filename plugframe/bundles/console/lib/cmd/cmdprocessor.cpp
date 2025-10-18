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

#include "cmd/cmdprocessor.h"
#include "terminal.h"
#include "console.h"

CmdProcessor::CmdProcessor(const QString& logChannel,
                           Console& console,
                           QString cmdName,
                           QString description):
    plugframe::Loggable{logChannel},
    m_console{console},
    m_cmdName{cmdName},
    m_description{description}
{

}

CmdProcessor::~CmdProcessor()
{

}

void CmdProcessor::next(QspCmdProcessor procCmd)
{
    m_nextProcessor = procCmd;
}

bool CmdProcessor::execCmd(const RawCmd &cmd)
{
    bool ret{false};
    if (cmd[0] == m_cmdName)
    {
        ret = exec(cmd);
    }
    else if (false == m_nextProcessor.isNull())
    {
        ret = m_nextProcessor->execCmd(cmd);
    }
    return ret;
}

void CmdProcessor::printCmdDescription()
{
    printDescription();
    if (false == m_nextProcessor.isNull())
    {
        m_nextProcessor->printCmdDescription();
    }
}

Console& CmdProcessor::console()
{
    return m_console;
}

void CmdProcessor::printDescription()
{
    console().printDescription(m_cmdName, m_description);
}
