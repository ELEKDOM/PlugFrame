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

#include "pfcore-lib_export.h"
#include "pfcore-lib_forward.h"
#include "plugin/plugin.h"
#include "service-int/backendcontrolserviceinterface.h"

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
namespace plugin
{

class PFCORELIB_EXPORT TcpServerPlugin : public core::plugin::Plugin,
                                         public frontenditf::service::BackendControlServiceInterface
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
    server::service::QspTcpServerService m_serverServiceImpl;
};

}//namespace plugin
}//namespace server
}//namespace tcp
}//namespace core
}//namespace plugframe
}//namespace elekdom

#endif // TCPSERVERPLUGIN_H
