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

#include "workerthread.h"
#include "workerouts.h"
#include "workersignal.h"

plugframe::WorkerThread::WorkerThread(WorkerSignal *wSignal,
                                      const plugframe::QspWorkerArgs &args,
                                      QObject *parent):
    QThread{parent},
    m_ret{false},
    m_wSignal{wSignal},
    m_args{args}
{

}

plugframe::WorkerThread::~WorkerThread()
{

}

void plugframe::WorkerThread::run()
{
    m_ret = execWork(m_args);

    // notify the watcher !
    plugframe::QspWorkerOuts outs{getWorkerOuts()};
    emit m_wSignal->workFinished(outs);
}

plugframe::WorkerOuts *plugframe::WorkerThread::getWorkerOuts()
{
    return new plugframe::WorkerOuts(m_ret);
}
