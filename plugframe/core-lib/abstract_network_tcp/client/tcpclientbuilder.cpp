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

#include "tcpclientbuilder.h"
#include "tcpclient.h"
#include "tcpclientfactory.h"
#include "tcpclientchannelmanager.h"
#include "abstract_network_tcp/common/tcpchanneldeserializer.h"
#include "abstract_network_tcp/common/tcpchannel.h"

plugframe::TcpClientBuilder::TcpClientBuilder(plugframe::Bundle4BuilderInterface &myBundle):
    plugframe::BundleBuilder{myBundle}
{

}

plugframe::TcpClientBuilder::~TcpClientBuilder()
{

}

void plugframe::TcpClientBuilder::specificBuild()
{
    plugframe::TcpClient& tcpBundle{dynamic_cast<plugframe::TcpClient&>(getBundle())};
    plugframe::TcpClientFactory& tcpClientFactory{dynamic_cast<plugframe::TcpClientFactory&>(tcpBundle.getFactory())};
    plugframe::TcpChannelDeserializer *deserializer{tcpClientFactory.createDeserializer()};
    plugframe::TcpChannel *channel{tcpClientFactory.createChannel(tcpClientFactory.createSocket(),deserializer)};
    plugframe::TcpClientChannelManager *channelManager{tcpClientFactory.createChannelManager(channel)};

    tcpBundle.tcpClientChannelManager(channelManager);
}
