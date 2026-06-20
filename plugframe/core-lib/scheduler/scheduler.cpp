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

plugframe::Scheduler::Scheduler(const QString &logChannel,const QString& id,QObject *parent):
    QObject{parent},
    plugframe::Loggable{logChannel},
    m_id{id},
    m_sequenceOfWeek{54}, // 0 is never used !
    m_curDailyScheduler{nullptr},
    m_nextEventToSchedule{nullptr},
    m_nextDayTimerId{0},
    m_nextScheduledEvtTimerId{0}
{
    // move this object to the main thread
    moveToThread(QCoreApplication::instance()->thread());

    // annual sequencing initialization
    for (int i = 0; i < 54; i++)
    {
        m_sequenceOfWeek[i] = nullptr;
    }

    // To start and stop timers
    connect(this,SIGNAL(startNextDayTimer(int)),SLOT(onStartNextDayTimer(int)),Qt::QueuedConnection);
    connect(this,SIGNAL(startNextEventTimer(int)),SLOT(onStartNextEventTimer(int)),Qt::QueuedConnection);
    connect(this,SIGNAL(stopTimer(int)),SLOT(onStopTimer(int)),Qt::QueuedConnection);
}

plugframe::Scheduler::~Scheduler()
{

}

void plugframe::Scheduler::addDailyScheduler(QspDailyScheduler ds)
{
    m_dsHash.insert(ds->name(), ds);
}

void plugframe::Scheduler::addWeeklyScheduler(QspWeeklyScheduler ws)
{
    m_wsList.append(ws);
    assignWeeklyScheduler(ws);
}

plugframe::QspDailyScheduler plugframe::Scheduler::dailyScheduler(QString dailySchedulerName)
{
    return m_dsHash.value(dailySchedulerName);
}

void plugframe::Scheduler::start(QString& currentEvt)
{
    // Initialize the timers event
    newDay();

    // Searching for previous event
    previousEvt(currentEvt);
}

void plugframe::Scheduler::stop()
{
    if (m_nextDayTimerId > 0)
    {
        emit stopTimer(m_nextDayTimerId);
    }

    if (m_nextScheduledEvtTimerId > 0)
    {
        emit stopTimer(m_nextScheduledEvtTimerId);
    }
}

void plugframe::Scheduler::timerEvent(QTimerEvent *event)
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

void plugframe::Scheduler::assignWeeklyScheduler(QspWeeklyScheduler ws)
{
    DigitalSuite suite{ws->assignedWeeks()};

    for (int i = 0; i < suite.size(); i++)
    {
        m_sequenceOfWeek[suite.at(i)] = ws.data();
    }
}

///
/// \brief Scheduler::newDay, Looks up for the dailyScheduler for this new day and arms the timers!
///
void plugframe::Scheduler::newDay()
{
    WeeklyScheduler *ws;
    int dow{QDate::currentDate().dayOfWeek()};
    int wn{QDate::currentDate().weekNumber()};

    pfInfo1(logChannel()) << tr("%1 selected day: ").arg(m_id) << dow << tr(" , week:") << wn;

    // Select a new daily scheduler
    //-----------------------------
    m_curDailyScheduler = nullptr;
    m_nextEventToSchedule = nullptr;
    ws = m_sequenceOfWeek[wn];
    if(ws)
    {
        emit weeklySequencer(ws->name());
        m_curDailyScheduler = ws->dailySched(dow);
        if (m_curDailyScheduler)
        {
            m_curDailyScheduler->initDay();
            emit dailySequencer(m_curDailyScheduler->name());
        }
    }

    // Arm the day timer
    //------------------
    initNextDayTimer();

    // Arm the next scheduled event timer
    //-----------------------------------
    initNextScheduledEvtTimer();
}

void plugframe::Scheduler::previousEvt(QString &currentEvt)
{
    currentEvt = ""; // By default, no previous programming for this day

    if (m_curDailyScheduler)
    {
        // search for the latest applicable event

        ScheduledEvent *latestApplicableEvent{m_curDailyScheduler->previousEvt()};

        if (latestApplicableEvent)
        {
            currentEvt = latestApplicableEvent->evt();
        }
        else
        {
            // search on the day before !

            int yesterday{QDate::currentDate().dayOfWeek() - 1};
            DailyScheduler *previousScheduler{nullptr};
            int wn{QDate::currentDate().weekNumber()};
            WeeklyScheduler *ws;

            if (yesterday > 0)
            {
                ws = m_sequenceOfWeek[wn]; // same week !
                previousScheduler = ws->dailySched(yesterday);
                if (previousScheduler)
                {
                    latestApplicableEvent = previousScheduler->lastEvt();
                    if (latestApplicableEvent)
                    {
                        currentEvt = latestApplicableEvent->evt();
                    }
                }
            }
            else
            {
                // search on the week before  !
                wn -= 1;
                if (wn > 0)
                {
                    ws = m_sequenceOfWeek[wn]; // previous week !
                    previousScheduler = ws->dailySched(7); // last day of a week !
                    if (previousScheduler)
                    {
                        latestApplicableEvent = previousScheduler->lastEvt();
                        if (latestApplicableEvent)
                        {
                            currentEvt = latestApplicableEvent->evt();
                        }
                    }
                }
            } // if (yesterday > 0)
        } // if (latestApplicableEvent)
    } // if (m_curDailyScheduler)
}

void plugframe::Scheduler::initNextDayTimer()
{
    QTime ct{QTime::currentTime()};
    QTime midnight(23,59,59);
    int msToMidnight;

    msToMidnight = ct.msecsTo(midnight);
    emit startNextDayTimer(msToMidnight + 1000);// next day at midnight !
}

void plugframe::Scheduler::initNextScheduledEvtTimer()
{
    if (m_curDailyScheduler) // if null, no programming this day !
    {
        m_nextEventToSchedule = m_curDailyScheduler->nextEvt();
        if (m_nextEventToSchedule)
        {
            QTime ct{QTime::currentTime()};
            int msToNextEvt;

            msToNextEvt = ct.msecsTo(m_nextEventToSchedule->time());
            if (msToNextEvt > 0)
            {
                emit startNextEventTimer(msToNextEvt);
            }
        }
    }
}

void plugframe::Scheduler::sendEvt()
{
    if (m_nextEventToSchedule)
    {
        pfInfo1(logChannel()) << tr("%1 event triggered:  ").arg(m_id) << m_nextEventToSchedule->evt();

        emit trigger(m_nextEventToSchedule->evt());
        emit dailySequencerIndex(m_curDailyScheduler->idx() -1);
    }
}

void plugframe::Scheduler::onStartNextDayTimer(int msToMidnight)
{
    m_nextDayTimerId = startTimer(msToMidnight);
}

void plugframe::Scheduler::onStartNextEventTimer(int msToNextEvt)
{
    m_nextScheduledEvtTimerId = startTimer(msToNextEvt);
    pfInfo1(logChannel()) << tr("%1 Next event triggered: ").arg(m_id) << m_nextEventToSchedule->evt() << tr(" at: %1").arg(m_nextEventToSchedule->time().toString("hh:mm"));
}

void plugframe::Scheduler::onStopTimer(int timerId)
{
    killTimer(timerId);
}
