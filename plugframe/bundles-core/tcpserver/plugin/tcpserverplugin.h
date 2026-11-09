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
#ifndef TCPSERVERPLUGIN_H
#define TCPSERVERPLUGIN_H

#include "plugin/plugin.h"
#include "service-int/backendcontrolserviceinterface.h"
#include "service-int/backendservernotifierregisterserviceinterface.h"
#include "tcpserverservice.h"
#include "tcpservernotifierregisterservice.h"

class TcpServerPlugin : public plugframe::Plugin,
                        public plugframe::BackendControlServiceInterface,
                        public plugframe::BackendServerNotifierRegisterServiceInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "plugframe.tcpserver.plugin" FILE "../tcpserverbundle.json")
    Q_INTERFACES(plugframe::BundleInterface
                 plugframe::BackendControlServiceInterface
                 plugframe::BackendServerNotifierRegisterServiceInterface)

public:
    TcpServerPlugin();
    ~TcpServerPlugin() override;

protected: // Plugin
    void bindServicesImplementations() override;
    plugframe::Bundle4PluginInterface *createImplementation() override;

protected: // BackendControlServiceInterface
    void startListen() override;
    void stopListen() override;
protected: // BackendServerNotifierRegisterServiceInterface
    void registerConnectionNotifier(plugframe::ServerConnectionsNotifier *serverSide) override;

private:
    QspTcpServerService                 m_serverServiceImpl;
    QspTcpServerNotifierRegisterService m_serverNotifierRegisterService;
};
#endif // TCPSERVERPLUGIN_H
