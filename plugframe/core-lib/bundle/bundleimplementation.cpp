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


#include "bundleimplementation.h"
#include "bundle/bundlecontext.h"
#include "service-int/serviceinterface.h"
#include "logger/pflog.h"

using namespace elekdom::plugframe::core::bundle;
using namespace elekdom::plugframe::core;

BundleImplementation::BundleImplementation(QString logBundleName):
    Bundle{logBundleName}
{

}

BundleImplementation::~BundleImplementation()
{

}

BundleImplementation *BundleImplementation::getImplementation()
{
    return this;
}

service::QspServiceImplementationInterface BundleImplementation::getServiceImplementation(const QString& serviceName)
{
    return m_exportedServices.value(serviceName);
}

void BundleImplementation::addExportedService(service::QspServiceImplementationInterface newService)
{
    m_exportedServices.insert(newService->serviceName(), newService);
}

service::QspServiceImplementationInterface BundleImplementation::getService(const QString &serviceName)
{
    return m_exportedServices.value(serviceName);
}

///
/// \brief BundleImplementation::registerExportedServices
/// \details
/// This method declares all services to the framework.
/// It's the plugin which implements the service(s) interface(s) to register.
/// Apply qobject_cast to plugin to get a service interface (see qtServiceInterface impl).
///
void BundleImplementation::registerExportedServices()
{
    service::ServiceImplementationInterfaceHashConstIt i = m_exportedServices.constBegin();

    while (i != m_exportedServices.constEnd())
    {
        QString serviceName{i.key()};
        plugin::ServiceInterface *qservice{qtServiceInterface(serviceName)};
        if (qservice)
        {
            registerService(serviceName,qservice);
        }
        else
        {
            pfErr(getLogBundleName()) << QObject::tr("service %1 interface Qt Null !").arg(serviceName);
        }
        ++i;
    }
}

void BundleImplementation::_start(QspBundleContext bundleContext)
{
    m_bundleContext = bundleContext;
    registerExportedServices();
}

void BundleImplementation::_stop()
{

}

bool BundleImplementation::registerService(const QString &serviceInterfaceName,
                                           plugin::ServiceInterface *service)
{
    bool ret{bundleContext()->registerService(serviceInterfaceName,service)};
    return ret;
}
