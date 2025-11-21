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

#include "tcpclientfactory.h"
#include "bundle/bundle.h"
#include "abstract_network_tcp/client/tcpclientchannel.h"
#include "abstract_network_tcp/client/tcpclientbuilder.h"
#include "abstract_network_tcp/client/tcpclientchannelmanager.h"
#include "abstract_network_tcp/client/service/tcpclientservice.h"
#include "service-int/frontendcontrolserviceinterface.h"

plugframe::TcpClientFactory::TcpClientFactory() {}

plugframe::TcpClientFactory::~TcpClientFactory()
{

}

plugframe::TcpClientChannelManager *plugframe::TcpClientFactory::createChannelManager(plugframe::TcpChannel *channel,
                                                                                      QObject *parent)
{
    return new plugframe::TcpClientChannelManager{channel,parent};
}

QTcpSocket *plugframe::TcpClientFactory::createSocket()
{
    return new QTcpSocket;
}

plugframe::TcpChannel *plugframe::TcpClientFactory::createChannel(QTcpSocket *socket,
                                                                  plugframe::TcpChannelDeserializer *deserializer,
                                                                  QObject *parent)
{
    return new plugframe::TcpClientChannel{socket,deserializer,parent};
}

plugframe::BundleBuilder *plugframe::TcpClientFactory::createBuilder(plugframe::Bundle &myBundle)
{
    return new plugframe::TcpClientBuilder{myBundle};
}

plugframe::TcpClientService *plugframe::TcpClientFactory::createFrontendControlService(plugframe::BundleImplementation *implementation)
{
    return new plugframe::TcpClientService{implementation};
}

plugframe::ServiceImplementationInterface *plugframe::TcpClientFactory::createServiceImplementation(plugframe::BundleImplementation *implementation,
                                                                                                    const QString &sName,
                                                                                                    const QString &serviceVersion)
{
    plugframe::ServiceImplementationInterface *ret{nullptr};

    if (plugframe::FrontendControlServiceInterface::serviceName() == sName)
    {
        if (plugframe::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createFrontendControlService(implementation);
        }
    }

    return ret;
}
