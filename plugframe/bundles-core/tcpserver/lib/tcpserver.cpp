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
#include <QSettings>
#include "tcpserver.h"
#include "tcpserverfactory.h"
#include "tcpserver_logchannel.h"
#include "network/backend/serverconnectionsnotifier.h"
#include "service-int/backendcontrolserviceinterface.h"
#include "logger/pflog.h"

TcpServer::TcpServer():
    plugframe::BundleImplementation{s_TcpServer_LogChannel}
{
}

TcpServer::~TcpServer()
{
    stopListen();
}

void TcpServer::tcpServerConnManager(TcpServerConnManager *serverComManager)
{
    m_serverComManager.reset(serverComManager);
}

void TcpServer::startListen(plugframe::ServerConnectionsNotifier *serverSide)
{
    QHostAddress serverIpAddr;
    quint16 ServerPort;

    readListenAddr(serverIpAddr,ServerPort);

    pfInfo1(logChannel()) << QObject::tr("The server listen on socket %1:%2").arg(serverIpAddr.toString()).arg(ServerPort);

    QObject::connect(m_serverComManager.get(),SIGNAL(newClientConnection(plugframe::ChannelManager*)),serverSide,SLOT(onNewClientConnection(plugframe::ChannelManager*)));
    if(!m_serverComManager->open(serverIpAddr,ServerPort))
    {
        pfErr(logChannel()) << QObject::tr("The server didn't open socket %1:%2").arg(serverIpAddr.toString()).arg(ServerPort);
    }
}

void TcpServer::stopListen()
{
    m_serverComManager->close();
}

plugframe::BundleFactory *TcpServer::createFactory()
{
    return new TcpServerFactory;
}

plugframe::ServiceInterface *TcpServer::qtServiceInterface(const QString &sName)
{
    plugframe::ServiceInterface *ret{nullptr};

    if (plugframe::BackendControlServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<plugframe::BackendControlServiceInterface*>(getQplugin());
    }

    return ret;
}

void TcpServer::readListenAddr(QHostAddress &ipAddr, quint16 &port)
{
    QString confPath{getConfPath()};
    QSettings listenAddrSettings{confPath,QSettings::IniFormat};

    ipAddr.setAddress(listenAddrSettings.value("ipv4").toString());
    port = listenAddrSettings.value("port").toUInt();
}

