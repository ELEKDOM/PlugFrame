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
#include "service-int/systemserviceregistryinterface.h"
#include "pfcore-lib_forward.h"
#include "framework_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace framework
{
namespace factory
{

class FrameworkFactory : public core::bundle::BundleFactory
{
public:
    FrameworkFactory();
    ~FrameworkFactory() override;

public:
    virtual core::bundle::BundleContext *createBundleContext(service::SystemServiceRegistryInterface *registryService);
    virtual core::event::BundlesStartingEvent *createBundlesStartingEvent(core::plugin::BundleList& bundlesToStart, int fwkLevel, int level);
    virtual core::event::StartBundleEvent *createStartBundleEvent(core::plugin::BundleInterface *toStart);
    virtual core::event::FrameworkStartedEvent *createFrameworkStartedEvent();
    virtual core::event::BundlesStoppingEvent *createBundlesStoppingEvent(core::plugin::BundleList& bundlesToStop, int level);
    virtual core::event::StopBundleEvent *createStopBundleEvent(core::plugin::BundleInterface *toStop);

protected:
    core::bundle::BundleEmitter *createBundleEmitter(core::bundle::Bundle& myBundle) override;
    core::bundle::BundleListener *createBundleListener(core::bundle::Bundle& myBundle) override;
    virtual service::ServiceRegistry *createServiceRegistry(core::bundle::BundleImplementation *implementation);
    virtual service::SystemService *createSystemService(core::bundle::BundleImplementation *implementation);
    core::service::ServiceImplementationInterface *createServiceImplementation(core::bundle::BundleImplementation *implementation,
                                                                               const QString& sName,
                                                                               const QString& serviceVersion) override;

};

} //namespace factory
} //namespace framework
} //namespace plugframe
} //namespace elekdom

#endif // FRAMEWORK_FACTORY_H
