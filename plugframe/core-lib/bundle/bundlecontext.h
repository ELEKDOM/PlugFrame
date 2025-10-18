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
#include <QSharedPointer>
#include "pfcore-lib_export.h"
#include "service-int/systemserviceregistryinterface.h"

namespace plugframe
{
class PFCORELIB_EXPORT BundleContext
{
private:
    SystemServiceRegistryInterface *m_registryService;

public:
    BundleContext(SystemServiceRegistryInterface *registryService);
    virtual ~BundleContext();

public:
    bool registerService(const QString& serviceInterfaceName,  ServiceInterface* service);

    template <typename T> T* getService(const QString& serviceInterfaceName)
    {
        ServiceInterface* servItf{m_registryService->getService(serviceInterfaceName)};
        T* ret;

        ret = dynamic_cast<T*>(servItf);
        return ret;
    }

    template <typename T> QList<T*> getServices(const QString& serviceInterfaceName)
    {
        ServiceInterfaceList servItfList{m_registryService->getServices(serviceInterfaceName)};
        ServiceInterfaceList_Iterator i;
        QList<T*> ret;

        for (i = servItfList.begin(); i != servItfList.end(); ++i)
        {
            ret.append(dynamic_cast<T*>(*i));
        }

        return ret;
    }
};
using QspBundleContext = QSharedPointer<BundleContext>;
} //namespace plugframe

#endif // BUNDLE_CONTEXT_H
