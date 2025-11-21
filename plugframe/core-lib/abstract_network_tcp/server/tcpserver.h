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

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QHostAddress>
#include <QTcpSocket>
#include "bundle/bundleimplementation.h"
#include "pfcore-lib_forward.h"
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT TcpServer : public BundleImplementation
{
public:
    TcpServer(QString logBundleName);
    ~TcpServer() override;

public:
    void tcpServerConnManager(TcpServerConnManager *serverComManager);
    void startListen();
    void stopListen();

public:
    TcpServerChannelManager *newChannelManager(QTcpSocket *newConn);

protected:
    ServiceInterface *qtServiceInterface(const QString& sName) override;

private:
    void readListenAddr(QHostAddress& ipAddr,quint16& port);

private:
    TcpServerConnManager *m_serverComManager;
};
}//namespace plugframe
#endif // TCPSERVER_H
