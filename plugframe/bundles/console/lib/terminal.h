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

#ifndef TERMINAL_H
#define TERMINAL_H

#include <QTextStream>
#include "worker/workerthread.h"
#include "worker/workerargs.h"
#include "cmd/cmdprocessor.h"
#include "console_forward.h"

class Terminal : public plugframe::WorkerThread
{
public:
    Terminal(QString& applicationName,
             plugframe::WorkerSignal *wSignal,
             const plugframe::QspWorkerArgs& args,
             Console& console);
    ~Terminal() override;
public:
    void addCmdProcessor(QspCmdProcessor cmdProcessor);
    void stopFlag();

protected:
    bool execWork(plugframe::QspWorkerArgs args) override;

private:
    void printPrompt();
    void waitForInput();
    void parseAndExec();

private:
    bool            m_stopFlag;
    QspCmdProcessor m_firstProc;
    QString         m_prompt;
    QTextStream     m_stream;
    QString         m_line;
    Console&        m_console;
};

using CmdArgs = QStringList;

#endif // TERMINAL_H
