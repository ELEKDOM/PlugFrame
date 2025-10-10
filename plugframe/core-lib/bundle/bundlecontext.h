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


#ifndef BUNDLE_CONTEXT_H
#define BUNDLE_CONTEXT_H

#include <QString>
#include <QList>
#include "pfcore-lib_export.h"
#include "service-int/systemserviceregistryinterface.h"


namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace bundle
{

class PFCORELIB_EXPORT BundleContext
{
private:
    framework::service::SystemServiceRegistryInterface *m_registryService;

public:
    BundleContext(framework::service::SystemServiceRegistryInterface *registryService);
    virtual ~BundleContext();

public:
    bool registerService(const QString& serviceInterfaceName,  plugin::ServiceInterface* service);

    template <typename T> T* getService(const QString& serviceInterfaceName)
    {
        plugin::ServiceInterface* servItf{m_registryService->getService(serviceInterfaceName)};
        T* ret;

        ret = dynamic_cast<T*>(servItf);
        return ret;
    }

    template <typename T> QList<T*> getServices(const QString& serviceInterfaceName)
    {
        plugin::ServiceInterfaceList servItfList{m_registryService->getServices(serviceInterfaceName)};
        plugin::ServiceInterfaceList_Iterator i;
        QList<T*> ret;

        for (i = servItfList.begin(); i != servItfList.end(); ++i)
        {
            ret.append(dynamic_cast<T*>(*i));
        }

        return ret;
    }
};

} //namespace bundle
} //namespace core
} //namespace plugframe
} //namespace elekdom

#endif // BUNDLE_CONTEXT_H
