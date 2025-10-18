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

#ifndef WEEKLYSCHEDULER_H
#define WEEKLYSCHEDULER_H

#include <QString>
#include <QVector>
#include <QSharedPointer>
#include "dailyscheduler.h"
#include "digitalsuite.h"
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT WeeklyScheduler
{
public:
    WeeklyScheduler(const QString &name, const DigitalSuite& assignedWeeks);

public:
    const QString& name() {return m_name;}
    void assignDailySequence(QspDailyScheduler dailyScheduler, const DigitalSuite& assignedDays);
    const DigitalSuite& assignedWeeks() {return m_assignedWeeks;}
    DailyScheduler* dailySched(int dayOfWeek);

private:
    QString                  m_name;
    DigitalSuite             m_assignedWeeks;
    QVector<DailyScheduler*> m_sequenceOfDay;
};
using QspWeeklyScheduler = QSharedPointer<WeeklyScheduler>;
}//namespace plugframe
#endif // WEEKLYSCHEDULER_H
