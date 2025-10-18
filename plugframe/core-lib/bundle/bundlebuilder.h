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


#ifndef BUNDLE_BUILDER_H
#define BUNDLE_BUILDER_H

#include "pfcore-lib_export.h"
#include "pfcore-lib_forward.h"
#include "service/serviceimplementationinterface.h"

namespace plugframe
{
class PFCORELIB_EXPORT BundleBuilder
{
private:
    Bundle4BuilderInterface& m_bundleItf;

public:
    BundleBuilder(Bundle4BuilderInterface& myBundle);
    virtual ~BundleBuilder();

public:
    virtual void build();

protected:
    Bundle& getBundle();
    BundleImplementation *getImplementation();
    const QString& getLogBundleName();
    BundleFactory& getFactory();
    void setHeaders(BundleHeaders* bundleHeaders);
    void loadManifestHeaders();
    void setEmitter(BundleEmitter *emitter);
    void setListener(BundleListener *listener);
    void defaultListening();
    void addExportedService(QspServiceImplementationInterface newService);
    virtual void specificBuild();

private:
    void buildExportedServices(const QList<QString>& providedServices);
};
} //namespace plugframe
#endif // BUNDLE_BUILDER_H
