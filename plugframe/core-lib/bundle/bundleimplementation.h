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

#ifndef BUNDLEIMPLEMENTATION_H
#define BUNDLEIMPLEMENTATION_H

#include <QMutex>
#include <QHash>
#include "bundle.h"
#include "service/serviceimplementationinterface.h"

namespace plugframe
{
class PFCORELIB_EXPORT BundleImplementation : public Bundle
{
public:
    BundleImplementation(QString logBundleName);
    ~BundleImplementation() override;

protected: // for Bundle4PluginInterface
    BundleImplementation *getImplementation() override;
    QspServiceImplementationInterface getServiceImplementation(const QString& serviceName) override;

protected:
    QspBundleContext& bundleContext() {return m_bundleContext;}
    void addExportedService(QspServiceImplementationInterface newService) override;
    QspServiceImplementationInterface getService(const QString& serviceName);
    void _start(QspBundleContext bundleContext) override;
    void _stop() override;

protected:
    virtual ServiceInterface *qtServiceInterface(const QString& sName)=0;
    virtual bool registerService(const QString &serviceInterfaceName,ServiceInterface* service);

private:
    void registerExportedServices();

private:
    QspBundleContext                   m_bundleContext;
    ServiceImplementationInterfaceHash m_exportedServices;

protected:
    QMutex m_mutex;
};
} //namespace plugframe

#define PF_qtServiceInterface_DECL plugframe::ServiceInterface *qtServiceInterface(const QString&) override;
#define PF_qtServiceInterface_DEF(TYPE) plugframe::ServiceInterface *TYPE::qtServiceInterface(const QString &){return nullptr;}

#endif // BUNDLEIMPLEMENTATION_H
