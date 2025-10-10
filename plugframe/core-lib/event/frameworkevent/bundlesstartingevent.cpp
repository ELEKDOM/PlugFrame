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


#include <QDebug>
#include "bundlesstartingevent.h"

using namespace elekdom::plugframe::core::event;

const QString BundlesStartingEvent::s_typeId {"PlugFrame.Framework.BundlesStarting"};

BundlesStartingEvent::BundlesStartingEvent(plugin::BundleList& bundleList, int frameworkStartLevel, int currentStartLevel):
    FrameworkEvent{BundlesStartingEvent::s_typeId},
    m_bundlesList{bundleList},
    m_frameworkStartLevel{frameworkStartLevel},
    m_currentStartLevel{currentStartLevel}
{
    //qDebug() << "--BundlesStartingEvent::BundlesStartingEvent";
}

BundlesStartingEvent::~BundlesStartingEvent()
{
    //qDebug() << "--BundlesStartingEvent::~BundlesStartingEvent";
}
