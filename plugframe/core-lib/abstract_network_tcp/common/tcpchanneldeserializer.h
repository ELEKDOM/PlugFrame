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

#ifndef TCPCHANNELDESERIALIZER_H
#define TCPCHANNELDESERIALIZER_H

#include <QDataStream>
#include "pfcore-lib_forward.h"
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT TcpChannelDeserializer
{
public:
    TcpChannelDeserializer();
    virtual ~TcpChannelDeserializer();

public:
    virtual TcpChannelMessage *deserialize(QDataStream& input)=0;
    virtual void serialize(TcpChannelMessage& msg, QDataStream& out)=0;
};
} //namespace plugframe
#endif // TCPCHANNELDESERIALIZER_H
