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


#include "tcpchannelmanager.h"
#include "tcpchannel.h"
#include "tcpchannelmessage.h"

using namespace elekdom::plugframe::core::tcp;

TcpChannelManager::TcpChannelManager(TcpChannel *channel,QObject *parent):
    QObject{parent},
    m_channel{channel}
{
    connect(m_channel,SIGNAL(newMessage(TcpChannelMessage*)),SLOT(onNewMessage(TcpChannelMessage*)));
}

TcpChannelManager::~TcpChannelManager()
{
    delete m_channel;
}

void TcpChannelManager::sendMessage(TcpChannelMessage &output)
{
    m_channel->sendMessage(output);
}

void TcpChannelManager::close()
{
    m_channel->close();
}

void TcpChannelManager::onNewMessage(TcpChannelMessage *input)
{
    processMessage(input);
    delete input;
}
