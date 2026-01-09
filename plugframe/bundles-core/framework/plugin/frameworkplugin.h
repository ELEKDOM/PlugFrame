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

#ifndef SMFFRAMEWORKPLUGIN_H
#define SMFFRAMEWORKPLUGIN_H

#include "plugin/plugin.h"
#include "plugin/frameworkinterface.h"
#include "service-int/systemserviceinterface.h"
#include "service-int/systemserviceregistryinterface.h"
#include "launcher/bundlesstore.h"
#include "launcher/launchingproperties.h"
#include "systemservice.h"
#include "serviceregistry.h"

class SmfFrameworkPlugin : public plugframe::Plugin,
                           public plugframe::FrameworkInterface,
                           public plugframe::SystemServiceInterface,
                           public plugframe::SystemServiceRegistryInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "plugframe.framework.plugin" FILE "../frameworkbundle.json")
    Q_INTERFACES(plugframe::BundleInterface
                 plugframe::FrameworkInterface
                 plugframe::SystemServiceInterface
                 plugframe::SystemServiceRegistryInterface)
public:
    SmfFrameworkPlugin();
    ~SmfFrameworkPlugin() override;

protected: // BundleInterface
    void init() override;
    plugframe::Bundle4PluginInterface *createImplementation() override;
    void bindServicesImplementations() override;

protected: // SmfFrameworkInitInterface
    void initFwk(plugframe::QspBundlesStore bundlesStore,
                 plugframe::QspLaunchingProperties launchingProperties) override;
                 plugframe::BundleInterface *getBundleInterface() override;

protected: // SmfSystemServiceInterface
    QString applicationName() override;
    bool registerListener(plugframe::BundleListener* observer) override;
    bool unregisterListener(plugframe::BundleListener* observer) override;
    plugframe::BundleList bundleList() override;
    int runningLevel() override;
    void quit() override;

protected: // SmfSystemServiceRegistryInterface
    bool registerService(const QString& serviceInterfaceName,  plugframe::ServiceInterface *service) override;
    plugframe::ServiceInterface *getService(const QString& serviceInterfaceName) override;
    plugframe::ServiceInterfaceList getServices(const QString& serviceInterfaceName) override;

private:
    plugframe::QspBundlesStore        m_bundlesStore;
    plugframe::QspLaunchingProperties m_launchingProperties;
    QSpSystemService                  m_systemServiceImpl;
    QspServiceRegistry                m_serviceRegistryImpl;
};
#endif // SMFFRAMEWORKPLUGIN_H
