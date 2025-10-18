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

#include "weeklyscheduler.h"
#include "dailyscheduler.h"

plugframe::WeeklyScheduler::WeeklyScheduler(const QString &name, const DigitalSuite& assignedWeeks):
    m_name{name},
    m_assignedWeeks{assignedWeeks},
    m_sequenceOfDay{8} // 0 is never used !
{
    for (int i= 0; i <8; i++)
    {
        m_sequenceOfDay[i] = nullptr;
    }
}

void plugframe::WeeklyScheduler::assignDailySequence(QspDailyScheduler dailyScheduler,
                                                     const DigitalSuite& assignedDays)
{
    for (int i = 0; i < assignedDays.size(); i++)
    {
        m_sequenceOfDay[assignedDays.at(i)] = dailyScheduler.data();
    }
}

plugframe::DailyScheduler *plugframe::WeeklyScheduler::dailySched(int dayOfWeek)
{
    plugframe::DailyScheduler *ret{nullptr};

    if (dayOfWeek > 0 && dayOfWeek < 8)
    {
        ret = m_sequenceOfDay[dayOfWeek];
    }

    return ret;
}
