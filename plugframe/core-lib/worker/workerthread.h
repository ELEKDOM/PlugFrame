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


#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include "pfcore-lib_export.h"
#include "pfcore-lib_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace worker
{

class PFCORELIB_EXPORT WorkerThread : public QThread
{
    Q_OBJECT

private:
    WorkerSignal *m_wSignal;
    QspWorkerArgs m_args;

protected:

    bool               m_ret;

public:
    WorkerThread(WorkerSignal *wSignal,
                    const QspWorkerArgs& args,
                    QObject *parent = nullptr);
    ~WorkerThread() override;

protected:
    void run() override;
    virtual bool execWork(QspWorkerArgs args) = 0;
    virtual WorkerOuts *getWorkerOuts();
};

}//namespace worker
}//namespace core
}//namespace plugframe
}//namespace elekdom

#endif // WORKERTHREAD_H
