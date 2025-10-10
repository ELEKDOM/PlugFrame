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
#include "startbundleevent.h"

using namespace elekdom::plugframe::core;
using namespace event;

const QString StartBundleEvent::s_typeId {"PlugFrame.Framework.StartBundle"};

StartBundleEvent::StartBundleEvent(plugin::BundleInterface *toStart):
     FrameworkEvent{StartBundleEvent::s_typeId},
     m_bundleToStart{toStart}
{
}

StartBundleEvent::~StartBundleEvent()
{
}

plugin::BundleInterface *StartBundleEvent::getBundleToStart()
{
    return m_bundleToStart;
}
