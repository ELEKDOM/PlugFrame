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

#ifndef TCPSERVERCHANNELMANAGER_H
#define TCPSERVERCHANNELMANAGER_H

#include <QSharedPointer>
#include "abstract_network_tcp/common/tcpchannelmanager.h"
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT TcpServerChannelManager : public TcpChannelManager
{
    Q_OBJECT

public:
    explicit TcpServerChannelManager(TcpServer& bundle,TcpChannel *channel,QObject *parent = nullptr);
    ~TcpServerChannelManager() override;

public slots:
    virtual void onDisconnectedFromClient() = 0;

protected:
    TcpServer& bundle() {return m_bundle;}

private:
    TcpServer& m_bundle;
};
using QspTcpServerChannelManager = QSharedPointer<TcpServerChannelManager>;
}//namespace plugframe
#endif // TCPSERVERCHANNELMANAGER_H
