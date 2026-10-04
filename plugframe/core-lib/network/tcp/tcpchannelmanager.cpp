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
#include "tcpchannelmanager.h"
#include "network/channel/messagescodec.h"
#include "logger/pflog.h"

plugframe::TcpChannelManager::TcpChannelManager(QTcpSocket *socket, const QString &logChannel, QObject *parent):
    ChannelManager{logChannel,parent},
    m_socket{socket}
{
    m_inputStream.setDevice(m_socket);
    m_inputStream.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    connect(m_socket,SIGNAL(readyRead()),SLOT(onReadyRead()));
}

plugframe::TcpChannelManager::~TcpChannelManager()
{
    delete m_socket;
}

void plugframe::TcpChannelManager::closeConnection()
{
    disconnect(m_socket,nullptr,nullptr,nullptr);
    m_socket->close();
}

void plugframe::TcpChannelManager::onReadyRead()
{
    bool rmOk, noMoreMsg;

    do  // message flow is possible on tcp socket !!!
    {
        rmOk = readMessage();
        noMoreMsg = m_inputStream.atEnd();
    } while (rmOk && !noMoreMsg);
}

void plugframe::TcpChannelManager::onMessageToSend(QByteArray outputStream)
{
    m_socket->write(outputStream);
    m_socket->flush();  // send data immediatly !
}

bool plugframe::TcpChannelManager::readMessage()
{
    bool ret;
    quint16 codecId;
    plugframe::MessagesCodec *selectedCodec;

    m_inputStream.startTransaction();
    m_inputStream >> codecId;
    selectedCodec = selectCodec(codecId);
    if (selectedCodec)
    {
        selectedCodec->extractMessage(m_inputStream);
    }
    else
    {
        // Log
        pfErr(logChannel()) << tr("No message codec registered for codecId : ") << codecId;
    }

    ret = m_inputStream.commitTransaction();

    return ret;
}
