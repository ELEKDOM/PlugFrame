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


#ifndef TCPSERVERCONNMANAGER_H
#define TCPSERVERCONNMANAGER_H

#include <QObject>
#include <QHostAddress>
#include <QTcpServer>
#include <QList>
#include "pfcore-lib_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace tcp
{
namespace server
{
namespace bundle
{

class TcpServerConnManager : public QObject
{
    Q_OBJECT

public:
    explicit TcpServerConnManager(TcpServer& bundle,QObject *parent = nullptr);
    ~TcpServerConnManager() override;

public:
    bool open(QHostAddress& ipAddr,quint16& port);
    void close();

private slots:
    void onNewConnection();

private:
    void addChannelManager(TcpServerChannelManager *channel);
    void closeChannelManagers();

private:
    TcpServer&                        m_bundle;
    QTcpServer                       *m_tcpServer;
    QList<QspTcpServerChannelManager> m_channelManagers;
};

}//namespace bundle
}//namespace server
}//namespace tcp
}//namespace core
}//namespace plugframe
}//namespace elekdom
#endif // TCPSERVERCONNMANAGER_H
