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

#include "tcpclientplugin.h"
#include "bundle/bundle4plugininterface.h"
#include "tcpclient.h"

TcpClientPlugin::TcpClientPlugin() {}

TcpClientPlugin::~TcpClientPlugin()
{

}

void TcpClientPlugin::bindServicesImplementations()
{
    plugframe::QspServiceImplementationInterface serviceImplementationItf;

    serviceImplementationItf = implementation()->getServiceImplementation(plugframe::FrontendControlServiceInterface::serviceName());
    m_clientServiceImpl = serviceImplementationItf.dynamicCast<TcpClientService>();

    serviceImplementationItf = implementation()->getServiceImplementation(plugframe::FrontendMessagesCodecRegisterServiceInterface::serviceName());
    m_messagesCodecRegisterImpl = serviceImplementationItf.dynamicCast<TcpMessagesCodecRegisterService>();
}

void TcpClientPlugin::connectToHost(plugframe::ClientConnectionStateNotifier *clientSide)
{
    m_clientServiceImpl->connectToHost(clientSide);
}

void TcpClientPlugin::closeConnection()
{
    m_clientServiceImpl->closeConnection();
}

void TcpClientPlugin::registerMessagesCodec(plugframe::MessagesCodec *codec)
{
    m_messagesCodecRegisterImpl->registerMessagesCodec(codec);
}

plugframe::Bundle4PluginInterface *TcpClientPlugin::createImplementation()
{
    return new TcpClient;
}
