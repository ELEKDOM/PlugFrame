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
#include "bundle/bundle.h"
#include "bundle/bundleimplementation.h"
#include "tcpserverfactory.h"
#include "tcpserverbuilder.h"
#include "tcpserverservice.h"
#include "tcpserverconnmanager.h"
#include "service-int/backendcontrolserviceinterface.h"

TcpServerFactory::TcpServerFactory() {}

TcpServerFactory::~TcpServerFactory()
{
}

TcpServerConnManager *TcpServerFactory::createTcpServerConnManager()
{
    return new TcpServerConnManager;
}

plugframe::BundleBuilder *TcpServerFactory::createBuilder(plugframe::Bundle &myBundle)
{
    return new TcpServerBuilder{myBundle};
}

TcpServerService *TcpServerFactory::createBackendControlService(plugframe::BundleImplementation *implementation)
{
    return new TcpServerService{implementation};
}

plugframe::ServiceImplementationInterface *TcpServerFactory::createServiceImplementation(plugframe::BundleImplementation *implementation,
                                                                                         const QString &sName,
                                                                                         const QString &serviceVersion)
{
    plugframe::ServiceImplementationInterface *ret{nullptr};

    if (plugframe::BackendControlServiceInterface::serviceName() == sName)
    {
        if (plugframe::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createBackendControlService(implementation);
        }
    }

    return ret;
}
