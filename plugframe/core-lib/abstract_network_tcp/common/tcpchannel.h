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


#ifndef TCPCHANNEL_H
#define TCPCHANNEL_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include "pfcore-lib_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace tcp
{

class TcpChannel : public QObject
{
    Q_OBJECT

public:
    explicit TcpChannel(QTcpSocket *socket,TcpChannelDeserializer *deserializer,QObject *parent = nullptr);
    ~TcpChannel() override;

public:
    void sendMessage(TcpChannelMessage& msg);
    void close();
    QTcpSocket *socket() {return m_socket;}

public slots:
    void onReadyRead();

signals:
    void newMessage(TcpChannelMessage *input);

private:
    bool readMessage();

protected:
    QTcpSocket             *m_socket;
private:

    TcpChannelDeserializer *m_deserializer;
    QDataStream             m_inputStream;
};

} //namespace tcp
} //namespace core
} //namespace plugframe
} //namespace elekdom

#endif // TCPCHANNEL_H
