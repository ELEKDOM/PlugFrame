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


#ifndef FACTORY_BUNDLE_H
#define FACTORY_BUNDLE_H

#include "pfcore-lib_export.h"
#include "pfcore-lib_forward.h"
#include "plugin/bundleinterface.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace bundle
{

class PFCORELIB_EXPORT BundleFactory
{
public:
    BundleFactory();
    virtual ~BundleFactory() {}

public:
    virtual BundleBuilder *createBuilder(Bundle& myBundle);
    virtual BundleHeaders *createHeaders(const QString& logChannel);
    virtual BundleEmitter *createBundleEmitter(Bundle& myBundle);
    virtual BundleListener *createBundleListener(Bundle& myBundle);
    virtual service::ServiceImplementationInterface *createServiceImplementation(BundleImplementation *implementation,
                                                                                 const QString& serviceName,
                                                                                 const QString& serviceVersion)=0;
    virtual event::BundleStartingEvent *createBundleStartingEvent(core::plugin::BundleInterface *bundleItf);
    virtual event::BundleStartedEvent *createBundleStartedEvent(core::plugin::BundleInterface *bundleItf);
    virtual event::BundleStoppingEvent *createBundleStoppingEvent(core::plugin::BundleInterface *bundleItf);
    virtual event::BundleStoppedEvent *createBundleStoppedEvent(core::plugin::BundleInterface *bundleItf);
 };

} //namespace bundle
} //namespace core
} //namespace plugframe
} //namespace elekdom

#define PF_createServiceImplementation_DECL elekdom::plugframe::core::service::ServiceImplementationInterface *createServiceImplementation(elekdom::plugframe::core::bundle::BundleImplementation*,const QString&,const QString&)override;
#define PF_createServiceImplementation_DEF(TYPE) elekdom::plugframe::core::service::ServiceImplementationInterface *TYPE::createServiceImplementation(elekdom::plugframe::core::bundle::BundleImplementation*,const QString&,const QString&){return nullptr;}

#endif // FACTORY_BUNDLE_H
