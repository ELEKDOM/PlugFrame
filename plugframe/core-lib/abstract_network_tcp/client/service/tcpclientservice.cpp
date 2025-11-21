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

#include "tcpclientservice.h"
#include "abstract_network_tcp/client/tcpclient.h"
#include "service-int/frontendcontrolserviceinterface.h"

plugframe::TcpClientService::TcpClientService(plugframe::BundleImplementation *implementation):
    plugframe::ServiceImplementation{implementation}
{

}

plugframe::TcpClientService::~TcpClientService()
{

}

void plugframe::TcpClientService::connectToHost(plugframe::FrontendClientSide *clientSide,
                                                QString serverIpv4,
                                                quint16 serverPort)
{
    plugframe::TcpClient *bundle{dynamic_cast<plugframe::TcpClient*>(implementation())};

    bundle->connectToHost(clientSide,serverIpv4,serverPort);
}

void plugframe::TcpClientService::closeConnection()
{
    plugframe::TcpClient *bundle{dynamic_cast<plugframe::TcpClient*>(implementation())};

    bundle->closeConnection();
}

void plugframe::TcpClientService::sendMessageToServer(plugframe::TcpChannelMessage &msg)
{
    plugframe::TcpClient *bundle{dynamic_cast<plugframe::TcpClient*>(implementation())};

    bundle->sendMessageToServer(msg);
}

QString plugframe::TcpClientService::serviceName()
{
    return plugframe::FrontendControlServiceInterface::serviceName();
}
