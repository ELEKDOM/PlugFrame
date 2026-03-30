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

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <QObject>
#include <QHash>
#include <QList>
#include <QVector>
#include <QSharedPointer>
#include "logger/loggable.h"
#include "dailyscheduler.h"
#include "weeklyscheduler.h"
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT Scheduler : public QObject, public Loggable
{
    Q_OBJECT

public:
    Scheduler(const QString& logChannel,const QString& id, QObject *parent=nullptr);
    ~Scheduler() override;

public:
    void addDailyScheduler(QspDailyScheduler ds);
    void addWeeklyScheduler(QspWeeklyScheduler ws);
    QspDailyScheduler dailyScheduler(QString dailySchedulerName);
    ///
    /// \brief start
    /// initializes all timers and returns the curent evt.
    /// \param currentEvt, out
    /// \attention
    /// This method can be called by a different thread than the one that will call the stop!
    void start(QString& currentEvt);
    ///
    /// \brief stop
    /// stops all timers.
    /// \attention
    /// This method can be called by a different thread than the one that had call the start!
    void stop();

signals:
    void trigger(QString evt); // sequenced evt
    void dailySequencerIndex(int idx);// index of the triggered evt
    void weeklySequencer(QString name);// name of the selected weekly sequencer
    void dailySequencer(QString name);// name of the selected daily sequencer

    // private signals to enable the management of timers for different threads
    void startNextDayTimer(int msToMidnight);
    void startNextEventTimer(int msToNextEvt);
    void stopTimer(int timerId);

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    void assignWeeklyScheduler(QspWeeklyScheduler ws);
    void newDay();
    void previousEvt(QString& currentEvt);
    void initNextDayTimer();
    void initNextScheduledEvtTimer();
    void sendEvt();

private slots:
    // slots to enable the management of timers for different threads
    void onStartNextDayTimer(int msToMidnight);
    void onStartNextEventTimer(int msToNextEvt);
    void onStopTimer(int timerId);

private:
    QString                           m_id;                         // scheduler identificator
    QHash<QString, QspDailyScheduler> m_dsHash;                     // set of daily schedulers
    QList<QspWeeklyScheduler>         m_wsList;                     // set of weekly schedulers
    QVector<WeeklyScheduler*>         m_sequenceOfWeek;             // annual sequencing (53 weeks max)
    DailyScheduler                   *m_curDailyScheduler;          // selected daily scheduler
    ScheduledEvent                   *m_nextEventToSchedule;        //
    int                               m_nextDayTimerId;             // day change timer identifier
    int                               m_nextScheduledEvtTimerId;    // event change timer identifier
};
using QspScheduler = QSharedPointer<Scheduler>;
}//namespace plugframe
#endif // SCHEDULER_H
