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


#ifndef BACKENDCONTROLSERVICEINTERFACE_H
#define BACKENDCONTROLSERVICEINTERFACE_H

#include "service-int/serviceinterface.h"

namespace elekdom
{
namespace plugframe
{
namespace frontenditf
{
namespace service
{

class BackendControlServiceInterface : public core::plugin::ServiceInterface
{
public:
    static QString serviceName() {return QStringLiteral("BackendControlServiceInterface");}

public:
    virtual ~BackendControlServiceInterface() {}

public: // service interface definition = 0
    virtual void startListen() = 0;
    virtual void stopListen() = 0;
};

}//namespace service
}//namespace frontenditf
}//namespace plugframe
}//namespace elekdom

#define PfBackendControlService_iid "elekdom.plugframe.frontenditf.service.BackendControlServiceInterface"
Q_DECLARE_INTERFACE(elekdom::plugframe::frontenditf::service::BackendControlServiceInterface,PfBackendControlService_iid)

#endif // BACKENDCONTROLSERVICEINTERFACE_H
