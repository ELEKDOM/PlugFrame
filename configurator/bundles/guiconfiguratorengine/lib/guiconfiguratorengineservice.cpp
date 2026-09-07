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
#include "guiconfiguratorengineservice.h"
#include "guiconfiguratorengine.h"
#include "service-int/guiconfiguratorengineserviceinterface.h"

GuiConfiguratorEngineService::GuiConfiguratorEngineService(plugframe::BundleImplementation *implementation):
    plugframe::ServiceImplementation{implementation}
{

}

GuiConfiguratorEngineService::~GuiConfiguratorEngineService()
{

}

QStringList GuiConfiguratorEngineService::getLauncherConfFileList(const QString &projectName, const QString &applicationName)
{
    GuiConfiguratorEngine *engine{dynamic_cast<GuiConfiguratorEngine*>(implementation())};

    return engine->getLauncherConfFileList(projectName,applicationName);
}

QStringList GuiConfiguratorEngineService::getBundleConfFileList(const QString &projectName, const QString &applicationName, const QString &bundleName)
{
    GuiConfiguratorEngine *engine{dynamic_cast<GuiConfiguratorEngine*>(implementation())};

    return engine->getBundleConfFileList(projectName,applicationName,bundleName);
}

QString GuiConfiguratorEngineService::serviceName()
{
    return configurator::GuiConfiguratorEngineServiceInterface::serviceName();
}
