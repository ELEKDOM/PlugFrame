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


#ifndef SERVICEREGISTRY_H
#define SERVICEREGISTRY_H

#include <QMultiHash>
#include "frameworkserviceimplementation.h"

namespace elekdom
{
namespace plugframe
{
namespace framework
{
namespace service
{

class ServiceRegistry : public FrameworkServiceImplementation
{
private:
    QMultiHash<QString, core::plugin::ServiceInterface*> m_registry;

public:
    ServiceRegistry(core::bundle::BundleImplementation *implementation);
    virtual ~ServiceRegistry();

public:
    bool registerService(const QString& serviceInterfaceName,  core::plugin::ServiceInterface *service);
    core::plugin::ServiceInterface *getService(const QString& serviceInterfaceName);
    QList<core::plugin::ServiceInterface*> getServices(const QString& serviceInterfaceName);

protected:
    virtual QString serviceName();
};

} //namespace service
} //namespace framework
} //namespace plugframe
} //namespace elekdom

#endif // SERVICEREGISTRY_H
