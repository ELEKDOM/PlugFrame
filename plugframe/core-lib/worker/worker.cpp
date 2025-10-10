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


#include "worker.h"
#include "workerargs.h"
#include "workerthread.h"

using namespace elekdom::plugframe::core::worker;

Worker::Worker(QObject *parent) : WorkerSignal(parent)
{
}

Worker::~Worker()
{

}

void Worker::startWork(QspWorkerArgs args)
{   
    // Creates and starts the background worker thread
    m_wThread.reset(createWorkerThread(args));

    // To manage the thread end
    connect(m_wThread.get(), SIGNAL(finished()), SLOT(onThreadFinished()), Qt::QueuedConnection);

    // Work starting ...
    m_wThread->start();
}

void Worker::onThreadFinished()
{
    m_wThread.reset();
}
