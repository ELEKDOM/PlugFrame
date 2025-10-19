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

#include "serviceregistry.h"
#include "service-int/systemserviceregistryinterface.h"

ServiceRegistry::ServiceRegistry(plugframe::BundleImplementation *implementation):
    FrameworkServiceImplementation{implementation}
{

}

ServiceRegistry::~ServiceRegistry()
{

}

bool ServiceRegistry::registerService(const QString &serviceInterfaceName,plugframe::ServiceInterface *service)
{
    QMutexLocker    mtxLck{&m_mtx};
    bool            ret{false};

    if (false == m_registry.contains(serviceInterfaceName))
    {
        m_registry.insert(serviceInterfaceName, service);
        ret = true;
    }

    return ret;
}

plugframe::ServiceInterface *ServiceRegistry::getService(const QString &serviceInterfaceName)
{
    QMutexLocker mtxLck{&m_mtx};
    plugframe::ServiceInterface *ret{m_registry.value(serviceInterfaceName)};

    return ret;
}

plugframe::ServiceInterfaceList ServiceRegistry::getServices(const QString &serviceInterfaceName)
{
    QMutexLocker mtxLck{&m_mtx};
    plugframe::ServiceInterfaceList ret;

    if (m_registry.contains(serviceInterfaceName))
    {
        ret = m_registry.values(serviceInterfaceName);
    }
    return ret;
}

QString ServiceRegistry::serviceName()
{
    return plugframe::SystemServiceRegistryInterface::serviceName();
}
