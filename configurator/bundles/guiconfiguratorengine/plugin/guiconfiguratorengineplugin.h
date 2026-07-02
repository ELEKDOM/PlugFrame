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
#include "guiengine/lib/guiregistercontrollerservice.h"

class GuiConfiguratorEnginePlugin : public plugframe::Plugin,
                                    public plugframe::GuiRegisterControllerServiceInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "plugframe.guiconfiguratorengine.plugin" FILE "../guiconfiguratorenginebundle.json")
    Q_INTERFACES(plugframe::BundleInterface
                 plugframe::GuiRegisterControllerServiceInterface)

public:
    GuiConfiguratorEnginePlugin();
    virtual ~GuiConfiguratorEnginePlugin();

protected: // Plugin
    plugframe::Bundle4PluginInterface *createImplementation() override;
    PF_bindServicesImplementations_DECL

protected: // GuiRegisterControllerInterface
    void registerController(const plugframe::QspGuiPageController& controller) override;

private:
    QspGuiRegisterControllerService m_registerControllerServiceImpl;

};
#endif // GUICONFIGURATORENGINEPLUGIN_H
