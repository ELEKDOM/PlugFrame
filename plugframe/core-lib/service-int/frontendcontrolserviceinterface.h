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


#ifndef FRONTENDCONTROLSERVICEINTERFACE_H
#define FRONTENDCONTROLSERVICEINTERFACE_H

#include "service-int/serviceinterface.h"
#include "service-int/frontendclientside.h"

namespace elekdom
{
namespace plugframe
{
namespace frontend
{
namespace service
{

class FrontendControlServiceInterface : public core::plugin::ServiceInterface
{
public:
    static QString serviceName() {return QStringLiteral("FrontendControlServiceInterface");}

public:
    virtual ~FrontendControlServiceInterface() {}

public: // service interface definition = 0
    virtual void connectToHost(FrontendClientSide *clientSide,QString serverIpv4,quint16 serverPort) = 0;
    virtual void closeConnection() = 0;
    virtual void sendMessageToServer(core::tcp::TcpChannelMessage& msg) = 0;
};
}//namespace service
}//namespace frontend
}//namespace plugframe
}//namespace elekdom

#define PfFrontendControlService_iid "elekdom.plugframe.frontend.service.FrontendControlServiceInterface"
Q_DECLARE_INTERFACE(elekdom::plugframe::frontend::service::FrontendControlServiceInterface,PfFrontendControlService_iid)

#endif // FRONTENDCONTROLSERVICEINTERFACE_H
