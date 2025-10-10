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


#ifndef BUNDLE_INTERFACE
#define BUNDLE_INTERFACE

#include <QtPlugin>
#include <QString>
#include <QJsonObject>
#include "pfcore-lib_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace plugin
{
/**
 * @brief The BundleInterface class
 * Bundle Plugin loaded by Qt
 */
class BundleInterface
{
public:
    enum class BundleState {Unknown, Loaded, Initialized, Starting, Started, Stopping, Stopped};

public:
    virtual ~BundleInterface() {}

public:
    QString stateStr() {
        BundleState state{getState()};

        switch(state)
        {
        case BundleState::Unknown:
            return QStringLiteral("Unknown");
        case BundleState::Loaded:
            return QStringLiteral("Loaded");
        case BundleState::Initialized:
            return QStringLiteral("Initialized");
        case BundleState::Starting:
            return QStringLiteral("Starting");
        case BundleState::Started:
            return QStringLiteral("Started");
        case BundleState::Stopping:
            return QStringLiteral("Stopping");
        case BundleState::Stopped:
            return QStringLiteral("Stopped");
        }
    }
public:
    virtual void setFileName(const QString& fileName) = 0;
    virtual void setAbsolutePath(const QString& absolutePath) = 0;
    virtual void setMetaData(const QJsonObject& metaData) = 0;
    virtual void setQplugin(QObject *qplugin) = 0;
    virtual void init() = 0;
    virtual void start(bundle::QspBundleContext bundleContext) = 0;
    virtual void stop() = 0;
    virtual QString getName() = 0;
    virtual core::bundle::Bundle *getImpl() = 0;
    virtual int getStartLevel() = 0;
    virtual BundleState getState() = 0;
    virtual QString state2String(BundleState state) = 0;
};

} //namespace plugin
} //namespace core
} //namespace plugframe
} //namespace elekdom

#define PfBundle_iid "elekdom.smf.core.plugin"
Q_DECLARE_INTERFACE(elekdom::plugframe::core::plugin::BundleInterface, PfBundle_iid)

#endif // BUNDLE_INTERFACE

