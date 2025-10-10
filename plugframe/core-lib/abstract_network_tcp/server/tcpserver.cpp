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
#include "tcpserverconnmanager.h"
#include "tcpserverfactory.h"
#include "tcpserverchannelmanager.h"
#include "abstract_network_tcp/common/tcpchannel.h"
#include "service-int/backendcontrolserviceinterface.h"
#include "logger/pflog.h"

using namespace elekdom::plugframe::core::tcp::server::bundle;

TcpServer::TcpServer(QString logBundleName):
    core::bundle::BundleImplementation{logBundleName},
    m_serverComManager{nullptr}
{

}

TcpServer::~TcpServer()
{
    stopListen();
    delete m_serverComManager;
}

void TcpServer::tcpServerConnManager(TcpServerConnManager *serverComManager)
{
    m_serverComManager = serverComManager;
}

void TcpServer::startListen()
{
    QHostAddress serverIpAddr;
    quint16 ServerPort;

    readListenAddr(serverIpAddr,ServerPort);
    if(!m_serverComManager->open(serverIpAddr,ServerPort))
    {
        pfErr(logChannel()) << QObject::tr("The server didn't open socket %1:%2").arg(serverIpAddr.toString()).arg(ServerPort);
    }
}

void TcpServer::stopListen()
{
    m_serverComManager->close();
}

TcpServerChannelManager *TcpServer::newChannelManager(QTcpSocket *newConn)
{
    factory::TcpServerFactory& tcpServerFactory{dynamic_cast<factory::TcpServerFactory&>(getFactory())};
    TcpChannelDeserializer *deserializer{tcpServerFactory.createDeserializer()};
    TcpChannel *channel{tcpServerFactory.createChannel(newConn,deserializer)};
    TcpServerChannelManager *channelManager(tcpServerFactory.createChannelManager(*this,channel));

    QObject::connect(channel->socket(),SIGNAL(disconnected()),channelManager,SLOT(onDisconnectedFromClient()));
    return channelManager;
}

elekdom::plugframe::core::plugin::ServiceInterface *TcpServer::qtServiceInterface(const QString &sName)
{
    plugframe::core::plugin::ServiceInterface *ret{nullptr};

    if (frontenditf::service::BackendControlServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<frontenditf::service::BackendControlServiceInterface*>(getQplugin());
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

