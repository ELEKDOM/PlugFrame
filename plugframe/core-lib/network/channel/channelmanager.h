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
#ifndef CHANNELMANAGER_H
#define CHANNELMANAGER_H

#include <QObject>
#include <QHash>
#include "pfcore-lib_forward.h"
#include "pfcore-lib_export.h"
#include "logger/loggable.h"

namespace plugframe
{
class PFCORELIB_EXPORT ChannelManager : public QObject, public Loggable
{
    Q_OBJECT

public:
    explicit ChannelManager(const QString& logChannel,QObject *parent = nullptr);
    ~ChannelManager() override;

public:
    void registerMessagesCodec(MessagesCodec* codec);

signals:
    void sigConnected();
    void sigDisconnected();

protected slots:
    virtual void onMessageToSend(QByteArray outputStream) =0;

protected:
    MessagesCodec* selectCodec(quint16 codecId);

private slots:
    void onUnregisterCodec(quint16 codecId);

private:
    QHash<quint16,MessagesCodec*> m_registeredCodecs;
};
} //namespace plugframe
#endif // CHANNELMANAGER_H
