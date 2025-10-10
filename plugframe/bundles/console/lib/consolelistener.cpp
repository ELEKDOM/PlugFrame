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

using namespace elekdom::plugframe::console;
using namespace elekdom::plugframe;

ConsoleListener::ConsoleListener(core::bundle::Bundle& bundle, QObject *parent):
    BundleListener{bundle, parent}
{

}

ConsoleListener::~ConsoleListener()
{

}

void ConsoleListener::onEvent(core::event::QspEvent ev)
{
    core::event::Event* event{ev.data()};
    QString evtTypeId {ev->getTypeId()};

    if (evtTypeId == core::event::FrameworkStartedEvent::s_typeId)
    {
        onFrameworkStartedEvent(dynamic_cast<core::event::FrameworkStartedEvent*>(event));
    }
}

void ConsoleListener::onFrameworkStartedEvent(core::event::FrameworkStartedEvent *evt)
{
    Q_UNUSED(evt)
    bundle::Console& console{dynamic_cast<bundle::Console&>(getBundle())};

    console.startTerminal();
}
