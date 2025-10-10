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


#include "bundlefactory.h"
#include "bundle/bundle.h"
#include "bundle/bundlebuilder.h"
#include "bundle/bundleheaders.h"
#include "bundle/bundleemitter.h"
#include "bundle/bundlelistener.h"
#include "event/bundleevent/bundlestartedevent.h"
#include "event/bundleevent/bundlestartingevent.h"
#include "event/bundleevent/bundlestoppedevent.h"
#include "event/bundleevent/bundlestoppingevent.h"

using namespace elekdom::plugframe::core;
using namespace elekdom::plugframe::core::bundle;

BundleFactory::BundleFactory()
{
}

BundleBuilder *BundleFactory::createBuilder(Bundle& myBundle)
{
    return new BundleBuilder{myBundle};
}

BundleHeaders *BundleFactory::createHeaders(const QString& logChannel)
{
    return new BundleHeaders{logChannel};
}

BundleEmitter *BundleFactory::createBundleEmitter(Bundle& myBundle)
{
    return new BundleEmitter{myBundle};
}

BundleListener *BundleFactory::createBundleListener(Bundle& myBundle)
{
    return new BundleListener{myBundle};
}

event::BundleStartingEvent *BundleFactory::createBundleStartingEvent(core::plugin::BundleInterface *bundleItf)
{
    return new event::BundleStartingEvent{bundleItf};
}

event::BundleStartedEvent *BundleFactory::createBundleStartedEvent(core::plugin::BundleInterface *bundleItf)
{
    return new event::BundleStartedEvent{bundleItf};
}

event::BundleStoppingEvent *BundleFactory::createBundleStoppingEvent(core::plugin::BundleInterface *bundleItf)
{
    return new event::BundleStoppingEvent{bundleItf};
}

event::BundleStoppedEvent *BundleFactory::createBundleStoppedEvent(core::plugin::BundleInterface *bundleItf)
{
    return new event::BundleStoppedEvent{bundleItf};
}

