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


#ifndef DAILYSCHEDULER_H
#define DAILYSCHEDULER_H

#include <QString>
#include <QList>
#include "pfcore-lib_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace scheduler
{

class DailyScheduler
{
public:
    DailyScheduler(const QString& name);

public:
    const QString& name() {return m_name;}

public:
    void addScheduledEvent(ScheduledEvent *sEvt);
    void initDay();
    ScheduledEvent *nextEvt();

private:
    QString                     m_name;
    QList<QspScheduledEvent> m_scheduledEvtList;
    int                         m_idx;
};

}//namespace scheduler
}//namespace core
}//namespace plugframe
}//namespace elekdom

#endif // DAILYSCHEDULER_H
