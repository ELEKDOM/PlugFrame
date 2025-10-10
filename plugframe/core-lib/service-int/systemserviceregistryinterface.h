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


#ifndef SYSTEMSERVICEREGISTRYINTERFACE_H
#define SYSTEMSERVICEREGISTRYINTERFACE_H

#include "serviceinterface.h"

namespace elekdom
{
namespace plugframe
{
namespace framework
{
namespace service
{

class SystemServiceRegistryInterface : public core::plugin::ServiceInterface
{
public:
    static QString serviceName() {return QStringLiteral("SystemServiceRegistryInterface");}

public:
    ~SystemServiceRegistryInterface() override {}

public:
    virtual bool registerService(const QString& serviceInterfaceName,  core::plugin::ServiceInterface *service) = 0;
    virtual core::plugin::ServiceInterface *getService(const QString& serviceInterfaceName) = 0;
    virtual core::plugin::ServiceInterfaceList getServices(const QString& serviceInterfaceName) = 0;
};

}//namespace service
}//namespace core
}//namespace plugframe
}//namespace elekdom

#define PfSystemServiceRegistry_iid "elekdom.plugframe.framework.service.SystemServiceRegistryInterface"
Q_DECLARE_INTERFACE(elekdom::plugframe::framework::service::SystemServiceRegistryInterface, PfSystemServiceRegistry_iid)

#endif // SYSTEMSERVICEREGISTRYINTERFACE_H
