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


#ifndef BUNDLE4BUILDERINTERFACE_H
#define BUNDLE4BUILDERINTERFACE_H

#include <QString>
#include "pfcore-lib_export.h"
#include "pfcore-lib_forward.h"
#include "service/serviceimplementationinterface.h"

namespace plugframe
{
class PFCORELIB_EXPORT Bundle4BuilderInterface
{
public:
    virtual ~Bundle4BuilderInterface() {}

public:
    virtual Bundle& getBundle() = 0;
    virtual BundleImplementation *getImplementation() = 0;
    virtual const QString& getLogBundleName() = 0;
    virtual BundleFactory& getFactory() = 0;
    virtual void setHeaders(BundleHeaders* bundleHeaders) = 0;
    virtual void loadManifestHeaders() = 0;
    virtual void setEmitter(BundleEmitter *emitter) = 0;
    virtual void setListener(BundleListener *listener) = 0;
    virtual void defaultListening() = 0;
    virtual void addExportedService(QspServiceImplementationInterface newService) = 0;
};
} //namespace plugframe

#endif // BUNDLE4BUILDERINTERFACE_H
