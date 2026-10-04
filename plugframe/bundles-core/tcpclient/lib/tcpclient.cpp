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
#include "tcpclient.h"
#include "tcpclientfactory.h"
#include "tcpclient_logchannel.h"
#include "service-int/frontendcontrolserviceinterface.h"
#include "service-int/frontendmessagescodecregisterserviceinterface.h"
#include "logger/pflog.h"

TcpClient::TcpClient():
    plugframe::BundleImplementation{s_TcpClient_LogChannel}
{
}

TcpClient::~TcpClient()
{
}

void TcpClient::tcpClientChannelManager(TcpClientChannelManager *clientChannelManager)
{
    m_clientChannelManager.reset(clientChannelManager);
}

void TcpClient::registerMessagesCodec(plugframe::MessagesCodec *codec)
{
    if (!m_clientChannelManager.isNull())
    {
        m_clientChannelManager->registerMessagesCodec(codec);
    }
}

void TcpClient::connectToHost(plugframe::ClientConnectionStateNotifier *clientSide)
{
    QHostAddress serverIp;
    quint16 serverPort;

    readServerAddr(serverIp,serverPort);
    pfInfo1(logChannel()) << QObject::tr("Connect to server ") << serverIp << ":" << serverPort;
    if (m_clientChannelManager)
    {
        QObject::connect(m_clientChannelManager.get(),SIGNAL(sigConnected()),clientSide,SLOT(onConnectedToServer()));
        QObject::connect(m_clientChannelManager.get(),SIGNAL(sigDisconnected()),clientSide,SLOT(onDisconnectedFromServer()));
        m_clientChannelManager->connectToServer(serverIp,serverPort);
    }
}

void TcpClient::closeConnection()
{
    m_clientChannelManager->closeConnection();
}

plugframe::BundleFactory *TcpClient::createFactory()
{
    return new TcpClientFactory;
}

plugframe::ServiceInterface *TcpClient::qtServiceInterface(const QString &sName)
{
    plugframe::ServiceInterface *ret{nullptr};

    if (plugframe::FrontendControlServiceInterface::serviceName()== sName)
    {
        ret = qobject_cast<plugframe::FrontendControlServiceInterface*>(getQplugin());
    }
    else if (plugframe::FrontendMessagesCodecRegisterServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<plugframe::FrontendMessagesCodecRegisterServiceInterface*>(getQplugin());
    }

    return ret;
}

void TcpClient::readServerAddr(QHostAddress &ipAddr, quint16 &port)
{
    QString confPath{getConfPath()};
    QSettings serverAddrSettings{confPath,QSettings::IniFormat};

    ipAddr.setAddress(serverAddrSettings.value("ipv4").toString());
    port = serverAddrSettings.value("port").toUInt();
}
