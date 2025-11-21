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
#include "pfcore-lib_forward.h"
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT TcpChannelManager : public QObject
{
    Q_OBJECT

public:
    explicit TcpChannelManager(TcpChannel *channel,QObject *parent = nullptr);
    ~TcpChannelManager() override;

public:
    void sendMessage(TcpChannelMessage& output);
    void close();

public slots:
    void onNewMessage(plugframe::TcpChannelMessage *input);

protected:
    virtual void processMessage(TcpChannelMessage *input)=0;
    TcpChannel *channel() {return m_channel;}

private:
    TcpChannel *m_channel;
};
} //namespace plugframe
#endif // TCPCHANNELMANAGER_H
