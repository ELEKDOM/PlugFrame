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

#include "tcpclientfactory.h"
#include "tcpclientchannelmanager.h"
#include "tcpclientbuilder.h"
#include "tcpclientservice.h"
#include "tcpmessagescodecregisterservice.h"
#include "bundle/bundle.h"
#include "service-int/frontendcontrolserviceinterface.h"
#include "service-int/frontendmessagescodecregisterserviceinterface.h"

TcpClientFactory::TcpClientFactory() {}

TcpClientFactory::~TcpClientFactory()
{

}

TcpClientChannelManager *TcpClientFactory::createChannelManager(QTcpSocket *socket,
                                                                const QString &logChannel)
{
    return new TcpClientChannelManager{socket,logChannel};
}

QTcpSocket *TcpClientFactory::createSocket()
{
    return new QTcpSocket;
}

plugframe::BundleBuilder *TcpClientFactory::createBuilder(plugframe::Bundle &myBundle)
{
    return new TcpClientBuilder{myBundle};
}

TcpClientService *TcpClientFactory::createFrontendControlService(plugframe::BundleImplementation *implementation)
{
    return new TcpClientService{implementation};
}

TcpMessagesCodecRegisterService *TcpClientFactory::createMessagesCodecRegisterService(plugframe::BundleImplementation *implementation)
{
    return new TcpMessagesCodecRegisterService{implementation};
}

plugframe::ServiceImplementationInterface *TcpClientFactory::createServiceImplementation(plugframe::BundleImplementation *implementation,
                                                                                         const QString &sName,
                                                                                         const QString &serviceVersion)
{
    plugframe::ServiceImplementationInterface *ret{nullptr};

    if (plugframe::FrontendControlServiceInterface::serviceName() == sName)
    {
        if (plugframe::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createFrontendControlService(implementation);
        }
    }
    else if(plugframe::FrontendMessagesCodecRegisterServiceInterface::serviceName() == sName)
    {
        if (plugframe::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createMessagesCodecRegisterService(implementation);
        }
    }

    return ret;
}
