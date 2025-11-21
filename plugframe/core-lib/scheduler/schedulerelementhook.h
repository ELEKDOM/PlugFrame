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


#ifndef SCHEDULERELEMENTHOOK_H
#define SCHEDULERELEMENTHOOK_H

#include <QTime>
#include <QString>
#include "digitalsuite.h"
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT SchedulerElementHook
{
public:
    virtual ~SchedulerElementHook() {}

public:
    virtual bool schedulerDeclarationBegin(const QString &schedulerId) = 0;
    virtual bool schedulerDeclarationEnd() = 0;
    virtual bool dailySchedulersDeclarationBegin() = 0;
    virtual bool dailySchedulersDeclarationEnd() = 0;
    virtual bool dailySchedulerDeclarationBegin(const QString& dailySchedulerId) = 0;
    virtual bool dailySchedulerDeclarationEnd() = 0;
    virtual bool dailySchedulerEventDeclaration(const QTime& timeEvt,const QString& evt) = 0;
    virtual bool weeklySchedulersDeclarationBegin() = 0;
    virtual bool weeklySchedulersDeclarationEnd() = 0;
    virtual bool weeklySchedulerDeclarationBegin(const QString& weeklySchedulerId,const DigitalSuite& assignedWeeks) = 0;
    virtual bool weeklySchedulerDeclarationEnd() = 0;
    virtual bool weeklySchedulerDailySequenceDeclaration(const QString& dailySchedulerId,const DigitalSuite& assignedDays) = 0;
};
}//namespace plugframe
#endif // SCHEDULERELEMENTHOOK_H
