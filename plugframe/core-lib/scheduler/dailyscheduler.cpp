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

#include <QTime>
#include "dailyscheduler.h"
#include "scheduledevent.h"

plugframe::DailyScheduler::DailyScheduler(const QString& name):
    m_name{name}
{}

void plugframe::DailyScheduler::addScheduledEvent(ScheduledEvent *sEvt)
{
    QspScheduledEvent newly{sEvt};

    m_scheduledEvtList.append(newly);
}

void plugframe::DailyScheduler::initDay()
{
    m_idx = 0;
}

///
/// \brief DailyScheduler::nextEvt
/// \details returns a pointer to the next event to fire.
///          The next event is selected based on the current time.
/// \return next event or nullptr if there no event to fire before midnight.
///
plugframe::ScheduledEvent *plugframe::DailyScheduler::nextEvt()
{
    plugframe::ScheduledEvent *ret{nullptr};
    QTime ct{QTime::currentTime()};

    while (m_idx < m_scheduledEvtList.size() && !ret)
    {
        plugframe::QspScheduledEvent se{m_scheduledEvtList.at(m_idx++)};
        QTime nextTime{se->time()};

        if (nextTime > ct)
        {
            ret =se.data();
        }
    }

    return ret;
}

