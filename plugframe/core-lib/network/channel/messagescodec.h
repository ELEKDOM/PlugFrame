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
#ifndef MESSAGESCODEC_H
#define MESSAGESCODEC_H

#include <QObject>
#include "pfcore-lib_export.h"
#include "logger/loggable.h"

namespace plugframe
{
class PFCORELIB_EXPORT MessagesCodec : public QObject, public Loggable
{
    Q_OBJECT

public:
    explicit MessagesCodec(quint16 codecId,const QString& logChannel,QObject *parent = nullptr);

public:
    quint16 codecId() {return m_codecId;}
    bool extractMessage(QDataStream& input);

signals:
    void unregister(quint16 codecId);
    void messageToSend(QByteArray outputStream);

protected:
    virtual bool extractArgsFromStream(quint16 msgId,QDataStream& input) = 0;

private:
    quint16 m_codecId;
};
} //namespace plugframe
#endif // MESSAGESCODEC_H
