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


#include <QSettings>
#include "tcpclient.h"
#include "tcpclientslots.h"
#include "tcpclientchannelmanager.h"
#include "service-int/frontendcontrolserviceinterface.h"
#include "logger/pflog.h"

using namespace elekdom::plugframe::core::tcp::client::bundle;

TcpClient::TcpClient(QString logBundleName):
    core::bundle::BundleImplementation{logBundleName},
    m_clientChannelManager{nullptr},
    m_clientSlots{new TcpClientSlots(*this)},
    m_clientSide{nullptr}
{}

TcpClient::~TcpClient()
{
    delete m_clientChannelManager;
    delete m_clientSlots;
}

void TcpClient::tcpClientChannelManager(TcpClientChannelManager *clientChannelManager)
{
    m_clientChannelManager = clientChannelManager;

    // For feedback from the manager
    m_clientSlots->connectChannelManager(clientChannelManager);
}

void TcpClient::connectToHost(frontend::FrontendClientSide *clientSide,
                              QString serverIpv4,
                              quint16 serverPort)
{
    m_clientSide = clientSide;

    if (m_clientChannelManager)
    {
        QHostAddress ipAddr(serverIpv4);
        m_clientChannelManager->connectToServer(ipAddr,serverPort);
    }
}

void TcpClient::closeConnection()
{
    m_clientChannelManager->close();
}

void TcpClient::sendMessageToServer(TcpChannelMessage &msg)
{
    m_clientChannelManager->sendMessage(msg);
}

void TcpClient::connectedToServer()
{
    m_clientSide->connectedToServer();
}

void TcpClient::disconnectedFromServer()
{
    m_clientSide->disconnectedFromServer();
}

void TcpClient::messageFromServer(TcpChannelMessage *msg)
{
    m_clientSide->messageFromServer(msg);
}

elekdom::plugframe::core::plugin::ServiceInterface *TcpClient::qtServiceInterface(const QString &sName)
{
    plugframe::core::plugin::ServiceInterface *ret{nullptr};

    if (frontend::service::FrontendControlServiceInterface::serviceName()== sName)
    {
        ret = qobject_cast<frontend::service::FrontendControlServiceInterface*>(getQplugin());
    }

    return ret;
}
