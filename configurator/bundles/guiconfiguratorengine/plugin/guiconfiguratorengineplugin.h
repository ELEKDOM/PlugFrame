// Copyright (C) 2026 ELEKDOM Christophe Mars c.mars@elekdom.fr
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

#ifndef GUICONFIGURATORENGINEPLUGIN_H
#define GUICONFIGURATORENGINEPLUGIN_H

#include "plugin/plugin.h"
#include "service-int/guiregistercontrollerserviceinterface.h"
#include "service-int/guiconfiguratorengineserviceinterface.h"
#include "guiengine/lib/guiregistercontrollerservice.h"
#include "guiconfiguratorengineservice.h"

class GuiConfiguratorEnginePlugin : public plugframe::Plugin,
                                    public plugframe::GuiRegisterControllerServiceInterface,
                                    public configurator::GuiConfiguratorEngineServiceInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "configurator.guiconfiguratorengine.plugin" FILE "../guiconfiguratorenginebundle.json")
    Q_INTERFACES(plugframe::BundleInterface
                 plugframe::GuiRegisterControllerServiceInterface
                 configurator::GuiConfiguratorEngineServiceInterface)

public:
    GuiConfiguratorEnginePlugin();
    ~GuiConfiguratorEnginePlugin() override;

protected: // Plugin
    plugframe::Bundle4PluginInterface *createImplementation() override;
    PF_bindServicesImplementations_DECL

protected: // GuiRegisterControllerInterface
    void registerController(const plugframe::QspGuiPageController& controller) override;

protected: // GuiConfiguratorEngineServiceInterface
    QStringList getLauncherConfFileList(const QString& projectName,const QString& applicationName) override;
    QStringList getBundleConfFileList(const QString& projectName,const QString& applicationName,const QString& bundleName) override;

private:
    QspGuiRegisterControllerService m_registerControllerServiceImpl;
    QspGuiConfiguratorEngineService m_configuratorEngineServiceImpl;
};
#endif // GUICONFIGURATORENGINEPLUGIN_H
