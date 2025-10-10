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


#include <QCoreApplication>
#include <QTime>
#include <QDate>
#include "scheduler.h"
#include "dailyscheduler.h"
#include "weeklyscheduler.h"
#include "scheduledevent.h"
#include "digitalsuite.h"
#include "logger/pflog.h"

using namespace elekdom::plugframe::core::scheduler;

Scheduler::Scheduler(const QString &logChannel,const QString& id,QObject *parent):
    QObject{parent},
    logger::Loggable{logChannel},
    m_id{id},
    m_sequenceOfWeek{54}, // 0 is never used !
    m_curDailyScheduler{nullptr},
    m_curScheduledEvent{nullptr},
    m_nextDayTimerId{0},
    m_nextScheduledEvtTimerId{0}
{
    moveToThread(QCoreApplication::instance()->thread());

    for (int i = 0; i < 54; i++)
    {
        m_sequenceOfWeek[i] = nullptr;
    }
}

Scheduler::~Scheduler()
{

}

void Scheduler::addDailyScheduler(QspDailyScheduler ds)
{
    m_dsHash.insert(ds->name(), ds);
}

void Scheduler::addWeeklyScheduler(QspWeeklyScheduler ws)
{
    m_wsList.append(ws);
    assignWeeklyScheduler(ws);
}

QspDailyScheduler Scheduler::dailyScheduler(QString dailySchedulerName)
{
    return m_dsHash.value(dailySchedulerName);
}

void Scheduler::init()
{
    /*
    To consider:
    It may be necessary, at software startup, to relaunch the last event emitted?
    So perhaps consider saving the "dynamic" parameters.
    */
    // TODO ...

    // Initialize the timers event
    newDay();
}

void Scheduler::timerEvent(QTimerEvent *event)
{
    if (event)
    {
        int timerId{event->timerId()};

        killTimer(timerId);
        if (timerId == m_nextDayTimerId)
        {
            newDay();
        }
        else if (timerId == m_nextScheduledEvtTimerId)
        {
            sendEvt();
            initNextScheduledEvtTimer();
        }
    }
}

void Scheduler::assignWeeklyScheduler(QspWeeklyScheduler ws)
{
    DigitalSuite suite{ws->assignedWeeks()};

    for (int i = 0; i < suite.size(); i++)
    {
        m_sequenceOfWeek[suite.at(i)] = ws.data();
    }
}

///
/// \brief Scheduler::newDay, Looks up for the dailyScheduler for this new day !
///
void Scheduler::newDay()
{
    WeeklyScheduler *ws;
    int dow{QDate::currentDate().dayOfWeek()};
    int wn{QDate::currentDate().weekNumber()};

    pfInfo1(logChannel()) << m_id << " New day: day of week = " << dow <<" , week number = " << wn;

    // Select a new daily scheduler
    //-----------------------------
    m_curDailyScheduler = nullptr;
    m_curScheduledEvent = nullptr;
    ws = m_sequenceOfWeek[wn];
    if(ws)
    {
        m_curDailyScheduler = ws->dailySched(dow);
        if (m_curDailyScheduler)
        {
            m_curDailyScheduler->initDay();
        }
    }

    // Arm the day timer
    //------------------
    initNextDayTimer();

    // Arm the next scheduled event timer
    //-----------------------------------
    initNextScheduledEvtTimer();
}

void Scheduler::initNextDayTimer()
{
    QTime ct{QTime::currentTime()};
    QTime midnight(23,59,59);
    int msToMidnight;

    msToMidnight = ct.msecsTo(midnight) + 2000;// next day at midnight + 1s !
    m_nextDayTimerId = startTimer(msToMidnight);
}

void Scheduler::initNextScheduledEvtTimer()
{
    if (m_curDailyScheduler)
    {
        m_curScheduledEvent = m_curDailyScheduler->nextEvt();
        if (m_curScheduledEvent)
        {
            QTime ct{QTime::currentTime()};
            int msToNextEvt;

            msToNextEvt = ct.msecsTo(m_curScheduledEvent->time());
            if (msToNextEvt > 0)
            {
                m_nextScheduledEvtTimerId = startTimer(msToNextEvt);
                pfInfo1(logChannel()) << m_id << " Next event : " << m_curScheduledEvent->evt() << " at : " << m_curScheduledEvent->time().toString("hh:mm");
            }
        }
    }
}

void Scheduler::sendEvt()
{
    if (m_curScheduledEvent)
    {
        pfInfo1(logChannel()) << m_id << " event order :  " << m_curScheduledEvent->evt();

        emit trigger(m_curScheduledEvent->evt());
    }
}
