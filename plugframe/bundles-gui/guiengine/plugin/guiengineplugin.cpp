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

#include "guiengineplugin.h"
#include "guiengine.h"

GuiEnginePlugin::GuiEnginePlugin()
{

}

GuiEnginePlugin::~GuiEnginePlugin()
{

}

plugframe::Bundle4PluginInterface *GuiEnginePlugin::createImplementation()
{
    return new GuiEngine;
}

void GuiEnginePlugin::registerController(const plugframe::QspGuiPageController &controller)
{
    m_registerControllerServiceImpl->registerController(controller);
}

void GuiEnginePlugin::bindServicesImplementations()
{
    plugframe::QspServiceImplementationInterface serviceImplementationItf;

    serviceImplementationItf = implementation()->getServiceImplementation(plugframe::GuiRegisterControllerServiceInterface::serviceName());
    m_registerControllerServiceImpl = serviceImplementationItf.dynamicCast<GuiRegisterControllerService>();
}

