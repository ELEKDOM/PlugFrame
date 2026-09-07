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
#include "guiconfiguratorenginefactory.h"
#include "service-int/guiconfiguratorengineserviceinterface.h"
#include "guiconfiguratorengineservice.h"

GuiConfiguratorEngineFactory::GuiConfiguratorEngineFactory() {}

GuiConfiguratorEngineFactory::~GuiConfiguratorEngineFactory()
{

}

plugframe::ServiceImplementationInterface *GuiConfiguratorEngineFactory::createServiceImplementation(plugframe::BundleImplementation *implementation,
                                                                                                     const QString &sName,
                                                                                                     const QString &serviceVersion)
{
    plugframe::ServiceImplementationInterface *ret;

    ret = GuiEngineFactory::createServiceImplementation(implementation,sName,serviceVersion);

    if (!ret && configurator::GuiConfiguratorEngineServiceInterface::serviceName() == sName)
    {
        if (plugframe::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createGuiConfiguratorEngineService(implementation);
        }
    }

    return ret;
}

GuiConfiguratorEngineService *GuiConfiguratorEngineFactory::createGuiConfiguratorEngineService(plugframe::BundleImplementation *implementation)
{
    return new GuiConfiguratorEngineService{implementation};
}
