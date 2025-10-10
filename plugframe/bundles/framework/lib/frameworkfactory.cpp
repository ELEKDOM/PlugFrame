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

using namespace elekdom::plugframe::framework;
using namespace elekdom::plugframe;

factory::FrameworkFactory::FrameworkFactory()
{
}

factory::FrameworkFactory::~FrameworkFactory()
{

}

core::bundle::BundleEmitter *factory::FrameworkFactory::createBundleEmitter(core::bundle::Bundle &myBundle)
{
    return new bundle::FrameworkStarter{myBundle};
}

core::bundle::BundleListener *factory::FrameworkFactory::createBundleListener(core::bundle::Bundle &myBundle)
{
   return new bundle::FrameworkStarterListener{myBundle};
}

core::service::ServiceImplementationInterface *factory::FrameworkFactory::createServiceImplementation(core::bundle::BundleImplementation *implementation,
                                                                                                      const QString &sName,
                                                                                                      const QString &serviceVersion)
{
    core::service::ServiceImplementationInterface *ret{nullptr};

    if (service::SystemServiceRegistryInterface::serviceName() == sName)
    {
        if (plugframe::core::plugin::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createServiceRegistry(implementation);
        }
    }
    else if (service::SystemServiceInterface::serviceName() == sName)
    {
        if (plugframe::core::plugin::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createSystemService(implementation);
        }
    }

    return ret;
}

core::bundle::BundleContext *factory::FrameworkFactory::createBundleContext(service::SystemServiceRegistryInterface *registryService)
{
    return new core::bundle::BundleContext{registryService};
}

core::event::BundlesStartingEvent *factory::FrameworkFactory::createBundlesStartingEvent(core::plugin::BundleList& bundlesToStart, int fwkLevel, int level)
{
    return  new core::event::BundlesStartingEvent{bundlesToStart, fwkLevel, level};
}

core::event::StartBundleEvent *factory::FrameworkFactory::createStartBundleEvent(core::plugin::BundleInterface *toStart)
{
    return new core::event::StartBundleEvent{toStart};
}

core::event::FrameworkStartedEvent *factory::FrameworkFactory::createFrameworkStartedEvent()
{
    return new core::event::FrameworkStartedEvent{};
}

core::event::BundlesStoppingEvent *factory::FrameworkFactory::createBundlesStoppingEvent(core::plugin::BundleList &bundlesToStop, int level)
{
    return  new core::event::BundlesStoppingEvent{bundlesToStop, level};
}

core::event::StopBundleEvent *factory::FrameworkFactory::createStopBundleEvent(core::plugin::BundleInterface *toStop)
{
    return new core::event::StopBundleEvent{toStop};
}

framework::service::ServiceRegistry *factory::FrameworkFactory::createServiceRegistry(core::bundle::BundleImplementation *implementation)
{
    return new framework::service::ServiceRegistry{implementation};
}

framework::service::SystemService *factory::FrameworkFactory::createSystemService(core::bundle::BundleImplementation *implementation)
{
    return new framework::service::SystemService{implementation};
}

