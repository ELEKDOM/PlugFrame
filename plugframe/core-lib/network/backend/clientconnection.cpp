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
#include "clientconnection.h"

plugframe::ClientConnection::ClientConnection(Publisher *bundle, MessagesCodec *codec,QObject *parent):
    QObject{parent},
    m_bundle{bundle},
    m_messagesCodec{codec}
{
}

plugframe::ClientConnection::~ClientConnection()
{

}

plugframe::OutputStreamBuilder *plugframe::ClientConnection::createOutputStream(quint16 msgId)
{
    return m_messagesCodec->createOutputStream(msgId);
}

void plugframe::ClientConnection::sendMessage(QspOutputStream& outputStream)
{
    m_messagesCodec->sendMessage(outputStream);
}
