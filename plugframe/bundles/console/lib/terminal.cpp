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

#include "terminal.h"
#include "console.h"
#include "cmd/cmdprocessor.h"
#include "worker/workerargs.h"

Terminal::Terminal(QString& applicationName,
                   plugframe::WorkerSignal *wSignal,
                   const plugframe::QspWorkerArgs& args,
                   Console& console):
    plugframe::WorkerThread{wSignal, args},
    m_stopFlag{false},
    m_stream{stdin},
    m_line{""},
    m_console{console}
{
    m_prompt.append(applicationName);
    m_prompt.append(">");
}

Terminal::~Terminal()
{

}

void Terminal::addCmdProcessor(QspCmdProcessor cmdProcessor)
{
    cmdProcessor->next(m_firstProc);
    m_firstProc = cmdProcessor;
}

void Terminal::stopFlag()
{
    m_stopFlag = true;
}

bool Terminal::execWork(plugframe::QspWorkerArgs args)
{
    Q_UNUSED(args)

    while (!m_stopFlag)
    {
        printPrompt();
        waitForInput();
        parseAndExec();
    }

    return true;
}

void Terminal::printPrompt()
{
    m_console.print(m_prompt);
}

void Terminal::waitForInput()
{
    m_line = QString();
    m_stream.readLineInto(&m_line);
}

void Terminal::parseAndExec()
{
    m_line = m_line.toLower();
    if (false == m_line.isEmpty())
    {
        auto parts = m_line.split(QLatin1Char(' '), Qt::SkipEmptyParts);
        m_firstProc->execCmd(parts);
    }
}


