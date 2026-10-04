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
#include "network/tcp/tcpchannelmanager.h"

class TcpClientChannelManager : public plugframe::TcpChannelManager
{
    Q_OBJECT

public:
    explicit TcpClientChannelManager(QTcpSocket *socket,const QString& logChannel,QObject *parent = nullptr);
    ~TcpClientChannelManager() override;

public:
    void connectToServer(QHostAddress& ipAddr,quint16& port);

private slots:
    void tryServerConnection();
    void onConnectedToServer();
    void onDisconnectedFromServer();

private:
    QTimer       m_connectionTimer;
    QHostAddress m_serverIp;
    quint16      m_serverPort;
    bool         m_connectedToHost;
    QTcpSocket  *m_socket;
};
using QspTcpClientChannelManager = QSharedPointer<TcpClientChannelManager>;
#endif // TCPCLIENTCHANNELMANAGER_H
