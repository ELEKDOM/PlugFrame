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

#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QHostAddress>
#include "pfcore-lib_forward.h"
#include "bundle/bundleimplementation.h"
#include "network/frontend/clientconnectionstatenotifier.h"
#include "tcpclientchannelmanager.h"

class TcpClient : public plugframe::BundleImplementation
{
public:
    TcpClient();
    ~TcpClient() override;

public:
    void tcpClientChannelManager(TcpClientChannelManager *clientChannelManager);
    void registerMessagesCodec(plugframe::MessagesCodec *codec);
    void connectToHost(plugframe::ClientConnectionStateNotifier *clientSide);
    void closeConnection();

protected:
    plugframe::BundleFactory* createFactory() override;
    plugframe::ServiceInterface *qtServiceInterface(const QString& sName) override;

private:
    void readServerAddr(QHostAddress &ipAddr, quint16 &port);

private:
    QspTcpClientChannelManager m_clientChannelManager;
};
#endif // TCPCLIENT_H
