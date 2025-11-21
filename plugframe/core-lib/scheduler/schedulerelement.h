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

#ifndef SCHEDULERELEMENT_H
#define SCHEDULERELEMENT_H

#include <QDomElement>
#include "schedulerelementhook.h"
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT SchedulerElement : public QDomElement
{
public:
    static QString schedulerTag() {return QStringLiteral("scheduler");}

protected:
    static QString dailySchedulersTag() {return QStringLiteral("daily-schedulers");}
    static QString dailySchedulerTag() {return QStringLiteral("daily-scheduler");}
    static QString scheduledEventTag() {return QStringLiteral("scheduled-event");}
    static QString weeklySchedulersTag() {return QStringLiteral("weekly-schedulers");}
    static QString weeklySchedulerTag() {return QStringLiteral("weekly-scheduler");}
    static QString dailySequenceTag() {return QStringLiteral("daily-sequence");}

    static QString nameAttr() {return QStringLiteral("name");}
    static QString timeAttr() {return QStringLiteral("time");}
    static QString evtAttr() {return QStringLiteral("evt");}
    static QString assignedWeeksAttr() {return QStringLiteral("assigned-weeks");}
    static QString assignedDaysAttr() {return QStringLiteral("assigned-days");}

public:
    SchedulerElement(const QDomElement &x,SchedulerElementHook& hook);
    virtual ~SchedulerElement();

public:
    virtual bool browse(const QString& schedulerId);

protected:
    virtual bool extractDailySchedulers();
    virtual bool extractWeeklySchedulers();
    virtual bool extractDailySchedulerEvents(const QDomElement& dsElement);
    virtual bool extractWeeklySchedulerSequences(const QDomElement& wsElement);

private:
    QDomNodeList dailySchedulers();
    QDomNodeList weeklySchedulers();

private:
    SchedulerElementHook& m_hook;
};
}//namespace plugframe
#endif // SCHEDULERELEMENT_H
