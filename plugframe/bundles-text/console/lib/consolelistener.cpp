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

#include "consolelistener.h"
#include "console.h"
#include "event/frameworkevent/frameworkstartedevent.h"

ConsoleListener::ConsoleListener(plugframe::Bundle& bundle, QObject *parent):
    BundleListener{bundle, parent}
{

}

ConsoleListener::~ConsoleListener()
{

}

void ConsoleListener::onEvent(plugframe::QspEvent ev)
{
    plugframe::Event* event{ev.data()};
    QString evtTypeId {ev->getTypeId()};

    if (evtTypeId == plugframe::FrameworkStartedEvent::s_typeId)
    {
        onFrameworkStartedEvent(dynamic_cast<plugframe::FrameworkStartedEvent*>(event));
    }
}

void ConsoleListener::onFrameworkStartedEvent(plugframe::FrameworkStartedEvent *evt)
{
    Q_UNUSED(evt)
    Console& console{dynamic_cast<Console&>(getBundle())};

    console.startTerminal();
}
