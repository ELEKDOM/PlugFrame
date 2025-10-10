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

using namespace elekdom::plugframe::core::tcp::server::service;
using namespace elekdom::plugframe::core::tcp::server::bundle;

TcpServerService::TcpServerService(plugframe::core::bundle::BundleImplementation *implementation):
    plugframe::core::service::ServiceImplementation{implementation}
{}

TcpServerService::~TcpServerService()
{

}

void TcpServerService::startListen()
{
    TcpServer *bundle{dynamic_cast<TcpServer*>(implementation())};

    bundle->startListen();
}

void TcpServerService::stopListen()
{
    TcpServer *bundle{dynamic_cast<TcpServer*>(implementation())};

    bundle->stopListen();
}

QString TcpServerService::serviceName()
{
    return frontenditf::service::BackendControlServiceInterface::serviceName();
}
