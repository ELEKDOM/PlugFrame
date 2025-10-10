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


#include "tcpserverconnmanager.h"
#include "tcpserverchannelmanager.h"
#include "tcpserver.h"
#include "tcpserverchannelmanager.h"
#include "abstract_network_tcp/common/tcpchanneldeserializer.h"
#include "abstract_network_tcp/common/tcpchannel.h"

using namespace elekdom::plugframe::core::tcp::server::bundle;

TcpServerConnManager::TcpServerConnManager(TcpServer& bundle,QObject *parent):
    QObject{parent},
    m_bundle{bundle},
    m_tcpServer{new QTcpServer}
{
    connect(m_tcpServer,SIGNAL(newConnection()),SLOT(onNewConnection()));
}

TcpServerConnManager::~TcpServerConnManager()
{
    delete m_tcpServer;
}

bool TcpServerConnManager::open(QHostAddress &ipAddr, quint16 &port)
{
    return m_tcpServer->listen(ipAddr,port);
}

void TcpServerConnManager::close()
{
    closeChannelManagers();
    m_tcpServer->close();
}

void TcpServerConnManager::onNewConnection()
{
    QTcpSocket *newConn{m_tcpServer->nextPendingConnection()};

    if (newConn)
    {
        TcpServerChannelManager *channelManager;

        channelManager = m_bundle.newChannelManager(newConn);
        addChannelManager(channelManager);
    }
}

void TcpServerConnManager::addChannelManager(TcpServerChannelManager *channel)
{
    QspTcpServerChannelManager newChannel{channel};

    m_channelManagers.append(newChannel);
}

void TcpServerConnManager::closeChannelManagers()
{
    for(int i = 0; i < m_channelManagers.size(); i++)
    {
        QspTcpServerChannelManager cur{m_channelManagers.at(i)};

        disconnect(cur.get(),nullptr,nullptr,nullptr);
        cur->close();
    }
}
