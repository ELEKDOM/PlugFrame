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


#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "bundle/longstartbundleimplementation.h"
#include "service-int/systemserviceregistryinterface.h"
#include "pfcore-lib_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace framework
{
namespace bundle
{

class Framework : public core::bundle::LongStartBundleImplementation
{
public:
    Framework(QSharedPointer<core::launcher::BundlesStore> bundlesStore,
                 QSharedPointer<core::launcher::LaunchingProperties> launchingProperties);
    ~Framework() override;

public: // for SmfSystemService
    core::plugin::BundleList bundleList();
    int runningLevel();
    void quit();

public: // for the emitter
    int startLevelToReach();
    void setNumberOfBundlesToStart(int nb);

public: // for the listener
    void postBundlesStartingEvt(core::plugin::BundleList& bundlesToStart,
                                int frameworkStartLevel,
                                int curStartLevel);
    void postBundlesStoppingEvt(core::plugin::BundleList& bundlesToStop,
                                int curStopLevel);
    void postFrameworkStartedEvt();
    int getNumberOfBundlesToStart();
    service::SystemServiceRegistryInterface *getRegistryService();
    void fwkStarted();
    void fwkStopped();

protected:
    core::bundle::BundleFactory *createFactory() override;
    void init() override;
    void _start(core::bundle::QspBundleContext bundleContext) override;
    void stop() override;
    void _stop() override;

protected:
    core::plugin::ServiceInterface *qtServiceInterface(const QString& sName) override;
    bool registerService(const QString &serviceInterfaceName, core::plugin::ServiceInterface* service) override;

private:
    core::launcher::QspBundlesStore        m_bundlesStore;
    core::launcher::QspLaunchingProperties m_launchingProperties;
    core::plugin::BundleList               m_ListBundles; // loaded bundles interfaces
    int                                    m_numberOfBundlesToStart;
};

} //namespace bundle
} //namespace framework
} //namespace plugframe
} //namespace elekdom

#endif // FRAMEWORK_H
