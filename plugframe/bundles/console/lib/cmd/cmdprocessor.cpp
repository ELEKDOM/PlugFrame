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


#include "logger/pflog.h"
#include "cmd/cmdprocessor.h"
#include "terminal.h"
#include "console.h"

using namespace elekdom::plugframe;

console::cmd::CmdProcessor::CmdProcessor(const QString& logChannel,
                                         console::bundle::Console& console,
                                         QString cmdName,
                                         QString description):
    core::logger::Loggable{logChannel},
    m_console{console},
    m_cmdName{cmdName},
    m_description{description}
{

}

console::cmd::CmdProcessor::~CmdProcessor()
{

}

void console::cmd::CmdProcessor::next(QspCmdProcessor procCmd)
{
    m_nextProcessor = procCmd;
}

bool console::cmd::CmdProcessor::execCmd(const RawCmd &cmd)
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

void console::cmd::CmdProcessor::printCmdDescription()
{
    printDescription();
    if (false == m_nextProcessor.isNull())
    {
        m_nextProcessor->printCmdDescription();
    }
}

console::bundle::Console& console::cmd::CmdProcessor::console()
{
    return m_console;
}

void console::cmd::CmdProcessor::printDescription()
{
    console().printDescription(m_cmdName, m_description);
}
