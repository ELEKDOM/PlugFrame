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

plugframe::BundleFactory::BundleFactory()
{
}

plugframe::BundleBuilder *plugframe::BundleFactory::createBuilder(Bundle& myBundle)
{
    return new BundleBuilder{myBundle};
}

plugframe::BundleHeaders *plugframe::BundleFactory::createHeaders(const QString& logChannel)
{
    return new BundleHeaders{logChannel};
}

plugframe::BundleEmitter *plugframe::BundleFactory::createBundleEmitter(plugframe::Bundle& myBundle)
{
    return new plugframe::BundleEmitter{myBundle};
}

plugframe::BundleListener *plugframe::BundleFactory::createBundleListener(plugframe::Bundle& myBundle)
{
    return new plugframe::BundleListener{myBundle};
}

plugframe::BundleStartingEvent *plugframe::BundleFactory::createBundleStartingEvent(plugframe::BundleInterface *bundleItf)
{
    return new plugframe::BundleStartingEvent{bundleItf};
}

plugframe::BundleStartedEvent *plugframe::BundleFactory::createBundleStartedEvent(plugframe::BundleInterface *bundleItf)
{
    return new plugframe::BundleStartedEvent{bundleItf};
}

plugframe::BundleStoppingEvent *plugframe::BundleFactory::createBundleStoppingEvent(plugframe::BundleInterface *bundleItf)
{
    return new plugframe::BundleStoppingEvent{bundleItf};
}

plugframe::BundleStoppedEvent *plugframe::BundleFactory::createBundleStoppedEvent(plugframe::BundleInterface *bundleItf)
{
    return new plugframe::BundleStoppedEvent{bundleItf};
}

