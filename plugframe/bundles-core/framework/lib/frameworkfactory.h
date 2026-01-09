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

#ifndef FRAMEWORK_FACTORY_H
#define FRAMEWORK_FACTORY_H

#include "factory/bundlefactory.h"
#include "event/frameworkevent/bundlesstartingevent.h"
#include "event/frameworkevent/bundlesstoppingevent.h"
#include "event/frameworkevent/startbundleevent.h"
#include "event/frameworkevent/stopbundleevent.h"
#include "event/frameworkevent/frameworkstartedevent.h"
#include "service-int/systemserviceregistryinterface.h"
#include "framework_forward.h"

class FrameworkFactory : public plugframe::BundleFactory
{
public:
    FrameworkFactory();
    ~FrameworkFactory() override;

public:
    virtual plugframe::BundleContext *createBundleContext(plugframe::SystemServiceRegistryInterface *registryService);
    virtual plugframe::BundlesStartingEvent *createBundlesStartingEvent(plugframe::BundleList& bundlesToStart,
                                                                        int fwkLevel,
                                                                        int level);
    virtual plugframe::StartBundleEvent *createStartBundleEvent(plugframe::BundleInterface *toStart);
    virtual plugframe::FrameworkStartedEvent *createFrameworkStartedEvent();
    virtual plugframe::BundlesStoppingEvent *createBundlesStoppingEvent(plugframe::BundleList& bundlesToStop, int level);
    virtual plugframe::StopBundleEvent *createStopBundleEvent(plugframe::BundleInterface *toStop);

protected:
    plugframe::BundleEmitter *createBundleEmitter(plugframe::Bundle& myBundle) override;
    plugframe::BundleListener *createBundleListener(plugframe::Bundle& myBundle) override;
    virtual ServiceRegistry *createServiceRegistry(plugframe::BundleImplementation *implementation);
    virtual SystemService *createSystemService(plugframe::BundleImplementation *implementation);
    plugframe::ServiceImplementationInterface *createServiceImplementation(plugframe::BundleImplementation *implementation,
                                                                           const QString& sName,
                                                                           const QString& serviceVersion) override;
};
#endif // FRAMEWORK_FACTORY_H
