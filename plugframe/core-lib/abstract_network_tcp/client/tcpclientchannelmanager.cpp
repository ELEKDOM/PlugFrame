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

#include "abstract_network_tcp/common/tcpchannel.h"
#include "tcpclientchannelmanager.h"

plugframe::TcpClientChannelManager::TcpClientChannelManager(plugframe::TcpChannel *channel, QObject *parent):
    plugframe::TcpChannelManager{channel,parent},
    m_connectedToHost{false}
{

}

plugframe::TcpClientChannelManager::~TcpClientChannelManager()
{

}

void plugframe::TcpClientChannelManager::connectToServer(QHostAddress &ipAddr, quint16 &port)
{
    if (!m_connectedToHost)
    {
        m_serverIp = ipAddr;
        m_serverPort = port;

        connect(channel()->socket(),SIGNAL(connected()),SLOT(onConnectedToServer()));
        connect(&m_connectionTimer,SIGNAL(timeout()),SLOT(tryServerConnection()));
        m_connectionTimer.start(2000);//Connection attempt every 2 seconds
    }
}

void plugframe::TcpClientChannelManager::processMessage(plugframe::TcpChannelMessage *input)
{
    emit sigMessageFromServer(input);
}

void plugframe::TcpClientChannelManager::onConnectedToServer()
{
    m_connectionTimer.stop();
    channel()->socket()->disconnect(SIGNAL(connected()));//Ok, connected to the server
    m_connectedToHost = true;
    connect(channel()->socket(),SIGNAL(disconnected()),SLOT(onDisconnectedFromServer()));
    emit sigConnectedToServer();
}

void plugframe::TcpClientChannelManager::onDisconnectedFromServer()
{
    channel()->socket()->disconnect(SIGNAL(disconnected()));
    m_connectedToHost = false;
    emit sigDisconnectedFromServer();
}

void plugframe::TcpClientChannelManager::tryServerConnection()
{
    channel()->socket()->connectToHost(m_serverIp,m_serverPort);
}
