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


#ifndef LOOP_EVENT_H
#define LOOP_EVENT_H

#include <QString>
#include "event.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace event
{

class PFCORELIB_EXPORT LoopEvent : public Event
{
private:
    quint16 m_cpt;

public:
    LoopEvent(const QString& typeId, unsigned short cpt);
    ~LoopEvent() override;

public:
    quint16 cpt() {return m_cpt;}

};

} //namespace event
} //namespace core
} //namespace plugframe
} //namespace elekdom

#endif // LOOP_EVENT_H
