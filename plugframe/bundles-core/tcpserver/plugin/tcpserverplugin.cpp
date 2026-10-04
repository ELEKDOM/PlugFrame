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
#include "tcpserver.h"

TcpServerPlugin::TcpServerPlugin()
{
}

TcpServerPlugin::~TcpServerPlugin()
{
}

void TcpServerPlugin::bindServicesImplementations()
{
    plugframe::QspServiceImplementationInterface serviceImplementationItf;

    serviceImplementationItf = implementation()->getServiceImplementation(plugframe::BackendControlServiceInterface::serviceName());
    m_serverServiceImpl = serviceImplementationItf.dynamicCast<TcpServerService>();
}

plugframe::Bundle4PluginInterface *TcpServerPlugin::createImplementation()
{
    return new TcpServer;
}

void TcpServerPlugin::startListen(plugframe::ServerConnectionsNotifier *serverSide)
{
    m_serverServiceImpl->startListen(serverSide);
}

void TcpServerPlugin::stopListen()
{
    m_serverServiceImpl->stopListen();
}
