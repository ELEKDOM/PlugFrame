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


#include "schedulerelement.h"

using namespace elekdom::plugframe::core::scheduler;

SchedulerElement::SchedulerElement(const QDomElement &x,SchedulerElementHook& hook):
    QDomElement(x),
    m_hook{hook}
{

}

SchedulerElement::~SchedulerElement()
{

}

bool SchedulerElement::browse(const QString &schedulerId)
{
    bool ret{false};

    ret = m_hook.schedulerDeclarationBegin(schedulerId);
    if (ret)
    {
        ret = extractDailySchedulers();
        if (ret)
        {
            ret = extractWeeklySchedulers();
        }
    }

    m_hook.schedulerDeclarationEnd();

    return ret;
}

bool SchedulerElement::extractDailySchedulers()
{
    bool ret{true};
    QDomNodeList dSchedulers{dailySchedulers()};

    m_hook.dailySchedulersDeclarationBegin();

    for (int i = 0; i < dSchedulers.size() && ret; i++)
    {
        QDomElement elem{dSchedulers.at(i).toElement()};
        QString dsName{elem.attribute(nameAttr())};

        m_hook.dailySchedulerDeclarationBegin(dsName);

        ret = extractDailySchedulerEvents(elem);

        m_hook.dailySchedulerDeclarationEnd();
    }

    m_hook.dailySchedulersDeclarationEnd();

    return ret;
}

bool SchedulerElement::extractWeeklySchedulers()
{
    bool ret{true};
    QDomNodeList wSchedulers{weeklySchedulers()};

    m_hook.weeklySchedulersDeclarationBegin();


    for (int i = 0; i < wSchedulers.size(); i++)
    {
        QDomElement elem{wSchedulers.at(i).toElement()};
        QString wsName{elem.attribute(nameAttr())};
        DigitalSuite assignedWeeks{elem.attribute(assignedWeeksAttr())};

        m_hook.weeklySchedulerDeclarationBegin(wsName,assignedWeeks);

        ret = extractWeeklySchedulerSequences(elem);

        m_hook.weeklySchedulerDeclarationEnd();
    }

    m_hook.weeklySchedulersDeclarationEnd();

    return ret;
}

bool SchedulerElement::extractDailySchedulerEvents(const QDomElement& dsElement)
{
    bool ret{true};
    QDomNodeList scheduledEvts{dsElement.elementsByTagName(scheduledEventTag())};

    for (int i = 0; i < scheduledEvts.size() && ret; i++)
    {
        QDomElement domElem{scheduledEvts.at(i).toElement()};
        QString strTime{domElem.attribute(timeAttr())};
        QTime timeEvt{QTime::fromString(strTime, "hh:mm")};
        QString evt{domElem.attribute(evtAttr())};

        ret = m_hook.dailySchedulerEventDeclaration(timeEvt,evt);
    }

    return ret;
}

bool SchedulerElement::extractWeeklySchedulerSequences(const QDomElement &wsElement)
{
    bool ret{true};
    QDomNodeList dailySeqs{wsElement.elementsByTagName(dailySequenceTag())};

    for (int i = 0; i < dailySeqs.size() && ret; i++)
    {
        QDomElement domElem{dailySeqs.at(i).toElement()};
        DigitalSuite assignedDays{domElem.attribute(assignedDaysAttr())};
        QString dailySchedulerId{domElem.attribute(nameAttr())};

        ret = m_hook.weeklySchedulerDailySequenceDeclaration(dailySchedulerId,assignedDays);
    }

    return ret;
}

QDomNodeList SchedulerElement::dailySchedulers()
{
    QDomNodeList ret;

    QDomNodeList descendants{elementsByTagName(dailySchedulersTag())};

    if (descendants.size() == 1)
    {
        ret = elementsByTagName(dailySchedulerTag());
    }

    return ret;
}

QDomNodeList SchedulerElement::weeklySchedulers()
{
    QDomNodeList ret;

    QDomNodeList descendants{elementsByTagName(weeklySchedulersTag())};

    if (descendants.size() == 1)
    {
        ret = elementsByTagName(weeklySchedulerTag());
    }

    return ret;
}
