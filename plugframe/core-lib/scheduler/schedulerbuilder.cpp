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


#include "schedulerbuilder.h"
#include "schedulerelement.h"
#include "scheduler.h"
#include "dailyscheduler.h"
#include "scheduledevent.h"
#include "weeklyscheduler.h"
#include "digitalsuite.h"

using namespace elekdom::plugframe::core::scheduler;

SchedulerBuilder::SchedulerBuilder(const QString& logChannel):
    Loggable{logChannel},
    m_newlyScheduler{nullptr}
{}

SchedulerBuilder::~SchedulerBuilder()
{

}

bool SchedulerBuilder::schedulerDeclarationBegin(const QString &schedulerId)
{
    bool ret{true};

    m_newlyScheduler = createScheduler(schedulerId);
    ret = m_newlyScheduler != nullptr;
    return ret;
}

bool SchedulerBuilder::schedulerDeclarationEnd()
{
    bool ret{true};

    return ret;
}

bool SchedulerBuilder::dailySchedulersDeclarationBegin()
{
    bool ret{true};

    return ret;
}

bool SchedulerBuilder::dailySchedulersDeclarationEnd()
{
    bool ret{true};

    return ret;
}

bool SchedulerBuilder::dailySchedulerDeclarationBegin(const QString &dailySchedulerId)
{
    bool ret{true};

    m_dailyScheduler.reset(createDailyScheduler(dailySchedulerId));
    ret = !m_dailyScheduler.isNull();

    return ret;
}

bool SchedulerBuilder::dailySchedulerDeclarationEnd()
{
    bool ret{true};

    m_newlyScheduler->addDailyScheduler(m_dailyScheduler);

    return ret;
}

bool SchedulerBuilder::dailySchedulerEventDeclaration(const QTime &timeEvt, const QString &evt)
{
    bool ret{true};
    ScheduledEvent *tmp{createScheduledEvent(timeEvt,evt)};

    if (tmp)
    {
        ret = true;
        m_dailyScheduler->addScheduledEvent(tmp);
    }

    return ret;
}

bool SchedulerBuilder::weeklySchedulersDeclarationBegin()
{
    bool ret{true};

    return ret;
}

bool SchedulerBuilder::weeklySchedulersDeclarationEnd()
{
    bool ret{true};

    return ret;
}

bool SchedulerBuilder::weeklySchedulerDeclarationBegin(const QString &weeklySchedulerId, const DigitalSuite &assignedWeeks)
{
    bool ret{true};

    m_weeklyScheduler.reset(createWeeklyScheduler(weeklySchedulerId,assignedWeeks));
    ret = !m_weeklyScheduler.isNull();

    return ret;
}

bool SchedulerBuilder::weeklySchedulerDeclarationEnd()
{
    bool ret{true};

    m_newlyScheduler->addWeeklyScheduler(m_weeklyScheduler);

    return ret;
}

bool SchedulerBuilder::weeklySchedulerDailySequenceDeclaration(const QString &dailySchedulerId, const DigitalSuite &assignedDays)
{
    bool ret{false};
    QspDailyScheduler dailyScheduler(m_newlyScheduler->dailyScheduler(dailySchedulerId));

    if (!dailyScheduler.isNull())
    {
        ret = true;
        m_weeklyScheduler->assignDailySequence(dailyScheduler,assignedDays);
    }

    return ret;
}

Scheduler *SchedulerBuilder::createScheduler(const QString& schedulerId)
{
    return new Scheduler{logChannel(),schedulerId};
}

DailyScheduler *SchedulerBuilder::createDailyScheduler(const QString &name)
{
    return new DailyScheduler{name};
}

ScheduledEvent *SchedulerBuilder::createScheduledEvent(const QTime& timeEvt,const QString& evt)
{
    return new ScheduledEvent{timeEvt, evt};
}

WeeklyScheduler *SchedulerBuilder::createWeeklyScheduler(const QString &name, const DigitalSuite& assignedWeeks)
{
    return new WeeklyScheduler{name, assignedWeeks};
}
