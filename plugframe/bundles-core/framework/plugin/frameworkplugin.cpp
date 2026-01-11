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

#include "frameworkplugin.h"
#include "framework.h"
#include "launcher/launchingproperties.h"
#include "launcher/bundlesstore.h"

SmfFrameworkPlugin::SmfFrameworkPlugin()
{

}

SmfFrameworkPlugin::~SmfFrameworkPlugin()
{

}

void SmfFrameworkPlugin::init()
{
    // Framework initialization is doing by initFwk !
}

plugframe::Bundle4PluginInterface *SmfFrameworkPlugin::createImplementation()
{
    return new Framework{m_bundlesStore,m_launchingProperties};
}

void SmfFrameworkPlugin::bindServicesImplementations()
{
    plugframe::QspServiceImplementationInterface serviceImplementationItf;

    serviceImplementationItf = implementation()->getServiceImplementation(SystemServiceInterface::serviceName());
    m_systemServiceImpl = serviceImplementationItf.dynamicCast<SystemService>();

    serviceImplementationItf = implementation()->getServiceImplementation(SystemServiceRegistryInterface::serviceName());
    m_serviceRegistryImpl = serviceImplementationItf.dynamicCast<ServiceRegistry>();
}

void SmfFrameworkPlugin::initFwk(plugframe::QspBundlesStore bundlesStore,
                                 plugframe::QspLaunchingProperties launchingProperties)
{
    m_bundlesStore = bundlesStore;
    m_launchingProperties = launchingProperties;
    _init();
}

plugframe::BundleInterface *SmfFrameworkPlugin::getBundleInterface()
{
    return qobject_cast<plugframe::BundleInterface*>(this);
}

QString SmfFrameworkPlugin::applicationName()
{
    return m_systemServiceImpl->applicationName();
}

bool SmfFrameworkPlugin::registerListener(plugframe::BundleListener *observer)
{
    return m_systemServiceImpl->registerListener(observer);
}

bool SmfFrameworkPlugin::unregisterListener(plugframe::BundleListener *observer)
{
    return m_systemServiceImpl->registerListener(observer);
}

plugframe::BundleList SmfFrameworkPlugin::bundleList()
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

bool SmfFrameworkPlugin::registerService(const QString &serviceInterfaceName,plugframe::ServiceInterface *service)
{
    return m_serviceRegistryImpl->registerService(serviceInterfaceName, service);
}

plugframe::ServiceInterface *SmfFrameworkPlugin::getService(const QString &serviceInterfaceName)
{
    return m_serviceRegistryImpl->getService(serviceInterfaceName);
}

plugframe::ServiceInterfaceList SmfFrameworkPlugin::getServices(const QString &serviceInterfaceName)
{
    return m_serviceRegistryImpl->getServices(serviceInterfaceName);
}
