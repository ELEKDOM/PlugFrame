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
#include "channelmanager.h"
#include "messagescodec.h"
#include "logger/pflog.h"

plugframe::ChannelManager::ChannelManager(const QString &logChannel, QObject *parent):
    QObject{parent},
    Loggable{logChannel}
{
}

plugframe::ChannelManager::~ChannelManager()
{
}

void plugframe::ChannelManager::registerMessagesCodec(MessagesCodec *codec)
{
    if (codec)
    {
        m_registeredCodecs.insert(codec->codecId(),codec);

        // connect codec
        connect(codec,SIGNAL(messageToSend(plugframe::TcpOutputStream)),SLOT(onMessageToSend(plugframe::TcpOutputStream)));
        connect(codec,SIGNAL(unregister(quint16)),SLOT(onUnregisterCodec(quint16)));

        pfInfo4(logChannel()) << tr("Register Message codec : ") << codec->codecId();
    }
}

void plugframe::ChannelManager::onUnregisterCodec(quint16 codecId)
{
    pfInfo4(logChannel()) << tr("Unregister Message codec : ") << codecId;

    m_registeredCodecs.remove(codecId);
}


plugframe::MessagesCodec *plugframe::ChannelManager::selectCodec(quint16 codecId)
{
    plugframe::MessagesCodec *ret;

    ret = m_registeredCodecs.value(codecId);
    return ret;
}
