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

using namespace elekdom::plugframe;

console::bundle::Terminal::Terminal(QString& applicationName,
                                 core::worker::WorkerSignal *wSignal,
                                 const core::worker::QspWorkerArgs &args,
                                 console::bundle::Console& console):
    core::worker::WorkerThread{wSignal, args},
    m_stopFlag{false},
    m_stream{stdin},
    m_line{""},
    m_console{console}
{
    m_prompt.append(applicationName);
    m_prompt.append(">");
}

console::bundle::Terminal::~Terminal()
{

}

void console::bundle::Terminal::addCmdProcessor(cmd::QspCmdProcessor procCmd)
{
    procCmd->next(m_firstProc);
    m_firstProc = procCmd;
}

void console::bundle::Terminal::stopFlag()
{
    m_stopFlag = true;
}

bool console::bundle::Terminal::execWork(core::worker::QspWorkerArgs args)
{
    Q_UNUSED(args)

    // To avoid log message into prompt line at starting
   // msleep(100);

    while (!m_stopFlag)
    {
        printPrompt();
        waitForInput();
        parseAndExec();
    }

    return true;
}

void console::bundle::Terminal::printPrompt()
{
    m_console.print(m_prompt);
}

void console::bundle::Terminal::waitForInput()
{
    m_line = QString();
    m_stream.readLineInto(&m_line);
}

void console::bundle::Terminal::parseAndExec()
{
    m_line = m_line.toLower();
    if (false == m_line.isEmpty())
    {
        auto parts = m_line.split(QLatin1Char(' '), Qt::SkipEmptyParts);
        m_firstProc->execCmd(parts);
    }
}


