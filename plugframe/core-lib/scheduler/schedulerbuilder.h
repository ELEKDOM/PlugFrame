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


#ifndef SCHEDULERBUILDER_H
#define SCHEDULERBUILDER_H

#include <QDomNodeList>
#include "logger/loggable.h"
#include "schedulerelementhook.h"
#include "dailyscheduler.h"
#include "weeklyscheduler.h"
#include "pfcore-lib_export.h"
#include "pfcore-lib_forward.h"

namespace plugframe
{
class PFCORELIB_EXPORT SchedulerBuilder : public Loggable, public SchedulerElementHook
{
public:
    explicit SchedulerBuilder(const QString& logChannel);
    ~SchedulerBuilder() override;

public:
    Scheduler *newly() {return m_newlyScheduler;}

protected:// SchedulerElementHook
    bool schedulerDeclarationBegin(const QString &schedulerId) override;
    bool schedulerDeclarationEnd() override;
    bool dailySchedulersDeclarationBegin() override;
    bool dailySchedulersDeclarationEnd() override;
    bool dailySchedulerDeclarationBegin(const QString& dailySchedulerId) override;
    bool dailySchedulerDeclarationEnd() override;
    bool dailySchedulerEventDeclaration(const QTime& timeEvt,const QString& evt) override;
    bool weeklySchedulersDeclarationBegin() override;
    bool weeklySchedulersDeclarationEnd() override;
    bool weeklySchedulerDeclarationBegin(const QString& weeklySchedulerId,const DigitalSuite& assignedWeeks) override;
    bool weeklySchedulerDeclarationEnd() override;
    bool weeklySchedulerDailySequenceDeclaration(const QString& dailySchedulerId,const DigitalSuite& assignedDays) override;

protected:
    virtual Scheduler *createScheduler(const QString& schedulerId);
    virtual DailyScheduler *createDailyScheduler(const QString& name);
    virtual ScheduledEvent *createScheduledEvent(const QTime& timeEvt,const QString& evt);
    virtual WeeklyScheduler *createWeeklyScheduler(const QString& name, const DigitalSuite& assignedWeeks);

private:
    Scheduler         *m_newlyScheduler;
    QspDailyScheduler  m_dailyScheduler;
    QspWeeklyScheduler m_weeklyScheduler;
};
}//namespace plugframe
#endif // SCHEDULERBUILDER_H
