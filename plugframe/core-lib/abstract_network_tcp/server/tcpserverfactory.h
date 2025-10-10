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


#ifndef TCPSERVERFACTORY_H
#define TCPSERVERFACTORY_H
#include <QTcpSocket>
#include "factory/bundlefactory.h"
#include "pfcore-lib_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace tcp
{
namespace server
{
namespace factory
{

class TcpServerFactory : public core::bundle::BundleFactory
{
public:
    TcpServerFactory();
    ~TcpServerFactory() override;

public:
    virtual TcpChannelDeserializer *createDeserializer()=0;
    virtual bundle::TcpServerChannelManager *createChannelManager(bundle::TcpServer& bundle,TcpChannel *channel,QObject *parent = nullptr)=0;
    virtual bundle::TcpServerConnManager *createTcpServerConnManager(bundle::TcpServer& myBundle);
    virtual TcpChannel *createChannel(QTcpSocket *socket,TcpChannelDeserializer *deserializer,QObject *parent = nullptr);

protected:
    core::bundle::BundleBuilder *createBuilder(core::bundle::Bundle& myBundle) override;
    virtual service::TcpServerService *createBackendControlService(core::bundle::BundleImplementation *implementation);
    plugframe::core::service::ServiceImplementationInterface *createServiceImplementation(core::bundle::BundleImplementation *implementation,
                                                                                          const QString& sName,
                                                                                          const QString& serviceVersion) override;
};

}//namespace factory
}//namespace server
}//namespace tcp
}//namespace core
}//namespace plugframe
}//namespace elekdom
#endif // TCPSERVERFACTORY_H
