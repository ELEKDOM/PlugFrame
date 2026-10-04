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

#ifndef TCPCLIENTPLUGIN_H
#define TCPCLIENTPLUGIN_H

#include "plugin/plugin.h"
#include "service-int/frontendcontrolserviceinterface.h"
#include "service-int/frontendmessagescodecregisterserviceinterface.h"
#include "tcpclientservice.h"
#include "tcpmessagescodecregisterservice.h"

class TcpClientPlugin : public plugframe::Plugin,
                        public plugframe::FrontendControlServiceInterface,
                        public plugframe::FrontendMessagesCodecRegisterServiceInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "plugframe.tcpclient.plugin" FILE "../tcpclientbundle.json")
    Q_INTERFACES(plugframe::BundleInterface
                 plugframe::FrontendControlServiceInterface
                 plugframe::FrontendMessagesCodecRegisterServiceInterface)

public:
    TcpClientPlugin();
    ~TcpClientPlugin() override;

protected: // Plugin
    void bindServicesImplementations() override;
    plugframe::Bundle4PluginInterface *createImplementation() override;

protected: // FrontendControlServiceInterface
    void connectToHost(plugframe::ClientConnectionStateNotifier *clientSide) override;
    void closeConnection() override;

protected: // FrontendMessagesCodecRegisterServiceInterface
    void registerMessagesCodec(plugframe::MessagesCodec *codec) override;

private:
    QspTcpClientService                m_clientServiceImpl;
    QspTcpMessagesCodecRegisterService m_messagesCodecRegisterImpl;
};
#endif // TCPCLIENTPLUGIN_H
