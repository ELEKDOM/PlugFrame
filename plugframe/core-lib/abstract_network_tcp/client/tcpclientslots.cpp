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

#include "tcpclientslots.h"
#include "tcpclient.h"
#include "tcpclientchannelmanager.h"

plugframe::TcpClientSlots::TcpClientSlots(plugframe::TcpClient &clientSide,QObject *parent)
    : QObject{parent}
    , m_clientSide{clientSide}
{}

plugframe::TcpClientSlots::~TcpClientSlots()
{

}

void plugframe::TcpClientSlots::connectChannelManager(TcpClientChannelManager *clientChannelManager)
{
    connect(clientChannelManager,SIGNAL(sigConnectedToServer()),SLOT(onConnectedToServer()));
    connect(clientChannelManager,SIGNAL(sigDisconnectedFromServer()),SLOT(onDisconnectedFromServer()));
    connect(clientChannelManager,SIGNAL(sigMessageFromServer(TcpChannelMessage*)),SLOT(onMessageFromServer(TcpChannelMessage*)));
}

void plugframe::TcpClientSlots::onConnectedToServer()
{
    m_clientSide.connectedToServer();
}

void plugframe::TcpClientSlots::onDisconnectedFromServer()
{
    m_clientSide.disconnectedFromServer();
}

void plugframe::TcpClientSlots::onMessageFromServer(plugframe::TcpChannelMessage *input)
{
    m_clientSide.messageFromServer(input);
}
