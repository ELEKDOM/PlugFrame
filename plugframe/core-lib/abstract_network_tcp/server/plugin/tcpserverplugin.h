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
#include "abstract_network_tcp/server/service/tcpserverservice.h"
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT TcpServerPlugin : public Plugin,
                                         public BackendControlServiceInterface
{
public:
    TcpServerPlugin();
    ~TcpServerPlugin() override;

protected: // Plugin
    void bindServicesImplementations() override;

protected: // BackendControlServiceInterface
    void startListen() override;
    void stopListen() override;

private:
    QspTcpServerService m_serverServiceImpl;
};
}//namespace plugframe
#endif // TCPSERVERPLUGIN_H
