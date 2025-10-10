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


#include <QByteArray>
#include "tcpchannel.h"
#include "tcpchannelmessage.h"
#include "tcpchanneldeserializer.h"

using namespace elekdom::plugframe::core::tcp;

TcpChannel::TcpChannel(QTcpSocket *socket,
                       TcpChannelDeserializer *deserializer,
                       QObject *parent):
    QObject{parent},
    m_socket{socket},
    m_deserializer{deserializer}
{
    m_inputStream.setDevice(m_socket);
    m_inputStream.setVersion(QDataStream::Qt_5_10);

    connect(m_socket,SIGNAL(readyRead()),SLOT(onReadyRead()));
}

TcpChannel::~TcpChannel()
{
    delete m_deserializer;
}

void TcpChannel::sendMessage(TcpChannelMessage &msg)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_5_10);
    m_deserializer->serialize(msg,out);
    m_socket->write(block);
    m_socket->flush();  // send data immediatly !
}

void TcpChannel::close()
{
    disconnect(m_socket,nullptr,nullptr,nullptr);
    m_socket->close();
}

void TcpChannel::onReadyRead()
{
    bool rmOk, noMoreMsg;

    do  // message flow it's possible on tcp socket !!!
    {
        rmOk = readMessage();
        noMoreMsg = m_inputStream.atEnd();
    } while (rmOk && !noMoreMsg);
}

bool TcpChannel::readMessage()
{
    bool ret;
    TcpChannelMessage *input{nullptr};
    m_inputStream.startTransaction();

    input = m_deserializer->deserialize(m_inputStream);
    ret = m_inputStream.commitTransaction();
    if (ret)
    {
        emit newMessage(input);
    }
    else
    {
        //error!
        delete input;
    }

    return ret;
}
