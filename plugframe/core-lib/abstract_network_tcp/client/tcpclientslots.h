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

#ifndef TCPCLIENTSLOTS_H
#define TCPCLIENTSLOTS_H

#include <QObject>
#include "pfcore-lib_forward.h"
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT TcpClientSlots : public QObject
{
    Q_OBJECT
public:
    explicit TcpClientSlots(TcpClient &clientSide,QObject *parent = nullptr);
    ~TcpClientSlots() override;

public:
    void connectChannelManager(TcpClientChannelManager *clientChannelManager);

private slots:
    void onConnectedToServer();
    void onDisconnectedFromServer();
    void onMessageFromServer(plugframe::TcpChannelMessage *input);

private:
    TcpClient &m_clientSide;
};
}//namespace plugframe
#endif // TCPCLIENTSLOTS_H
