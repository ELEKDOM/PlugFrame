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


#ifndef WORKERWATCHER_H
#define WORKERWATCHER_H

#include <QObject>
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

class PFCORELIB_EXPORT WorkerWatcher : public QObject
{
    Q_OBJECT

public:
    explicit WorkerWatcher(QObject *parent = nullptr);
    ~WorkerWatcher() override;

public:
    void connectWorker(WorkerSignal* workerSign);

protected slots:
    virtual void onWorkFinished(QspWorkerOuts outs) = 0;
};

}//namespace worker
}//namespace core
}//namespace plugframe
}//namespace elekdom

#endif // WORKERWATCHER_H
