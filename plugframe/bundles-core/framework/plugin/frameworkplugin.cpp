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

FrameworkPlugin::FrameworkPlugin()
{

}

FrameworkPlugin::~FrameworkPlugin()
{

}

void FrameworkPlugin::init()
{
    // Framework initialization is doing by initFwk !
}

plugframe::Bundle4PluginInterface *FrameworkPlugin::createImplementation()
{
    return new Framework{m_bundlesStore,m_launchingProperties};
}

void FrameworkPlugin::bindServicesImplementations()
{
    plugframe::QspServiceImplementationInterface serviceImplementationItf;

    serviceImplementationItf = implementation()->getServiceImplementation(SystemServiceInterface::serviceName());
    m_systemServiceImpl = serviceImplementationItf.dynamicCast<SystemService>();

    serviceImplementationItf = implementation()->getServiceImplementation(SystemServiceRegistryInterface::serviceName());
    m_serviceRegistryImpl = serviceImplementationItf.dynamicCast<ServiceRegistry>();
}

void FrameworkPlugin::initFwk(plugframe::QspBundlesStore bundlesStore,
                                 plugframe::QspLaunchingProperties launchingProperties)
{
    m_bundlesStore = bundlesStore;
    m_launchingProperties = launchingProperties;
    _init();
}

plugframe::BundleInterface *FrameworkPlugin::getBundleInterface()
{
    return qobject_cast<plugframe::BundleInterface*>(this);
}

QString FrameworkPlugin::applicationName()
{
    return m_systemServiceImpl->applicationName();
}

bool FrameworkPlugin::registerListener(plugframe::BundleListener *observer)
{
    return m_systemServiceImpl->registerListener(observer);
}

bool FrameworkPlugin::unregisterListener(plugframe::BundleListener *observer)
{
    return m_systemServiceImpl->registerListener(observer);
}

plugframe::BundleList FrameworkPlugin::bundleList()
{
    return m_systemServiceImpl->bundleList();
}

int FrameworkPlugin::runningLevel()
{
    return m_systemServiceImpl->runningLevel();
}

void FrameworkPlugin::quit()
{
    m_systemServiceImpl->quit();
}

bool FrameworkPlugin::registerService(const QString &serviceInterfaceName,plugframe::ServiceInterface *service)
{
    return m_serviceRegistryImpl->registerService(serviceInterfaceName, service);
}

plugframe::ServiceInterface *FrameworkPlugin::getService(const QString &serviceInterfaceName)
{
    return m_serviceRegistryImpl->getService(serviceInterfaceName);
}

plugframe::ServiceInterfaceList FrameworkPlugin::getServices(const QString &serviceInterfaceName)
{
    return m_serviceRegistryImpl->getServices(serviceInterfaceName);
}
