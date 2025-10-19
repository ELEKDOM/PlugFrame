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
#include "launcher/bundlesstore.h"
#include "launcher/launchingproperties.h"
#include "service-int/systemserviceregistryinterface.h"

class Framework : public plugframe::LongStartBundleImplementation
{
public:
    Framework(plugframe::QspBundlesStore bundlesStore,
              plugframe::QspLaunchingProperties launchingProperties);
    ~Framework() override;

public: // for SmfSystemService
    plugframe::BundleList bundleList();
    int runningLevel();
    void quit();

public: // for the emitter
    int startLevelToReach();
    void setNumberOfBundlesToStart(int nb);

public: // for the listener
    void postBundlesStartingEvt(plugframe::BundleList& bundlesToStart,
                                int frameworkStartLevel,
                                int curStartLevel);
    void postBundlesStoppingEvt(plugframe::BundleList& bundlesToStop,
                                int curStopLevel);
    void postFrameworkStartedEvt();
    int getNumberOfBundlesToStart();
    plugframe::SystemServiceRegistryInterface *getRegistryService();
    void fwkStarted();
    void fwkStopped();

protected:
    plugframe::BundleFactory *createFactory() override;
    void init() override;
    void _start(plugframe::QspBundleContext bundleContext) override;
    void stop() override;
    void _stop() override;

protected:
    plugframe::ServiceInterface *qtServiceInterface(const QString& sName) override;
    bool registerService(const QString &serviceInterfaceName, plugframe::ServiceInterface* service) override;

private:
    plugframe::QspBundlesStore        m_bundlesStore;
    plugframe::QspLaunchingProperties m_launchingProperties;
    plugframe::BundleList             m_ListBundles; // loaded bundles interfaces
    int                               m_numberOfBundlesToStart;
};
#endif // FRAMEWORK_H
