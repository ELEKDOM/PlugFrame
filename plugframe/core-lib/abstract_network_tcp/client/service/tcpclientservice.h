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


#ifndef TCPCLIENTSERVICE_H
#define TCPCLIENTSERVICE_H

#include "service/serviceimplementation.h"
#include "service-int/frontendclientside.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace tcp
{
namespace client
{
namespace service
{

class TcpClientService : public plugframe::core::service::ServiceImplementation
{
public:
    TcpClientService(plugframe::core::bundle::BundleImplementation *implementation);
    ~TcpClientService() override;

public:
    void connectToHost(frontend::FrontendClientSide *clientSide,
                       QString serverIpv4,
                       quint16 serverPort);
    void closeConnection();
    void sendMessageToServer(TcpChannelMessage& msg);

protected:
    QString serviceName() override;
};

}//namespace service
}//namespace client
}//namespace tcp
}//namespace core
}//namespace plugframe
}//namespace elekdom
#endif // TCPCLIENTSERVICE_H
