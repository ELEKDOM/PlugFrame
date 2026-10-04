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
#ifndef TCPCHANNELMANAGER_H
#define TCPCHANNELMANAGER_H

#include <QObject>
#include <QSharedPointer>
#include <QTcpSocket>
#include "network/channel/channelmanager.h"
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT TcpChannelManager : public ChannelManager
{
    Q_OBJECT

public:
    explicit TcpChannelManager(QTcpSocket *socket,const QString& logChannel,QObject *parent = nullptr);
    ~TcpChannelManager() override;

public:
    void closeConnection();

protected:
    void onMessageToSend(QByteArray outputStream) override;

private slots:
    void onReadyRead();

private:
    bool readMessage();

private:
    QTcpSocket *m_socket;
    QDataStream m_inputStream;
};
using QspTcpChannelManager = QSharedPointer<TcpChannelManager>;
} //namespace plugframe
#endif // TCPCHANNELMANAGER_H
