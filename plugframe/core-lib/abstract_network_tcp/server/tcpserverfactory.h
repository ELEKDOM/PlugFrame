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
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT TcpServerFactory : public BundleFactory
{
public:
    TcpServerFactory();
    ~TcpServerFactory() override;

public:
    virtual TcpChannelDeserializer *createDeserializer()=0;
    virtual TcpServerChannelManager *createChannelManager(TcpServer& bundle,TcpChannel *channel,QObject *parent = nullptr)=0;
    virtual TcpServerConnManager *createTcpServerConnManager(TcpServer& myBundle);
    virtual TcpChannel *createChannel(QTcpSocket *socket,TcpChannelDeserializer *deserializer,QObject *parent = nullptr);

protected:
    BundleBuilder *createBuilder(Bundle& myBundle) override;
    virtual TcpServerService *createBackendControlService(BundleImplementation *implementation);
    ServiceImplementationInterface *createServiceImplementation(BundleImplementation *implementation,
                                                                const QString& sName,
                                                                const QString& serviceVersion) override;
};
}//namespace plugframe
#endif // TCPSERVERFACTORY_H
