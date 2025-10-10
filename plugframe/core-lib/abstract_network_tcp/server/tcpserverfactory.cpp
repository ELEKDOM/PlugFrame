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

using namespace elekdom::plugframe::core::tcp::server::factory;
using namespace elekdom::plugframe::core::tcp::server::service;
using namespace elekdom::plugframe::core::tcp::server::bundle;
using namespace elekdom::plugframe::core;

TcpServerFactory::TcpServerFactory() {}

TcpServerFactory::~TcpServerFactory()
{

}

TcpServerConnManager *TcpServerFactory::createTcpServerConnManager(bundle::TcpServer &myBundle)
{
    return new TcpServerConnManager{myBundle};
}

tcp::TcpChannel *TcpServerFactory::createChannel(QTcpSocket *socket,
                                                 TcpChannelDeserializer *deserializer,
                                                 QObject *parent)
{
    return new tcp::TcpChannel{socket,deserializer,parent};
}

bundle::BundleBuilder *TcpServerFactory::createBuilder(plugframe::core::bundle::Bundle &myBundle)
{
    return new builder::TcpServerBuilder{myBundle};
}

TcpServerService *TcpServerFactory::createBackendControlService(plugframe::core::bundle::BundleImplementation *implementation)
{
    return new TcpServerService{implementation};
}

service::ServiceImplementationInterface *TcpServerFactory::createServiceImplementation(plugframe::core::bundle::BundleImplementation *implementation, const QString &sName, const QString &serviceVersion)
{
    plugframe::core::service::ServiceImplementationInterface *ret{nullptr};

    if (frontenditf::service::BackendControlServiceInterface::serviceName() == sName)
    {
        if (plugin::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createBackendControlService(implementation);
        }
    }

    return ret;
}
