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


#ifndef TCPCLIENTCHANNEL_H
#define TCPCLIENTCHANNEL_H

#include "abstract_network_tcp/common/tcpchannel.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace tcp
{
namespace client
{
namespace bundle
{

class TcpClientChannel : public TcpChannel
{
public:
    TcpClientChannel(QTcpSocket *socket,TcpChannelDeserializer *deserializer,QObject *parent = nullptr);
    ~TcpClientChannel() override;
};

}//namespace bundle
}//namespace client
}//namespace tcp
}//namespace core
}//namespace plugframe
}//namespace elekdom
#endif // TCPCLIENTCHANNEL_H
