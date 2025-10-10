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
#include "pfcore-lib_export.h"
#include "pfcore-lib_forward.h"
#include "logger/loggable.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace scheduler
{

class PFCORELIB_EXPORT Scheduler : public QObject, public logger::Loggable
{
    Q_OBJECT

public:
    Scheduler(const QString& logChannel,const QString& id, QObject *parent=nullptr);
    ~Scheduler() override;

public:
    void addDailyScheduler(QspDailyScheduler ds);
    void addWeeklyScheduler(QspWeeklyScheduler ws);
    QspDailyScheduler dailyScheduler(QString dailySchedulerName);
    void init();

signals:
    void trigger(QString evt);

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    void assignWeeklyScheduler(QspWeeklyScheduler ws);
    void newDay();
    void initNextDayTimer();
    void initNextScheduledEvtTimer();
    void sendEvt();

private:
    QString m_id;
    QHash<QString, QspDailyScheduler> m_dsHash;
    QList<QspWeeklyScheduler>         m_wsList;
    QVector<WeeklyScheduler*>      m_sequenceOfWeek;
    DailyScheduler                   *m_curDailyScheduler;
    ScheduledEvent                   *m_curScheduledEvent;
    int                               m_nextDayTimerId;
    int                               m_nextScheduledEvtTimerId;
};

}//namespace scheduler
}//namespace core
}//namespace plugframe
}//namespace elekdom

#endif // SCHEDULER_H
