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
#include "guienginefactory.h"
#include "service-int/guiregistercontrollerserviceinterface.h"
#include "guiregistercontrollerservice.h"

GuiEngineFactory::GuiEngineFactory()
{

}

GuiEngineFactory::~GuiEngineFactory()
{

}

GuiRegisterControllerService *GuiEngineFactory::createGuiRegisterControllerService(plugframe::BundleImplementation *implementation)
{
    return new GuiRegisterControllerService{implementation};
}

plugframe::ServiceImplementationInterface *GuiEngineFactory::createServiceImplementation(plugframe::BundleImplementation *implementation,
                                                                                         const QString &sName,
                                                                                         const QString &serviceVersion)
{
    plugframe::ServiceImplementationInterface *ret{nullptr};

    if (plugframe::GuiRegisterControllerServiceInterface::serviceName() == sName)
    {
        if (plugframe::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createGuiRegisterControllerService(implementation);
        }
    }

    return ret;
}
