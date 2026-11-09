// Copyright (C) 2026 ELEKDOM Christophe Mars c.mars@elekdom.fr
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
#include "messagescodec.h"
#include "outputstreambuilder.h"

plugframe::MessagesCodec::MessagesCodec(quint16 codecId, const QString &logChannel, QObject *parent):
    QObject{parent},
    Loggable{logChannel},
    m_codecId{codecId},
    m_clientConnection{nullptr}
{

}

bool plugframe::MessagesCodec::extractMessage(QDataStream &input)
{
    bool ret;
    quint16 msgId;

    input >> msgId;
    ret = extractArgsFromStream(msgId,input);
    return ret;
}

plugframe::OutputStreamBuilder *plugframe::MessagesCodec::createOutputStream(quint16 msgId)
{
    return new OutputStreamBuilder{m_codecId,msgId};
}

void plugframe::MessagesCodec::sendMessage(QspOutputStream& outputStream)
{
    emit messageToSend(outputStream->bytes());
}

