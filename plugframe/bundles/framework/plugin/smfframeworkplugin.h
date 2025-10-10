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
#include "framework_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace framework
{
namespace plugin
{

class SmfFrameworkPlugin : public core::plugin::Plugin,
                           public FrameworkInterface,
                           public service::SystemServiceInterface,
                           public service::SystemServiceRegistryInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "elekdom.plugframe.framework.plugin" FILE "../frameworkbundle.json")
    Q_INTERFACES(elekdom::plugframe::core::plugin::BundleInterface
                 elekdom::plugframe::framework::plugin::FrameworkInterface
                 elekdom::plugframe::framework::service::SystemServiceInterface
                 elekdom::plugframe::framework::service::SystemServiceRegistryInterface)
public:
    SmfFrameworkPlugin();
    ~SmfFrameworkPlugin() override;

protected: // BundleInterface
    void init() override;
    core::bundle::Bundle4PluginInterface *createImplementation() override;
    void bindServicesImplementations() override;

protected: // SmfFrameworkInitInterface
    void initFwk(QSharedPointer<core::launcher::BundlesStore> bundlesStore,
                 QSharedPointer<core::launcher::LaunchingProperties> launchingProperties) override;
    plugframe::core::plugin::BundleInterface *getBundleInterface() override;

protected: // SmfSystemServiceInterface
    QString applicationName() override;
    bool registerListener(core::bundle::BundleListener* observer) override;
    bool unregisterListener(core::bundle::BundleListener* observer) override;
    core::plugin::BundleList bundleList() override;
    int runningLevel() override;
    void quit() override;

protected: // SmfSystemServiceRegistryInterface
    bool registerService(const QString& serviceInterfaceName,  core::plugin::ServiceInterface *service) override;
    core::plugin::ServiceInterface *getService(const QString& serviceInterfaceName) override;
    core::plugin::ServiceInterfaceList getServices(const QString& serviceInterfaceName) override;

private:
    QSharedPointer<core::launcher::BundlesStore>        m_bundlesStore;
    QSharedPointer<core::launcher::LaunchingProperties> m_launchingProperties;
    QSharedPointer<framework::service::SystemService>   m_systemServiceImpl;
    QSharedPointer<framework::service::ServiceRegistry> m_serviceRegistryImpl;
};

} //namespace plugin
} //namespace framework
} //namespace plugframe
} //namespace elekdom

#endif // SMFFRAMEWORKPLUGIN_H
