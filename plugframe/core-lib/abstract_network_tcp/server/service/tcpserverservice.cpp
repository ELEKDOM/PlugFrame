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

#include "tcpserverservice.h"
#include "abstract_network_tcp/server/tcpserver.h"
#include "service-int/backendcontrolserviceinterface.h"

plugframe::TcpServerService::TcpServerService(plugframe::BundleImplementation *implementation):
    plugframe::ServiceImplementation{implementation}
{}

plugframe::TcpServerService::~TcpServerService()
{

}

void plugframe::TcpServerService::startListen()
{
    plugframe::TcpServer *bundle{dynamic_cast<plugframe::TcpServer*>(implementation())};

    bundle->startListen();
}

void plugframe::TcpServerService::stopListen()
{
    plugframe::TcpServer *bundle{dynamic_cast<plugframe::TcpServer*>(implementation())};

    bundle->stopListen();
}

QString plugframe::TcpServerService::serviceName()
{
    return plugframe::BackendControlServiceInterface::serviceName();
}
