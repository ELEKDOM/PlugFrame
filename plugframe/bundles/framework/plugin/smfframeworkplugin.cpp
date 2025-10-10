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


#include "smfframeworkplugin.h"
#include "framework.h"
#include "serviceregistry.h"
#include "systemservice.h"
#include "bundle/bundlecontext.h"
#include "launcher/launchingproperties.h"
#include "launcher/bundlesstore.h"

using namespace elekdom::plugframe::framework::plugin;
using namespace elekdom::plugframe;

SmfFrameworkPlugin::SmfFrameworkPlugin()
{

}

SmfFrameworkPlugin::~SmfFrameworkPlugin()
{

}

void elekdom::plugframe::framework::plugin::SmfFrameworkPlugin::init()
{
    // Framework initialization is doing by initFwk !
}

core::bundle::Bundle4PluginInterface *SmfFrameworkPlugin::createImplementation()
{
    return new framework::bundle::Framework{m_bundlesStore,
                                               m_launchingProperties};
}

void SmfFrameworkPlugin::bindServicesImplementations()
{
    core::service::QspServiceImplementationInterface serviceImplementationItf;

    serviceImplementationItf = implementation()->getServiceImplementation(SystemServiceInterface::serviceName());
    m_systemServiceImpl = serviceImplementationItf.dynamicCast<service::SystemService>();

    serviceImplementationItf = implementation()->getServiceImplementation(SystemServiceRegistryInterface::serviceName());
    m_serviceRegistryImpl = serviceImplementationItf.dynamicCast<service::ServiceRegistry>();
}

void SmfFrameworkPlugin::initFwk(core::launcher::QspBundlesStore bundlesStore,
                                 core::launcher::QspLaunchingProperties launchingProperties)
{
    m_bundlesStore = bundlesStore;
    m_launchingProperties = launchingProperties;
    _init();
}

core::plugin::BundleInterface *SmfFrameworkPlugin::getBundleInterface()
{
    return qobject_cast<core::plugin::BundleInterface*>(this);
}

QString SmfFrameworkPlugin::applicationName()
{
    return m_systemServiceImpl->applicationName();
}

bool SmfFrameworkPlugin::registerListener(elekdom::plugframe::core::bundle::BundleListener *observer)
{
    return m_systemServiceImpl->registerListener(observer);
}

bool SmfFrameworkPlugin::unregisterListener(elekdom::plugframe::core::bundle::BundleListener *observer)
{
    return m_systemServiceImpl->registerListener(observer);
}

core::plugin::BundleList SmfFrameworkPlugin::bundleList()
{
    return m_systemServiceImpl->bundleList();
}

int SmfFrameworkPlugin::runningLevel()
{
    return m_systemServiceImpl->runningLevel();
}

void SmfFrameworkPlugin::quit()
{
    m_systemServiceImpl->quit();
}

bool SmfFrameworkPlugin::registerService(const QString &serviceInterfaceName, elekdom::plugframe::core::plugin::ServiceInterface *service)
{
    return m_serviceRegistryImpl->registerService(serviceInterfaceName, service);
}

elekdom::plugframe::core::plugin::ServiceInterface *SmfFrameworkPlugin::getService(const QString &serviceInterfaceName)
{
    return m_serviceRegistryImpl->getService(serviceInterfaceName);
}

elekdom::plugframe::core::plugin::ServiceInterfaceList SmfFrameworkPlugin::getServices(const QString &serviceInterfaceName)
{
    return m_serviceRegistryImpl->getServices(serviceInterfaceName);
}
