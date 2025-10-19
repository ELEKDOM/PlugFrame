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

#include "framework.h"
#include "frameworkfactory.h"
#include "frameworkstarter.h"
#include "frameworkstarterlistener.h"
#include "serviceregistry.h"
#include "systemservice.h"
#include "event/frameworkevent/bundlesstartingevent.h"
#include "event/frameworkevent/startbundleevent.h"
#include "event/frameworkevent/frameworkstartedevent.h"
#include "event/frameworkevent/bundlesstoppingevent.h"
#include "event/frameworkevent/stopbundleevent.h"
#include "bundle/bundle.h"
#include "bundle/bundlecontext.h"
#include "service-int/systemserviceinterface.h"
#include "service-int/systemserviceregistryinterface.h"

FrameworkFactory::FrameworkFactory()
{
}

FrameworkFactory::~FrameworkFactory()
{

}

plugframe::BundleEmitter *FrameworkFactory::createBundleEmitter(plugframe::Bundle &myBundle)
{
    return new FrameworkStarter{myBundle};
}

plugframe::BundleListener *FrameworkFactory::createBundleListener(plugframe::Bundle &myBundle)
{
   return new FrameworkStarterListener{myBundle};
}

plugframe::ServiceImplementationInterface *FrameworkFactory::createServiceImplementation(plugframe::BundleImplementation *implementation,
                                                                                         const QString &sName,
                                                                                         const QString &serviceVersion)
{
    plugframe::ServiceImplementationInterface *ret{nullptr};

    if (plugframe::SystemServiceRegistryInterface::serviceName() == sName)
    {
        if (plugframe::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createServiceRegistry(implementation);
        }
    }
    else if (plugframe::SystemServiceInterface::serviceName() == sName)
    {
        if (plugframe::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createSystemService(implementation);
        }
    }

    return ret;
}

plugframe::BundleContext *FrameworkFactory::createBundleContext(plugframe::SystemServiceRegistryInterface *registryService)
{
    return new plugframe::BundleContext{registryService};
}

plugframe::BundlesStartingEvent *FrameworkFactory::createBundlesStartingEvent(plugframe::BundleList& bundlesToStart,
                                                                              int fwkLevel,
                                                                              int level)
{
    return  new plugframe::BundlesStartingEvent{bundlesToStart,fwkLevel,level};
}

plugframe::StartBundleEvent *FrameworkFactory::createStartBundleEvent(plugframe::BundleInterface *toStart)
{
    return new plugframe::StartBundleEvent{toStart};
}

plugframe::FrameworkStartedEvent *FrameworkFactory::createFrameworkStartedEvent()
{
    return new plugframe::FrameworkStartedEvent{};
}

plugframe::BundlesStoppingEvent *FrameworkFactory::createBundlesStoppingEvent(plugframe::BundleList &bundlesToStop,
                                                                              int level)
{
    return  new plugframe::BundlesStoppingEvent{bundlesToStop, level};
}

plugframe::StopBundleEvent *FrameworkFactory::createStopBundleEvent(plugframe::BundleInterface *toStop)
{
    return new plugframe::StopBundleEvent{toStop};
}

ServiceRegistry *FrameworkFactory::createServiceRegistry(plugframe::BundleImplementation *implementation)
{
    return new ServiceRegistry{implementation};
}

SystemService *FrameworkFactory::createSystemService(plugframe::BundleImplementation *implementation)
{
    return new SystemService{implementation};
}

