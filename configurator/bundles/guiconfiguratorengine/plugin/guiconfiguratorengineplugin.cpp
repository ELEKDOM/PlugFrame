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
#include "guiconfiguratorengineplugin.h"
#include "guiconfiguratorengine.h"

GuiConfiguratorEnginePlugin::GuiConfiguratorEnginePlugin()
{

}

GuiConfiguratorEnginePlugin::~GuiConfiguratorEnginePlugin()
{

}

plugframe::Bundle4PluginInterface *GuiConfiguratorEnginePlugin::createImplementation()
{
    return new GuiConfiguratorEngine;
}

void GuiConfiguratorEnginePlugin::registerController(const plugframe::QspGuiPageController &controller)
{
    m_registerControllerServiceImpl->registerController(controller);
}

QStringList GuiConfiguratorEnginePlugin::getLauncherConfFileList(const QString &projectName, const QString &applicationName)
{
    return m_configuratorEngineServiceImpl->getLauncherConfFileList(projectName,applicationName);
}

QStringList GuiConfiguratorEnginePlugin::getBundleConfFileList(const QString &projectName, const QString &applicationName, const QString &bundleName)
{
    return m_configuratorEngineServiceImpl->getBundleConfFileList(projectName,applicationName,bundleName);
}

void GuiConfiguratorEnginePlugin::bindServicesImplementations()
{
    plugframe::QspServiceImplementationInterface serviceImplementationItf;

    serviceImplementationItf = implementation()->getServiceImplementation(plugframe::GuiRegisterControllerServiceInterface::serviceName());
    m_registerControllerServiceImpl = serviceImplementationItf.dynamicCast<GuiRegisterControllerService>();

    serviceImplementationItf = implementation()->getServiceImplementation(configurator::GuiConfiguratorEngineServiceInterface::serviceName());
    m_configuratorEngineServiceImpl = serviceImplementationItf.dynamicCast<GuiConfiguratorEngineService>();
}

