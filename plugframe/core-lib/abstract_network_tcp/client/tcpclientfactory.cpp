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

using namespace elekdom::plugframe::core::bundle;
using namespace elekdom::plugframe::core::service;
using namespace elekdom::plugframe::core::tcp;
using namespace elekdom::plugframe::core::tcp::client::factory;
using namespace elekdom::plugframe::core::tcp::client::service;
using namespace elekdom::plugframe::core::tcp::client::builder;

TcpClientFactory::TcpClientFactory() {}

TcpClientFactory::~TcpClientFactory()
{

}

client::bundle::TcpClientChannelManager *TcpClientFactory::createChannelManager(TcpChannel *channel, QObject *parent)
{
    return new bundle::TcpClientChannelManager{channel,parent};
}

QTcpSocket *TcpClientFactory::createSocket()
{
    return new QTcpSocket;
}

TcpChannel *TcpClientFactory::createChannel(QTcpSocket *socket,
                                            TcpChannelDeserializer *deserializer,
                                            QObject *parent)
{
    return new client::bundle::TcpClientChannel{socket,deserializer,parent};
}

BundleBuilder *TcpClientFactory::createBuilder(core::bundle::Bundle &myBundle)
{
    return new TcpClientBuilder{myBundle};
}

TcpClientService *TcpClientFactory::createFrontendControlService(core::bundle::BundleImplementation *implementation)
{
    return new TcpClientService{implementation};
}

ServiceImplementationInterface *TcpClientFactory::createServiceImplementation(core::bundle::BundleImplementation *implementation,
                                                                              const QString &sName,
                                                                              const QString &serviceVersion)
{
    plugframe::core::service::ServiceImplementationInterface *ret{nullptr};

    if (frontend::service::FrontendControlServiceInterface::serviceName() == sName)
    {
        if (plugin::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createFrontendControlService(implementation);
        }
    }

    return ret;
}
