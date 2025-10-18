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

#include <QHostAddress>
#include <QObject>
#include "pfcore-lib_forward.h"
#include "bundle/bundleimplementation.h"
#include "service-int/frontendclientside.h"
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT TcpClient : public BundleImplementation
{
public:
    TcpClient(QString logBundleName);
    ~TcpClient() override;

public:
    void tcpClientChannelManager(TcpClientChannelManager *clientChannelManager);
    void connectToHost(FrontendClientSide *clientSide,
                       QString serverIpv4,
                       quint16 serverPort);
    void closeConnection();
    void sendMessageToServer(TcpChannelMessage& msg);

public:
    void connectedToServer();
    void disconnectedFromServer();
    void messageFromServer(TcpChannelMessage *msg);

protected:
    ServiceInterface *qtServiceInterface(const QString& sName) override;

private:
    TcpClientChannelManager *m_clientChannelManager;
    TcpClientSlots          *m_clientSlots;
    FrontendClientSide      *m_clientSide;
};
}//namespace plugframe
#endif // TCPCLIENT_H
