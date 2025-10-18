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

#ifndef BUNDLE4PLUGININTERFACE_H
#define BUNDLE4PLUGININTERFACE_H

#include <QSharedPointer>
#include "plugin/bundleinterface.h"
#include "service/serviceimplementationinterface.h"
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT Bundle4PluginInterface
{
public:
    virtual ~Bundle4PluginInterface() {}

public:
    virtual void setQplugin(QObject *qplugin) = 0;
    virtual void setFileName(const QString& fileName) = 0;
    virtual void setAbsolutePath(const QString& absolutePath) = 0;
    virtual void setMetaData(const QJsonObject& metaData) = 0;
    virtual QspServiceImplementationInterface getServiceImplementation(const QString& serviceName) = 0;
    virtual void init() = 0;
    virtual void start(QspBundleContext bundleContext) = 0;
    virtual void stop() = 0;
    virtual QString getName() = 0;
    virtual Bundle *getImpl() = 0;
    virtual int getStartLevel() = 0;
    virtual BundleInterface::BundleState getState() = 0;
};
using QspBundle4PluginInterface = QSharedPointer<Bundle4PluginInterface>;
} //namespace plugframe

#endif // BUNDLE4PLUGININTERFACE_H
