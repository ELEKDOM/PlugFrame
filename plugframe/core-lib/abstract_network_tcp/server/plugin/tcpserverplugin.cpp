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

#include "tcpserverplugin.h"
#include "bundle/bundle4plugininterface.h"
#include "abstract_network_tcp/server/service/tcpserverservice.h"

plugframe::TcpServerPlugin::TcpServerPlugin() {}

plugframe::TcpServerPlugin::~TcpServerPlugin()
{

}

void plugframe::TcpServerPlugin::bindServicesImplementations()
{
    plugframe::QspServiceImplementationInterface serviceImplementationItf;

    serviceImplementationItf = implementation()->getServiceImplementation(plugframe::BackendControlServiceInterface::serviceName());
    m_serverServiceImpl = serviceImplementationItf.dynamicCast<plugframe::TcpServerService>();
}

void plugframe::TcpServerPlugin::startListen()
{
    m_serverServiceImpl->startListen();
}

void plugframe::TcpServerPlugin::stopListen()
{
    m_serverServiceImpl->stopListen();
}
