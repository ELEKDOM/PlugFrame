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

#ifndef TCPCLIENTCHANNELMANAGER_H
#define TCPCLIENTCHANNELMANAGER_H

#include <QHostAddress>
#include <QTimer>
#include "abstract_network_tcp/common/tcpchannelmanager.h"
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT TcpClientChannelManager : public TcpChannelManager
{
    Q_OBJECT

public:
    explicit TcpClientChannelManager(TcpChannel *channel,QObject *parent = nullptr);
    ~TcpClientChannelManager() override;

public:
    void connectToServer(QHostAddress& ipAddr,quint16& port);

protected:
    void processMessage(TcpChannelMessage *input) override;

signals:
    void sigConnectedToServer();
    void sigDisconnectedFromServer();
    void sigMessageFromServer(TcpChannelMessage *input);

private slots:
    void tryServerConnection();
    void onConnectedToServer();
    void onDisconnectedFromServer();

private:
    QTimer       m_connectionTimer;
    QHostAddress m_serverIp;
    quint16      m_serverPort;
    bool         m_connectedToHost;
};
}//namespace plugframe
#endif // TCPCLIENTCHANNELMANAGER_H
