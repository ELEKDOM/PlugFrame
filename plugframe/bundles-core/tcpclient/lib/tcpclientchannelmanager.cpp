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
#include "tcpclientchannelmanager.h"

TcpClientChannelManager::TcpClientChannelManager(QTcpSocket *socket, const QString &logChannel, QObject *parent):
    plugframe::TcpChannelManager{socket,logChannel,parent},
    m_connectedToHost{false},
    m_socket{socket}
{

}

TcpClientChannelManager::~TcpClientChannelManager()
{

}

void TcpClientChannelManager::connectToServer(QHostAddress &ipAddr, quint16 &port)
{
    if (!m_connectedToHost)
    {
        m_serverIp = ipAddr;
        m_serverPort = port;

        connect(m_socket,SIGNAL(connected()),SLOT(onConnectedToServer()));
        connect(&m_connectionTimer,SIGNAL(timeout()),SLOT(tryServerConnection()));
        m_connectionTimer.start(2000);//Connection attempt every 2 seconds
    }
}

void TcpClientChannelManager::onConnectedToServer()
{
    m_connectionTimer.stop();
    m_socket->disconnect(SIGNAL(connected()));//Ok, connected to the server
    m_connectedToHost = true;
    connect(m_socket,SIGNAL(disconnected()),SLOT(onDisconnectedFromServer()));
    emit sigConnected();
}

void TcpClientChannelManager::onDisconnectedFromServer()
{
    m_socket->disconnect(SIGNAL(disconnected()));
    m_connectedToHost = false;
    emit sigDisconnected();
}

void TcpClientChannelManager::tryServerConnection()
{
    m_socket->connectToHost(m_serverIp,m_serverPort);
}


