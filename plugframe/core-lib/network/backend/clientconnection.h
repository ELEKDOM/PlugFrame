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
#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QObject>
#include <QSharedPointer>
#include "pfcore-lib_export.h"
#include "pfcore-lib_forward.h"
#include "network/channel/messagescodec.h"
#include "network/channel/outputstream.h"

namespace plugframe
{
class PFCORELIB_EXPORT ClientConnection :  public QObject
{
    Q_OBJECT

public:
    explicit ClientConnection(Publisher *bundle,MessagesCodec *codec,QObject *parent = nullptr);
    virtual ~ClientConnection();

public:
    MessagesCodec *messagesCodec() {return m_messagesCodec.get();}

protected:
    Publisher *bundle() {return m_bundle;}
    OutputStreamBuilder *createOutputStream(quint16 msgId);
    void sendMessage(QspOutputStream& outputStream);

private:
    Publisher       *m_bundle;
    QspMessagesCodec m_messagesCodec;
};
using QspClientConnection = QSharedPointer<ClientConnection>;
} //namespace plugframe
#endif // CLIENTCONNECTION_H
