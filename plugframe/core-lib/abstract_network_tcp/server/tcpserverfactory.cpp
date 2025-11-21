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
#include "tcpserverconnmanager.h"
#include "service-int/backendcontrolserviceinterface.h"
#include "abstract_network_tcp/server/service/tcpserverservice.h"
#include "abstract_network_tcp/common/tcpchannel.h"

plugframe::TcpServerFactory::TcpServerFactory() {}

plugframe::TcpServerFactory::~TcpServerFactory()
{

}

plugframe::TcpServerConnManager *plugframe::TcpServerFactory::createTcpServerConnManager(plugframe::TcpServer &myBundle)
{
    return new TcpServerConnManager{myBundle};
}

plugframe::TcpChannel *plugframe::TcpServerFactory::createChannel(QTcpSocket *socket,
                                                                  plugframe::TcpChannelDeserializer *deserializer,
                                                                  QObject *parent)
{
    return new plugframe::TcpChannel{socket,deserializer,parent};
}

plugframe::BundleBuilder *plugframe::TcpServerFactory::createBuilder(plugframe::Bundle &myBundle)
{
    return new plugframe::TcpServerBuilder{myBundle};
}

plugframe::TcpServerService *plugframe::TcpServerFactory::createBackendControlService(plugframe::BundleImplementation *implementation)
{
    return new plugframe::TcpServerService{implementation};
}

plugframe::ServiceImplementationInterface *plugframe::TcpServerFactory::createServiceImplementation(plugframe::BundleImplementation *implementation,
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
